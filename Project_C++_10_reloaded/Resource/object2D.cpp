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
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;	// ���_�o�b�t�@�̃|�C���^��������
	m_pTex = nullptr;		// �e�N�X�`���̃|�C���^��������

	m_pos = { 0.0f, 0.0f, 0.0f };	// �ʒu
	m_rot = { 0.0f, 0.0f, 0.0f };	// ����
	m_size = { 0.0f, 0.0f, 0.0f };	// �T�C�Y
	m_fLength = 0.0f;				// �W�J�p�Ίp��
	m_fAngle = 0.0f;				// �Ίp���p�p�x
	m_fTexWidth = 1.0f;				// ���e�N�X�`��������
	m_fTexHeight = 1.0f;			// �c�e�N�X�`�����c��
	m_nNowPatternU = 0;				// ���݂̉��e�N�X�`�����
	m_nNowPatternV = 0;				// ���݂̏c�e�N�X�`�����
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
void CObject2D::Uninit()
{
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
	if (m_pVtxBuff == nullptr)
	{ // ���_�o�b�t�@������
		assert(false);
	}

	// �K�v�Ȑ��l���Z�o
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y);
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
	pVtx[0].tex = { m_fTexWidth * m_nNowPatternU, m_fTexHeight * m_nNowPatternV };
	pVtx[1].tex = { m_fTexWidth * (m_nNowPatternU + 1), m_fTexHeight * m_nNowPatternV };
	pVtx[2].tex = { m_fTexWidth * (m_nNowPatternU), m_fTexHeight * (m_nNowPatternV + 1) };
	pVtx[3].tex = { m_fTexWidth * (m_nNowPatternU + 1), m_fTexHeight * (m_nNowPatternV + 1) };

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================================================
// �`�揈��
//============================================================================
void CObject2D::Draw()
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
// �e�N�X�`������
//============================================================================
void CObject2D::BindTex(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}

//============================================================================
// �ʒu�擾
//============================================================================
D3DXVECTOR3 CObject2D::GetPos()
{
	return m_pos;
}

//============================================================================
// �ʒu�ݒ�
//============================================================================
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================================================
// �����擾
//============================================================================
D3DXVECTOR3 CObject2D::GetRot()
{
	return m_rot;
}

//============================================================================
// �����ݒ�
//============================================================================
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================================================
// �T�C�Y�擾
//============================================================================
D3DXVECTOR3 CObject2D::GetSize()
{
	return m_size;
}

//============================================================================
// �T�C�Y�ݒ�
//============================================================================
void CObject2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//============================================================================
// �W�J�p�Ίp���擾
//============================================================================
float CObject2D::GetLength()
{
	return m_fLength;
}

//============================================================================
// ���e�N�X�`���������ݒ�
//============================================================================
void CObject2D::SetTexWidth(float fWidth)
{
	m_fTexWidth = fWidth;
}

//============================================================================
// �c�e�N�X�`���������ݒ�
//============================================================================
void CObject2D::SetTexHeight(float fHeight)
{
	m_fTexHeight = fHeight;
}

//============================================================================
// ���݂̃e�N�X�`�����������擾
//============================================================================
int CObject2D::GetNowPatternU()
{
	return m_nNowPatternU;
}

//============================================================================
// ���݂̃e�N�X�`�����������ݒ�
//============================================================================
void CObject2D::SetNowPatternU(int nNowPatternU)
{
	m_nNowPatternU = nNowPatternU;
}

//============================================================================
// ���݂̃e�N�X�`���c�������擾
//============================================================================
int CObject2D::GetNowPatternV()
{
	return m_nNowPatternV;
}

//============================================================================
// ���݂̃e�N�X�`���c�������ݒ�
//============================================================================
void CObject2D::SetNowPatternV(int nNowPatternV)
{
	m_nNowPatternV = nNowPatternV;
}

//============================================================================
// ����
//============================================================================
CObject2D* CObject2D::Create()
{
	CObject2D* pObject2D = DBG_NEW CObject2D;

	// �����o���Ă����珉���ݒ�
	if (pObject2D != nullptr)
	{
		pObject2D->Init();
	}

	return pObject2D;
}