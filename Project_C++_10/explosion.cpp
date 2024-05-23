//============================================================================
// 
// ���� [explosion.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "explosion.h"
#include "main.h"
#include "manager.h"
#include "bullet.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CExplosion::CExplosion() : CObject2D::CObject2D()
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
CExplosion::~CExplosion()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CExplosion::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CExplosion::Uninit()
{
	// ���N���X�̏I������
	CObject2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CExplosion::Update()
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

	// �A�j���[�V����
	Animation();
}

//============================================================================
// �`�揈��
//============================================================================
void CExplosion::Draw()
{
	// ���N���X�̕`�揈��
	CObject2D::Draw();
}

//============================================================================
// ����
//============================================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion* pExplosion = new CExplosion;

	// �����o���Ă����珉���ݒ�
	if (pExplosion != nullptr)
	{
		pExplosion->Init();
		pExplosion->m_pos = pos;
		pExplosion->m_size = size;
	}

	// �f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();

	// �e�N�X�`���̃|�C���^
	LPDIRECT3DTEXTURE9 pTex = nullptr;

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDev,
		"data\\TEXTURE\\explosion000.png",
		&pTex);

	// �e�N�X�`����ݒ�
	pExplosion->BindTex(pTex);

	return pExplosion;
}

//============================================================================
// �A�j���[�V����
//============================================================================
void CExplosion::Animation()
{
	// �e�N�X�`���ύX�Ǘ��J�E���g�A�b�v
	m_nCntTexChange++;

	if (m_nCntTexChange >= 15)
	{
		// �e�N�X�`���p�^�[���ύX
		m_nCntTexPattern++;

		if (m_nCntTexPattern >= 8)
		{
			// ���g��j��
			CObject::Release();
		}

		// �ύX�Ǘ��J�E���g�����Z�b�g
		m_nCntTexChange = 0;
	}
}