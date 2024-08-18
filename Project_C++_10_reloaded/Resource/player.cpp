//============================================================================
// 
// �v���C���[ [player.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "player.h"
#include "player_state.h"
#include "utility.h"

// �t�F�[�Y���p
#include "game_manager.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �I�u�W�F�N�g���p 
#include "block.h"
#include "block_destructible.h"
#include "block_spikes.h"
#include "explosion.h"
#include "fakescreen.h"
#include "goal.h"
#include "start.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer() :
	CObject_X(static_cast<int>(LAYER::FRONT_MIDDLE)),	// �v���C�I���e�B�̐ݒ�
	m_pStateManager{ nullptr },							// ��ԃ}�l�[�W���[�̏�����
	m_velocity{ 0.0f, 0.0f, 0.0f },						// �����x�̏�����
	m_posTarget{ 0.0f, 0.0f, 0.0f },					// �ڕW�ʒu�̏�����
	m_rotTarget{ 0.0f, 0.0f, 0.0f },					// �ڕW�����̏�����
	m_fAngleFlying{ 0.0f }								// ��s�����̏�����
{
	
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayer::~CPlayer()
{
	m_pStateManager = nullptr;				// ��ԃ}�l�[�W���[�̏�����
	m_velocity = { 0.0f, 0.0f, 0.0f };		// �����x�̏�����
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW�ʒu�̏�����
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW�����̏�����
	m_fAngleFlying = 0.0f;					// ��s�����̏�����
}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CPlayer::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	if (m_pStateManager == nullptr)
	{
		// ��ԃ}�l�[�W���[�̐���
		m_pStateManager = DBG_NEW CPlayerStateManager;

		// �����ݒ�
		m_pStateManager->Init(this);
	}

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CPlayer::Uninit()
{
	// ��ԃ}�l�[�W���[�̔j��
	if (m_pStateManager != nullptr)
	{
		// �I������
		m_pStateManager->Uninit();
	
		// �����������
		delete m_pStateManager;

		// �|�C���^��������
		m_pStateManager = nullptr;
	}

	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CPlayer::Update()
{
	// ���ݍ��W���R�s�[���A�ȍ~���̃R�s�[��ڕW���W�Ƃ��ĕύX�������Ă���
	m_posTarget = CObject_X::GetPos();

	// ��ԃI�u�W�F�N�g����������Ă����
	if (m_pStateManager->GetState() != nullptr)
	{
		// ��Ԃ̍X�V
		m_pStateManager->GetState()->Update();

		// ��Ԃ̕ύX���m�F���� (������������܂ޏ����̂��߁A�X�V�̌�ɕʓr�s��)
		m_pStateManager->CheckStateChange();
	}

	// �ڕW���W�𔽉f
	SetPos(m_posTarget);

	// ���W���f�o�b�O�\��
	CRenderer::GetInstance()->SetDebugString("�y�v���C���[���W�z");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());

	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CPlayer::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// �����蔻��
//============================================================================
bool CPlayer::Collision()
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
			// �����o������
			CUtility::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), GetSize(), pBlock->GetPos(), pBlock->GetSize());

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
			// �����o������
			CUtility::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), GetSize(), pDestructible->GetPos(), pDestructible->GetSize());

			// ��s��Ԃ̏ꍇ�̂�
			if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying))
			{
				// ��u���b�N��j��
				pDestructible->SetRelease();
			}

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
			// �~�X��ԂɈڍs
			m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);

			// �Փ˔�����o��
			bDetected = 1;
		}
	}

	// �S�[���I�u�W�F�N�g���擾
	CGoal* pGoal = CGoal::DownCast(CObject::FindObject(CObject::TYPE::GOAL));

	// �S�[���ƏՓ˂���ꍇ
	if (CUtility::GetInstance()->SphereAndCube(pGoal->GetPos(), pGoal->GetSize().x, m_posTarget, GetSize()))
	{
		// �S�[����ԂɈڍs
		m_pStateManager->SetPendingState(CPlayerState::STATE::GOAL);

		// ���x���I���t�F�[�Y�ֈڍs
		CFakeScreen::GetInstance()->SetWave(CGameManager::PHASE::FINISH);
	}

	return bDetected;
}

//============================================================================
// �����x���擾
//============================================================================
D3DXVECTOR3 CPlayer::GetVelocity()
{
	return m_velocity;
}

//============================================================================
// �����x��ݒ�
//============================================================================
void CPlayer::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

//============================================================================
// ��s�������擾
//============================================================================
float CPlayer::GetAngleFlying()
{
	return m_fAngleFlying;
}

//============================================================================
// ��s������ݒ�
//============================================================================
void CPlayer::SetAngleFlying(float fAngleFlying)
{
	m_fAngleFlying = fAngleFlying;
}

//============================================================================
// �ڕW�ʒu���擾
//============================================================================
D3DXVECTOR3 CPlayer::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// �ڕW�ʒu��ݒ�
//============================================================================
void CPlayer::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// �ڕW�������擾
//============================================================================
D3DXVECTOR3 CPlayer::GetRotTarget()
{
	return m_rotTarget;
}

//============================================================================
// �ڕW������ݒ�
//============================================================================
void CPlayer::SetRotTarget(D3DXVECTOR3 rotTarget)
{
	m_rotTarget = rotTarget;
}

//============================================================================
// ��ԊǗ��擾
//============================================================================
CPlayerStateManager* CPlayer::GetStateManager()
{
	return m_pStateManager;
}

//============================================================================
// ����
//============================================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X�𐶐�
	CPlayer* pPlayer = DBG_NEW CPlayer;

	if (pPlayer == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pPlayer->SetType(TYPE::PLAYER);

	// ���N���X�̏����ݒ�
	pPlayer->Init();

	// �ʒu�̐ݒ�
	pPlayer->SetPos(pos);

	return pPlayer;
}