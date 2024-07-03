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
#include "bullet.h"
#include "enemy.h"
#include "item.h"
#include "particle.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
const int CPlayer::TEXTURE_DIVIDE_U = 30;		// �e�N�X�`����U����������
const int CPlayer::TEXTURE_DIVIDE_V = 1;		// �e�N�X�`����V����������
const float CPlayer::MAX_VELOCITY = 3.0f;		// �����x���
const float CPlayer::JUMP_FORCE = -10.;			// �W�����v��
const float CPlayer::BRAKING_FORCE = 0.9f;		// ������

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer() : CObject2D(static_cast<int>(LAYER::FRONT_MIDDLE))
{
	m_nCntTexChange = 0;					// �e�N�X�`���ύX�Ǘ�
	m_nLeftNumJump = 0;						// �W�����v�\��
	m_velocity = { 0.0f, 0.0f, 0.0f };		// �����x
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW�ʒu
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW����

	m_bAnimationLock = false;	// ( �����I )
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
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CPlayer::Uninit()
{
	// ���N���X�̏I������
	CObject2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CPlayer::Update()
{
	// ���݈ʒu���擾�A�ȍ~���̃R�s�[��ڕW�ʒu�Ƃ��ĕύX�������Ă���
	m_posTarget = CObject2D::GetPos();

	// ����
	Control();

	// ��������
	Braking();

	// �d�͉���
	GravityFall();

	// �ʒu�𒲐��A���̏����̏I���ɖڕW�ʒu�𔽉f������
	AdjustPos();

	// �A�j���[�V����
	Animation();

	// ���N���X�̍X�V
	CObject2D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CPlayer::Draw()
{
	// ���N���X�̕`�揈��
	CObject2D::Draw();
}

//============================================================================
// ����
//============================================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X�𐶐�
	CPlayer* pPlayer = new CPlayer;

	if (pPlayer == nullptr)
	{ // �������s
		assert(false);
	}

	pPlayer->SetType(TYPE::PLAYER);	// �^�C�v��ݒ�

	pPlayer->Init();		// ���N���X�̏����ݒ�
	pPlayer->SetPos(pos);	// ���S�ʒu�̐ݒ�
	pPlayer->SetSize(size);	// �T�C�Y�̐ݒ�

	pPlayer->SetTexWidth(1.0f / (float)CPlayer::TEXTURE_DIVIDE_U);	// ���e�N�X�`��������
	pPlayer->SetTexHeight(1.0f / (float)CPlayer::TEXTURE_DIVIDE_V);	// �c�e�N�X�`�����c��

	// �e�N�X�`����ݒ�
	pPlayer->BindTex(CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::PLAYER_000));

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
	}

	// �L�[�{�[�h�擾
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// �ړ������p
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

	// Y��
	if (pKeyboard->GetPress(DIK_W))
	{
		Y = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_S))
	{
		Y = 1.0f;
	}

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
		m_velocity.x += sinf(atan2f(X, Y));
	}

	// �W�����v
	if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::X))
	{
		if (m_nLeftNumJump > 0)
		{ // �W�����v�\�񐔂��c���Ă����

			// Y�������̉����x��������֌Œ�
			m_velocity.y = CPlayer::JUMP_FORCE;

			// �W�����v�\�񐔂�����
			m_nLeftNumJump--;
		}
	}

	// �f�o�b�O�p�ɃT�E���h�Đ� (�L�[�{�[�h�A�p�b�h�擾������̂ł�����)
	if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::B))
	{
		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_00);

		// ���܂��ɒe�̐���
		CBullet::Create(
			m_posTarget,			// ���S�ʒu
			{ 15.0f, 15.0f, 0.0f },	// �T�C�Y
			100,					// �g�p����
			0.0f);					// ��Ԋp�x
	}
}

////============================================================================
//// �g�k
////============================================================================
//void CPlayer::Scaling()
//{
//
//}
//
////============================================================================
//// ��]
////============================================================================
//void CPlayer::Rotation()
//{
//	//// �������擾
//	//D3DXVECTOR3 rot = CObject2D::GetRot();
//
//	//// �u���[�L��
//	//float fStopEnergy = 0.1f;
//
//	//// ��]���f�Ɖ�]�ʂ̌���
//	//if (m_rotTarget.z - rot.z > D3DX_PI)
//	//{
//	//	rot.z += ((m_rotTarget.z - rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
//	//}
//	//else if (m_rotTarget.z - rot.z < -D3DX_PI)
//	//{
//	//	rot.z += ((m_rotTarget.z - rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
//	//}
//	//else
//	//{
//	//	rot.z += ((m_rotTarget.z - rot.z) * fStopEnergy);
//	//}
//
//	//// �������ݒ�
//	//CObject2D::SetRot(rot);
//}
//
////============================================================================
//// �ړ�
////============================================================================
//void CPlayer::Translation()
//{
//
//}

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

	// ��������X�������ւ̉����x������
	m_velocity.x = m_velocity.x * CPlayer::BRAKING_FORCE;
}

//============================================================================
// �d�͗���
//============================================================================
void CPlayer::GravityFall()
{
	// �d�͕��A�������ւ̉����x����
	m_velocity.y = m_velocity.y + CObject::GRAVITY_FORCE;
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

	// �T�C�Y���擾
	D3DXVECTOR3 fSize = CObject2D::GetSize();

	// ��ʂ̍��E�[�ɓ��B�ł��ꂼ�ꃋ�[�v
	if (m_posTarget.x - fSize.x > SCREEN_WIDTH)
	{
		// �ʒu�����[�֐ݒ�
		m_posTarget.x = 0.0f - fSize.x;
	}
	else if (m_posTarget.x + fSize.x < 0.0f)
	{
		// �ʒu���E�[�֐ݒ�
		m_posTarget.x = SCREEN_WIDTH + fSize.x;
	}

	// ��ʂ̉��[�ɓ��B�ŉ��~����
	if (m_posTarget.y + fSize.y > SCREEN_HEIGHT)
	{
		// �W�����v�\�񐔂�ݒ�
		m_nLeftNumJump = 2;

		// �ʒu�����[�ɐݒ�
		m_posTarget.y = SCREEN_HEIGHT - fSize.y;

		// Y�������̉����x�����Z�b�g
		m_velocity.y = 0.0f;
	}

	// ���S�ʒu����ݒ�
	CObject2D::SetPos(m_posTarget);
}

//============================================================================
// �����蔻��
//============================================================================
void CPlayer::Collision()
{
	D3DXVECTOR3 copy = m_posTarget;

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

#if 0
				// �u���b�N�ƏՓ˂���ꍇ
				if (m_posTarget.x + CObject2D::GetSize().x >= pBlock->GetPos().x - pBlock->GetSize().x &&
					m_posTarget.x - CObject2D::GetSize().x <= pBlock->GetPos().x + pBlock->GetSize().x &&
					m_posTarget.y + CObject2D::GetSize().y >= pBlock->GetPos().y - pBlock->GetSize().y &&
					m_posTarget.y - CObject2D::GetSize().y <= pBlock->GetPos().y + pBlock->GetSize().y)
				{
					// ���݂��̋������Z�o
					D3DXVECTOR3 dist = pBlock->GetPos() - CObject2D::GetPos();

					// �ՓˑO���炻�̎������ɂ���ꍇ
					if (dist.x * dist.x > dist.y * dist.y)
					{
						if (CObject2D::GetPos().x < pBlock->GetPos().x)
						{
							// �ʒu�����̃u���b�N�̍��[�ɐݒ�
							m_posTarget.x = -CObject2D::GetSize().x + (pBlock->GetPos().x - pBlock->GetSize().x);
						}
						else if (CObject2D::GetPos().x > pBlock->GetPos().x)
						{
							// �ʒu�����̃u���b�N�̉E�[�ɐݒ�
							m_posTarget.x = CObject2D::GetSize().x + (pBlock->GetPos().x + pBlock->GetSize().x);
						}
					}
					else
					{
						if (CObject2D::GetPos().y < pBlock->GetPos().y)
						{
							// �W�����v�\�񐔂�ݒ�
							m_nLeftNumJump = 2;

							// �ʒu�����̃u���b�N�̏�[�ɐݒ�
							m_posTarget.y = -CObject2D::GetSize().y + (pBlock->GetPos().y - pBlock->GetSize().y);

							// Y�������̉����x�����Z�b�g
							m_velocity.y = 0.0f;
						}
						else if (CObject2D::GetPos().y > pBlock->GetPos().y)
						{
							// �ʒu�����̃u���b�N�̉��[�ɐݒ�
							m_posTarget.y = CObject2D::GetSize().y + (pBlock->GetPos().y + pBlock->GetSize().y);
						}
					}
				}
#else
				// �u���b�N�ƏՓ˂���ꍇ
				if (copy.x + CObject2D::GetSize().x >= pBlock->GetPos().x - pBlock->GetSize().x &&
					copy.x - CObject2D::GetSize().x <= pBlock->GetPos().x + pBlock->GetSize().x &&
					copy.y + CObject2D::GetSize().y >= pBlock->GetPos().y - pBlock->GetSize().y &&
					copy.y - CObject2D::GetSize().y <= pBlock->GetPos().y + pBlock->GetSize().y)
				{
					// �ߋ��̈ʒu���ǂ��炩�̎������ɏd�Ȃ��Ă������ŏ�������
					if (CObject2D::GetPos().x + CObject2D::GetSize().x > pBlock->GetPos().x - pBlock->GetSize().x &&
						CObject2D::GetPos().x - CObject2D::GetSize().x < pBlock->GetPos().x + pBlock->GetSize().x)
					{
						if (CObject2D::GetPos().y < pBlock->GetPos().y)
						{
							// �W�����v�\�񐔂�ݒ�
							m_nLeftNumJump = 2;

							// �ʒu�����̃u���b�N�̏�[�ɐݒ�
							m_posTarget.y = -CObject2D::GetSize().y + (pBlock->GetPos().y - pBlock->GetSize().y);
						}
						else if (CObject2D::GetPos().y > pBlock->GetPos().y)
						{
							// �ʒu�����̃u���b�N�̉��[�ɐݒ�
							m_posTarget.y = CObject2D::GetSize().y + (pBlock->GetPos().y + pBlock->GetSize().y);
						}

						// Y�������̉����x�����Z�b�g
						m_velocity.y = 0.0f;
					}
					else if (CObject2D::GetPos().y + CObject2D::GetSize().y > pBlock->GetPos().y - pBlock->GetSize().y &&
						CObject2D::GetPos().y - CObject2D::GetSize().y < pBlock->GetPos().y + pBlock->GetSize().y)
					{
						if (CObject2D::GetPos().x < pBlock->GetPos().x)
						{
							// �ʒu�����̃u���b�N�̍��[�ɐݒ�
							m_posTarget.x = -CObject2D::GetSize().x + (pBlock->GetPos().x - pBlock->GetSize().x);
						}
						else if (CObject2D::GetPos().x > pBlock->GetPos().x)
						{
							// �ʒu�����̃u���b�N�̉E�[�ɐݒ�
							m_posTarget.x = CObject2D::GetSize().x + (pBlock->GetPos().x + pBlock->GetSize().x);
						}

						// X�������̉����x�����Z�b�g
						m_velocity.x = 0.0f;
					}
				}
#endif
			}
			//else if (pObject->GetType() == CObject::TYPE::ENEMY)
			//{ // �G�l�~�[�^�C�v�Ȃ�

			//	// �I�u�W�F�N�g�N���X���u���b�N�N���X�փ_�E���L���X�g
			//	CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObject);

			//	if (pEnemy == nullptr)
			//	{ // �_�E���L���X�g���s
			//		assert(false);
			//	}

			//	// �e�X�g
			//	auto �Ă��� = pEnemy->GetVelocity();

			//	// �G�l�~�[�ƏՓ˂���ꍇ
			//	if (m_posTarget.x + CObject2D::GetSize().x >= pEnemy->GetPos().x - pEnemy->GetSize().x &&
			//		m_posTarget.x - CObject2D::GetSize().x <= pEnemy->GetPos().x + pEnemy->GetSize().x &&
			//		m_posTarget.y + CObject2D::GetSize().y >= pEnemy->GetPos().y - pEnemy->GetSize().y &&
			//		m_posTarget.y - CObject2D::GetSize().y <= pEnemy->GetPos().y + pEnemy->GetSize().y)
			//	{
			//		// �ߋ��̈ʒu���ǂ��炩�̎������ɏd�Ȃ��Ă������ŏ�������
			//		if (CObject2D::GetPos().x + CObject2D::GetSize().x > pEnemy->GetPos().x - pEnemy->GetSize().x &&
			//			CObject2D::GetPos().x - CObject2D::GetSize().x < pEnemy->GetPos().x + pEnemy->GetSize().x)
			//		{
			//			if (CObject2D::GetPos().y < pEnemy->GetPos().y)
			//			{
			//				// �W�����v�\�񐔂�ݒ�
			//				m_nLeftNumJump = 2;

			//				m_posTarget.x += �Ă���.x;

			//				// �ʒu�����̃u���b�N�̏�[�ɐݒ�
			//				m_posTarget.y = -CObject2D::GetSize().y + (pEnemy->GetPos().y - pEnemy->GetSize().y);

			//				// Y�������̉����x�����Z�b�g
			//				m_velocity.y = 0.0f;
			//			}
			//			else if (CObject2D::GetPos().y > pEnemy->GetPos().y)
			//			{
			//				// �ʒu�����̃u���b�N�̉��[�ɐݒ�
			//				m_posTarget.y = CObject2D::GetSize().y + (pEnemy->GetPos().y + pEnemy->GetSize().y);
			//			}
			//		}
			//		else if (CObject2D::GetPos().y + CObject2D::GetSize().y > pEnemy->GetPos().y - pEnemy->GetSize().y - �Ă���.y &&
			//			CObject2D::GetPos().y - CObject2D::GetSize().y < pEnemy->GetPos().y + pEnemy->GetSize().y - �Ă���.y)
			//		{
			//			if (CObject2D::GetPos().x < pEnemy->GetPos().x)
			//			{
			//				// �ʒu�����̃u���b�N�̍��[�ɐݒ�
			//				m_posTarget.x = -CObject2D::GetSize().x + (pEnemy->GetPos().x - pEnemy->GetSize().x);
			//			}
			//			else if (CObject2D::GetPos().x > pEnemy->GetPos().x)
			//			{
			//				// �ʒu�����̃u���b�N�̉E�[�ɐݒ�
			//				m_posTarget.x = CObject2D::GetSize().x + (pEnemy->GetPos().x + pEnemy->GetSize().x);
			//			}
			//		}

			//		int aa = 0;
			//	}
			//}
			else if (pObject->GetType() == CObject::TYPE::ITEM)
			{ // �A�C�e���^�C�v�Ȃ�

				// �I�u�W�F�N�g�N���X���A�C�e���N���X�փ_�E���L���X�g
				CItem* pItem = dynamic_cast<CItem*>(pObject);

				if (pItem == nullptr)
				{ // �_�E���L���X�g���s
					assert(false);
				}

				// �A�C�e���ƏՓ˂���ꍇ
				if (m_posTarget.x + CObject2D::GetSize().x >= pItem->GetPos().x - pItem->GetSize().x &&
					m_posTarget.x - CObject2D::GetSize().x <= pItem->GetPos().x + pItem->GetSize().x &&
					m_posTarget.y + CObject2D::GetSize().y >= pItem->GetPos().y - pItem->GetSize().y &&
					m_posTarget.y - CObject2D::GetSize().y <= pItem->GetPos().y + pItem->GetSize().y)
				{
					// �p�[�e�B�N���𐶐�
					for (int i = 0; i < 10; i++)
					{
						CParticle::Create(
							m_posTarget,			// ���S�ʒu
							pItem->GetSize(),	// �T�C�Y
							atan2f((float)(rand() % 314), (float)(rand() % 314)) * (rand() % 314));	// ��Ԋp�x
					}

					// �����I�Ƀe�N�X�`����ύX
					LPDIRECT3DTEXTURE9 pTex = CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::PLAYER_001);

					if (pTex == nullptr)
					{ // �擾���s
						assert(false);
					}

					// �e�N�X�`����ݒ�
					CObject2D::BindTex(pTex);

					// �A�j���[�V���������b�N
					m_bAnimationLock = true;

					// �A�C�e����j��
					pObject->Release();
				}
			}
		}
	}
}

//============================================================================
// �A�j���[�V����
//============================================================================
void CPlayer::Animation()
{
	if (!m_bAnimationLock)
	{
		// �e�N�X�`���ύX�Ǘ��J�E���g�A�b�v
		m_nCntTexChange++;

		if (m_nCntTexChange >= 15)
		{ // ��莞�Ԍo�߂ɂ��

			// ���e�N�X�`����ޏ��擾
			int nTexPatternU = CObject2D::GetNowPatternU();

			// ���e�N�X�`����ޕύX
			nTexPatternU++;

			if (nTexPatternU >= CPlayer::TEXTURE_DIVIDE_U)
			{ // U�����̕������𒴂����

				// �e�N�X�`���p�^�[�������Z�b�g
				nTexPatternU = 0;
			}

			// ���e�N�X�`����ޏ��ݒ�
			CObject2D::SetNowPatternU(nTexPatternU);

			// �ύX�Ǘ��J�E���g�����Z�b�g
			m_nCntTexChange = 0;
		}
	}
	else
	{
		// ��U�A�����I�Ƀe�N�X�`���T�C�Y��ݒ�
		CObject2D::SetTexWidth(1.0f);
		CObject2D::SetNowPatternU(1);
	}
}