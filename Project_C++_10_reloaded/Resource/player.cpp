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
#include "manager.h"
#include "game_manager.h"
#include "physics.h"
#include "fakescreen.h"

#include "block.h"
#include "block_destructible.h"
#include "explosion.h"
#include "goal.h"
#include "start.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer() : CObject_X(static_cast<int>(LAYER::FRONT_MIDDLE))
{
	m_pStateManager = nullptr;				// ��ԃ}�l�[�W���[�̏�����
	m_velocity = { 0.0f, 0.0f, 0.0f };		// �����x�̏�����
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW�ʒu�̏�����
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW�����̏�����
	m_fAngleFlying = 0.0f;					// ��s�����̏�����
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayer::~CPlayer()
{

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

		// ��Ԃ̕ύX���m�F���� (������������܂ޏ����͍X�V�̌�Ƀt���O���Q�Ƃ��čs��)
		m_pStateManager->CheckStateChange();
	}

	// �ڕW���W�𔽉f
	SetPos(m_posTarget);

	// ���W���f�o�b�O�\��
	CManager::GetRenderer()->SetDebugString("�y�v���C���[���W�z");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	CManager::GetRenderer()->SetDebugString(oss.str().c_str());

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
// ���W�ύX�𔽉f
//============================================================================
bool CPlayer::ApplyPos()
{
	// �Փˌ��o�p
	bool bDetected = false;

	// �����x�����W��ϓ�
	m_posTarget += m_velocity;

	// �����蔻��
	bDetected = Collision();

	// ���W��ݒ�
	SetPos(m_posTarget);

	// �Փˌ��o��Ԃ�
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

//============================================================================
// �_�E���L���X�g
//============================================================================
CPlayer* CPlayer::DownCast(CObject* pObject)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);

	if (pPlayer == nullptr)
	{ // �_�E���L���X�g���s
		assert(false);
	}

	return pPlayer;
}

//============================================================================
// �����蔻��
//============================================================================
bool CPlayer::Collision()
{
	// �Փˌ��o
	bool bDetected = 0;

	// �I�u�W�F�N�g���擾
	CObject** pObject = CObject::FindAllObject(CObject::TYPE::BLOCK);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �u���b�N�N���X�փ_�E���L���X�g
		CBlock* pBlock = CBlock::DownCast(pObject[nCntObj]);

		// �u���b�N�ƏՓ˂���ꍇ
		if (CPhysics::GetInstance()->OnlyCube(pBlock->GetPos(), pBlock->GetSize(), m_posTarget, GetSize()))
		{
			// �����o������
			CPhysics::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), GetSize(), pBlock->GetPos(), pBlock->GetSize());

			// �Փ˔�����o��
			bDetected = 1;
		}
	}

	// �I�u�W�F�N�g���擾
	pObject = CObject::FindAllObject(CObject::TYPE::DESTRUCTIBLE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ��u���b�N�փ_�E���L���X�g
		CBlockDestructible* pDestructible = CBlockDestructible::DownCast(pObject[nCntObj]);

		// ��u���b�N�ƏՓ˂���ꍇ
		if (CPhysics::GetInstance()->OnlyCube(pDestructible->GetPos(), pDestructible->GetSize(), m_posTarget, GetSize()))
		{
			// �����o������
			CPhysics::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), GetSize(), pDestructible->GetPos(), pDestructible->GetSize());

			// ����
			pDestructible->Release();

			// �Փ˔�����o��
			bDetected = 1;
		}
	}

	// �S�[���I�u�W�F�N�g���擾
	CGoal* pGoal = CGoal::DownCast(CObject::FindObject(CObject::TYPE::GOAL));

	// �S�[���ƏՓ˂���ꍇ
	if (CPhysics::GetInstance()->SphereAndCube(pGoal->GetPos(), pGoal->GetSize().x, m_posTarget, GetSize()))
	{			
		// �S�[����ԂɈڍs���鍇�}��ݒ�
		m_pStateManager->SetPendingState(CPlayerState::STATE::GOAL);

		// ���x���I���t�F�[�Y�ֈڍs
		CFakeScreen::GetInstance()->SetWave(CGameManager::PHASE::FINISH);
	}

	return bDetected;
}