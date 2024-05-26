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
	m_nCntTexChange = 0;	// �e�N�X�`���ύX�Ǘ�
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
	// �A�j���[�V����
	Animation();

	// ���N���X�̍X�V
	CObject2D::Update();
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
	// �����𐶐�
	CExplosion* pExplosion = new CExplosion;

	// �����o���Ă����珉���ݒ�
	if (pExplosion != nullptr)
	{
		pExplosion->Init();			// ���N���X�̏����ݒ�
		pExplosion->SetPos(pos);	// ���S�ʒu�̐ݒ�
		pExplosion->SetSize(size);	// �T�C�Y�̐ݒ�

		pExplosion->SetTexWidth(1.0f / 8.0f);	// ���e�N�X�`��������
		pExplosion->SetTexHeight(1.0f);			// �c�e�N�X�`�����c��
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
		// ���e�N�X�`����ޏ��擾
		int nTexPatternU = CObject2D::GetNowPatternU();

		// ���e�N�X�`����ޕύX
		nTexPatternU++;

		if (nTexPatternU >= 8)
		{
			// ���g��j��
			CObject::Release();
		}

		// ���e�N�X�`����ޏ��ݒ�
		CObject2D::SetNowPatternU(nTexPatternU);

		// �ύX�Ǘ��J�E���g�����Z�b�g
		m_nCntTexChange = 0;
	}
}