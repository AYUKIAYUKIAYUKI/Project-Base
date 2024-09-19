//============================================================================
// 
// �e [bullet.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "bullet.h"
#include "utility.h"
#include "sound.h"

// �I�u�W�F�N�g�p
#include "player.h"
#include "player_state.h"
#include "block.h"
#include "block_destructible.h"
#include "block_destructible_big.h"
#include "block_spikes.h"
#include "block_spikes_move.h"
#include "smoke.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CBullet::CBullet() :
	CObject_X{ static_cast<int>(LAYER::BACK) },	// �`��D��x���w��
	m_posTarget{ 0.0f, 0.0f, 0.0f },			// �ڕW���W
	m_velocity{ 0.0f, 0.0f, 0.0f },				// �����x
	m_nDuration{ 0 }							// ����
{

}

//============================================================================
// �����ݒ�R���X�g���N�^
//============================================================================
CBullet::CBullet(int nDuration) :
	CObject_X{ static_cast<int>(LAYER::BACK) },	// �`��D��x���w��
	m_posTarget{ 0.0f, 0.0f, 0.0f },			// �ڕW���W
	m_velocity{ 0.0f, 0.0f, 0.0f },				// �����x
	m_nDuration{ nDuration }					// ����
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CBullet::~CBullet()
{
	// ���𐶐�
	CSmoke* pSmoke{ CSmoke::Create(
		GetPos() + m_velocity * 15.0f,	// ���W
		m_velocity * -0.75f) };			// �����x

	// �����߂�
	pSmoke->SetScale(0.25f);

	// �`�悳���O�Ɉ�x�X�V
	pSmoke->Update();
}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CBullet::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CBullet::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CBullet::Update()
{
	// �����J�E���g�_�E��
	m_nDuration--;

	if (m_nDuration <= 0)
	{
		// �j���\��
		SetRelease();
	}

	// ��]
	D3DXVECTOR3 rotTaget = GetRot();
	//rotTaget.x += CUtility::GetInstance()->GetRandomValue<float>() * 0.01f;
	rotTaget.y += fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.0025f;
	rotTaget.z += fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.0025f;
	SetRot(rotTaget);

	// ���݂̍��W���擾���A�ύX�������Ă���
	m_posTarget = GetPos();

	// �ړ�
	Translate();

	// �����蔻��
	if (Collision())
	{
		// �j���\��
		SetRelease();
	}

	// ���W�𔽉f
	SetPos(m_posTarget);

	// ���Œ��O�ɏk��
	if (m_nDuration <= 10)
	{
		SetScale(CUtility::GetInstance()->AdjustToTarget(GetScale(), 0.0f, 0.1f));
	}

	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CBullet::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// ����
//============================================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X�𐶐�
	CBullet* pBullet = DBG_NEW CBullet{ 60 };

	if (pBullet == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pBullet->SetType(TYPE::BULLET);

	// ���N���X�̏����ݒ�
	pBullet->Init();

	// �ʒu�̐ݒ�
	pBullet->SetPos(pos);

	// �T�C�Y�̐ݒ�
	pBullet->SetSize(size);

	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::BULLET_CORE) };

	// ���f����ݒ�
	pBullet->BindModel(Model);

	// �v���C���[���擾
	CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(CObject::FindObject(TYPE::PLAYER));

	// �v���C���[�ւ̃x�N�g�����K�����A�����x�ɐݒ�
	D3DXVECTOR3 pV{ (pPlayer->GetPos() - pos) };
	D3DXVec3Normalize(&pBullet->m_velocity, &pV);

	// �`��O�ɍ��W�𔽉f
	pBullet->Update();

	return pBullet;
}

//============================================================================
// �ړ�
//============================================================================
void CBullet::Translate()
{
	//// ���W���擾
	//D3DXVECTOR3 posTarget = GetPos();

	//// �ڕW���W�ɉ����x�����Z
	//posTarget += m_velocity;

	//// �ڕW���W�𔽉f
	//SetPos(posTarget);

	m_posTarget += m_velocity * 2.0f;
}

//============================================================================
// �����蔻��
//============================================================================
bool CBullet::Collision()
{
	// �Փˌ��o
	bool bDetected = 0;

	// �u���b�N�^�O���擾
	CObject** pObject = CObject::FindAllObject(CObject::TYPE::BLOCK);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �u���b�N�^�O�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �u���b�N�N���X�փ_�E���L���X�g
		CBlock* pBlock = CUtility::GetInstance()->DownCast<CBlock, CObject>(pObject[nCntObj]);

		// �u���b�N�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pBlock->GetPos(), pBlock->GetSize(), m_posTarget, GetSize()))
		{
			// �Փ˔�����o��
			bDetected = 1;
		}
	}

	// ��^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::DESTRUCTIBLE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// ��^�O�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ��u���b�N�փ_�E���L���X�g
		CBlockDestructible* pDestructible = CUtility::GetInstance()->DownCast<CBlockDestructible, CObject>(pObject[nCntObj]);

		// ��u���b�N�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pDestructible->GetPos(), pDestructible->GetSize(), m_posTarget, GetSize()))
		{
			// �Փ˔�����o��
			bDetected = 1;
		}
	}

	// ��ł��^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::DEST_BIG);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// ��ł��^�O�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ��ł��u���b�N�փ_�E���L���X�g
		CBlockDestructibleBig* pDest_Big = CUtility::GetInstance()->DownCast<CBlockDestructibleBig, CObject>(pObject[nCntObj]);

		// ��ł��u���b�N�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pDest_Big->GetPos(), pDest_Big->GetSize(), m_posTarget, GetSize()))
		{
			// �Փ˔�����o��
			bDetected = 1;
		}
	}

	// �Ƃ��^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �Ƃ��^�O�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �Ƃ��u���b�N�փ_�E���L���X�g
		CBlockSpikes* pBlockSpikes = CUtility::GetInstance()->DownCast<CBlockSpikes, CObject>(pObject[nCntObj]);

		// �Ƃ��u���b�N�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pBlockSpikes->GetPos(), pBlockSpikes->GetSize(), m_posTarget, GetSize()))
		{
			// �Փ˔�����o��
			bDetected = 1;
		}
	}

	// �Ƃ��ړ��^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES_MOVE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �Ƃ��ړ��^�O�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �Ƃ��ړ��u���b�N�փ_�E���L���X�g
		CBlockSpikesMove* pSpikes_Move = CUtility::GetInstance()->DownCast<CBlockSpikesMove, CObject>(pObject[nCntObj]);

		// �Ƃ��ړ��u���b�N�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pSpikes_Move->GetPos(), pSpikes_Move->GetSize(), m_posTarget, GetSize()))
		{
			// �Փ˔�����o��
			bDetected = 1;
		}
	}

	// �v���C���[���擾
	CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(CObject::FindObject(CObject::TYPE::PLAYER));

	// �v���C���[�ƏՓ˂���ꍇ
	if (CUtility::GetInstance()->OnlyCube(pPlayer->GetPos(), pPlayer->GetSize(), m_posTarget, GetSize()))
	{
		// �ːi��ԁE�S�[����ԂŖ������
		if (typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerStateGoal) &&
			typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerStateRushing))
		{
			// �v���C���[���~�X��Ԃֈڍs
			pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::MISS);
		
			// ���S��
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}

		// �Փ˔�����o��
		bDetected = 1;
	}

	return bDetected;
}