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
#include "utility.h"
#include "sound.h"

// �C���v�b�g�擾�p
#include "manager.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �I�u�W�F�N�g���p
#include "ripple.h"
#include "smoke.h"
#include "star.h"
#include "start.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
const float CPlayerStateDefault::MAX_WALK_VELOCITY = 1.5f;	// ���s���̍ő�����x
const float CPlayerStateDefault::BRAKING_WALK_SPEED = 0.8f;	// ���s���̐�����
const int CPlayerStateBeginning::BEGIN_CNT_MAX = 20;		// �ϐg�K�v����
const float CPlayerStateBeginning::BEGIN_FLOATING = 1.25f;	// �ϐg���㏸��
const float CPlayerStateBeginning::BEGIN_SPINNING = 0.5f;	// �ϐg����]��
const float CPlayerStateFlying::MAX_FLY_VELOCITY = 3.0f;	// ��s���̍ő�����x
const float CPlayerStateFlying::FLY_SPEED = 3.0f;			// ��s���x
const int CPlayerStateStopping::STOP_CNT_MAX = 10;			// �ϐg��~�K�v����
const float CPlayerStateStopping::RECOIL_SPEED = 3.0f;		// �����ړ����x
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
	m_pPlayer = nullptr;	// �v���C���[�̃|�C���^��������
}

//============================================================================
// �v���C���[��o�^
//============================================================================
void CPlayerState::RegisterPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
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
	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_000);

	// ���f���̐ݒ�
	m_pPlayer->BindModel(model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(model->size);
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
	CUtility::GetInstance()->Gravity(velocity);
	m_pPlayer->SetVelocity(velocity);

	// ��������
	Braking();

	// �����x���A�ڕW���W��ϓ�
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);

	// �����蔻��
	m_pPlayer->Collision();

	// �������ȂƂ���ɍs���ƈ�U�E��
	if (m_pPlayer->GetPosTarget().y < -300.0f)
	{
		// ���s��ԂɕύX
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::MISS);
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
			// ��s��Ԃ�
			m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::BEGINNING);

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
	m_nCntMetamorphose = 0;	// �ϐg���ԃJ�E���g��������
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateBeginning::~CPlayerStateBeginning()
{
	m_nCntMetamorphose = 0;	// �ϐg���ԃJ�E���g��������
}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateBeginning::Enter()
{
	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_001);

	// ���f���̐ݒ�
	m_pPlayer->BindModel(model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(model->size);

	for (int i = 0; i < 10; i++)
	{
		// �����_���ȉ����x�𐶐�
		D3DXVECTOR3 velocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

		// ���𐶐�
		CSmoke::Create(
			m_pPlayer->GetPos(),	// ���W
			velocity * 0.005f);		// �����x
	}

	// ����SE
	CSound::GetInstance()->Play(CSound::LABEL::TAKEOFF);
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
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::FLYING);
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
	m_velocityTarget = { 0.0f, 0.0f, 0.0f };	// �ڕW�����x��������
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateFlying::~CPlayerStateFlying()
{
	m_velocityTarget = { 0.0f, 0.0f, 0.0f };	// �ڕW�����x��������
}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateFlying::Enter()
{
	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_002);

	// ���f���̐ݒ�
	m_pPlayer->BindModel(model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(model->size);
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateFlying::Update()
{
	// ��s
	if (!Control())
	{
		return;
	}

	// ��]
	Rotation();

	// ��������
	Braking();

	// �����x���A�ڕW���W��ϓ�
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);

	// �����蔻��
	if (m_pPlayer->Collision())
	{
		// �����ɏՓ˂ŕϐg��~��
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::STOPPING);
	}
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateFlying::Exit()
{
	// ��s�����ɁA�ŏI�I�ȉ����x�̕����������Ă���
	//m_pPlayer->SetAngleFlying(atan2f(m_pPlayer->GetVelocity().y, m_pPlayer->GetVelocity().x));

	// �Փˎ��_�ł̉����x�ƁA�����x�x�N�g���̕�����\��
	//CRenderer::GetInstance()->SetTimeString("X:" + std::to_string(m_pPlayer->GetVelocity().x), 240);
	//CRenderer::GetInstance()->SetTimeString("Y:" + std::to_string(m_pPlayer->GetVelocity().y), 240);
	//CRenderer::GetInstance()->SetTimeString(std::to_string(atan2f(m_pPlayer->GetVelocity().y, m_pPlayer->GetVelocity().x)), 240);
}

//============================================================================
// ���c
//============================================================================
bool CPlayerStateFlying::Control()
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

	// ���̉����x���擾
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();

	// �ڕW�����x��ݒ�
	m_velocityTarget.x = sinf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	m_velocityTarget.y = cosf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;

	// �ڕW�����x�ւƕ␳���Ă���
	velocity += (m_velocityTarget - (velocity * 0.5f)) * 0.1f;
	
	// �ύX���������x�𔽉f
	m_pPlayer->SetVelocity(velocity);

	if (rand() % 3 == 0)
	{
		// �g��𐶐�
		CRipple::Create(
			m_pPlayer->GetPos(),	// ���W
			-velocity);				// �����x (��s�����̋t)

		// ���𐶐�
		CStar::Create(
			m_pPlayer->GetPos(),	// ���W
			-velocity);				// �����x (��s�����̋t)

		// �L���L��SE
		CSound::GetInstance()->Play(CSound::LABEL::TWINKLING_00);
	}

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
	m_nCntStopMetamorphose = 0;	// �ϐg���ԃJ�E���g��������
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateStopping::~CPlayerStateStopping()
{
	m_nCntStopMetamorphose = 0;	// �ϐg���ԃJ�E���g��������
}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateStopping::Enter()
{
	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_003);

	// ���f���̐ݒ�
	m_pPlayer->BindModel(model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(model->size);

	for (int i = 0; i < 10; i++)
	{
		// �����_���ȉ����x�𐶐�
		D3DXVECTOR3 velocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

		// ���𐶐�
		CSmoke::Create(
			m_pPlayer->GetPos(),	// ���W
			velocity * 0.005f);		// �����x
	}

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
		CUtility::GetInstance()->Gravity(velocity);
		m_pPlayer->SetVelocity(velocity);

		// �����x���A�ڕW���W��ϓ�
		D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
		posTarget += m_pPlayer->GetVelocity();
		m_pPlayer->SetPosTarget(posTarget);

		// �����蔻��
		m_pPlayer->Collision();
	}
	else
	{
		// ��ԕύX
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::DEFAULT);
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

	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_000);

	// ���f���̐ݒ�
	m_pPlayer->BindModel(model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(model->size);
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

	// ��s����
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
	m_posStartObject = { 0.0f, 0.0f, 0.0f };	// �X�^�[�g�I�u�W�F�N�g�̈ʒu��������
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateMistook::~CPlayerStateMistook()
{
	m_posStartObject = { 0.0f, 0.0f, 0.0f };	// �X�^�[�g�I�u�W�F�N�g�̈ʒu��������
}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateMistook::Enter()
{
	// ��]��������
	m_pPlayer->SetRot({ 0.0f, 0.0f, 0.0f });

	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_004);

	// ���f���̐ݒ�
	m_pPlayer->BindModel(model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(model->size);

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
	CStart* pStart = CStart::DownCast(CObject::FindObject(CObject::TYPE::START));

	if (pStart == nullptr)
	{ // �������s
		assert(false);
	}

	// �X�^�[�g�I�u�W�F�N�g�̈ʒu���擾
	m_posStartObject = pStart->GetPos();
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
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::DEFAULT);
	}
}



//============================================================================
// 
// �v���C���[�S�[����N���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateGoal::CPlayerStateGoal()
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateGoal::~CPlayerStateGoal()
{

}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateGoal::Enter()
{
	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_005);

	// ���f���̐ݒ�
	m_pPlayer->BindModel(model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(model->size);
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateGoal::Update()
{
	// �����x�����炵�Ă���
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();
	velocity = velocity * 0.9f;
	m_pPlayer->SetVelocity(velocity);

	// �ϐg���Ԓ��͋����㏸
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget.y += 1.0f;
	m_pPlayer->SetPosTarget(posTarget);

	// Y����������]���AZ����]��������
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.y = posTarget.y * 0.1f;
	rot.z = 0.0f;
	m_pPlayer->SetRot(rot);

	// �����x���A�ڕW���W��ϓ�
	posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateGoal::Exit()
{

}



//============================================================================
// 
// �v���C���[��ԃ}�l�[�W���[�N���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateManager::CPlayerStateManager() : m_pPlayer(nullptr), m_pState(nullptr)
{
	m_PendingState = CPlayerState::STATE::NONE;	// �ύX�\��̏�Ԃ�������
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateManager::~CPlayerStateManager()
{
	m_pPlayer = nullptr;						// �v���C���[�̃|�C���^��������
	m_pState = nullptr;							// ��Ԃ̃|�C���^��������
	m_PendingState = CPlayerState::STATE::NONE;	// �ύX�\��̏�Ԃ�������
}

//============================================================================
// ��Ԃ̕ύX���m�F
//============================================================================
void CPlayerStateManager::CheckStateChange()
{
	if (m_pState)
	{
		// �^���̃f�o�b�O�\��
		CRenderer::GetInstance()->SetDebugString(typeid(*m_pState).name());
	}

	// �ύX�\��̏�Ԃ�������΃��^�[��
	if (m_PendingState == CPlayerState::STATE::NONE)
	{
		return;
	}

	// ���ɏ�Ԃ���������Ă���Δj��
	if (m_pState != nullptr)
	{
		// �ύX�I�����̏���
		m_pState->Exit();

		// �����������
		delete m_pState;

		// ��ԃN���X�̃|�C���^��������
		m_pState = nullptr;
	}

	// ���̏�Ԃ𐶐�
	Create(m_PendingState);

	// �ύX�\��̏�Ԃ�������
	m_PendingState = CPlayerState::STATE::NONE;

	// �V������ԂɃv���C���[��o�^
	m_pState->RegisterPlayer(m_pPlayer);

	// �ύX���̏���
	m_pState->Enter();
}

//============================================================================
// �����ݒ�
//============================================================================
void CPlayerStateManager::Init(CPlayer* pPlayer)
{
	// ��ԃ}�l�[�W���[�Ƀv���C���[��o�^
	RegisterPlayer(pPlayer);

	// ������Ԃ�\�肵�Ă���
	m_PendingState = CPlayerState::STATE::MISS;

	// ������Ԃ𔽉f����
	CheckStateChange();
}

//============================================================================
// �v���C���[��o�^
//============================================================================
void CPlayerStateManager::RegisterPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

//============================================================================
// �I������
//============================================================================
void CPlayerStateManager::Uninit()
{
	// �v���C���[�̃|�C���^��������
	m_pPlayer = nullptr;

	// ��Ԃ�j��
	if (m_pState != nullptr)
	{
		// �����������
		delete m_pState;

		// �|�C���^��������
		m_pState = nullptr;
	}
}

//============================================================================
// �v���C���[���擾
//============================================================================
CPlayer* CPlayerStateManager::GetPlayer()
{
	return m_pPlayer;
}

//============================================================================
// ��Ԃ��擾
//============================================================================
CPlayerState* CPlayerStateManager::GetState()
{
	return m_pState;
}

//============================================================================
// �ύX�\��̏�Ԃ��擾
//============================================================================
CPlayerState::STATE CPlayerStateManager::GetPendingState()
{
	return m_PendingState;
}

//============================================================================
// �ύX�\��̏�Ԃ�ݒ�
//============================================================================
void CPlayerStateManager::SetPendingState(CPlayerState::STATE state)
{
	m_PendingState = state;
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

	case CPlayerState::STATE::GOAL:
		m_pState = DBG_NEW CPlayerStateGoal;
		break;

	default:
		assert(false);
		break;
	}
}