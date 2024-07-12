//============================================================================
// 
// �e�X�g�p�|���S�� [test_polygon_2D.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "test_polygon_2D.h"
#include "manager.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
CTestPolygon2D* CTestPolygon2D::m_pInstance = nullptr;	// ���N���X���

//============================================================================
// �R���X�g���N�^
//============================================================================
CTestPolygon2D::CTestPolygon2D()
{
	m_pVtxBuff = nullptr;			// ���_�o�b�t�@�̃|�C���^
	m_pTex = nullptr;				// �e�N�X�`�����̃|�C���^
	m_pSurface = nullptr;			// �T�[�t�F�C�X���̃|�C���^
	m_pos = { 0.0f, 0.0f, 0.0f };	// �ʒu
	m_size = { 0.0f, 0.0f, 0.0f };	// �T�C�Y

	// �ʒu�𒆐S�ɐݒ�
	m_pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f };

	// �T�C�Y��K���ɐݒ�
	float ff = 0.4f;
	m_size = { SCREEN_WIDTH * ff, SCREEN_HEIGHT * ff, 0.0f };
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CTestPolygon2D::~CTestPolygon2D()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CTestPolygon2D::Init()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// ���_�o�b�t�@�̐���
	pDev->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	if (m_pVtxBuff == nullptr)
	{ // �������s
		return E_FAIL;
	}

#if 1
	// �e�N�X�`�����쐬
	pDev->CreateTexture(
		SCREEN_WIDTH,			// U
		SCREEN_HEIGHT,			// V
		0,						// �~�b�v�}�b�v���x��
		D3DUSAGE_RENDERTARGET,	// �e�N�X�`���̐���
		D3DFMT_A8R8G8B8,		// �s�N�Z���t�H�[�}�b�g
		D3DPOOL_DEFAULT,		// �������Ǘ��t���O
		&m_pTex,				// �e�N�X�`���ۑ���
		nullptr);				// �n���h��
#else
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFileA(pDev,
		"Data\\TEXTURE\\AL-1S.png",
		&m_pTex);
#endif

	// �e�N�X�`���̃T�[�t�F�C�X���擾
	m_pTex->GetSurfaceLevel(0, &m_pSurface);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

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

//============================================================================
// �I������
//============================================================================
void CTestPolygon2D::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �e�N�X�`�����̔j��
	if (m_pTex != nullptr)
	{
		m_pTex->Release();
		m_pTex = nullptr;
	}

	// �T�[�t�F�X���̔j��
	if (m_pSurface != nullptr)
	{
		m_pSurface->Release();
		m_pSurface = nullptr;
	}
}

//============================================================================
// �X�V����
//============================================================================
void CTestPolygon2D::Update()
{
	// ����
	Move();

	// ���_���̐ݒ�
	SetVtx();
}

//============================================================================
// �`�揈��
//============================================================================
void CTestPolygon2D::Draw()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDev->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDev->SetTexture(0, m_pTex);

	// �|���S���̕`��
	pDev->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,										// ���_���̐擪�A�h���X
		2);										// �v���~�e�B�u��
}

//============================================================================
// ����
//============================================================================
void CTestPolygon2D::Create()
{
	if (m_pInstance != nullptr)
	{ // ��d�����֎~
		assert(false);
	}

	// �C���X�^���X�𐶐�
	m_pInstance = DBG_NEW CTestPolygon2D;
}

//============================================================================
// ���
//============================================================================
void CTestPolygon2D::Release()
{
	if (m_pInstance != nullptr)
	{
		// �I������
		m_pInstance->Uninit();

		// �����������
		delete m_pInstance;

		// �|�C���^��������
		m_pInstance = nullptr;
	}
}

//============================================================================
// �e�N�X�`�������擾
//============================================================================
LPDIRECT3DTEXTURE9 CTestPolygon2D::GetTexture()
{
	return m_pTex;
}

//============================================================================
// �T�[�t�F�C�X�����擾
//============================================================================
LPDIRECT3DSURFACE9 CTestPolygon2D::GetSurface()
{
	return m_pSurface;
}

//============================================================================
// �擾
//============================================================================
CTestPolygon2D* CTestPolygon2D::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// ����
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// ����
//============================================================================
void CTestPolygon2D::Move()
{
	// �ړ�
	static D3DXVECTOR3 move = { 3.0f, 3.0f, 0.0f };
	m_pos += move;

	// ���E�[�ɓ��B
	if (m_pos.x + m_size.x >= SCREEN_WIDTH || m_pos.x - m_size.x <= 0.0f)
	{
		move.x *= -1.0f;
	}

	// �㉺�[�ɓ��B
	if (m_pos.y + m_size.y >= SCREEN_HEIGHT || m_pos.y - m_size.y <= 0.0f)
	{
		move.y *= -1.0f;
	}
}

//============================================================================
// ���_���̐ݒ�
//============================================================================
void CTestPolygon2D::SetVtx()
{
	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	// �F�̐ݒ�
	pVtx[0].pos = { m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f };
	pVtx[1].pos = { m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f };
	pVtx[2].pos = { m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f };
	pVtx[3].pos = { m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f };

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}