//============================================================================
// 
// 3D���� [explosion3D.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "explosion3D.h"
#include "manager.h"
#include "bullet.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CExplosion3D::CExplosion3D() : CObjectBillboard(static_cast<int>(LAYER::FRONT_MIDDLE))
{
	m_nCntTexChange = 0;	// �e�N�X�`���ύX�Ǘ�
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CExplosion3D::~CExplosion3D()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CExplosion3D::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObjectBillboard::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CExplosion3D::Uninit()
{
	// ���N���X�̏I������
	CObjectBillboard::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CExplosion3D::Update()
{
	// �A�j���[�V����
	if (!Animation())
	{ // �j������Ă�����X�V�I��
		return;
	}

	// ���N���X�̍X�V
	CObjectBillboard::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CExplosion3D::Draw()
{
	// ���N���X�̕`�揈��
	CObjectBillboard::Draw();
}

//============================================================================
// ����
//============================================================================
CExplosion3D* CExplosion3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X�𐶐�
	CExplosion3D* pExplosion = new CExplosion3D;

	if (pExplosion == nullptr)
	{ // �������s
		assert(false);
	}

	pExplosion->SetType(TYPE::NONE);	// �^�C�v��ݒ�

	pExplosion->Init();			// ���N���X�̏����ݒ�
	pExplosion->SetPos(pos);	// ���S�ʒu�̐ݒ�
	pExplosion->SetSize(size);	// �T�C�Y�̐ݒ�

	pExplosion->SetTexWidth(1.0f / 8.0f);	// ���e�N�X�`��������
	pExplosion->SetTexHeight(1.0f);			// �c�e�N�X�`�����c��

	// �e�N�X�`����ݒ�
	pExplosion->BindTex(CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::EXPLOSION_000));

	return pExplosion;
}

//============================================================================
// �A�j���[�V����
//============================================================================
bool CExplosion3D::Animation()
{
	// �e�N�X�`���ύX�Ǘ��J�E���g�A�b�v
	m_nCntTexChange++;

	if (m_nCntTexChange >= 10)
	{
		// ���e�N�X�`����ޏ��擾
		int nTexPatternU = CObjectBillboard::GetNowPatternU();

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
		CObjectBillboard::SetNowPatternU(nTexPatternU);

		// �ύX�Ǘ��J�E���g�����Z�b�g
		m_nCntTexChange = 0;
	}

	return true;
}