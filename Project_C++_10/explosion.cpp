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
#include "manager.h"
#include "bullet.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CExplosion::CExplosion() : CObject2D(static_cast<int>(LAYER::BACK_MIDDLE))
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
	if (!Animation())
	{ // �j������Ă�����X�V�I��
		return;
	}

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
	CExplosion* pExplosion = new CExplosion;

	// �����o���Ă����珉���ݒ�
	if (pExplosion != nullptr)
	{
		pExplosion->SetType(TYPE::NONE);	// �^�C�v��ݒ�

		pExplosion->Init();			// ���N���X�̏����ݒ�
		pExplosion->SetPos(pos);	// ���S�ʒu�̐ݒ�
		pExplosion->SetSize(size);	// �T�C�Y�̐ݒ�

		pExplosion->SetTexWidth(1.0f / 8.0f);	// ���e�N�X�`��������
		pExplosion->SetTexHeight(1.0f);			// �c�e�N�X�`�����c��
	}

	// �e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 pTex = CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::EXPLOSION_000);

	if (pTex == nullptr)
	{ // �擾���s
		assert(false);
	}

	// �e�N�X�`����ݒ�
	pExplosion->BindTex(pTex);

	return pExplosion;
}

//============================================================================
// �A�j���[�V����
//============================================================================
bool CExplosion::Animation()
{
	// �e�N�X�`���ύX�Ǘ��J�E���g�A�b�v
	m_nCntTexChange++;

	if (m_nCntTexChange >= 10)
	{
		// ���e�N�X�`����ޏ��擾
		int nTexPatternU = CObject2D::GetNowPatternU();

		// ���e�N�X�`����ޕύX
		nTexPatternU++;

		if (nTexPatternU >= 8)
		{
			// ���g��j��
			CObject::Release();

			// �I��
			return false;
		}

		// ���e�N�X�`����ޏ��ݒ�
		CObject2D::SetNowPatternU(nTexPatternU);

		// �ύX�Ǘ��J�E���g�����Z�b�g
		m_nCntTexChange = 0;
	}

	return true;
}