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
#include "arrow.h"
#include "object_2D.h"
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
const float CPlayerStateFlying::MAX_FLY_VELOCITY =	10.0f;	// ��s���̍ő�����x (��s���x�ȏ㐄��)
const float CPlayerStateFlying::FLY_SPEED = 3.0f;			// ��s���x
const float CPlayerStateCharging::MAX_SPAN = 0.25f;			// ��
const int CPlayerStateStopping::STOP_CNT_MAX = 15;			// �ϐg��~�K�v����
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

	// �p�b�h�擾
	CInputPad* pPad = CManager::GetPad();

	// �ړ������p
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

	// X��
	if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::LEFT))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::RIGHT))
	{
		X = 1.0f;
	}

	// �X�e�B�b�N
	X = pPad->GetJoyStickL().X;

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
	if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::A) || pPad->GetTrigger(CInputPad::JOYKEY::B) ||
		pPad->GetTrigger(CInputPad::JOYKEY::X) || pPad->GetTrigger(CInputPad::JOYKEY::Y))
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
			velocity * 0.0075f);	// �����x
	}

	// ������
	CSound::GetInstance()->Play(CSound::LABEL::EXPLOSION);

	// �ϐg��
	CSound::GetInstance()->Play(CSound::LABEL::METAMORPHOSE);
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

		// �����蔻��
		if (m_pPlayer->Collision())
		{
			// ���̎��A����ɂ�莀�S��ԂɈڍs����Ȃ狭���I��
			if (m_pPlayer->GetStateManager()->GetPendingState() == CPlayerState::STATE::MISS)
			{
				return;
			}

			// �����ɏՓ˂ŕϐg��~��
			m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::STOPPING);

			// �Փˉ�
			CSound::GetInstance()->Play(CSound::LABEL::STOP);

			// ���S��
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
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

	// �ڕW�����x��������
	m_pPlayer->SetVelocityTarget({ 0.0f, 0.0f, 0.0f });

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
	
	// ���̎��_�ł̉����x��ێ�
	D3DXVECTOR3 oldVelocity{ m_pPlayer->GetVelocity() };

	// �����蔻��
	if (m_pPlayer->Collision())
	{
		// ���̎��A����ɂ�莀�S��ԂɈڍs����Ȃ狭���I��
		if (m_pPlayer->GetStateManager()->GetPendingState() == CPlayerState::STATE::MISS)
		{
			return;
		}

		// �����ɏՓ˂ŕϐg��~��
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::STOPPING);

		// �����蔻��ɂ��������������x��߂�
		m_pPlayer->SetVelocity(oldVelocity);

		// �Փˉ�
		CSound::GetInstance()->Play(CSound::LABEL::STOP);

		// �o�E���h��
		CSound::GetInstance()->Play(CSound::LABEL::BOUND);
	}
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateFlying::Exit()
{

}

//============================================================================
// ���c
//============================================================================
bool CPlayerStateFlying::Control()
{
	// �L�[�{�[�h�擾
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// �p�b�h�擾
	CInputPad* pPad = CManager::GetPad();

	// �ړ������p
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

	// X��
	if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::LEFT))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::RIGHT))
	{
		X = 1.0f;
	}

	// Y��
	if (pKeyboard->GetPress(DIK_W) || pPad->GetPress(CInputPad::JOYKEY::UP))
	{
		Y = 1.0f;
	}
	else if (pKeyboard->GetPress(DIK_S) || pPad->GetPress(CInputPad::JOYKEY::DOWN))
	{
		Y = -1.0f;
	}

	// �X�e�B�b�N
	X = pPad->GetJoyStickL().X;
	Y = pPad->GetJoyStickL().Y;

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

	// �ڕW�����x��ݒ�
	D3DXVECTOR3 velocityTarget{ 0.0f, 0.0f, 0.0f };
	velocityTarget.x = sinf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	velocityTarget.y = cosf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	m_pPlayer->SetVelocityTarget(velocityTarget);

#ifdef _DEBUG
	// �ڕW�����x���f�o�b�O�\��
	CRenderer::GetInstance()->SetDebugString("�y�@�ڕW�����x�@�z");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(3) << "X:" << m_pPlayer->GetVelocityTarget().x << "\nY:" << m_pPlayer->GetVelocityTarget().y;
	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());
#endif // _DEBUG

	// ���݂̉����x���擾
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();

#ifdef _DEBUG
	// ���݂̉����x���f�o�b�O�\��
	CRenderer::GetInstance()->SetDebugString("�y�@���݂̉����x�@�z");
	std::ostringstream oss1;
	oss1 << std::fixed << std::setprecision(3) << "X:" << velocity.x << "\nY:" << velocity.y;
	CRenderer::GetInstance()->SetDebugString(oss1.str().c_str());
#endif // _DEBUG

	// ���݂̉����x��␳
	velocity += (m_pPlayer->GetVelocityTarget() - velocity) * 0.1f;

	// �ύX���������x�𔽉f
	m_pPlayer->SetVelocity(velocity);

	if (rand() % 3 == 0)
	{
		// �g��𐶐�
		CRipple::Create(
			m_pPlayer->GetPos() + (-velocity * 5.0f),	// ���W
			-velocity);									// �����x (��s�����̋t)

		// ���𐶐�
		CStar::Create(
			m_pPlayer->GetPos() + (-velocity * 5.0f),	// ���W
			-velocity);									// �����x (��s�����̋t)

		// ���炫�特
		//CSound::GetInstance()->Play(CSound::LABEL::TWINKLING);
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::A) || pPad->GetTrigger(CInputPad::JOYKEY::B) ||
		pPad->GetTrigger(CInputPad::JOYKEY::X) || pPad->GetTrigger(CInputPad::JOYKEY::Y))
	{
		// ���ߏ�ԂɈڍs
		m_pPlayer->GetStateManager()->SetPendingState(STATE::CHARGING);
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
// �v���C���[���ߏ�ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateCharging::CPlayerStateCharging() :
	m_rotHold{ 0.0f, 0.0f, 0.0f },
	m_fCoeff{ 0.0f },
	m_pArrow{ nullptr }
{
	// ���̐���
	m_pArrow = CArrow::Create();
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateCharging::~CPlayerStateCharging()
{
	// ���̔j��
	if (m_pArrow)
	{
		// ���ŗ\��
		m_pArrow->SetDisappear();
	
		// �|�C���^��������
		m_pArrow = nullptr;
	}
}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateCharging::Enter()
{
	// �����ʂ�ݒ�
	m_fCoeff = 0.015f;

	// �o���ݒ�
	m_pArrow->SetAppear();

	// �������W��ݒ�
	m_pArrow->SetPos(m_pPlayer->GetPos());
	
	// ��s�����ɍ��킹�������𐶐�
	D3DXVECTOR3 newRot{ 0.0f, 0.0f, m_pPlayer->GetRot().z * 0.5f };

	// ������ݒ�
	m_pArrow->SetRot(newRot);

	// ���̌�����ێ�
	m_rotHold = newRot;

	// �ڕW�T�C�Y��ݒ�
	m_pArrow->SetSizeTarget({ 20.0f, 20.0f, 0.0f });

	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_004);

	// ���f���̐ݒ�
	m_pPlayer->BindModel(model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(model->size);
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateCharging::Update()
{ 
	// �p�b�h�擾
	CInputPad* pPad = CManager::GetPad();

	// �k����
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.x = CUtility::GetInstance()->GetRandomValue<float>() * 0.0005f;
	rot.y = CUtility::GetInstance()->GetRandomValue<float>() * 0.0005f;
	m_pPlayer->SetRot(rot);

	// �����x����
	D3DXVECTOR3 newVelocity{ m_pPlayer->GetVelocity() };
	newVelocity = CUtility::GetInstance()->AdjustToTarget(newVelocity, D3DXVECTOR3{ 0.0f, 0.0f, 0.0f }, 0.2f);
	m_pPlayer->SetVelocity(newVelocity);

	// �����x���A�ڕW���W��ϓ�
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);

	// �G�t�F�N�g����
	if (rand() % 5 == 0)
	{
		// �����_���ȃx�N�g��
		D3DXVECTOR3 random{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

		// ���𐶐�
		CStar::Create(
			m_pPlayer->GetPos() + random * 2.0f,	// ���W
			random);								// �����x (�����_��)
	}

	// ���̎��_�ł̉����x��ێ�
	D3DXVECTOR3 oldVelocity{ m_pPlayer->GetVelocity() };

	// �����蔻��
	if (m_pPlayer->Collision())
	{
		// ���̎��A����ɂ�莀�S��ԂɈڍs����Ȃ狭���I��
		if (m_pPlayer->GetStateManager()->GetPendingState() == CPlayerState::STATE::MISS)
		{
			return;
		}

		// �����ɏՓ˂ŕϐg��~��
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::STOPPING);

		// �����蔻��ɂ��������������x��߂�
		m_pPlayer->SetVelocity(oldVelocity);

		// �Փˉ�
		CSound::GetInstance()->Play(CSound::LABEL::STOP);

		// �o�E���h��
		CSound::GetInstance()->Play(CSound::LABEL::BOUND);
	}

	// ���̍X�V���s��
	UpdateArrow();

	// �ːi��Ԃ�
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::A) || pPad->GetTrigger(CInputPad::JOYKEY::B) ||
		pPad->GetTrigger(CInputPad::JOYKEY::X) || pPad->GetTrigger(CInputPad::JOYKEY::Y))
	{
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::RUSHING);
	}
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateCharging::Exit()
{
	// XY����]��������
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.x = 0.0f;
	rot.y = 0.0f;
	m_pPlayer->SetRot(rot);

	// ���̌����Ă���������s�p�x�ɐݒ�
	m_pPlayer->SetAngleFlying(-m_pArrow->GetRot().z * 2.0f);
}

//============================================================================
// ���̍X�V���s��
//============================================================================
void CPlayerStateCharging::UpdateArrow()
{
	// �L�[�{�[�h�擾
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// �p�b�h�擾
	CInputPad* pPad = CManager::GetPad();

	// �V���Ȍ������쐬
	D3DXVECTOR3 newRot{ 0.0f, 0.0f, 0.0f };

	// �ړ������p
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

	// X��
	if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::LEFT))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::RIGHT))
	{
		X = 1.0f;
	}

	// Y��
	if (pKeyboard->GetPress(DIK_W) || pPad->GetPress(CInputPad::JOYKEY::UP))
	{
		Y = 1.0f;
	}
	else if (pKeyboard->GetPress(DIK_S) || pPad->GetPress(CInputPad::JOYKEY::DOWN))
	{
		Y = -1.0f;
	}

	// �X�e�B�b�N
	X = pPad->GetJoyStickL().X;
	Y = pPad->GetJoyStickL().Y;

	// �������͂��Ă���Έړ�������o��
	if (X != 0.0f || Y != 0.0f)
	{
		bMove = true;
	}

	// �ړ����肪�o�Ă����
	if (bMove)
	{
		// ������I������
		newRot.z = atan2f(X, Y);
	}

	// �����𔽉f
	m_pArrow->SetRot(-newRot * 0.5f);

	// �V���ȍ��W���쐬
	D3DXVECTOR3 newPos{ 0.0f, 0.0f, 0.0f };

	// �v���C���[���W���擾
	newPos = m_pPlayer->GetPos();

	// ���W��␳
#if 0
	// �ړ���������p�x�𔲂��o��
	float fAngle{ atan2f(m_pPlayer->GetVelocity().x, m_pPlayer->GetVelocity().y) };

	// �v���C���[�̍��W����_�ɁA�ړ����Ă��������̉�������ɏo������
	newPos += {
		sinf(fAngle) * 20.0f,
		cosf(fAngle) * 20.0f,
		0.0f
	};
#elif 0
	// �ړ���������p�x�𔲂��o��
	float fAngle{ atan2f(m_pPlayer->GetVelocity().x, m_pPlayer->GetVelocity().y) };

	// �v���C���[�̍��W����_�ɁA�����ɍ��킹�ĉ~��`���悤�ɏo������
	newPos += {
		sinf(-newRot.z * 2.0f) * 20.0f,
		cosf(-newRot.z * 2.0f) * 20.0f,
		0.0f
	};
#elif 1
	// �ړ������̉�������ւ��炷
	/* �U��������Ȃǃv���C���[�̈ړ������ƃ��f���̌���������邽�߁A����͌����ڂ̊p�x����ɂ��� */
	newPos += {
		sinf(newRot.z) * 10.0f,
		cosf(newRot.z) * 10.0f,
		0.0f
	};

	// ���炳�ꂽ���W����_�Ɍʂ�`���悤�Ɉړ�
	newPos += {
		sinf(newRot.z) * 20.0f,
		cosf(newRot.z) * 20.0f,
		0.0f
	};
#endif

	// ���W�𔽉f
	m_pArrow->SetPos(newPos);
}



//============================================================================
// 
// �v���C���[�ˌ���ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateRushing::CPlayerStateRushing()
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayerStateRushing::~CPlayerStateRushing()
{

}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateRushing::Enter()
{
	// �ڕW������ݒ�
	D3DXVECTOR3 newRotTarget{ 0.0f, 0.0f, -m_pPlayer->GetAngleFlying() };
	m_pPlayer->SetRotTarget(newRotTarget);

	// ��s�p�x����V���ȉ����x���쐬
	D3DXVECTOR3 newVelocity{ 
		sinf(m_pPlayer->GetAngleFlying()),
		cosf(m_pPlayer->GetAngleFlying()),
		0.0f
	};

	// �����x��ݒ�
	m_pPlayer->SetVelocity(newVelocity * 5.0f);

#ifdef _DEBUG
	// �V���ȉ����x��\��
	CRenderer::GetInstance()->SetTimeString("�y�ݒ肳��Ă����s�p�x�z" + std::to_string(m_pPlayer->GetAngleFlying()), 600);
	CRenderer::GetInstance()->SetTimeString("�y��s��������ݒ肵���V���ȉ����x�z" + std::to_string(newVelocity.x) + " : " + std::to_string(newVelocity.y), 600);
#endif

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
void CPlayerStateRushing::Update()
{
	// ��]
	Rotation();

	// �����x���A�ڕW���W��ϓ�
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);

	// �G�t�F�N�g����
	if (rand() % 2 == 0)
	{
		// �����_���ȃx�N�g��
		D3DXVECTOR3 random{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

		// ���𐶐�
		CSmoke::Create(
			m_pPlayer->GetPos() - (m_pPlayer->GetVelocity() * 5.0f) + random,	// ���W
			m_pPlayer->GetVelocity());											// �����x (��s����)

		// ���𐶐�
		CStar::Create(
			m_pPlayer->GetPos() - m_pPlayer->GetVelocity() + random * 5.0f,	// ���W
			-m_pPlayer->GetVelocity());										// �����x (��s�����̋t)
		
		// �g��𐶐�
		CRipple::Create(
			m_pPlayer->GetPos() - m_pPlayer->GetVelocity() + random * 5.0f,	// ���W
			-m_pPlayer->GetVelocity());										// �����x (��s�����̋t)

		// ���炫�特
		//CSound::GetInstance()->Play(CSound::LABEL::TWINKLING);
	}

	// ���̎��_�ł̉����x��ێ�
	D3DXVECTOR3 oldVelocity{ m_pPlayer->GetVelocity() };

	// �����蔻��
	if (m_pPlayer->Collision())
	{
		// ���̎��A����ɂ�莀�S��ԂɈڍs����Ȃ狭���I��
		if (m_pPlayer->GetStateManager()->GetPendingState() == CPlayerState::STATE::MISS)
		{
			return;
		}

		// �����ɏՓ˂ŕϐg��~��
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::STOPPING);

		// �����蔻��ɂ��������������x��߂�
		m_pPlayer->SetVelocity(oldVelocity);

		// �Փˉ�
		CSound::GetInstance()->Play(CSound::LABEL::STOP);

		// �o�E���h��
		CSound::GetInstance()->Play(CSound::LABEL::BOUND);
	}

#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::STOPPING);
	}
#endif // _DEBUG
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateRushing::Exit()
{

}

//============================================================================
// ��]
//============================================================================
void CPlayerStateRushing::Rotation()
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

	// �k����
	rot.x = CUtility::GetInstance()->GetRandomValue<float>() * 0.0005f;
	rot.y = CUtility::GetInstance()->GetRandomValue<float>() * 0.0005f;
	
	// �������ݒ�
	m_pPlayer->SetRot(rot);
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
			velocity * 0.0075f);	// �����x
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
	// �Փː��O�̉����x���擾
	D3DXVECTOR3 newVelocity{ m_pPlayer->GetVelocity() };

#ifdef _DEBUG
	CRenderer::GetInstance()->SetTimeString("\n�Փˎ��̉����xX : " + std::to_string(newVelocity.x), 120);
	CRenderer::GetInstance()->SetTimeString("�Փˎ��̉����xY : " + std::to_string(newVelocity.y), 120);
#endif	// _DEBUG

	// ���O�̌����̐^�t�̊p�x���Z�o
	float fNewFlyingAngle{ atan2f(newVelocity.x, newVelocity.y) };

	// �^�t�̊p�x�����ɉ����x��ݒ�
	newVelocity.x = -sinf(fNewFlyingAngle) * RECOIL_SPEED;
	newVelocity.y = -cosf(fNewFlyingAngle) * RECOIL_SPEED;

#ifdef _DEBUG
	CRenderer::GetInstance()->SetTimeString("�Փˌ�̉����xX : " + std::to_string(newVelocity.x), 120);
	CRenderer::GetInstance()->SetTimeString("�Փˌ�̉����xY : " + std::to_string(newVelocity.y), 120);
#endif	// _DEBUG

	m_pPlayer->SetVelocity(newVelocity);
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
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_006);

	// ���f���̐ݒ�
	m_pPlayer->BindModel(model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(model->size);

	// �X�^�[�g�I�u�W�F�N�g�̈ʒu�����擾
	FindStartObject();

	// �~�X��
	CSound::GetInstance()->Play(CSound::LABEL::MISS);
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
	// �����x��������
	m_pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });
}

//============================================================================
// �X�^�[�g�I�u�W�F�N�g�̈ʒu������
//============================================================================
void CPlayerStateMistook::FindStartObject()
{
	CStart* pStart = CUtility::GetInstance()->DownCast<CStart, CObject>(CObject::FindObject(CObject::TYPE::START));

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
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_007);

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
#ifdef _DEBUG
	if (m_pState)
	{
		// �^���̃f�o�b�O�\��
		CRenderer::GetInstance()->SetDebugString(typeid(*m_pState).name());
	}
#endif	// _DEBUG

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

	case CPlayerState::STATE::CHARGING:
		m_pState = DBG_NEW CPlayerStateCharging;
		break;

	case CPlayerState::STATE::RUSHING:
		m_pState = DBG_NEW CPlayerStateRushing;
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