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
#include "ring.h"
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
const float CPlayerStateFlying::FLY_SPEED = 3.5f;			// ��s���x
const int CPlayerStateCharging::MAX_LIMITCHARGE = 120;		// �ő�`���[�W�P�\
const int CPlayerStateStopping::STOP_CNT_MAX = 25;			// �ϐg��~�K�v����
const float CPlayerStateStopping::RECOIL_SPEED = 4.0f;		// �����ړ����x
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
CPlayerStateDefault::CPlayerStateDefault() : 
	m_OldRotTarget{ 0.0f, 0.0f, 0.0f }
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
	// X�EY���̌��������Z�b�g
	m_pPlayer->SetRot(D3DXVECTOR3{ 0.0f, 0.0f, m_pPlayer->GetRot().z });

	// �ڕW���������Z�b�g
	m_pPlayer->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });

	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_000) };

	// ���f���̐ݒ�
	m_pPlayer->BindModel(Model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(Model->size);
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateDefault::Update()
{
	// ����
	if (!Control())
	{
		// �ύX�J�n��ԂɂȂ��Ă�����I��
		return;
	}

	// ��]
	Rotation();

	// �d�͉���
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };
	CUtility::GetInstance()->Gravity(NewVelocity);
	m_pPlayer->SetVelocity(NewVelocity);

	// �����x������
	NewVelocity.x = CUtility::GetInstance()->AdjustToTarget(NewVelocity.x, 0.0f, 0.1f);
	m_pPlayer->SetVelocity(NewVelocity);

	// ��������
	Braking();

	// �����x���A�ڕW���W��ϓ�
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
	NewPosTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(NewPosTarget);

	// �ڕW�T�C�Y�֊g��
	m_pPlayer->SetScale(CUtility::GetInstance()->AdjustToTarget(m_pPlayer->GetScale(), 1.0f, 0.1f));

	// �����蔻��
	m_pPlayer->Collision();

	// ���ȏ㗎�������
	if (m_pPlayer->GetPosTarget().y < -300.0f)
	{
		// ���S��ԂɕύX
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::MISS);
	}
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateDefault::Exit()
{

}

//============================================================================
// �ړ�
//============================================================================
bool CPlayerStateDefault::Control()
{
	// �L�[�{�[�h�擾
	CInputKeyboard* pKeyboard{ CManager::GetKeyboard() };

	// �p�b�h�擾
	CInputPad* pPad{ CManager::GetPad() };

	// �ړ������p
	bool bMove{ false };
	float X{ 0.0f };

	// �X�e�B�b�N��X���̌X�����擾
	X = pPad->GetJoyStickL().X;

	// X��
	if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::LEFT))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::RIGHT))
	{
		X = 1.0f;
	}

	// �������͂��Ă���Έړ�������o��
	if (X != 0.0f)
	{
		bMove = true;
	}

	if (bMove)
	{
		// ���͕����ɉ����x��ݒ�
		D3DXVECTOR3 NewVeloctiy{ m_pPlayer->GetVelocity() };
		NewVeloctiy.x += sinf(atan2f(X, 0.0f)) * 0.25f;
		m_pPlayer->SetVelocity(NewVeloctiy);

		// ���͕����Ƀ��f���̖ڕW������ݒ�
		D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };
		NewRotTarget.y = atan2f(X, 0.0f);
		m_pPlayer->SetRotTarget(NewRotTarget);
	}

	// �ϐg
	if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::A) || pPad->GetTrigger(CInputPad::JOYKEY::B) ||
		pPad->GetTrigger(CInputPad::JOYKEY::X) || pPad->GetTrigger(CInputPad::JOYKEY::Y))
	{
		// Y�����ւ̉����x��������Εϐg
		if (m_pPlayer->GetVelocity().y == 0.0f)
		{
			// �ϐg�J�n��Ԃ֕ύX
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
	// �V�������������쐬
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };

	// �ڕW�������Y��ɒǂ�������悤�ɁAY���̌�����␳
	if (NewRotTarget.y > 0.0f && m_OldRotTarget.y < 0.0f)
	{
		NewRot.y += D3DX_PI * 2.0f;
	}
	else if (NewRotTarget.y < 0.0f && m_OldRotTarget.y > 0.0f)
	{
		NewRot.y += D3DX_PI * -2.0f;
	}

	// �ڕW�����֕␳
	NewRot = CUtility::GetInstance()->AdjustToTarget(NewRot, NewRotTarget, 0.1f);

	// �V�����������𔽉f
	m_pPlayer->SetRot(NewRot);

	// �ڕW�������L�^
	m_OldRotTarget = NewRotTarget;
}

//============================================================================
// ��������
//============================================================================
void CPlayerStateDefault::Braking()
{
	// �V���������x���쐬
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };

	// �����x����ɓ��B�ő��x�Œ�
	if (NewVelocity.x > MAX_WALK_VELOCITY)
	{
		NewVelocity.x = MAX_WALK_VELOCITY;
	}
	else if (NewVelocity.x < -MAX_WALK_VELOCITY)
	{
		NewVelocity.x = -MAX_WALK_VELOCITY;
	}

	// �V���������x�𔽉f
	m_pPlayer->SetVelocity(NewVelocity);
}

//============================================================================
// ����
//============================================================================
void CPlayerStateDefault::Recoil()
{

}



//============================================================================
// 
// �v���C���[�ϐg�J�n��ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateBeginning::CPlayerStateBeginning() :
	m_nCntMetamorphose{ 0 }
{

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
	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_001) };

	// ���f���̐ݒ�
	m_pPlayer->BindModel(Model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(Model->size);

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
		D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
		NewPosTarget.y += BEGIN_FLOATING;
		m_pPlayer->SetPosTarget(NewPosTarget);

		// Y��������������]���AZ�������̓��Z�b�g
		D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
		NewRot.y = NewPosTarget.y * BEGIN_SPINNING;
		NewRot.z = 0.0f;
		m_pPlayer->SetRot(NewRot);

		// �����蔻��
		if (m_pPlayer->Collision())
		{
			// ���̎��A����ɂ�莀�S��ԂɈڍs����Ȃ狭���I��
			if (m_pPlayer->GetStateManager()->GetPendingState() == CPlayerState::STATE::MISS)
			{
				return;
			}

			// �����ɏՓ˂Œʏ��Ԃ�
			m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::DEFAULT);

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
	m_pPlayer->SetVelocity(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });

	// �ڕW�����x��������
	m_pPlayer->SetVelocityTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });

	// ��s������������
	m_pPlayer->SetAngleFlying(0.0f);

	// Y���̌��������Z�b�g
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	NewRot.y = 0.0f;
	m_pPlayer->SetRot(NewRot);

	// Z���̖ڕW���������Z�b�g
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };
	NewRotTarget.z = 0.0f;
	m_pPlayer->SetRotTarget(NewRotTarget);
}



//============================================================================
// 
// �v���C���[��s��ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateFlying::CPlayerStateFlying() :
	m_OldRotTarget{ 0.0f, 0.0f, 0.0f }
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
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_002) };

	// ���f���̐ݒ�
	m_pPlayer->BindModel(Model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(Model->size);

	// �G�t�F�N�g����
	for (int i = 0; i < 10; i++)
	{
		// �����_���ȉ����x���쐬
		D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

		// ���𐶐�
		CSmoke::Create(
			m_pPlayer->GetPos(),		// ���W
			RandomVelocity * 0.0075f);	// �����x
	}
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
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
	NewPosTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(NewPosTarget);
	
	// ���̎��_�ł̉����x��ێ�
	D3DXVECTOR3 OldVelocity{ m_pPlayer->GetVelocity() };

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

		// �������ɏՓ˂��Ă���Ȃ�
		if (m_pPlayer->GetVelocity().x == 0.0f)
		{
			// �������̔��˃x�N�g���������Ă���
			OldVelocity.x *= -1.0f;
		}

		// �c�����ɏՓ˂��Ă���Ȃ�
		if (m_pPlayer->GetVelocity().y == 0.0f)
		{
			// �c�����̔��˃x�N�g���������Ă���
			OldVelocity.y *= -1.0f;
		}
		
		m_pPlayer->SetVelocity(OldVelocity);

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
	CInputKeyboard* pKeyboard{ CManager::GetKeyboard() };

	// �p�b�h�擾
	CInputPad* pPad{ CManager::GetPad() };

	// �ړ������p
	bool bMove{ false };
	float X{ 0.0f }, Y{ 0.0f };

	// �X�e�B�b�N�̌X�����擾
	X = pPad->GetJoyStickL().X;
	Y = pPad->GetJoyStickL().Y;

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

	// �������͂��Ă���Έړ�������o��
	if (X != 0.0f || Y != 0.0f)
	{
		bMove = true;
	}

	if (bMove)
	{
		// ��s������ݒ�
		m_pPlayer->SetAngleFlying(atan2f(X, Y));
	
		// ���f���̖ڕW������ݒ�
		D3DXVECTOR3 NewRotTarget{ 0.0f, 0.0f, 0.0f };
		NewRotTarget.z = atan2f(-X, Y);
		m_pPlayer->SetRotTarget(NewRotTarget);
	}

	// �ڕW�����x��ݒ�
	D3DXVECTOR3 NewVelocityTarget{ 0.0f, 0.0f, 0.0f };
	NewVelocityTarget.x = sinf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	NewVelocityTarget.y = cosf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	m_pPlayer->SetVelocityTarget(NewVelocityTarget);

//#ifdef _DEBUG
//	// �ڕW�����x���f�o�b�O�\��
//	CRenderer::GetInstance()->SetDebugString("�y�@�ڕW�����x�@�z");
//	std::ostringstream oss;
//	oss << std::fixed << std::setprecision(3) << "X:" << m_pPlayer->GetVelocityTarget().x << "\nY:" << m_pPlayer->GetVelocityTarget().y;
//	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());
//#endif // _DEBUG

	// ���݂̉����x���擾
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };

//#ifdef _DEBUG
//	// ���݂̉����x���f�o�b�O�\��
//	CRenderer::GetInstance()->SetDebugString("�y�@���݂̉����x�@�z");
//	std::ostringstream oss1;
//	oss1 << std::fixed << std::setprecision(3) << "X:" << NewVelocity.x << "\nY:" << NewVelocity.y;
//	CRenderer::GetInstance()->SetDebugString(oss1.str().c_str());
//#endif // _DEBUG

	// ���݂̉����x��␳
	NewVelocity += (m_pPlayer->GetVelocityTarget() - NewVelocity) * 0.1f;

	// �ύX���������x�𔽉f
	m_pPlayer->SetVelocity(NewVelocity);

	// �G�t�F�N�g����
	if (rand() % 3 == 0)
	{
		// �g��𐶐�
		CRipple::Create(
			m_pPlayer->GetPos() + (-NewVelocity * 5.0f),	// ���W
			-NewVelocity);									// �����x (��s�����̋t)

		// ���𐶐�
		CStar::Create(
			m_pPlayer->GetPos() + (-NewVelocity * 5.0f),	// ���W
			-NewVelocity);									// �����x (��s�����̋t)
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
	// �V�������������쐬
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };

	// �ڕW�������Y��ɒǂ�������悤�ɁAZ���̌�����␳
	if (NewRotTarget.z > 0.0f && m_OldRotTarget.z < 0.0f)
	{
		NewRot.z += D3DX_PI * 2.0f;
	}
	else if (NewRotTarget.z < 0.0f && m_OldRotTarget.z > 0.0f)
	{
		NewRot.z += D3DX_PI * -2.0f;
	}

	// �ڕW�����֕␳
	NewRot = CUtility::GetInstance()->AdjustToTarget(NewRot, NewRotTarget, 0.1f);

	// �V�����������𔽉f
	m_pPlayer->SetRot(NewRot);

	// �ڕW�������L�^
	m_OldRotTarget = NewRotTarget;
}

//============================================================================
// ��������
//============================================================================
void CPlayerStateFlying::Braking()
{
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };

	// �����x����ɓ��B�ő��x�Œ�
	if (NewVelocity.x > MAX_FLY_VELOCITY)
	{
		NewVelocity.x = MAX_FLY_VELOCITY;
	}
	else if (NewVelocity.x < -MAX_FLY_VELOCITY)
	{
		NewVelocity.x = -MAX_FLY_VELOCITY;
	}

	if (NewVelocity.y > MAX_FLY_VELOCITY)
	{
		NewVelocity.y = MAX_FLY_VELOCITY;
	}
	else if (NewVelocity.y < -MAX_FLY_VELOCITY)
	{
		NewVelocity.y = -MAX_FLY_VELOCITY;
	}

	m_pPlayer->SetVelocity(NewVelocity);
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
	m_OldRotTarget{ 0.0f, 0.0f, 0.0f },
	m_rotHold{ 0.0f, 0.0f, 0.0f },
	m_nLimitCharge{ 0 },
	m_pArrow{ nullptr },
	m_fArrowSize{ 0.0f },
	m_pRing{ nullptr },
	m_fRingSize{ 0.0f }
{
	// �����O�̐��� (��s)
	m_pRing = CRing::Create();

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

	// �����O�̔j��
	if (m_pRing)
	{
		// ���ŗ\��
		m_pRing->SetDisappear();

		// �|�C���^��������
		m_pRing = nullptr;
	}
}

//============================================================================
// �ύX�J�n
//============================================================================
void CPlayerStateCharging::Enter()
{
	// �o���ݒ�
	m_pArrow->SetAppear();
	m_pRing->SetAppear();

	// UI�������W��ݒ�
	m_pArrow->SetPos(m_pPlayer->GetPos());
	m_pRing->SetPos(m_pPlayer->GetPos());

	// ���p�̃z�[���h�����ɁA���f���̌��Ă��������ݒ�
	D3DXVECTOR3 NewRot{ 0.0f, 0.0f, -m_pPlayer->GetRot().z };
	m_rotHold = NewRot;

	// UI�����T�C�Y��ݒ�
	m_fArrowSize = 30.0f;
	m_pArrow->SetSize({ m_fArrowSize, m_fArrowSize, 0.0f });
	m_fRingSize = 27.5f;
	m_pRing->SetSize({ m_fRingSize, m_fRingSize, 0.0f });
	m_pRing->SetSizeTarget({ m_fRingSize, m_fRingSize, 0.0f });

	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_004) };

	// ���f���̐ݒ�
	m_pPlayer->BindModel(Model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(Model->size);

	// �`���[�W��
	CSound::GetInstance()->Play(CSound::LABEL::CHARGE);
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateCharging::Update()
{ 
	// �`���[�W���I���Ƌ����I��
	if (m_nLimitCharge > MAX_LIMITCHARGE)
	{
		// �ʏ��Ԃ�
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::DEFAULT);

		return;
	}

	// �`���[�W�P�\�J�E���g
	m_nLimitCharge++;

	// �p�b�h�擾
	CInputPad* pPad{ CManager::GetPad() };

	// ��]
	Rotation();

	// �����x����
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };
	NewVelocity = CUtility::GetInstance()->AdjustToTarget(NewVelocity, D3DXVECTOR3{ 0.0f, 0.0f, 0.0f }, 0.2f);
	m_pPlayer->SetVelocity(NewVelocity);

	// �����x���A�ڕW���W��ϓ�
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
	NewPosTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(NewPosTarget);

	// �G�t�F�N�g����
	if (rand() % 5 == 0)
	{
		// �����_���ȉ����x���쐬
		D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

		// ���𐶐�
		CStar::Create(
			m_pPlayer->GetPos() + RandomVelocity * 2.0f,	// ���W
			RandomVelocity);								// �����x (�����_��)
	}

	// ���̎��_�ł̉����x��ێ�
	D3DXVECTOR3 OldVelocity{ m_pPlayer->GetVelocity() };

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

		// �������ɏՓ˂��Ă���Ȃ�
		if (m_pPlayer->GetVelocity().x == 0.0f)
		{
			// �������̔��˃x�N�g���������Ă���
			OldVelocity.x *= -1.0f;
		}

		// �c�����ɏՓ˂��Ă���Ȃ�
		if (m_pPlayer->GetVelocity().y == 0.0f)
		{
			// �c�����̔��˃x�N�g���������Ă���
			OldVelocity.y *= -1.0f;
		}

		m_pPlayer->SetVelocity(OldVelocity);

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
	// X�EY����]�����Z�b�g
	D3DXVECTOR3 NweRot{ m_pPlayer->GetRot() };
	NweRot.x = 0.0f;
	NweRot.y = 0.0f;
	m_pPlayer->SetRot(NweRot);

	// ���̌����Ă���������s�p�x�ɐݒ�
	m_pPlayer->SetAngleFlying(-m_pArrow->GetRot().z * 2.0f);
}

//============================================================================
// ��]
//============================================================================
void CPlayerStateCharging::Rotation()
{
	// ���������擾
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };

#ifdef _DEBUG
	CRenderer::GetInstance()->SetDebugString("�y���݂̌��� :" + std::to_string(NewRot.z) + "�z");
	CRenderer::GetInstance()->SetDebugString("�y�ڕW�̌��� :" + std::to_string(NewRotTarget.z) + "�z");
#endif // _DEBUG

	// �ڕW�������Y��ɒǂ�������悤�ɁAZ���̌�����␳
	if (NewRotTarget.z > 0.0f && m_OldRotTarget.z < 0.0f)
	{
		NewRot.z += D3DX_PI * 2.0f;
#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("�Ȃ�Ȃ�Ȃ�Ȃ�Ȃ�Ȃ�Ȃ�Ȃ�Ȃ�", 60);
#endif // _DEBUG
	}
	else if (NewRotTarget.z < 0.0f && m_OldRotTarget.z > 0.0f)
	{
		NewRot.z += D3DX_PI * -2.0f;
#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("���񂨂񂨂񂨂񂨂񂨂񂨂񂨂񂨂�", 60);
#endif // _DEBUG
	}

	// �ڕW�����֕␳
	NewRot = CUtility::GetInstance()->AdjustToTarget(NewRot, NewRotTarget, 0.1f);

	// �k����
	NewRot.x = CUtility::GetInstance()->GetRandomValue<float>() * 0.00025f;
	NewRot.y = CUtility::GetInstance()->GetRandomValue<float>() * 0.00025f;

	// �������ݒ�
	m_pPlayer->SetRot(NewRot);

	// �ڕW�������L�^
	m_OldRotTarget = NewRotTarget;
}

//============================================================================
// ���̍X�V���s��
//============================================================================
void CPlayerStateCharging::UpdateArrow()
{
	// �L�[�{�[�h�擾
	CInputKeyboard* pKeyboard{ CManager::GetKeyboard() };

	// �p�b�h�擾
	CInputPad* pPad{ CManager::GetPad() };

	// �V���Ȍ������쐬
	D3DXVECTOR3 NewRot{ m_rotHold };

	// �ړ������p
	bool bMove{ false };
	float X{ 0.0f }, Y{ 0.0f };

	// �X�e�B�b�N�̌X�����擾
	X = pPad->GetJoyStickL().X;
	Y = pPad->GetJoyStickL().Y;

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

	// �������͂��Ă���Έړ�������o��
	if (X != 0.0f || Y != 0.0f)
	{
		bMove = true;
	}

	// �ړ����肪�o�Ă����
	if (bMove)
	{
		// �V����������ݒ�
		NewRot.z = atan2f(X, Y);

		// ���̕��������f���̖ڕW�����ɐݒ�
		m_pPlayer->SetRotTarget(D3DXVECTOR3{  0.0f, 0.0f, -NewRot.z });
	}

	// ���ɐV���������𔽉f
	m_pArrow->SetRot(-NewRot * 0.5f);

	// �z�[���h�����ɋL�^
	m_rotHold = NewRot;

	// ���̖ڕW�T�C�Y���k��
	D3DXVECTOR3 NewArrowSizeTarget{ m_pArrow->GetSizeTarget() };
	NewArrowSizeTarget.x = m_fArrowSize - ((m_fArrowSize / MAX_LIMITCHARGE) * (m_nLimitCharge));
	NewArrowSizeTarget.y = m_fArrowSize - ((m_fArrowSize / MAX_LIMITCHARGE) * (m_nLimitCharge));
	m_pArrow->SetSizeTarget(NewArrowSizeTarget);

	// �����O�̖ڕW�T�C�Y���k��
	D3DXVECTOR3 NewRingSizeTarget{ m_pRing->GetSizeTarget() };
	NewRingSizeTarget.x = m_fRingSize - ((m_fRingSize / MAX_LIMITCHARGE) * (m_nLimitCharge));
	NewRingSizeTarget.y = m_fRingSize - ((m_fRingSize / MAX_LIMITCHARGE) * (m_nLimitCharge));
	m_pRing->SetSizeTarget(NewRingSizeTarget);

	// �V���ȍ��W���쐬
	D3DXVECTOR3 NewPos{ 0.0f, 0.0f, 0.0f };

	// �v���C���[���W���擾
	NewPos = m_pPlayer->GetPos();

	// �����O�֍��W�𔽉f
	m_pRing->SetPos(NewPos);

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
	//newPos += {
	//	sinf(newRot.z) * (10.0f - ((10.0f / 120) * (m_nLimitCharge))),
	//	cosf(newRot.z) * (10.0f - ((10.0f / 120) * (m_nLimitCharge))),
	//	0.0f
	//};

	//// ���炳�ꂽ���W����_�Ɍʂ�`���悤�Ɉړ�
	//newPos += {
	//	sinf(newRot.z) * (20.0f - ((20.0f / 120) * (m_nLimitCharge))),
	//	cosf(newRot.z) * (20.0f - ((20.0f / 120) * (m_nLimitCharge))),
	//	0.0f
	//};
#endif

	// ���֍��W�𔽉f
	m_pArrow->SetPos(NewPos);
}



//============================================================================
// 
// �v���C���[�ˌ���ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateRushing::CPlayerStateRushing() :
	m_OldRotTarget{ 0.0f, 0.0f, 0.0f }
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
	D3DXVECTOR3 NewRotTarget{ 0.0f, 0.0f, -m_pPlayer->GetAngleFlying() };
	m_pPlayer->SetRotTarget(NewRotTarget);

	// ��s�p�x����V���ȉ����x���쐬
	D3DXVECTOR3 NewVelocity{ sinf(m_pPlayer->GetAngleFlying()),cosf(m_pPlayer->GetAngleFlying()), 0.0f };

	// �����x��ݒ�
	m_pPlayer->SetVelocity(NewVelocity * 5.0f);

#ifdef _DEBUG
	// �V���ȉ����x��\��
	CRenderer::GetInstance()->SetTimeString("�y�ݒ肳��Ă����s�p�x�z" + std::to_string(m_pPlayer->GetAngleFlying()), 600);
	CRenderer::GetInstance()->SetTimeString("�y��s��������ݒ肵���V���ȉ����x�z" + std::to_string(NewVelocity.x) + " : " + std::to_string(NewVelocity.y), 600);
#endif

	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_005) };

	// ���f���̐ݒ�
	m_pPlayer->BindModel(Model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(Model->size);

	// �ːi��
	CSound::GetInstance()->Play(CSound::LABEL::RUSH);
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateRushing::Update()
{
	// ��]
	Rotation();

	// �����x���A�ڕW���W��ϓ�
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
	NewPosTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(NewPosTarget);

	// �G�t�F�N�g����
	if (rand() % 2 == 0)
	{
		// �����_���ȉ����x���쐬
		D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

		// ���𐶐�
		CSmoke::Create(
			m_pPlayer->GetPos() - (m_pPlayer->GetVelocity() * 5.0f) + RandomVelocity,	// ���W
			m_pPlayer->GetVelocity());													// �����x (��s����)

		// ���𐶐�
		CStar::Create(
			m_pPlayer->GetPos() - m_pPlayer->GetVelocity() + RandomVelocity * 5.0f,	// ���W
			-m_pPlayer->GetVelocity());												// �����x (��s�����̋t)
		
		// �g��𐶐�
		CRipple::Create(
			m_pPlayer->GetPos() - m_pPlayer->GetVelocity() + RandomVelocity * 5.0f,	// ���W
			-m_pPlayer->GetVelocity());												// �����x (��s�����̋t)
	}

	// ���̎��_�ł̉����x��ێ�
	D3DXVECTOR3 OldVelocity{ m_pPlayer->GetVelocity() };

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

		// �������ɏՓ˂��Ă���Ȃ�
		if (m_pPlayer->GetVelocity().x == 0.0f)
		{
			// �������̔��˃x�N�g���������Ă���
			OldVelocity.x *= -1.0f;
		}
		
		// �c�����ɏՓ˂��Ă���Ȃ�
		if (m_pPlayer->GetVelocity().y == 0.0f)
		{
			// �c�����̔��˃x�N�g���������Ă���
			OldVelocity.y *= -1.0f;
		}

		m_pPlayer->SetVelocity(OldVelocity);

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
	// X�EY���̌����������傰���ɐݒ�
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	NewRot.x = CUtility::GetInstance()->GetRandomValue<float>() * 0.003f;
	NewRot.y = CUtility::GetInstance()->GetRandomValue<float>() * 0.003f;
	m_pPlayer->SetRot(NewRot);
}

//============================================================================
// ��]
//============================================================================
void CPlayerStateRushing::Rotation()
{
	// ���������擾
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };

	// �ڕW�������Y��ɒǂ�������悤�ɁAZ���̌�����␳
	if (NewRotTarget.z > 0.0f && m_OldRotTarget.z < 0.0f)
	{
		NewRot.z += D3DX_PI * 2.0f;
	}
	else if (NewRotTarget.z < 0.0f && m_OldRotTarget.z > 0.0f)
	{
		NewRot.z += D3DX_PI * -2.0f;
	}

	// �ڕW�����֕␳
	NewRot = CUtility::GetInstance()->AdjustToTarget(NewRot, NewRotTarget, 0.1f);

	// �k����
	NewRot.x = CUtility::GetInstance()->GetRandomValue<float>() * 0.001f;
	NewRot.y = CUtility::GetInstance()->GetRandomValue<float>() * 0.001f;

	// �������ݒ�
	m_pPlayer->SetRot(NewRot);

	// �ڕW�������L�^
	m_OldRotTarget = NewRotTarget;
}



//============================================================================
// 
// �v���C���[�ϐg��~��ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateStopping::CPlayerStateStopping() :
	m_OldRotTarget{ 0.0f, 0.0f, 0.0f },
	m_nCntStopMetamorphose{ 0 }
{

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
	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_003) };

	// ���f���̐ݒ�
	m_pPlayer->BindModel(Model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(Model->size);

	// �G�t�F�N�g�𐶐�
	for (int i = 0; i < 10; i++)
	{
		// �����_���ȉ����x���쐬
		D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

		// ���𐶐�
		CSmoke::Create(
			m_pPlayer->GetPos(),		// ���W
			RandomVelocity * 0.0075f);	// �����x
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
		Rotation();

		// �d�͉���
		D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };
		CUtility::GetInstance()->Gravity(NewVelocity);
		m_pPlayer->SetVelocity(NewVelocity);

		// �����x������
		m_pPlayer->SetVelocity(CUtility::GetInstance()->AdjustToTarget(m_pPlayer->GetVelocity(), D3DXVECTOR3{ 0.0f, 0.0f, 0.0f }, 0.05f));

		// �����x���A�ڕW���W��ϓ�
		D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
		NewPosTarget += m_pPlayer->GetVelocity();
		m_pPlayer->SetPosTarget(NewPosTarget);

		// ���̎��_�ł̉����x��ێ�
		D3DXVECTOR3 OldVelocity{ m_pPlayer->GetVelocity() };

		// �����蔻��
		if (m_pPlayer->Collision())
		{
			// �����_���ȉ����x���쐬
			D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

			// ���𐶐�
			CSmoke* pSmoke = CSmoke::Create(
				m_pPlayer->GetPos(),		// ���W
				RandomVelocity * 0.0075f);	// �����x

			// �����߂�
			pSmoke->SetScale(0.5f);

			// �������ɏՓ˂��Ă���Ȃ�
			if (m_pPlayer->GetVelocity().x == 0.0f)
			{
				// �������̔��˃x�N�g���������Ă���
				OldVelocity.x *= -1.0f;
			}

			// �c�����ɏՓ˂��Ă���Ȃ�
			if (m_pPlayer->GetVelocity().y == 0.0f)
			{
				// �c�����̔��˃x�N�g���������Ă���
				OldVelocity.y *= -1.0f;

				OldVelocity.y *= 0.9f;
			}

			// �����x�𔽉f
			m_pPlayer->SetVelocity(OldVelocity);
		}
	}
	else
	{
		// �ʏ��ԂɕύX
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::DEFAULT);
	}
}

//============================================================================
// �ύX�I��
//============================================================================
void CPlayerStateStopping::Exit()
{
	// �ڕW���������Z�b�g
	m_pPlayer->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });

	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_000) };

	// ���f���̐ݒ�
	m_pPlayer->BindModel(Model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(Model->size);
}

//============================================================================
// ��]
//============================================================================
void CPlayerStateStopping::Rotation()
{
	// �V�������������쐬
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };

	// �ڕW�������Y��ɒǂ�������悤�ɁAZ���̌�����␳
	if (NewRotTarget.z > 0.0f && m_OldRotTarget.z < 0.0f)
	{
		NewRot.z += D3DX_PI * 2.0f;
	}
	else if (NewRotTarget.y < 0.0f && m_OldRotTarget.z > 0.0f)
	{
		NewRot.z += D3DX_PI * -2.0f;
	}

	// �ڕW�����֕␳
	NewRot = CUtility::GetInstance()->AdjustToTarget(NewRot, NewRotTarget, 0.1f);

	// �V�����������𔽉f
	m_pPlayer->SetRot(NewRot);

	// �ڕW�������L�^
	m_OldRotTarget = NewRotTarget;
}

//============================================================================
// ����
//============================================================================
void CPlayerStateStopping::Recoil()
{
	// �Փː��O�̉����x���擾
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };

#ifdef _DEBUG
	CRenderer::GetInstance()->SetTimeString("\n�Փˎ��̉����xX : " + std::to_string(NewVelocity.x), 120);
	CRenderer::GetInstance()->SetTimeString("�Փˎ��̉����xY : " + std::to_string(NewVelocity.y), 120);
#endif	// _DEBUG

	// ���O�̉����x�̊p�x���Z�o
	float fNewFlyingAngle{ atan2f(NewVelocity.x, NewVelocity.y) };

	// �^�t�̊p�x�����ɉ����x��ݒ�
	NewVelocity.x = sinf(fNewFlyingAngle) * RECOIL_SPEED;
	NewVelocity.y = cosf(fNewFlyingAngle) * RECOIL_SPEED;

	//newVelocity.x = sinf(fNewFlyingAngle) * (fabsf(newVelocity.x) + fabsf(newVelocity.y));
	//newVelocity.y = cosf(fNewFlyingAngle) * (fabsf(newVelocity.x) + fabsf(newVelocity.y));

#ifdef _DEBUG
	CRenderer::GetInstance()->SetTimeString("�Փˌ�̉����xX : " + std::to_string(NewVelocity.x), 120);
	CRenderer::GetInstance()->SetTimeString("�Փˌ�̉����xY : " + std::to_string(NewVelocity.y), 120);
#endif	// _DEBUG

	m_pPlayer->SetVelocity(NewVelocity);
}



//============================================================================
// 
// �v���C���[���s��ԃN���X
// 
//============================================================================

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayerStateMistook::CPlayerStateMistook() :
	m_PosStartObject{ 0.0f, 0.0f, 0.0f }
{

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
	// ������������
	m_pPlayer->SetRot({ 0.0f, 0.0f, 0.0f });

	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_006) };

	// ���f���̐ݒ�
	m_pPlayer->BindModel(Model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(Model->size);

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

	// �k�ڂ����Z�b�g
	m_pPlayer->SetScale(0.0f);
}

//============================================================================
// �X�^�[�g�I�u�W�F�N�g�̈ʒu������
//============================================================================
void CPlayerStateMistook::FindStartObject()
{
	// �X�^�[�g�I�u�W�F�N�g���擾
	CStart* pStart{ CUtility::GetInstance()->DownCast<CStart, CObject>(CObject::FindObject(CObject::TYPE::START)) };

	if (pStart == nullptr)
	{ // �������s
		assert(false);
	}

	// �X�^�[�g���W���R�s�[
	m_PosStartObject = pStart->GetActualPos();
}

//============================================================================
// ���X�|�[��
//============================================================================
void CPlayerStateMistook::Respawn()
{
	// �V�����ڕW���W���쐬
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };

	// �v���C���[�̍��W���X�^�[�g�̍��W�ƈقȂ��
	if (NewPosTarget != m_PosStartObject)
	{
		// �v���C���[���W�ƃX�^�[�g�ʒu�̍�������o��
		D3DXVECTOR3 Distance{ m_PosStartObject - NewPosTarget };

		// �������ȏ゠��ΐ�����t����
		if (Distance.x > MAX_WARP_SPEED)
		{
			Distance.x = MAX_WARP_SPEED;
		}
		else if (Distance.x < -MAX_WARP_SPEED)
		{
			Distance.x = -MAX_WARP_SPEED;
		}

		if (Distance.y > MAX_WARP_SPEED)
		{
			Distance.y = MAX_WARP_SPEED;
		}
		else if (Distance.y < -MAX_WARP_SPEED)
		{
			Distance.y = -MAX_WARP_SPEED;
		}

		// �����k�߂č��W��␳���Ă���
		NewPosTarget += Distance;

		// �ڕW���W��ݒ肷��
		m_pPlayer->SetPosTarget(NewPosTarget);

		// �k�������Ă���
		m_pPlayer->SetScale(CUtility::GetInstance()->AdjustToTarget(m_pPlayer->GetScale(), 0.0f, 0.1f));
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
	// �^������ɉ����x��ݒ�
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };
	NewVelocity.y += 10.0f;
	m_pPlayer->SetVelocity(NewVelocity);

	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_007) };

	// ���f���̐ݒ�
	m_pPlayer->BindModel(Model);

	// �T�C�Y��ݒ�
	m_pPlayer->SetSize(Model->size);
}

//============================================================================
// �X�V
//============================================================================
void CPlayerStateGoal::Update()
{
	// Y��������������]���AZ�����������Z�b�g
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	NewRot.y += 0.1f;
	NewRot.z = 0.0f;
	m_pPlayer->SetRot(NewRot);

	// �����x������
	m_pPlayer->SetVelocity(CUtility::GetInstance()->AdjustToTarget(m_pPlayer->GetVelocity(), D3DXVECTOR3{ 0.0f, 0.0f, 0.0f }, 0.05f));

	// �����x���A�ڕW���W��ϓ�
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
	NewPosTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(NewPosTarget);

	// �k�������Ă���
	m_pPlayer->SetScale(CUtility::GetInstance()->AdjustToTarget(m_pPlayer->GetScale(), 0.0f, 0.035f));

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
CPlayerStateManager::CPlayerStateManager() :
	m_pPlayer{ nullptr },
	m_pState{ nullptr },
	m_PendingState{ CPlayerState::STATE::NONE }
{

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