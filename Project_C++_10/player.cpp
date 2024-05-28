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

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer() : CObject2D(FRONT_MIDDLE)
{
	m_nCntTexChange = 0;				// �e�N�X�`���ύX�Ǘ�
	m_rot_tgt = { 0.0f, 0.0f, 0.0f };	// �ڕW����
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
	// �g�k
	Scaling();

	// ��]
	Rotation();

	// �ړ�
	Translation();

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

		pPlayer->SetTexWidth(1.0f / 8.0f);	// ���e�N�X�`��������
		pPlayer->SetTexHeight(1.0f);		// �c�e�N�X�`�����c��
	}

	// �e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 pTex = CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::PLAYER_000);

	// �e�N�X�`����ݒ�
	pPlayer->BindTex(pTex);

	return pPlayer;
}

//============================================================================
// �g�k
//============================================================================
void CPlayer::Scaling()
{
	// �K�v�ȏ����擾
	D3DXVECTOR3 pos = CObject2D::GetPos();		// ���S�ʒu���
	D3DXVECTOR3 size = CObject2D::GetSize();	// �T�C�Y���
	float fLength = CObject2D::GetLength();		// �W�J�p�Ίp�����

	if ((pos.x - fLength) > SCREEN_WIDTH)
	{ // ��ʂ̉E�[�ɓ��B�Ŋg�債���[�v
		pos.x = 0.0f - fLength;
		size *= 3.0f;
	}
	else if ((pos.x + fLength) < 0.0f)
	{ // ��ʂ̉E�[�ɓ��B�ŏk�������[�v
		pos.x = SCREEN_WIDTH;
		size /= 3.0f;
	}

	// �K�v�ȏ���ݒ�
	CObject2D::SetPos(pos);		// ���S�ʒu��ݒ�
	CObject2D::SetSize(size);	// �T�C�Y��ݒ�
}

//============================================================================
// ��]
//============================================================================
void CPlayer::Rotation()
{
	// �������擾
	D3DXVECTOR3 rot = CObject2D::GetRot();

	// �u���[�L��
	float fStopEnergy = 0.1f;

	// ��]���f�Ɖ�]�ʂ̌���
	if (m_rot_tgt.z - rot.z > D3DX_PI)
	{
		rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (m_rot_tgt.z - rot.z < -D3DX_PI)
	{
		rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy);
	}

	// �������ݒ�
	CObject2D::SetRot(rot);
}

//============================================================================
// �ړ�
//============================================================================
void CPlayer::Translation()
{
	// ���S�ʒu�����擾
	D3DXVECTOR3 pos = CObject2D::GetPos();

	// ���X�e�B�b�N�擾
	CInputPad* pPad = CManager::GetPad();
	CInputPad::JOYSTICK Stick = pPad->GetJoyStickL();

	// ���͂�����Έړ�
	if (Stick.X != 0 || Stick.Y != 0)
	{
		// �ړ��ʂƖڕW��]�ʂ�ݒ�
		pos.x += sinf(atan2f(Stick.X, -Stick.Y)) * 5.0f;
		pos.y += cosf(atan2f(Stick.X, -Stick.Y)) * 5.0f;
		m_rot_tgt.z = atan2f(Stick.X, -Stick.Y);
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
		pos.x += sinf(atan2f(X, Y)) * 5.0f;
		pos.y += cosf(atan2f(X, Y)) * 5.0f;
		m_rot_tgt.z = atan2f(X, Y);
	}

	// �e�𔭎� (�L�[�{�[�h�A�p�b�h�擾������̂ł�����)
	if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY_X))
	{
		// �e�̐���
		CBullet::Create(
			pos,					// ���S�ʒu
			{ 15.0f, 15.0f, 0.0f },	// �T�C�Y
			100,					// �g�p����
			CObject2D::GetRot().z);	// ��Ԋp�x
	}

	// �f�o�b�O�p�ɃT�E���h�Đ� (�L�[�{�[�h�A�p�b�h�擾������̂ł�����)
	if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY_B))
	{
		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_00);
	}

	// ���S�ʒu��ݒ�
	CObject2D::SetPos(pos);
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

		if (nTexPatternU >= 8)
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