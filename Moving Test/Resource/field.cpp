//============================================================================
// 
// �n�� [field.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "field.h"
#include "main.h"
#include "manager.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CField::CField() : CObject3D(static_cast<int>(LAYER::FRONT_MIDDLE))
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CField::~CField()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CField::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject3D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CField::Uninit()
{
	// ���N���X�̏I������
	CObject3D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CField::Update()
{
	// ���N���X�̍X�V
	CObject3D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CField::Draw()
{
	// ���N���X�̕`�揈��
	CObject3D::Draw();
}

//============================================================================
// ����
//============================================================================
CField* CField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X�𐶐�
	CField* pField = DBG_NEW CField;

	if (pField == nullptr)
	{ // �������s
		assert(false);
	}
	
	pField->SetType(TYPE::NONE);	// �^�C�v��ݒ�

	pField->Init();			// ���N���X�̏����ݒ�
	pField->SetPos(pos);	// ���S�ʒu�̐ݒ�
	pField->SetSize(size);	// �T�C�Y�̐ݒ�

	// �e�N�X�`����ݒ�
	pField->BindTex(CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::BG_000));

	return pField;
}