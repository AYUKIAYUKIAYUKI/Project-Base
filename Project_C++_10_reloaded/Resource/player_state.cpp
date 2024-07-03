//============================================================================
// 
// �v���C���[��ԊǗ� [player_state.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "player_state.h"

#include "manager.h"
#include "physics.h"
#include "explosion3D.h"
#include "start.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
const float CPlayerStateDefault::MAX_WALK_VELOCITY = 0.75f;	// ���s���̍ő�����x
const float CPlayerStateDefault::BRAKING_WALK_SPEED = 0.8f;	// ���s���̐�����
const int CPlayerStateBeginning::BEGIN_CNT_MAX = 20;		// �ϐg�K�v����
const float CPlayerStateBeginning::BEGIN_FLOATING = 1.25f;	// �ϐg���㏸��
const float CPlayerStateBeginning::BEGIN_SPINNING = 0.5f;	// �ϐg����]��
const float CPlayerStateFlying::MAX_FLY_VELOCITY = 2.0f;	// ��s���̍ő�����x
const float CPlayerStateFlying::FLY_SPEED = 0.25f;			// ��s���x
const int CPlayerStateStopping::STOP_CNT_MAX = 20;			// �ϐg��~�K�v����
const float CPlayerStateStopping::RECOIL_SPEED = 1.0f;		// �����ړ����x
const float CPlayerStateMistook::MAX_WARP_SPEED = 15.0f;	// �����ړ����x�̏��

//============================================================================
// 
// �v���C���[��ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerState::CPlayerState() : m_pPlayer(nullptr)
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerState::~CPlayerState()
{

}

//============================================================================
// �X�V
//============================================================================
void CPlayerState::Update()
{

}

//============================================================================
// �v���C���[���̐ݒ�
//============================================================================
void CPlayerState::SetPlayerInstance(CPlayer* player)
{
	m_pPlayer = player;
}



//============================================================================
// 
// �v���C���[�ʏ��ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateDefault::CPlayerStateDefault()
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateDefault::~CPlayerStateDefault()
{

}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateDefault::Enter()
{
	// �����ڂ�ύX
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_000));
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateDefault::Update()
{
	// ����
	if (!Walk())
	{
		return;
	}

	// ��]
	Rotation();

	// �d�͗���
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();
	CPhysics::GetInstance()->Gravity(velocity);
	m_pPlayer->SetVelocity(velocity);

	// ��������
	Braking();

	// �����x���ʒu�ɉ��Z
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);

	// �ʒu����
	m_pPlayer->AdjustPos();

	// �������ȂƂ���ɍs���ƈ�U�E��
	if (posTarget.y < -300.0f)
	{
		// ���s��ԂɕύX
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::MISS);
	}
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateDefault::Exit()
{
	// �����x��������
	m_pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });

	// ��s������������
	m_pPlayer->SetAngleFlying(0.0f);

	// Z����]��������
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.z = 0.0f;
	m_pPlayer->SetRot(rot);
}

//============================================================================
// �ړ�
//============================================================================
bool CPlayerStateDefault::Walk()
{
	// �L�[�{�[�h�擾
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// �ړ������p
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

	// X��
	if (pKeyboard->GetPress(DIK_A))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{
		X = 1.0f;
	}

	// �������͂��Ă���Έړ�������o��
	if (X != 0.0f || Y != 0.0f)
	{
		bMove = true;
	}

	if (bMove)
	{
		// �ړ��ʂƖڕW��]�ʂ�ݒ�
		D3DXVECTOR3 veloctiy = m_pPlayer->GetVelocity();
		D3DXVECTOR3 rotTarget = m_pPlayer->GetRotTarget();

		veloctiy.x += sinf(atan2f(X, 0.0f));
		rotTarget.y = atan2f(X, 0.0f);

		m_pPlayer->SetVelocity(veloctiy);
		m_pPlayer->SetRotTarget(rotTarget);
	}

	// ��ԕύX
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		// Y�����ւ̉����x��������Εϐg
		if (m_pPlayer->GetVelocity().y == 0.0f)
		{
			// �����ڂ�ύX����
			m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::BEGINNING);

			// �ȍ~�̍X�V�������s��Ȃ�
			return false;
		}
	}

	return true;
}

//============================================================================
// ��]
//============================================================================
void CPlayerStateDefault::Rotation()
{
	// �������擾
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	D3DXVECTOR3 rotTarget = m_pPlayer->GetRotTarget();

	// �u���[�L��
	float fStopEnergy = 0.1f;

	// ��]���f�Ɖ�]�ʂ̌���
	if (rotTarget.y - rot.y > D3DX_PI)
	{
		rot.y += ((rotTarget.y - rot.y) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (rotTarget.y - rot.y < -D3DX_PI)
	{
		rot.y += ((rotTarget.y - rot.y) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.y += ((rotTarget.y - rot.y) * fStopEnergy);
	}

	// �������ݒ�
	m_pPlayer->SetRot(rot);
}

//============================================================================
// ��������
//============================================================================
void CPlayerStateDefault::Braking()
{
	// �����x���擾
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();

	// �����x����ɓ��B�ő��x�Œ�
	if (velocity.x > MAX_WALK_VELOCITY)
	{
		velocity.x = MAX_WALK_VELOCITY;
	}
	else if (velocity.x < -MAX_WALK_VELOCITY)
	{
		velocity.x = -MAX_WALK_VELOCITY;
	}

	// �����������x������
	velocity.x = velocity.x * BRAKING_WALK_SPEED;

	// �����x��ݒ�
	m_pPlayer->SetVelocity(velocity);
}



//============================================================================
// 
// �v���C���[�ϐg�J�n��ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateBeginning::CPlayerStateBeginning()
{
	m_nCntMetamorphose = 0;	// �ϐg���ԃJ�E���g
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateBeginning::~CPlayerStateBeginning()
{

}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateBeginning::Enter()
{
	// �����ڂ�ύX
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_001));

	// �����𐶐�
	CExplosion3D::Create(
		m_pPlayer->GetPos(),		// �ʒu
		{ 30.0f, 0.0f, 30.0f });	// �T�C�Y
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateBeginning::Update()
{
	if (m_nCntMetamorphose < BEGIN_CNT_MAX)
	{
		// �ϐg���Ԃ��J�E���g�A�b�v
		m_nCntMetamorphose++;

		// �ϐg���Ԓ��͋����㏸
		D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
		posTarget.y += BEGIN_FLOATING;
		m_pPlayer->SetPosTarget(posTarget);

		// Y����������]���AZ����]��������
		D3DXVECTOR3 rot = m_pPlayer->GetRot();
		rot.y = posTarget.y * BEGIN_SPINNING;
		rot.z = 0.0f;
		m_pPlayer->SetRot(rot);
	}
	else
	{
		// ��ԕύX
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::FLYING);
	}
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateBeginning::Exit()
{
	// �����x��������
	m_pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });

	// ��s������������
	m_pPlayer->SetAngleFlying(0.0f);

	// Z����]�ڕW��������
	D3DXVECTOR3 rotTarget = m_pPlayer->GetRotTarget();
	rotTarget.z = 0.0f;
	m_pPlayer->SetRotTarget(rotTarget);

	// Y����]��������
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.y = 0.0f;
	m_pPlayer->SetRot(rot);
}



//============================================================================
// 
// �v���C���[��s��ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateFlying::CPlayerStateFlying()
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateFlying::~CPlayerStateFlying()
{

}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateFlying::Enter()
{
	// �����ڂ�ύX
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_002));
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateFlying::Update()
{
	// ��s
	if (!Flying())
	{
		return;
	}

	// ��]
	Rotation();

	// ��������
	Braking();

	// �����x���ʒu�ɉ��Z
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);

	// �ʒu����
	if (m_pPlayer->AdjustPos())
	{
		// �����ɏՓ˂ŕϐg��~��
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::STOPPING);
	}
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateFlying::Exit()
{
	// �����x��������
	m_pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });
}

//============================================================================
// ��s
//============================================================================
bool CPlayerStateFlying::Flying()
{
	// �L�[�{�[�h�擾
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// �ړ������p
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

	// X��
	if (pKeyboard->GetPress(DIK_A))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{
		X = 1.0f;
	}

	// Y��
	if (pKeyboard->GetPress(DIK_W))
	{
		Y = 1.0f;
	}
	else if (pKeyboard->GetPress(DIK_S))
	{
		Y = -1.0f;
	}

	// �������͂��Ă���Έړ�������o��
	if (X != 0.0f || Y != 0.0f)
	{
		bMove = true;
	}

	if (bMove)
	{
		// �ڕW������ݒ�
		D3DXVECTOR3 rotTarget = { 0.0f, 0.0f, 0.0f };
		rotTarget.z = atan2f(-X, Y);
		m_pPlayer->SetRotTarget(rotTarget);

		// ��s������ݒ�
		m_pPlayer->SetAngleFlying(atan2f(X, Y));
	}

	// ��s�����ɓːi
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();
	velocity.x += sinf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	velocity.y += cosf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	m_pPlayer->SetVelocity(velocity);

	return true;
}

//============================================================================
// ��]
//============================================================================
void CPlayerStateFlying::Rotation()
{
	// �������擾
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	D3DXVECTOR3 rotTarget = m_pPlayer->GetRotTarget();

	// �u���[�L��
	float fStopEnergy = 0.1f;

	// ��]���f�Ɖ�]�ʂ̌���
	if (rotTarget.z - rot.z > D3DX_PI)
	{
		rot.z += ((rotTarget.z - rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (rotTarget.z - rot.z < -D3DX_PI)
	{
		rot.z += ((rotTarget.z - rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.z += ((rotTarget.z - rot.z) * fStopEnergy);
	}

	// �������ݒ�
	m_pPlayer->SetRot(rot);
}

//============================================================================
// ��������
//============================================================================
void CPlayerStateFlying::Braking()
{
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();

	// �����x����ɓ��B�ő��x�Œ�
	if (velocity.x > MAX_FLY_VELOCITY)
	{
		velocity.x = MAX_FLY_VELOCITY;
	}
	else if (velocity.x < -MAX_FLY_VELOCITY)
	{
		velocity.x = -MAX_FLY_VELOCITY;
	}

	if (velocity.y > MAX_FLY_VELOCITY)
	{
		velocity.y = MAX_FLY_VELOCITY;
	}
	else if (velocity.y < -MAX_FLY_VELOCITY)
	{
		velocity.y = -MAX_FLY_VELOCITY;
	}

	m_pPlayer->SetVelocity(velocity);
}



//============================================================================
// 
// �v���C���[�ϐg��~��ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateStopping::CPlayerStateStopping()
{
	m_nCntStopMetamorphose = 0;	// �ϐg���ԃJ�E���g
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateStopping::~CPlayerStateStopping()
{

}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateStopping::Enter()
{
	// �����ڂ�ύX
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_003));

	// �����𐶐�
	CExplosion3D::Create(
		m_pPlayer->GetPos(),		// �ʒu
		{ 30.0f, 0.0f, 30.0f });	// �T�C�Y

	// ����
	Recoil();
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateStopping::Update()
{
	if (m_nCntStopMetamorphose < STOP_CNT_MAX)
	{
		// �ϐg��~���Ԃ��J�E���g�A�b�v
		m_nCntStopMetamorphose++;

		// ��]
		Rolling();

		// �d�͉���
		D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();
		CPhysics::GetInstance()->Gravity(velocity);
		m_pPlayer->SetVelocity(velocity);

		// �����x���ʒu�ɉ��Z
		D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
		posTarget += m_pPlayer->GetVelocity();
		m_pPlayer->SetPosTarget(posTarget);

		// �ʒu����
		m_pPlayer->AdjustPos();
	}
	else
	{
		// ��ԕύX
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::DEFAULT);
	}
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateStopping::Exit()
{
	// X, Z����]��������
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.x = 0.0f;
	rot.z = 0.0f;
	m_pPlayer->SetRot(rot);

	// �����ڂ�ύX
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_000));
}

//============================================================================
// ��]
//============================================================================
void CPlayerStateStopping::Rolling()
{
	// �������擾
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	D3DXVECTOR3 rotTarget = m_pPlayer->GetRotTarget();
	m_pPlayer->SetRotTarget(rotTarget);

	// �u���[�L��
	float fStopEnergy = 0.1f;

	// ��]���f�Ɖ�]�ʂ̌���
	if (rotTarget.x - rot.x > D3DX_PI)
	{
		rot.x += ((rotTarget.x - rot.x) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (rotTarget.x - rot.x < -D3DX_PI)
	{
		rot.x += ((rotTarget.x - rot.x) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.x += ((rotTarget.x - rot.x) * fStopEnergy);
	}

	// �������ݒ�
	m_pPlayer->SetRot(rot);
}

//============================================================================
// ����
//============================================================================
void CPlayerStateStopping::Recoil()
{
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();

	// ��s�����ɓːi
	velocity.x += -sinf(m_pPlayer->GetAngleFlying()) * RECOIL_SPEED;
	velocity.y += -cosf(m_pPlayer->GetAngleFlying()) * RECOIL_SPEED;

	m_pPlayer->SetVelocity(velocity);
}



//============================================================================
// 
// �v���C���[���s��ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateMistook::CPlayerStateMistook()
{
	m_posStartObject = { 0.0f, 0.0f, 0.0f };
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateMistook::~CPlayerStateMistook()
{

}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateMistook::Enter()
{
	// ��]��������
	m_pPlayer->SetRot({ 0.0f, 0.0f, 0.0f });

	// �����ڂ�ύX
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_004));

	// �X�^�[�g�I�u�W�F�N�g�̈ʒu�����擾
	FindStartObject();
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateMistook::Update()
{
	// ���X�|�[��
	Respawn();
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateMistook::Exit()
{

}

//============================================================================
// �X�^�[�g�I�u�W�F�N�g�̈ʒu������
//============================================================================
void CPlayerStateMistook::FindStartObject()
{
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(CObject::LAYER::MAX); nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// �I�u�W�F�N�g�����擾
			CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{ // ��񂪂Ȃ���΃R���e�B�j���[
				continue;
			}

			if (pObject->GetType() == CObject::TYPE::START)
			{ // �X�^�[�g�I�u�W�F�N�g�Ȃ�

				// �X�^�[�g�N���X�փ_�E���L���X�g
				CStart* pStart = dynamic_cast<CStart*>(pObject);

				if (pStart == nullptr)
				{ // �_�E���L���X�g���s
					assert(false);
				}

				// �X�^�[�g�I�u�W�F�N�g�̈ʒu���擾
				m_posStartObject = pStart->GetPos();

				// �I��
				return;
			}
		}
	}

	// �����ł��Ȃ���΃G���[
	assert(false);
}

//============================================================================
// ���X�|�[��
//============================================================================
void CPlayerStateMistook::Respawn()
{
	// �ڕW�ʒu�擾
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();

	// �v���C���[�̈ʒu���X�^�[�g�I�u�W�F�N�g�̈ʒu�ƈقȂ��
	if (posTarget != m_posStartObject)
	{
		// �v���C���[�ʒu�ƃX�^�[�g�ʒu�̍�������o��
		D3DXVECTOR3 distance = m_posStartObject - posTarget;

		// �������ȏ゠��ΐ�����t����
		if (distance.x > MAX_WARP_SPEED)
		{
			distance.x = MAX_WARP_SPEED;
		}
		else if (distance.x < -MAX_WARP_SPEED)
		{
			distance.x = -MAX_WARP_SPEED;
		}

		if (distance.y > MAX_WARP_SPEED)
		{
			distance.y = MAX_WARP_SPEED;
		}
		else if (distance.y < -MAX_WARP_SPEED)
		{
			distance.y = -MAX_WARP_SPEED;
		}

		// �����k�߂Ĉʒu��␳���Ă���
		posTarget += distance;

		// �ڕW�ʒu��ݒ肷��
		m_pPlayer->SetPosTarget(posTarget);
	}
	else
	{
		// �ʏ��ԂɕύX
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::DEFAULT);
	}
}



//============================================================================
// 
// �v���C���[��ԊǗ��N���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateManager::CPlayerStateManager() : m_pPlayer(nullptr), m_pState(nullptr)
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateManager::~CPlayerStateManager()
{

}

//============================================================================
// �����ݒ�
//============================================================================
void CPlayerStateManager::Init()
{
	// ������Ԃ�ݒ肵�Ă���
	ChangeState(CPlayerState::STATE::MISS);
}

//============================================================================
// �I������
//============================================================================
void CPlayerStateManager::Uninit()
{
	if (m_pState != nullptr)
	{
		// �����������
		delete m_pState;

		// �|�C���^��������
		m_pState = nullptr;
	}
}

//============================================================================
// �v���C���[���̎擾
//============================================================================
CPlayer* CPlayerStateManager::GetPlayerInstance()
{
	return m_pPlayer;
}

//============================================================================
// �v���C���[���̐ݒ�
//============================================================================
void CPlayerStateManager::SetPlayerInstance(CPlayer* player)
{
	m_pPlayer = player;
}

//============================================================================
// ��Ԃ�ύX
//============================================================================
void CPlayerStateManager::ChangeState(CPlayerState::STATE state)
{
	if (m_pState != nullptr)
	{
		// �ύX�I�����̏���
		m_pState->Exit();

		// �����������
		delete m_pState;

		// �|�C���^��������
		m_pState = nullptr;
	}

	// ���̏�Ԃ𐶐�
	Create(state);

	m_pState->SetPlayerInstance(m_pPlayer);

	// ����ύX���̏���
	m_pState->Enter();
}

//============================================================================
// ��Ԃ��擾
//============================================================================
CPlayerState* CPlayerStateManager::GetState()
{
	return m_pState;
}

//============================================================================
// �V���ȏ�Ԃ𐶐�
//============================================================================
void CPlayerStateManager::Create(CPlayerState::STATE state)
{
	switch (state)
	{
	case CPlayerState::STATE::DEFAULT:
		m_pState = DBG_NEW CPlayerStateDefault;
		break;

	case CPlayerState::STATE::BEGINNING:
		m_pState = DBG_NEW CPlayerStateBeginning;
		break;

	case CPlayerState::STATE::FLYING:
		m_pState = DBG_NEW CPlayerStateFlying;
		break;

	case CPlayerState::STATE::STOPPING:
		m_pState = DBG_NEW CPlayerStateStopping;
		break;

	case CPlayerState::STATE::MISS:
		m_pState = DBG_NEW CPlayerStateMistook;
		break;

	default:
		assert(false);
		break;
	}
}