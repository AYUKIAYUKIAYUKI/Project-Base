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
#include "bullet.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
const int CPlayer::TEXTURE_DIVIDE_U = 30;	// �e�N�X�`����U����������
const int CPlayer::TEXTURE_DIVIDE_V = 1;	// �e�N�X�`����V����������
const float CPlayer::MAX_VELOCITY = 5.0f;	// �����x���
const float CPlayer::JUMP_FORCE = -10.0f;	// �W�����v��
const float CPlayer::BRAKING_FORCE = 0.9f;	// ������
const float CPlayer::GRAVITY_FORCE = 0.25f;	// �d��

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer() : CObject2D(FRONT_MIDDLE)
{
	m_nCntTexChange = 0;	// �e�N�X�`���ύX�Ǘ�
	m_velocity = {};		// �����x
	m_pos_tgt = {};			// �ڕW�ʒu
	m_rot_tgt = {};			// �ڕW����
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
	m_pos_tgt = CObject2D::GetPos();

	// ����
	Control();

	// ��������
	Braking();

	// �d�͉���
	GravityFall();

	// �����蔻��
	Collision();

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
	// �v���C���[�𐶐�
	CPlayer* pPlayer = new CPlayer;

	// �����o���Ă����珉���ݒ�
	if (pPlayer != nullptr)
	{
		pPlayer->SetType(TYPE::PLAYER);	// �^�C�v��ݒ�

		pPlayer->Init();		// ���N���X�̏����ݒ�
		pPlayer->SetPos(pos);	// ���S�ʒu�̐ݒ�
		pPlayer->SetSize(size);	// �T�C�Y�̐ݒ�

		pPlayer->SetTexWidth(1.0f / (float)TEXTURE_DIVIDE_U);	// ���e�N�X�`��������
		pPlayer->SetTexHeight(1.0f / (float) TEXTURE_DIVIDE_V);	// �c�e�N�X�`�����c��
	}

	// �e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 pTex = CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::PLAYER_000);

	// �e�N�X�`����ݒ�
	pPlayer->BindTex(pTex);

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
	if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY_X))
	{
		// Y�������̉����x��������֌Œ�
		m_velocity.y = JUMP_FORCE;
	}

	// �f�o�b�O�p�ɃT�E���h�Đ� (�L�[�{�[�h�A�p�b�h�擾������̂ł�����)
	if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY_B))
	{
		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_00);

		// ���܂��ɒe�̐���
		CBullet::Create(
			m_pos_tgt,				// ���S�ʒu
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
//	//if (m_rot_tgt.z - rot.z > D3DX_PI)
//	//{
//	//	rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
//	//}
//	//else if (m_rot_tgt.z - rot.z < -D3DX_PI)
//	//{
//	//	rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
//	//}
//	//else
//	//{
//	//	rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy);
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
	if (m_velocity.x > MAX_VELOCITY)
	{
		m_velocity.x = MAX_VELOCITY;
	}
	else if (m_velocity.x < -MAX_VELOCITY)
	{
		m_velocity.x = -MAX_VELOCITY;
	}

	// ��������X�������ւ̉����x������
	m_velocity.x = m_velocity.x * BRAKING_FORCE;
}

//============================================================================
// �d�͗���
//============================================================================
void CPlayer::GravityFall()
{
	// �d�͕��A�������ւ̉����x����
	m_velocity.y = m_velocity.y + GRAVITY_FORCE;
}

//============================================================================
// �����蔻��
//============================================================================
void CPlayer::Collision()
{
	
}

//============================================================================
// �ʒu����
//============================================================================
void CPlayer::AdjustPos()
{
	// �����x���ʒu��ϓ�
	m_pos_tgt += m_velocity;

	// �T�C�Y���擾
	D3DXVECTOR3 fSize = CObject2D::GetSize();

	// ��ʂ̍��E�[�ɓ��B�ł��ꂼ�ꃋ�[�v
	if (m_pos_tgt.x - fSize.x > SCREEN_WIDTH)
	{
		// ���[�֐ݒ�
		m_pos_tgt.x = 0.0f - fSize.x;
	}
	else if (m_pos_tgt.x + fSize.x < 0.0f)
	{
		// �E�[�֐ݒ�
		m_pos_tgt.x = SCREEN_WIDTH + fSize.x;
	}

	// ��ʂ̉��[�ɓ��B�ŉ��~����
	if (m_pos_tgt.y + fSize.y > SCREEN_HEIGHT)
	{
		// ���[�ɐݒ�
		m_pos_tgt.y = SCREEN_HEIGHT - fSize.y;

		// Y�������̉����x�����Z�b�g
		m_velocity.y = 0.0f;
	}

	// ���S�ʒu����ݒ�
	CObject2D::SetPos(m_pos_tgt);
}

//============================================================================
// �A�j���[�V����
//============================================================================
void CPlayer::Animation()
{
	// �e�N�X�`���ύX�Ǘ��J�E���g�A�b�v
	m_nCntTexChange++;

	if (m_nCntTexChange >= 15)
	{
		// ���e�N�X�`����ޏ��擾
		int nTexPatternU = CObject2D::GetNowPatternU();

		// ���e�N�X�`����ޕύX
		nTexPatternU++;

		if (nTexPatternU >= TEXTURE_DIVIDE_U)
		{
			// �e�N�X�`���p�^�[�������Z�b�g
			nTexPatternU = 0;
		}

		// ���e�N�X�`����ޏ��ݒ�
		CObject2D::SetNowPatternU(nTexPatternU);

		// �ύX�Ǘ��J�E���g�����Z�b�g
		m_nCntTexChange = 0;
	}
}