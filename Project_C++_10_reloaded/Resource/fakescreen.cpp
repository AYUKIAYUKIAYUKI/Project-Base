//============================================================================
// 
// �^���X�N���[�� [fakescreen.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "fakescreen.h"
#include "manager.h"

//****************************************************
// �}�N����`
//****************************************************
#define MESH_DBG 0	// ���b�V�����̃f�o�b�O�\���؂�ւ�

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
CFakeScreen* CFakeScreen::m_pInstance = nullptr;	// ���N���X���
const int CFakeScreen::SPLIT_ALONG_X_AXIS = 50;		// X�������̕�����
const int CFakeScreen::SPLIT_ALONG_Y_AXIS = 50;		// Y�������̕�����

//============================================================================
// �R���X�g���N�^
//============================================================================
CFakeScreen::CFakeScreen()
{
	m_pVtxBuff = nullptr;			// ���_�o�b�t�@�̃|�C���^
	m_pIdxBuff = nullptr;			// �C���f�b�N�X�o�b�t�@�̃|�C���^
	m_pTex = nullptr;				// �e�N�X�`�����̃|�C���^
	m_pSurface = nullptr;			// �T�[�t�F�C�X���̃|�C���^
	m_nNumVtx = 0;					// ���_��
	m_nNumPolygon = 0;				// �|���S����
	m_nNumDegenerated = 0;			// �k�ރ|���S����
	m_nNumIndex = 0;				// �C���f�b�N�X��
	m_pos = { 0.0f, 0.0f, 0.0f };	// �ʒu
	m_size = { 0.0f, 0.0f, 0.0f };	// �T�C�Y
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CFakeScreen::~CFakeScreen()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CFakeScreen::Init()
{
	// �ʒu�𒆐S�ɐݒ�
	m_pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f };

	// �T�C�Y��ݒ�
	float fSize = 0.3f;
	m_size = { SCREEN_WIDTH * fSize, SCREEN_HEIGHT * fSize, 0.0f };

	// ���b�V�����̌v�Z
	CalcMesh();

	// ���_�o�b�t�@�̐���
	if (FAILED(CreateVtxBuff()))
	{
		return E_FAIL;
	}

	// �C���f�b�N�X�o�b�t�@�̐���
	if (FAILED(CreateIdxBuff()))
	{
		return E_FAIL;
	}

	// �e�N�X�`���̐���
	if (FAILED(CreateTex()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CFakeScreen::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
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
void CFakeScreen::Update()
{
	// �ړ�
	//Move();
	 
	// �g�ł�
	Wave();

	// ���_���̐ݒ�
	//SetVtx();
}

//============================================================================
// �`�揈��
//============================================================================
void CFakeScreen::Draw()
{
#if 0
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
#else
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�C���f�b�N�X���f�[�^�X�g���[���ɐݒ�
	pDev->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDev->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDev->SetTexture(0, m_pTex);

	// ���b�V���t�B�[���h�̕`��
	pDev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_nNumVtx,
		0,
		m_nNumPolygon);
#endif
}

//============================================================================
// ����
//============================================================================
void CFakeScreen::Create()
{
	if (m_pInstance != nullptr)
	{ // ��d�����֎~
		assert(false);
	}

	// �C���X�^���X�𐶐�
	m_pInstance = DBG_NEW CFakeScreen;
}

//============================================================================
// ���
//============================================================================
void CFakeScreen::Release()
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
LPDIRECT3DTEXTURE9 CFakeScreen::GetTexture()
{
	return m_pTex;
}

//============================================================================
// �T�[�t�F�C�X�����擾
//============================================================================
LPDIRECT3DSURFACE9 CFakeScreen::GetSurface()
{
	return m_pSurface;
}

//============================================================================
// �擾
//============================================================================
CFakeScreen* CFakeScreen::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// ����
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// ���_�o�b�t�@�̐���
//============================================================================
HRESULT CFakeScreen::CreateVtxBuff()
{
	// ���_�o�b�t�@�̐���
	CManager::GetRenderer()->GetDeviece()->CreateVertexBuffer(sizeof(VERTEX_2D) * m_nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	if (m_pVtxBuff == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	int nCntVtxX = 0, nCntVtxY = 0;								// �e�����̒��_�����J�E���g����
	float fEachSizeX = (m_size.x * 2.0f) / SPLIT_ALONG_X_AXIS;	// �|���S��1���������X�����ւ̒��_�z�u�Ԋu
	float fEachSizeY = (m_size.y * 2.0f) / SPLIT_ALONG_Y_AXIS;	// �|���S��1���������Y�����ւ̒��_�z�u�Ԋu

	for (int i = 0; i < m_nNumVtx; i++)
	{
		// ���_���W�̐ݒ� (�T�C�Y�l�����Ƃɂ�������̒��_�ʒu�ɁA�ϓ��ʒu�����Z���ċ�`���`��)
		pVtx[i].pos = {
			m_pos.x - m_size.x + (fEachSizeX * nCntVtxX),
			m_pos.y - m_size.y + (fEachSizeY * nCntVtxY),
			0.0f };

#if MESH_DBG

		// �e���_���W�̃f�o�b�O�\��
		CManager::GetRenderer()->SetTimeString(std::to_string(i + 1) + "���_:" + std::to_string(pVtx[i].pos.x) + ":" + std::to_string(pVtx[i].pos.y) + ":" + std::to_string(pVtx[i].pos.z), 30);

#endif	// MESH_DBG

		// ���Z���̐ݒ�
		pVtx[i].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ� (�������ւ�炸�T�C�Y�ɍ��킹�ċϓ��ɐݒ�)
		pVtx[i].tex = {
			(fEachSizeX * nCntVtxX) / (m_size.x * 2.0f),
			(fEachSizeY * nCntVtxY) / (m_size.y * 2.0f) };

#if MESH_DBG

		// �eUV���W�̃f�o�b�O�\��
		CManager::GetRenderer()->SetTimeString(std::to_string(i + 1) + "UV:" + std::to_string(pVtx[i].tex.x) + " : " + std::to_string(pVtx[i].tex.y), 30);

#endif	// MESH_DBG

		// X�������_���̃J�E���g���s��
		if (nCntVtxX >= SPLIT_ALONG_X_AXIS)
		{ // �J�E���g�����������ɒB������

			// X�������_���̃J�E���g�����Z�b�g
			nCntVtxX = 0;

			// Y�������_�����J�E���g�A�b�v
			nCntVtxY++;
		}
		else
		{
			// X�������_�����J�E���g�A�b�v
			nCntVtxX++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================================================
// �C���f�b�N�X���̐���
//============================================================================
HRESULT CFakeScreen::CreateIdxBuff()
{
	// �C���f�b�N�X�o�b�t�@�̐���
	CManager::GetRenderer()->GetDeviece()->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	if (m_pIdxBuff == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �C���f�b�N�X���ւ̃|�C���^
	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, reinterpret_cast<void**>(&pIdx), 0);

	int columnCnt = 0, rowCnt = 0;	// ���쐧��p

	for (int i = 0; i < m_nNumIndex / 2; i++, pIdx += 2)
	{
		int id_vtx[2] = { 0, 0 };	// ���_�ԍ�

		if (columnCnt < SPLIT_ALONG_Y_AXIS + 1)
		{ // ��J�E���g�����ۂ̗񐔂𒴂���܂�

			// �J�E���g�ɉ����āA2���_���Ƃɔԍ���U���Ă���
			id_vtx[0] = (columnCnt + SPLIT_ALONG_Y_AXIS + 1) + rowCnt;
			id_vtx[1] = columnCnt + rowCnt;

			columnCnt++;	// ��J�E���g����
		}
		else
		{ // ��J�E���g���񐔂𒴂����

			// �k�ރ|���S���̕���U�蕪��
			id_vtx[0] = (columnCnt - 1) + rowCnt;
			id_vtx[1] = (columnCnt + SPLIT_ALONG_Y_AXIS + 1) + rowCnt;

			columnCnt = 0;	// ��J�E���g���Z�b�g

			rowCnt += SPLIT_ALONG_Y_AXIS + 1;	// �s�J�E���g����
		}

		// �C���f�b�N�X�ɔ��f
		pIdx[0] = static_cast<WORD>(id_vtx[0]);
		pIdx[1] = static_cast<WORD>(id_vtx[1]);
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//============================================================================
// �e�N�X�`���̐���
//============================================================================
HRESULT CFakeScreen::CreateTex()
{
#if 1
	// �e�N�X�`�����쐬
	CManager::GetRenderer()->GetDeviece()->CreateTexture(
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
	D3DXCreateTextureFromFileA(CManager::GetRenderer()->GetDeviece(),
		"Data\\TEXTURE\\AL-1S.png",
		&m_pTex);
#endif

	// �e�N�X�`���̃T�[�t�F�C�X���擾
	m_pTex->GetSurfaceLevel(0, &m_pSurface);

	return S_OK;
}

//============================================================================
// ���b�V�����̌v�Z
//============================================================================
void CFakeScreen::CalcMesh()
{
	// ���_���̎Z�o
	m_nNumVtx = (SPLIT_ALONG_X_AXIS + 1) * (SPLIT_ALONG_Y_AXIS + 1);

	// ���_�����|���S���\���̍Œᐔ�ɖ����Ȃ�
	if (m_nNumVtx < 3)
	{
		assert(false);
	}

	// �k�ރ|���S�����̎Z�o
	m_nNumDegenerated = (SPLIT_ALONG_X_AXIS - 1) * 4;

	// �|���S�����̎Z�o
	m_nNumPolygon = (SPLIT_ALONG_X_AXIS * SPLIT_ALONG_Y_AXIS * 2) + m_nNumDegenerated;

	// �C���f�b�N�X���̎Z�o
	m_nNumIndex = m_nNumPolygon + 2;
}

//============================================================================
// �ړ�
//============================================================================
void CFakeScreen::Move()
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
// �g�ł�
//============================================================================
void CFakeScreen::Wave()
{
	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	float fWavePosX = 0.0f;		// �䂪�݋
	int nCntAdd = 0;
	static float fAdd = 0.00f;	// �䂪�ݑ�����
	static float fHoge = 50.0f;	// �䂪�݋��x
	if (CManager::GetKeyboard()->GetPress(DIK_R))
	{
		fAdd += 0.01f;
	}
	else if	(CManager::GetKeyboard()->GetPress(DIK_F))
	{
		fAdd += -0.01f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_V))
	{
		fAdd = 0.0f;
	}
	CManager::GetRenderer()->SetDebugString("�䂪�݋:" + std::to_string(fAdd));

	int nCntVtxX = 0, nCntVtxY = 0;								// �e�����̒��_�����J�E���g����
	float fEachSizeX = (m_size.x * 2.0f) / SPLIT_ALONG_X_AXIS;	// �|���S��1���������X�����ւ̒��_�z�u�Ԋu
	float fEachSizeY = (m_size.y * 2.0f) / SPLIT_ALONG_Y_AXIS;	// �|���S��1���������Y�����ւ̒��_�z�u�Ԋu

	for (int i = 0; i < m_nNumVtx; i++)
	{
		// ���_���W�̐ݒ� (�T�C�Y�l�����Ƃɂ�������̒��_�ʒu�ɁA�ϓ��ʒu�����Z���ċ�`���`��)
		pVtx[i].pos = {
			m_pos.x - m_size.x + (fEachSizeX * nCntVtxX) + (sinf(fWavePosX) * fHoge),
			m_pos.y - m_size.y + (fEachSizeY * nCntVtxY),
			0.0f };

		// X�������_���̃J�E���g���s��
		if (nCntVtxX >= SPLIT_ALONG_X_AXIS)
		{ // �J�E���g�����������ɒB������

			// X�������_���̃J�E���g�����Z�b�g
			nCntVtxX = 0;

			// Y�������_�����J�E���g�A�b�v
			nCntVtxY++;

			// �䂪�݂𑝉�
			fWavePosX += fAdd;
		}
		else
		{
			// X�������_�����J�E���g�A�b�v
			nCntVtxX++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================================================
// ���_���̐ݒ�
//============================================================================
void CFakeScreen::SetVtx()
{
	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	int nCntVtxX = 0, nCntVtxY = 0;								// �e�����̒��_�����J�E���g����
	float fEachSizeX = (m_size.x * 2.0f) / SPLIT_ALONG_X_AXIS;	// �|���S��1���������X�����ւ̒��_�z�u�Ԋu
	float fEachSizeY = (m_size.y * 2.0f) / SPLIT_ALONG_Y_AXIS;	// �|���S��1���������Y�����ւ̒��_�z�u�Ԋu

	for (int i = 0; i < m_nNumVtx; i++)
	{
		// ���_���W�̐ݒ� (�T�C�Y�l�����Ƃɂ�������̒��_�ʒu�ɁA�ϓ��ʒu�����Z���ċ�`���`��)
		pVtx[i].pos = {
			m_pos.x - m_size.x + (fEachSizeX * nCntVtxX),
			m_pos.y - m_size.y + (fEachSizeY * nCntVtxY),
			0.0f };

		// X�������_���̃J�E���g���s��
		if (nCntVtxX >= SPLIT_ALONG_X_AXIS)
		{ // �J�E���g�����������ɒB������

			// X�������_���̃J�E���g�����Z�b�g
			nCntVtxX = 0;

			// Y�������_�����J�E���g�A�b�v
			nCntVtxY++;
		}
		else
		{
			// X�������_�����J�E���g�A�b�v
			nCntVtxX++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}