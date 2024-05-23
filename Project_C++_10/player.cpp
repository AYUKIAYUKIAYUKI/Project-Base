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
#include "main.h"
#include "manager.h"
#include "bullet.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer() : CObject2D::CObject2D()
{
	m_nCntTexChange = 0;			// �e�N�X�`���ύX�Ǘ�
	m_nCntTexPattern = 0;			// �e�N�X�`���p�^�[���Ǘ�
	m_pos = { 0.0f, 0.0f, 0.0f };	// ���S�ʒu
	m_rot = { 0.0f, 0.0f, 0.0f };	// ��]��
	m_fAngle = 0.0f;				// �p�x
	m_size = { 0.0f, 0.0f, 0.0f };	// �T�C�Y
	m_fLength = 0.0f;				// �Ίp��
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
	// �K�v�Ȑ��l���Z�o
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.y);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@���擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�̐ݒ�
	pVtx[0].pos = {
		m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength,
		m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	};

	pVtx[1].pos = {
		m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	};

	pVtx[2].pos = {
		m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength,
		m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength,
		0.0f
	};

	pVtx[3].pos = {
		m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength,
		m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength,
		0.0f
	};

	// �e�N�X�`���̐ݒ�
	pVtx[0].tex = { m_nCntTexPattern / 8.0f, 0.0f };
	pVtx[1].tex = { (m_nCntTexPattern + 1) / 8.0f, 0.0f };
	pVtx[2].tex = { m_nCntTexPattern / 8.0f, 1.0f };
	pVtx[3].tex = { (m_nCntTexPattern + 1) / 8.0f, 1.0f };

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

	// �g�k
	Scaling();

	// ��]
	Rotation();

	// �ړ�
	Translation();

	// �A�j���[�V����
	Animation();
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
	CPlayer* pPlayer = new CPlayer;

	// �����o���Ă����珉���ݒ�
	if (pPlayer != nullptr)
	{
		pPlayer->Init();
		pPlayer->m_pos = pos;
		pPlayer->m_size = size;
	}

	// �f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();

	// �e�N�X�`���̃|�C���^
	LPDIRECT3DTEXTURE9 pTex = nullptr;

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDev,
		"data\\TEXTURE\\runningman000.png",
		&pTex);

	// �e�N�X�`����ݒ�
	pPlayer->BindTex(pTex);

	return pPlayer;
}

//============================================================================
// �g�k
//============================================================================
void CPlayer::Scaling()
{
	if ((m_pos.x - m_fLength) > SCREEN_WIDTH)
	{ // ��ʂ̉E�[�ɓ��B�Ŋg�債���[�v
		m_pos.x = 0.0f - m_fLength;
		m_size *= 3.0f;
	}
	else if ((m_pos.x + m_fLength) < 0.0f)
	{ // ��ʂ̉E�[�ɓ��B�ŏk�������[�v
		m_pos.x = SCREEN_WIDTH;
		m_size /= 3.0f;
	}
}

//============================================================================
// ��]
//============================================================================
void CPlayer::Rotation()
{
	// �u���[�L��
	float fStopEnergy = 0.1f;

	// ��]���f�Ɖ�]�ʂ̌���
	if (m_rot_tgt.z - m_rot.z > D3DX_PI)
	{
		m_rot.z += ((m_rot_tgt.z - m_rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (m_rot_tgt.z - m_rot.z < -D3DX_PI)
	{
		m_rot.z += ((m_rot_tgt.z - m_rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		m_rot.z += ((m_rot_tgt.z - m_rot.z) * fStopEnergy);
	}
}

//============================================================================
// �ړ�
//============================================================================
void CPlayer::Translation()
{
	// ���X�e�B�b�N�擾
	CInputPad* pPad = CManager::GetPad();
	CInputPad::JOYSTICK Stick = pPad->GetJoyStickL();

	// ���͂�����Έړ�
	if (Stick.X != 0 || Stick.Y != 0)
	{
		// �ړ��ʂƖڕW��]�ʂ�ݒ�
		m_pos.x += sinf(atan2f(Stick.X, -Stick.Y)) * 5.0f;
		m_pos.y += cosf(atan2f(Stick.X, -Stick.Y)) * 5.0f;
		m_rot_tgt.z = atan2f(Stick.X, -Stick.Y);
	}

	// �f�o�b�O�p�ɃT�E���h�Đ� (�p�b�h�擾������̂ł�����)
	if (pPad->GetTrigger(CInputPad::JOYKEY_B))
	{
		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_00);
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
		m_pos.x += sinf(atan2f(X, Y)) * 5.0f;
		m_pos.y += cosf(atan2f(X, Y)) * 5.0f;
		m_rot_tgt.z = atan2f(-X, -Y);
	}

	// �e�𔭎� (�L�[�{�[�h�擾������̂ł�����)
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		// �e�̐���
		CBullet::Create(
			m_pos,					// ���S�ʒu
			{ 30.0f, 30.0f, 0.0f },	// �T�C�Y
			50);					// �g�p����
	}

	// �f�o�b�O�p�ɃT�E���h�Đ� (�L�[�{�[�h�擾������̂ł�����)
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_00);
	}
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
		// �e�N�X�`���p�^�[���ύX
		m_nCntTexPattern++;

		if (m_nCntTexPattern >= 8)
		{
			// �e�N�X�`���p�^�[�������Z���g
			m_nCntTexPattern = 0;
		}

		// �ύX�Ǘ��J�E���g�����Z�b�g
		m_nCntTexChange = 0;
	}
}