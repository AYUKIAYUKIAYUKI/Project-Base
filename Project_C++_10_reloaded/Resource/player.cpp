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
#include "block.h"
#include "explosion.h"
#include "explosion3D.h"
#include "particle.h"

// �e�X�g
#include "physics.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
const float CPlayer::MAX_VELOCITY = 0.5f;	// �����x���
const float CPlayer::JUMP_FORCE = 6.0f;		// �W�����v��
const float CPlayer::BRAKING_FORCE = 0.9f;	// ������

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer() : CObject_X(static_cast<int>(LAYER::FRONT_MIDDLE))
{
	m_state = STATE::NONE;					// ���
	m_bMetamorphose = 0;					// �ϐg����
	m_nCntMetamorphose = 0;					// �ϐg����
	m_velocity = { 0.0f, 0.0f, 0.0f };		// �����x
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW�ʒu
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW����
	m_fAngleFlying = 0.0f;					// ��s����

	m_nTestExplosionCnt = 0;	// ����̓e�X�g�p�ł�
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

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CPlayer::Uninit()
{
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
	
	if (!m_bMetamorphose)
	{
		// ���s
		Walking();

		// ��]
		Rotation();

		// ��������
		Braking();

		// �d�͗���
		CPhysics::GetInstance()->Gravity(m_velocity);
	}
	else
	{
		// ��s
		Flying();

		// ����
		Rolling();

		// ��C��R
		AirResistance();
	}

	// �ʒu�𒲐��A���̏����̏I���ɖڕW�ʒu�𔽉f������
	AdjustPos();

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
	pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::MODEL_PLAYER_000));

	return pPlayer;
}

//============================================================================
// ���s
//============================================================================
void CPlayer::Walking()
{
	// ���X�e�B�b�N�擾
	CInputPad* pPad = CManager::GetPad();
	CInputPad::JOYSTICK Stick = pPad->GetJoyStickL();

	// ���͂�����Έړ�
	if (Stick.X != 0 || Stick.Y != 0)
	{
		// �ړ��ʂƖڕW��]�ʂ�ݒ�
		m_velocity.x += sinf(atan2f((float)Stick.X, 0.0f));
		m_rotTarget.y = atan2f((float)-Stick.X, 0.0f);
	}

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
	else
	{ // �e�X�g�p
		m_nTestExplosionCnt = 39;
	}

	if (bMove)
	{
		// �ړ��ʂƖڕW��]�ʂ�ݒ�
		m_velocity.x += sinf(atan2f(X, 0.0f));
		m_rotTarget.y = atan2f(X, 0.0f);

		// �e�X�g�p
		m_nTestExplosionCnt > 40 ? m_nTestExplosionCnt = 0, (int)CExplosion3D::Create({ GetPos().x, GetPos().y + 3.0f, GetPos().z }, { 7.5f, 0.0f, 7.5f }) : m_nTestExplosionCnt++;
	}

	// �ϐg
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		if (!m_bMetamorphose)
		{
			// �ϐg������o��
			m_bMetamorphose = 1;

			// �ϐg���Ԃ�ݒ�
			m_nCntMetamorphose = 30;

			// �����x��������
			m_velocity = { 0.0f, 0.0f, 0.0f };

			// ��s������������
			m_fAngleFlying = 0.0f;

			// Z����]��������
			m_rotTarget.z = 0.0f;
			SetRot({ GetRot().x, GetRot().y, 0.0f });

			// �����ڂ�ύX
			BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::MODEL_PLAYER_001));

			// �����𐶐�
			CExplosion3D::Create(
				{ GetPos().x, GetPos().y, GetPos().z },	// �ʒu
				{ 30.0f, 0.0f, 30.0f });				// �T�C�Y
		}
	}
}

//============================================================================
// ��]
//============================================================================
void CPlayer::Rotation()
{
	// �������擾
	D3DXVECTOR3 rot = GetRot();

	// �u���[�L��
	float fStopEnergy = 0.1f;

	// ��]���f�Ɖ�]�ʂ̌���
	if (m_rotTarget.y - rot.y > D3DX_PI)
	{
		rot.y += ((m_rotTarget.y - rot.y) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (m_rotTarget.y - rot.y < -D3DX_PI)
	{
		rot.y += ((m_rotTarget.y - rot.y) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.y += ((m_rotTarget.y - rot.y) * fStopEnergy);
	}

	// �������ݒ�
	SetRot(rot);
}

//============================================================================
// ��������
//============================================================================
void CPlayer::Braking()
{
	// �����x����ɓ��B�ő��x�Œ�
	if (m_velocity.x > CPlayer::MAX_VELOCITY)
	{
		m_velocity.x = CPlayer::MAX_VELOCITY;
	}
	else if (m_velocity.x < -CPlayer::MAX_VELOCITY)
	{
		m_velocity.x = -CPlayer::MAX_VELOCITY;
	}

	// �����������x������
	m_velocity = m_velocity * CPlayer::BRAKING_FORCE;
}

//============================================================================
// ��s
//============================================================================
void CPlayer::Flying()
{
	// ���X�e�B�b�N�擾
	CInputPad* pPad = CManager::GetPad();
	CInputPad::JOYSTICK Stick = pPad->GetJoyStickL();

	// ���͂�����Έړ�
	if (Stick.X != 0 || Stick.Y != 0)
	{
		// �ڕW������ݒ�
		m_rotTarget.z = atan2f((float)-Stick.X, (float)-Stick.Y);

		// ��s������ݒ�
		m_fAngleFlying = atan2f((float)Stick.X, (float)-Stick.Y);
	}

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
	else
	{ // �e�X�g�p
		m_nTestExplosionCnt = 2;
	}

	if (bMove)
	{
		// �ڕW������ݒ�
		m_rotTarget.z = atan2f(-X, Y);

		// ��s������ݒ�
		m_fAngleFlying = atan2f(X, Y);

		// �e�X�g�p
		m_nTestExplosionCnt > 3 ? m_nTestExplosionCnt = 0, (int)CExplosion3D::Create({ GetPos().x, GetPos().y + 3.0f, GetPos().z }, { 7.5f, 0.0f, 7.5f }) : m_nTestExplosionCnt++;
	}

	// ��s�����ɓːi
	m_velocity.x += sinf(m_fAngleFlying) * 0.1f;
	m_velocity.y += cosf(m_fAngleFlying) * 0.1f;
}

//============================================================================
// ����
//============================================================================
void CPlayer::Rolling()
{
	// �������擾
	D3DXVECTOR3 rot = GetRot();

	// �u���[�L��
	float fStopEnergy = 0.1f;

	// ��]���f�Ɖ�]�ʂ̌���
	if (m_rotTarget.z - rot.z > D3DX_PI)
	{
		rot.z += ((m_rotTarget.z - rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (m_rotTarget.z - rot.z < -D3DX_PI)
	{
		rot.z += ((m_rotTarget.z - rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.z += ((m_rotTarget.z - rot.z) * fStopEnergy);
	}

	// �������ݒ�
	SetRot(rot);
}

//============================================================================
// ��C��R
//============================================================================
void CPlayer::AirResistance()
{
	float ����̓e�X�g�p = 2.0f;

	// �����x����ɓ��B�ő��x�Œ�
	if (m_velocity.x > ����̓e�X�g�p)
	{
		m_velocity.x = ����̓e�X�g�p;
	}
	else if (m_velocity.x < -����̓e�X�g�p)
	{
		m_velocity.x = -����̓e�X�g�p;
	}

	if (m_velocity.y > ����̓e�X�g�p)
	{
		m_velocity.y = ����̓e�X�g�p;
	}
	else if (m_velocity.y < -����̓e�X�g�p)
	{
		m_velocity.y = -����̓e�X�g�p;
	}
}

//============================================================================
// �ʒu����
//============================================================================
void CPlayer::AdjustPos()
{
	if (m_nCntMetamorphose > 0)
	{
		m_nCntMetamorphose--;

		// �ϐg���Ԓ��͋����㏸
		m_posTarget.y += 1.0f;

		// Y����������]���AZ����]��������
		SetRot({ GetRot().x, m_posTarget.y * 0.25f, 0.0f });

		// �ǂ����悤
		if (m_nCntMetamorphose == 0)
		{
			// �����x��������
			m_velocity = { 0.0f, 0.0f, 0.0f };

			// ��s������������
			m_fAngleFlying = 0.0f;

			// Z����]�ڕW��������
			m_rotTarget.z = 0.0f;

			// Y����]��������
			SetRot({ GetRot().x, 0.0f, GetRot().z });
		}
	}
	else
	{	
		// �����x���ʒu��ϓ�
		m_posTarget += m_velocity;
	}

	// �����蔻��
	if (Collision())
	{
		// �ϐg����
		FinishTransform();
	}

	// ��ʂ̉��[�ɓ��B�ŉ��~����
	if (m_posTarget.y < 0.0f)
	{
		// �ʒu�����[�ɐݒ�
		m_posTarget.y = 0.0f;

		// Y�������̉����x�����Z�b�g
		m_velocity.y = 0.0f;

		// �ϐg����
		FinishTransform();
	}

	// �ʒu��ݒ�
	SetPos(m_posTarget);
}

//============================================================================
// �����蔻��
//============================================================================
bool CPlayer::Collision()
{
	// �Փ˔���
	bool bDetected = 0;

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
				if(CPhysics::GetInstance()->Cube(m_posTarget, { 10.0f, 10.0f ,10.0f }, pBlock->GetPos(), { 10.0f, 10.0f ,10.0f }))
				{
					// �����o������
					CPhysics::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), { 10.0f, 10.0f ,10.0f }, pBlock->GetPos(), { 10.0f, 10.0f ,10.0f });

					// �Փ˔�����o��
					bDetected = 1;
				}
			}
		}
	}

	return bDetected;
}

//============================================================================
// �ϐg����
//============================================================================
void CPlayer::FinishTransform()
{
	if (m_bMetamorphose)
	{
		// �ϐg���������
		m_bMetamorphose = 0;

		// �����x��������
		m_velocity = { 0.0f, 0.0f, 0.0f };

		// Z����]��������
		m_rotTarget.z = 0.0f;
		SetRot({ GetRot().x, GetRot().y, 0.0f });

		// �����ڂ�ύX
		BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::MODEL_PLAYER_000));

		// �����𐶐�
		CExplosion3D::Create(
			{ GetPos().x, GetPos().y, GetPos().z },	// �ʒu
			{ 30.0f, 0.0f, 30.0f });				// �T�C�Y

		// �����𐶐�
		Recoil();

		// ��s������������
		m_fAngleFlying = 0.0f;
	}
}

//============================================================================
// ����
//============================================================================
void CPlayer::Recoil()
{
	//// ��s�����̋t�ɓːi
	//m_velocity.x += sinf(m_fAngleFlying + D3DX_PI) * 10.0f;
	//m_velocity.y += cosf(m_fAngleFlying + D3DX_PI) * 10.0f;
}