//============================================================================
// 
// 2D�I�u�W�F�N�g�Ǘ� [object2D.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object2D.h"
#include "main.h"
#include "manager.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CObject2D::CObject2D()
{
	m_pVtxBuff = nullptr;			// ���_�o�b�t�@�̃|�C���^��������
	m_pTex = nullptr;				// �e�N�X�`���̃|�C���^��������
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CObject2D::~CObject2D()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CObject2D::Init()
{
	// �f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();
	
	// �e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDev,
		"data\\TEXTURE\\.png",
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

	// ��
	pVtx[0].pos = { 100.0f, 100.0f, 0.0f };
	pVtx[1].pos = { 200.0f, 100.0f, 0.0f };
	pVtx[2].pos = { 100.0f, 200.0f, 0.0f };
	pVtx[3].pos = { 200.0f, 200.0f, 0.0f };

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
void CObject2D::Uninit()
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

//============================================================================
// �X�V����
//============================================================================
void CObject2D::Update()
{

}

//============================================================================
// �`�揈��
//============================================================================
void CObject2D::Draw()
{
	// �f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();

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
CObject2D* CObject2D::Create()
{
	CObject2D* pObject2D = new CObject2D;

	// �����o���Ă����珉���ݒ�
	if (pObject2D != nullptr)
	{
		pObject2D->Init();
	}

	return pObject2D;
}