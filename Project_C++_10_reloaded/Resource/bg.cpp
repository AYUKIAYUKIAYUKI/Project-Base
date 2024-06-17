//============================================================================
// 
// �w�i [bg.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "bg.h"
#include "manager.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CBg::CBg() : CObject_2D(static_cast<int>(LAYER::BACK))
{
	m_nCntPAKU = 0;		// �p�N�p�N��
	m_nDelayPAKU = 0;	// �p�N�p�N�x��
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CBg::~CBg()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CBg::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_2D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CBg::Uninit()
{
	// ���N���X�̏I������
	CObject_2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CBg::Update()
{
	// �p�N�p�N���܂�
	PAKUPAKU();

	// ���N���X�̍X�V
	CObject_2D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CBg::Draw()
{
	// ���N���X�̕`�揈��
	CObject_2D::Draw();
}

//============================================================================
// ����
//============================================================================
CBg* CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X�𐶐�
	CBg* pBg = DBG_NEW CBg;

	if (pBg == nullptr)
	{ // �������s
		assert(false);
	}

	pBg->SetType(TYPE::NONE);	// �^�C�v��ݒ�

	pBg->Init();		// ���N���X�̏����ݒ�
	pBg->SetPos(pos);	// �ʒu�̐ݒ�
	pBg->SetSize(size);	// �T�C�Y�̐ݒ�

	// �e�N�X�`����ݒ�
	pBg->BindTex(CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::BG_000));

	return pBg;
}

//============================================================================
// �p�N�p�N���܂�
//============================================================================
void CBg::PAKUPAKU()
{
	m_nDelayPAKU++;

	if (m_nCntPAKU <= 0)
	{
		if (m_nDelayPAKU >= 140)
		{
			BindTex(CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::BG_000));

			m_nCntPAKU++;

			m_nDelayPAKU = 0;
		}
		if (m_nDelayPAKU >= 120)
		{
			BindTex(CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::BG_001));
		}
	}
	else
	{
		if (m_nDelayPAKU >= 40)
		{
			BindTex(CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::BG_000));

			m_nCntPAKU++;

			m_nDelayPAKU = 0;

			if (m_nCntPAKU >= 4)
			{
				m_nCntPAKU = 0;
			}
		}
		if (m_nDelayPAKU >= 20)
		{
			BindTex(CManager::CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::BG_001));
		}
	}
}