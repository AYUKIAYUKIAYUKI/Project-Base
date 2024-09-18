//============================================================================
// 
// �o���A�A���J�[ [barrier_anchor.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "barrier_anchor.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CBarrier_Anchor::CBarrier_Anchor() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) }
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CBarrier_Anchor::~CBarrier_Anchor()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CBarrier_Anchor::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CBarrier_Anchor::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CBarrier_Anchor::Update()
{
	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CBarrier_Anchor::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// ����
//============================================================================
CBarrier_Anchor* CBarrier_Anchor::Create(D3DXVECTOR3 Pos)
{
	// �C���X�^���X�𐶐�
	CBarrier_Anchor* pAnchor = DBG_NEW CBarrier_Anchor{};

	if (pAnchor == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pAnchor->SetType(TYPE::BARRIER_ANCHOR);

	// ���N���X�̏����ݒ�
	pAnchor->Init();

	// ���W�̐ݒ�
	pAnchor->SetPos(Pos);

	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::BARRIER_ANCHOR) };

	// ���f����ݒ�
	pAnchor->BindModel(Model);

	// �T�C�Y��ݒ�
	pAnchor->SetSize(Model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pAnchor->Update();

	return pAnchor;
}