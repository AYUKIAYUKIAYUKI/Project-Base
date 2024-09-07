//============================================================================
// 
// �Ƌ� [furniture.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "furniture.h"

// �f�o�C�X�擾�p
#include "renderer.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CFurniture::CFurniture() :
	CObject_X{ static_cast<int>(LAYER::BG) }	// �`��D��x���w��
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CFurniture::~CFurniture()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CFurniture::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CFurniture::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CFurniture::Update()
{
	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CFurniture::Draw()
{
	// �f�o�C�X���擾
	auto pDev = CRenderer::GetInstance()->GetDeviece();

	// �A���t�@�e�X�g��L���ɂ���
	pDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDev->SetRenderState(D3DRS_ALPHAREF, 0);
	pDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���N���X�̕`�揈��
	CObject_X::Draw();

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================================================================
// ����
//============================================================================
CFurniture* CFurniture::Create(D3DXVECTOR3 pos, float fScale, CModel_X_Manager::TYPE type)
{
	// �C���X�^���X�𐶐�
	CFurniture* pFurniture = DBG_NEW CFurniture;

	if (pFurniture == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pFurniture->SetType(TYPE::NONE);

	// ���N���X�̏����ݒ�
	pFurniture->Init();

	// ���W�̐ݒ�
	pFurniture->SetPos(pos);

	// �k�ڂ̐ݒ�
	pFurniture->SetScale(fScale);

	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(type);

	// ���f����ݒ�
	pFurniture->BindModel(model);

	// �T�C�Y��ݒ�
	pFurniture->SetSize(model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pFurniture->Update();

	return pFurniture;
}