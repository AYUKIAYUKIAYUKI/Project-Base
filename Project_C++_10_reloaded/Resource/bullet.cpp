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

// �e�N�X�`���擾�p
#include "texture_manager.h"

// �I�u�W�F�N�g�p
#include "player.h"
#include "player_state.h"
#include "block.h"
#include "block_destructible.h"
#include "block_spikes.h"

// �f�o�b�O�\���p
#include "renderer.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CBullet::CBullet() :
	CObject_billboard{ static_cast<int>(LAYER::BACK_MIDDLE) },	// �v���C�I���e�B�w��
	m_posTarget{ 0.0f, 0.0f, 0.0f },							// �ڕW���W
	m_velocity{ 0.0f, 0.0f, 0.0f },								// �����x
	m_nDuration{ 0 }											// ����
{

}

//============================================================================
// �����ݒ�R���X�g���N�^
//============================================================================
CBullet::CBullet(int nDuration) :
	CObject_billboard{ static_cast<int>(LAYER::BACK_MIDDLE) },	// �v���C�I���e�B�w��
	m_posTarget{ 0.0f, 0.0f, 0.0f },							// �ڕW���W
	m_velocity{ 0.0f, 0.0f, 0.0f },								// �����x
	m_nDuration{ nDuration }									// ����
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CBullet::~CBullet()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CBullet::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_billboard::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CBullet::Uninit()
{
	// ���N���X�̏I������
	CObject_billboard::Uninit();
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

	// ���N���X�̍X�V
	CObject_billboard::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CBullet::Draw()
{
	// ���N���X�̕`�揈��
	CObject_billboard::Draw();
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

	// �e�N�X�`����ݒ�
	pBullet->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::BULLET_00));

	// �v���C���[���擾
	CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(CObject::FindObject(TYPE::PLAYER));

	// �v���C���[�ւ̃x�N�g�����K�����A�����x�ɐݒ�
	D3DXVECTOR3 pV{ (pPlayer->GetPos() - pos) };
	D3DXVec3Normalize(&pBullet->m_velocity, &pV);

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

	m_posTarget += m_velocity * 3.0f;
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
			// ��u���b�N��j��
			pDestructible->SetRelease();

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

	// �v���C���[���擾
	CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(CObject::FindObject(CObject::TYPE::PLAYER));

	// �v���C���[�ƏՓ˂���ꍇ
	if (CUtility::GetInstance()->OnlyCube(pPlayer->GetPos(), pPlayer->GetSize(), m_posTarget, GetSize()))
	{
		// �v���C���[���~�X��Ԃֈڍs
		pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::MISS);

		// �Փ˔�����o��
		bDetected = 1;
	}

	return bDetected;
}