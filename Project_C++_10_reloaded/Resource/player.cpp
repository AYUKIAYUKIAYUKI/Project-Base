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
#include "explosion3D.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
const float CPlayer::MAX_VELOCITY = 0.5f;	// �����x���
const float CPlayer::JUMP_FORCE = 6.0f;		// �W�����v��
const float CPlayer::BRAKING_FORCE = 0.9f;	// ������

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer() : CObjectX(static_cast<int>(LAYER::FRONT_MIDDLE))
{
	m_nLeftNumJump = 0;						// �W�����v�\��
	m_velocity = { 0.0f, 0.0f, 0.0f };		// �����x
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW�ʒu
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW����

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
	HRESULT hr = CObjectX::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CPlayer::Uninit()
{
	// ���N���X�̏I������
	CObjectX::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CPlayer::Update()
{
	// ���݈ʒu���擾�A�ȍ~���̃R�s�[��ڕW�ʒu�Ƃ��ĕύX�������Ă���
	m_posTarget = CObjectX::GetPos();

	// ����
	Control();

	// ��]
	Rotation();

	// ��������
	Braking();

	// �d�͉���
	GravityFall();

	// �ʒu�𒲐��A���̏����̏I���ɖڕW�ʒu�𔽉f������
	AdjustPos();

	// ���N���X�̍X�V
	CObjectX::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CPlayer::Draw()
{
	// ���N���X�̕`�揈��
	CObjectX::Draw();
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
	pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::MODEL_PLAYER));

	return pPlayer;
}

//============================================================================
// ����
//============================================================================
void CPlayer::Control()
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
	else
	{ // �e�X�g�p
		m_nTestExplosionCnt = 19;
	}

	if (bMove)
	{
		// �ړ��ʂƖڕW��]�ʂ�ݒ�
		m_velocity.x += sinf(atan2f(X, Z) + CManager::GetCamera()->GetRot().y) * 0.1f;
		m_velocity.z += cosf(atan2f(X, Z) + CManager::GetCamera()->GetRot().y) * 0.1f;
		m_rotTarget.y = atan2f(-X, -Z) + CManager::GetCamera()->GetRot().y;

		// �e�X�g�p
		m_nTestExplosionCnt > 20 ? m_nTestExplosionCnt = 0, (int)CExplosion3D::Create({ GetPos().x, GetPos().y + 3.0f, GetPos().z }, { 7.5f, 0.0f, 7.5f }) : m_nTestExplosionCnt++;
	}

	// �W�����v
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		if (m_nLeftNumJump > 0)
		{ // �W�����v�\�񐔂��c���Ă����

			// Y�������̉����x��������֌Œ�
			m_velocity.y = JUMP_FORCE;

			// �W�����v�\�񐔂�����
			m_nLeftNumJump--;
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
	// 
	//// �����x����ɓ��B�ő��x�Œ�
	//if (m_velocity.x > CPlayer::MAX_VELOCITY)
	//{
	//	m_velocity.x = CPlayer::MAX_VELOCITY;
	//}
	//else if (m_velocity.x < -CPlayer::MAX_VELOCITY)
	//{
	//	m_velocity.x = -CPlayer::MAX_VELOCITY;
	//}

	//if (m_velocity.z > CPlayer::MAX_VELOCITY)
	//{
	//	m_velocity.z = CPlayer::MAX_VELOCITY;
	//}
	//else if (m_velocity.z < -CPlayer::MAX_VELOCITY)
	//{
	//	m_velocity.z = -CPlayer::MAX_VELOCITY;
	//}

	// �����������x������
	m_velocity = m_velocity * CPlayer::BRAKING_FORCE;
}

//============================================================================
// �d�͗���
//============================================================================
void CPlayer::GravityFall()
{
	// �d�͕��A�������ւ̉����x����
	m_velocity.y = m_velocity.y - GRAVITY_FORCE;
}

//============================================================================
// �ʒu����
//============================================================================
void CPlayer::AdjustPos()
{
	// �����x���ʒu��ϓ�
	m_posTarget += m_velocity;

	// �����蔻��
	Collision();

	// ��ʂ̉��[�ɓ��B�ŉ��~����
	if (m_posTarget.y < 0.0f)
	{
		// �W�����v�\�񐔂�ݒ�
		m_nLeftNumJump = 2;

		// �ʒu�����[�ɐݒ�
		m_posTarget.y = 0.0f;

		// Y�������̉����x�����Z�b�g
		m_velocity.y = 0.0f;
	}

	// �ʒu��ݒ�
	SetPos(m_posTarget);
}

//============================================================================
// �����蔻��
//============================================================================
void CPlayer::Collision()
{
	// �u���b�N�T�C�Y
	float fHalfSizeBlock = 10.0f;

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
				if (m_posTarget.x + fHalfSizeBlock >= pBlock->GetPos().x - fHalfSizeBlock &&
					m_posTarget.x - fHalfSizeBlock <= pBlock->GetPos().x + fHalfSizeBlock &&
					m_posTarget.z + fHalfSizeBlock >= pBlock->GetPos().z - fHalfSizeBlock &&
					m_posTarget.z - fHalfSizeBlock <= pBlock->GetPos().z + fHalfSizeBlock &&
					m_posTarget.y + fHalfSizeBlock >= pBlock->GetPos().y - fHalfSizeBlock &&
					m_posTarget.y - fHalfSizeBlock <= pBlock->GetPos().y + fHalfSizeBlock)
				{
					// �ߋ��̈ʒu�Ő������ɏՓ˂��Ă����̂�����
					if (GetPos().y + fHalfSizeBlock > pBlock->GetPos().y - fHalfSizeBlock &&
						GetPos().y - fHalfSizeBlock < pBlock->GetPos().y + fHalfSizeBlock)
					{
						// �ߋ��̈ʒu���ǂ��炩�̎������ɏd�Ȃ��Ă������ŏ�������
						if (GetPos().x + fHalfSizeBlock > pBlock->GetPos().x - fHalfSizeBlock &&
							GetPos().x - fHalfSizeBlock < pBlock->GetPos().x + fHalfSizeBlock)
						{
							if (GetPos().z < pBlock->GetPos().z)
							{
								// �ʒu�����̃u���b�N�̌�[�ɐݒ�
								m_posTarget.z = -fHalfSizeBlock + (pBlock->GetPos().z - fHalfSizeBlock);
							}
							else if (GetPos().z > pBlock->GetPos().z)
							{
								// �ʒu�����̃u���b�N�̑O�[�ɐݒ�
								m_posTarget.z = fHalfSizeBlock + (pBlock->GetPos().z + fHalfSizeBlock);
							}

							// Z�������̉����x�����Z�b�g
							m_velocity.z = 0.0f;
						}
						else if (GetPos().z + fHalfSizeBlock > pBlock->GetPos().z - fHalfSizeBlock &&
							GetPos().z - fHalfSizeBlock < pBlock->GetPos().z + fHalfSizeBlock)
						{
							if (GetPos().x < pBlock->GetPos().x)
							{
								// �ʒu�����̃u���b�N�̍��[�ɐݒ�
								m_posTarget.x = -fHalfSizeBlock + (pBlock->GetPos().x - fHalfSizeBlock);
							}
							else if (GetPos().x > pBlock->GetPos().x)
							{
								// �ʒu�����̃u���b�N�̉E�[�ɐݒ�
								m_posTarget.x = fHalfSizeBlock + (pBlock->GetPos().x + fHalfSizeBlock);
							}

							// X�������̉����x�����Z�b�g
							m_velocity.x = 0.0f;
						}
					}
					else if (GetPos().x + fHalfSizeBlock > pBlock->GetPos().x - fHalfSizeBlock &&
						GetPos().x - fHalfSizeBlock < pBlock->GetPos().x + fHalfSizeBlock &&
						GetPos().z + fHalfSizeBlock > pBlock->GetPos().z - fHalfSizeBlock &&
						GetPos().z - fHalfSizeBlock < pBlock->GetPos().z + fHalfSizeBlock)
					{
						if (GetPos().y < pBlock->GetPos().y)
						{
							// �ʒu�����̃u���b�N�̉��[�ɐݒ�
							m_posTarget.y = -fHalfSizeBlock + (pBlock->GetPos().y - fHalfSizeBlock);
						}
						else if (GetPos().y > pBlock->GetPos().y)
						{
							// �ʒu�����̃u���b�N�̏�[�ɐݒ�
							m_posTarget.y = fHalfSizeBlock + (pBlock->GetPos().y + fHalfSizeBlock);

							// �W�����v�\�񐔂�ݒ�
							m_nLeftNumJump = 2;
						}

						// Y�������̉����x�����Z�b�g
						m_velocity.y = 0.0f;
					}
				}
			}
		}
	}
}