//============================================================================
// 
// �v���C���[ [player.cpp]
// Author : ���c����
// 
//============================================================================

// �C���N���[�h�t�@�C��
#include "player.h"
#include "main.h"
#include "manager.h"

//****************************************************************************
// �R���X�g���N�^
//****************************************************************************
CPlayer::CPlayer() : CObject2D::CObject2D()
{

}

//****************************************************************************
// �f�X�g���N�^
//****************************************************************************
CPlayer::~CPlayer()
{
	Uninit();
}

//****************************************************************************
// �����ݒ�
//****************************************************************************
HRESULT CPlayer::Init()
{
	// �f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDev,
		"data\\TEXTURE\\runningman000.png",
		&m_pTex);

	// ���_�o�b�t�@�̐���
	pDev->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�̐ݒ�
	pVtx[0].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[1].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[2].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[3].pos = { 0.0f, 0.0f, 0.0f };

	// ���Z���̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �F�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`���̐ݒ�
	pVtx[0].tex = { 0.0f, 0.0f };
	pVtx[1].tex = { 1.0f, 0.0f };
	pVtx[2].tex = { 0.0f, 1.0f };
	pVtx[3].tex = { 1.0f, 1.0f };

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//****************************************************************************
// �I������
//****************************************************************************
void CPlayer::Uninit()
{
	// �e�N�X�`���̔j��
	if (m_pTex != nullptr)
	{
		m_pTex->Release();
		m_pTex = nullptr;
	}

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//****************************************************************************
// �X�V����
//****************************************************************************
void CPlayer::Update()
{
	// �K�v�Ȑ��l���Z�o
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.y);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
	m_pVtxBuff->Unlock();

	// �g�k
	Scaling();

	// ��]
	Rotation();

	// �ړ�
	Translation();

	// �A�j���[�V����
	Animation();
}

//****************************************************************************
// �g�k
//****************************************************************************
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

//****************************************************************************
// ��]
//****************************************************************************
void CPlayer::Rotation()
{
	m_rot.z += 0.05f;
}

//****************************************************************************
// �ړ�
//****************************************************************************
void CPlayer::Translation()
{
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

	if (pKeyboard->GetPress(DIK_D))
	{
		X = 1.0f;
	}

	// �f�o�b�O�p�ɃT�E���h�Đ�
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_00);
	}

	if (bMove)
	{
		// �ړ��ʂƖڕW������ݒ�
		m_pos.x += sinf(atan2f(X, Y)) * 5.0f;
		m_pos.y += cosf(atan2f(X, Y)) * 5.0f;
	}

	// ���X�e�B�b�N�擾
	CInputPad* pPad = CManager::GetPad();
	CInputPad::JOYSTICK Stick = pPad->GetJoyStickL();

	// ���͂�����Έړ�
	if (Stick.X != 0 || Stick.Y != 0)
	{
		// �ړ��ʂƖڕW������ݒ�
		m_pos.x += sinf(atan2f(Stick.X, Stick.Y)) * 5.0f;
		m_pos.y += cosf(atan2f(Stick.X, Stick.Y)) * 5.0f;
	}
}

//****************************************************************************
// �A�j���[�V����
//****************************************************************************
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

//****************************************************************************
// �`�揈��
//****************************************************************************
void CPlayer::Draw()
{
	// �f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDev->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDev->SetTexture(0, m_pTex);

	//�|���S���̕`��
	pDev->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,										// ���_���̐擪�A�h���X
		2);										// �v���~�e�B�u��
}

//****************************************************************************
// ����
//****************************************************************************
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

	return pPlayer;
}