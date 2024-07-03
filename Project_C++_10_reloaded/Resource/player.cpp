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
#include "physics.h"
#include "block.h"
#include "explosion.h"
#include "explosion3D.h"
#include "goal.h"
#include "particle.h"
#include "start.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer() : CObject_X(static_cast<int>(LAYER::FRONT_MIDDLE))
{
	m_pStateManager = nullptr;				// ��ԊǗ�
	m_velocity = { 0.0f, 0.0f, 0.0f };		// �����x
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW�ʒu
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW����
	m_fAngleFlying = 0.0f;					// ��s����
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

	// �傫����ݒ�
	SetSize({ 10.0f, 10.0f, 10.0f });

	// ��ԊǗ��N���X�̐���
	if (m_pStateManager == nullptr)
	{
		m_pStateManager = DBG_NEW CPlayerStateManager;

		// �v���C���[�̃C���X�^���X������ԊǗ��N���X�ɓn��
		m_pStateManager->SetPlayerInstance(this);

		// ������
		m_pStateManager->Init();

		// �v���C���[�̃C���X�^���X������ԃN���X�ɓn��
		m_pStateManager->GetState()->SetPlayerInstance(this);
	}

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CPlayer::Uninit()
{
	// ��ԊǗ��N���X�̔j��
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
	// ���݈ʒu���擾�A�ȍ~���̃R�s�[��ڕW�ʒu�Ƃ��ĕύX�������Ă���
	m_posTarget = CObject_X::GetPos();

	// ��Ԃ̍X�V����
	m_pStateManager->GetState()->Update();

	// �ʒu�𔽉f
	SetPos(m_posTarget);

	// �ʒu���f�o�b�O�\��
	CManager::GetRenderer()->SetDebugString("�y�v���C���[�ʒu�z");
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

	pPlayer->SetType(TYPE::PLAYER);	// �^�C�v��ݒ�

	pPlayer->Init();		// ���N���X�̏����ݒ�
	pPlayer->SetPos(pos);	// �ʒu�̐ݒ�

	return pPlayer;
}

//============================================================================
// �ʒu����
//============================================================================
bool CPlayer::AdjustPos()
{
	// �����ւ̏Փˌ��o
	bool bDetected = false;

	// �����x���ʒu��ϓ�
	m_posTarget += m_velocity;

	// �����蔻��
	bDetected = Collision();

	// �ʒu��ݒ�
	SetPos(m_posTarget);

	// ���o��Ԃ�
	return bDetected;
}

//============================================================================
// �����蔻��
//============================================================================
bool CPlayer::Collision()
{
	// �Փ˔���
	bool bDetected = 0;

	// ���T�C�Y
	D3DXVECTOR3 BlockSize = { 10.0f, 10.0f, 10.0f };

	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// �I�u�W�F�N�g�����擾
			CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{ // ��񂪂Ȃ���΃R���e�B�j���[
				continue;
			}

			if (pObject->GetType() == CObject::TYPE::BLOCK)
			{ // �u���b�N�^�C�v�Ȃ�

				// �I�u�W�F�N�g�N���X���u���b�N�N���X�փ_�E���L���X�g
				CBlock* pBlock = dynamic_cast<CBlock*>(pObject);

				if (pBlock == nullptr)
				{ // �_�E���L���X�g���s
					assert(false);
				}

				// �u���b�N�ƏՓ˂���ꍇ
				if (CPhysics::GetInstance()->OnlyCube(m_posTarget, GetSize(), pBlock->GetPos(), BlockSize))
				{
					// �����o������
					CPhysics::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), GetSize(), pBlock->GetPos(), BlockSize);

					// �Փ˔�����o��
					bDetected = 1;
				}
			}
			else if (pObject->GetType() == CObject::TYPE::GOAL)
			{ // �S�[���^�C�v�Ȃ�

				// �I�u�W�F�N�g�N���X���S�[���N���X�փ_�E���L���X�g
				CGoal* pGoal = dynamic_cast<CGoal*>(pObject);

				// �S�[���ƏՓ˂���ꍇ
				if (CPhysics::GetInstance()->SphereAndCube(pGoal->GetPos(), 10.0f, m_posTarget, GetSize()))
				{
					// �Ƃ肠�����Q�[�����I��������
					CManager::GetFade()->SetFade(CScene::MODE::RESULT);
				}
			}
		}
	}

	return bDetected;
}