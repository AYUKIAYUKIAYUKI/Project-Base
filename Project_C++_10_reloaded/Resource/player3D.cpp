//============================================================================
// 
// 3D�v���C���[ [player3D.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "player3D.h"
#include "manager.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
const float CPlayer3D::MAX_VELOCITY = 0.5f;		// �����x���
const float CPlayer3D::BRAKING_FORCE = 0.9f;	// ������

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer3D::CPlayer3D() : CObjectX(static_cast<int>(LAYER::FRONT_MIDDLE))
{
	m_velocity = { 0.0f, 0.0f, 0.0f };		// �����x
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW�ʒu
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW����
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayer3D::~CPlayer3D()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CPlayer3D::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObjectX::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CPlayer3D::Uninit()
{
	// ���N���X�̏I������
	CObjectX::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CPlayer3D::Update()
{
	// ���݈ʒu���擾�A�ȍ~���̃R�s�[��ڕW�ʒu�Ƃ��ĕύX�������Ă���
	m_posTarget = CObjectX::GetPos();

	// ����
	Control();

	// ��]
	Rotation();

	// ��������
	Braking();

	// �ʒu�𒲐��A���̏����̏I���ɖڕW�ʒu�𔽉f������
	AdjustPos();

	// ���N���X�̍X�V
	CObjectX::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CPlayer3D::Draw()
{
	// ���N���X�̕`�揈��
	CObjectX::Draw();
}

//============================================================================
// ����
//============================================================================
CPlayer3D* CPlayer3D::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X�𐶐�
	CPlayer3D* pPlayer3D = new CPlayer3D;

	if (pPlayer3D == nullptr)
	{ // �������s
		assert(false);
	}

	pPlayer3D->SetType(TYPE::PLAYER);	// �^�C�v��ݒ�

	pPlayer3D->Init();			// ���N���X�̏����ݒ�
	pPlayer3D->SetPos(pos);		// ���S�ʒu�̐ݒ�

	// ���f����ݒ�
	pPlayer3D->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel::MODEL_TYPE::MODEL_BLOCK));

	return pPlayer3D;
}

//============================================================================
// ����
//============================================================================
void CPlayer3D::Control()
{
	// ���X�e�B�b�N�擾
	CInputPad* pPad = CManager::GetPad();
	CInputPad::JOYSTICK Stick = pPad->GetJoyStickL();

	// ���͂�����Έړ�
	if (Stick.X != 0 || Stick.Y != 0)
	{
		// �ړ��ʂƖڕW��]�ʂ�ݒ�
		m_velocity.x += sinf(atan2f((float)Stick.X, (float)-Stick.Y));
		m_velocity.z += cosf(atan2f((float)Stick.X, (float)-Stick.Y));
		m_rotTarget.y = atan2f((float)-Stick.X, (float)Stick.Y);
	}

	// �L�[�{�[�h�擾
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// �ړ������p
	bool bMove = 0;
	float X = 0.0f;
	float Z = 0.0f;

	// X��
	if (pKeyboard->GetPress(DIK_A))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{
		X = 1.0f;
	}

	// Z��
	if (pKeyboard->GetPress(DIK_W))
	{
		Z = 1.0f;
	}
	else if (pKeyboard->GetPress(DIK_S))
	{
		Z = -1.0f;
	}

	// �������͂��Ă���Έړ�������o��
	if (X != 0.0f || Z != 0.0f)
	{
		bMove = true;
	}

	if (bMove)
	{
		// �ړ��ʂƖڕW��]�ʂ�ݒ�
		m_velocity.x += sinf(atan2f(X, Z) + CManager::GetCamera()->GetRot().y)* 0.1f;
		//m_velocity.x += -sinf(m_rotTarget.y);
		//float f = atan2f(X, Z);
		//float roty = CManager::GetCamera()->GetRot().y;
		//float iofjioeaf = sinf(atan2f(X, Z) + CManager::GetCamera()->GetRot().y);
		m_velocity.z += cosf(atan2f(X, Z) + CManager::GetCamera()->GetRot().y) * 0.1f;
		//m_velocity.z += -cosf(m_rotTarget.y);
		m_rotTarget.y = atan2f(-X, -Z) + CManager::GetCamera()->GetRot().y;
	}
}

//============================================================================
// ��]
//============================================================================
void CPlayer3D::Rotation()
{
	// �������擾
	D3DXVECTOR3 rot = CObjectX::GetRot();

	// �u���[�L��
	float fStopEnergy = 0.1f;

	// ��]���f�Ɖ�]�ʂ̌���
	if (m_rotTarget.y - rot.y > D3DX_PI)
	{
		rot.y += ((m_rotTarget.y - rot.y) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (m_rotTarget.y - rot.y < -D3DX_PI)
	{
		rot.y += ((m_rotTarget.y- rot.y) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.y += ((m_rotTarget.y - rot.y) * fStopEnergy);
	}

	// �������ݒ�
	CObjectX::SetRot(rot);
}

//============================================================================
// ��������
//============================================================================
void CPlayer3D::Braking()
{
	// �����x����ɓ��B�ő��x�Œ�
	//if (m_velocity.x > CPlayer3D::MAX_VELOCITY)
	//{
	//	m_velocity.x = CPlayer3D::MAX_VELOCITY;
	//}
	//else if (m_velocity.x < -CPlayer3D::MAX_VELOCITY)
	//{
	//	m_velocity.x = -CPlayer3D::MAX_VELOCITY;
	//}

	//if (m_velocity.z > CPlayer3D::MAX_VELOCITY)
	//{
	//	m_velocity.z = CPlayer3D::MAX_VELOCITY;
	//}
	//else if (m_velocity.z < -CPlayer3D::MAX_VELOCITY)
	//{
	//	m_velocity.z = -CPlayer3D::MAX_VELOCITY;
	//}

	// �����������x������
	m_velocity = m_velocity * CPlayer3D::BRAKING_FORCE;
}

//============================================================================
// �ʒu����
//============================================================================
void CPlayer3D::AdjustPos()
{
	// �����x���ʒu��ϓ�
	m_posTarget += m_velocity;

	// ���S�ʒu����ݒ�
	CObjectX::SetPos(m_posTarget);
}