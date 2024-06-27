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
#include "manager.h"
#include "physics.h"
#include "block.h"
#include "explosion.h"
#include "explosion3D.h"
#include "particle.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
const float CPlayerStateDefault::MAX_WALK_VELOCITY = 0.5f;	// ���s���̍ő�����x
const float CPlayerStateDefault::BRAKING_WALK_SPEED = 0.9f;	// ���s���̐�����
const int CPlayerStateBeginning::BEGIN_CNT_MAX = 30;		// �ϐg�K�v����
const float CPlayerStateFlying::MAX_FLY_VELOCITY = 1.5f;	// ��s���̍ő�����x
const int CPlayerStateStopping::STOP_CNT_MAX = 30;			// �ϐg��~�K�v����

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

		// ������
		m_pStateManager->Init();
	}

	// �v���C���[�̃C���X�^���X������ԊǗ��N���X�ɓn��
	m_pStateManager->SetPlayerInstance(this);

	// �v���C���[�̃C���X�^���X������ԃN���X�ɓn��
	m_pStateManager->GetState()->SetPlayerInstance(this);

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

	// �ʒu��ݒ�
	SetPos(m_posTarget);

	// �����蔻���͈͐����Ȃǈʒu�����A���̏����̏I���ɖڕW�ʒu�𔽉f������
	//AdjustPos();

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

	// ���f����ݒ�
	pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_000));

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

	//// ��ʂ̉��[�ɓ��B�ŉ��~����
	//if (m_posTarget.y < 0.0f)
	//{
	//	// �ʒu�����[�ɐݒ�
	//	m_posTarget.y = 0.0f;

	//	// Y�������̉����x�����Z�b�g
	//	m_velocity.y = 0.0f;

	//	// �n�ʂ����o
	//	bDetected = true;
	//}

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
				if (CPhysics::GetInstance()->Cube(m_posTarget, GetSize(), pBlock->GetPos(), BlockSize))
				{
					// �����o������
					CPhysics::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), GetSize(), pBlock->GetPos(), BlockSize);

					// �Փ˔�����o��
					bDetected = 1;
				}
			}
		}
	}

	return bDetected;
}



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
// �����ݒ�
//============================================================================
void CPlayerState::Init()
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
// �J�n
//============================================================================
void CPlayerStateDefault::Init()
{
	// ���N���X�̏����ݒ�
	CPlayerState::Init();
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
}

//============================================================================
// �I��
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

	// �����ڂ�ύX
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_001));

	// �����𐶐�
	CExplosion3D::Create(
		m_pPlayer->GetPos(),		// �ʒu
		{ 30.0f, 0.0f, 30.0f });	// �T�C�Y
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
		// ��ԕύX
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::BEGINNING);

		return false;
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
	velocity = velocity * BRAKING_WALK_SPEED;

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
// �J�n
//============================================================================
void CPlayerStateBeginning::Init()
{
	// ���N���X�̏����ݒ�
	CPlayerState::Init();
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
		posTarget.y += 1.0f;
		m_pPlayer->SetPosTarget(posTarget);

		// Y����������]���AZ����]��������
		D3DXVECTOR3 rot = m_pPlayer->GetRot();
		rot.y = posTarget.y * 0.25f;
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
// �I��
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

	// �����ڂ�ύX
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_002));
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
// �J�n
//============================================================================
void CPlayerStateFlying::Init()
{
	// ���N���X�̏����ݒ�
	CPlayerState::Init();
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
// �I��
//============================================================================
void CPlayerStateFlying::Exit()
{
	// �����x��������
	m_pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });

	//// Z����]��������
	//D3DXVECTOR3 rot = m_pPlayer->GetRot();
	//rot.z = 0.0f;
	//m_pPlayer->SetRot(rot);

	// �����ڂ�ύX
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_003));

	// �����𐶐�
	CExplosion3D::Create(
		m_pPlayer->GetPos(),		// �ʒu
		{ 30.0f, 0.0f, 30.0f });	// �T�C�Y
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
	velocity.x += sinf(m_pPlayer->GetAngleFlying()) * 0.1f;
	velocity.y += cosf(m_pPlayer->GetAngleFlying()) * 0.1f;
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
// �J�n
//============================================================================
void CPlayerStateStopping::Init()
{
	// ���N���X�̏����ݒ�
	CPlayerState::Init();
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

		// ����
		Recoil();

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
// �I��
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
	velocity.x += -sinf(m_pPlayer->GetAngleFlying()) * 0.04f;
	velocity.y += -cosf(m_pPlayer->GetAngleFlying()) * 0.04f;

	m_pPlayer->SetVelocity(velocity);
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
	ChangeState(CPlayerState::STATE::DEFAULT);
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
		// �I��������̏���
		m_pState->Exit();

		// �����������
		delete m_pState;

		// �|�C���^��������
		m_pState = nullptr;
	}

	// ���̏�Ԃ𐶐�
	Create(state);

	m_pState->SetPlayerInstance(m_pPlayer);

	// ��Ԃ̏����ݒ�
	m_pState->Init();
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

	default:
		assert(false);
		break;
	}
}