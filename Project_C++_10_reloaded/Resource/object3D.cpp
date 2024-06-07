//============================================================================
// 
// 3D�I�u�W�F�N�g�Ǘ� [object3D.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object3D.h"
#include "main.h"
#include "manager.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;	// ���_�o�b�t�@�̃|�C���^��������
	m_pTex = nullptr;		// �e�N�X�`���̃|�C���^��������

	m_pos = { 0.0f, 0.0f, 0.0f };		// ���S�ʒu
	m_rot = { 0.0f, 0.0f, 0.0f };		// ����
	m_size = { 0.0f, 0.0f, 0.0f };		// �T�C�Y
	m_fLength = 0.0f;					// �W�J�p�Ίp��
	m_fAngle = 0.0f;					// �Ίp���p�p�x
	D3DXMatrixIdentity(&m_mtxWorld);	// ���[���h�s��
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CObject3D::~CObject3D()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CObject3D::Init()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// ���_�o�b�t�@�̐���
	pDev->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	if (m_pVtxBuff == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�̐ݒ�
	pVtx[0].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[1].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[2].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[3].pos = { 0.0f, 0.0f, 0.0f };

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[1].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[2].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[3].nor = { 0.0f, 1.0f, 0.0f };

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
void CObject3D::Uninit()
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
void CObject3D::Update()
{
	if (m_pVtxBuff == nullptr)
	{ // ���_�o�b�t�@������
		assert(false);
	}

	// �K�v�Ȑ��l���v�Z
	m_fAngle = atan2f(m_size.x, m_size.z);
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.z * m_size.z);

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	// �ʒu�̐ݒ�
	pVtx[0].pos = {
		sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f,
		-cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength
	};

	pVtx[1].pos = {
		sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f,
		-cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength
	};

	pVtx[2].pos = {
		sinf(m_rot.z - m_fAngle) * m_fLength,
		0.0f,
		-cosf(m_rot.z - m_fAngle) * m_fLength
	};

	pVtx[3].pos = {
		sinf(m_rot.z + m_fAngle) * m_fLength,
		0.0f,
		-cosf(m_rot.z + m_fAngle) * m_fLength
	};

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// ���[���h�s��̐ݒ�
	SetMtxWorld();
}

//============================================================================
// �`�揈��
//============================================================================
void CObject3D::Draw()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// ���[���h�s��̐ݒ�
	pDev->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDev->SetFVF(FVF_VERTEX_3D);

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
void CObject3D::BindTex(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}

//============================================================================
// ���S�ʒu�擾
//============================================================================
D3DXVECTOR3 CObject3D::GetPos()
{
	return m_pos;
}

//============================================================================
// ���S�ʒu�ݒ�
//============================================================================
void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================================================
// �����擾
//============================================================================
D3DXVECTOR3 CObject3D::GetRot()
{
	return m_rot;
}

//============================================================================
// �����ݒ�
//============================================================================
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================================================
// �T�C�Y�擾
//============================================================================
D3DXVECTOR3 CObject3D::GetSize()
{
	return m_size;
}

//============================================================================
// �T�C�Y�ݒ�
//============================================================================
void CObject3D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//============================================================================
// �W�J�p�Ίp���擾
//============================================================================
float CObject3D::GetLength()
{
	return m_fLength;
}

//============================================================================
// ����
//============================================================================
CObject3D* CObject3D::Create()
{
	CObject3D* pObject3D = DBG_NEW CObject3D;

	// �����o���Ă����珉���ݒ�
	if (pObject3D != nullptr)
	{
		pObject3D->Init();
	}

	return pObject3D;
}

//============================================================================
// ���[���h�s��ݒ�
//============================================================================
void CObject3D::SetMtxWorld()
{
	// �v�Z�p�s��
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�s���������
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�s��쐬
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	// ��]�s��Ƃ̊|���Z
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// ���s�ړ��s��쐬
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	// ���s�ړ��s��Ƃ̊|���Z
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);
}