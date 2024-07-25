//============================================================================
// 
// ��u���b�N [block_destructible.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "block_destructible.h"
#include "manager.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CBlockDestructible::CBlockDestructible() : CObject_X{ static_cast<int>(LAYER::FRONT_MIDDLE) }
{

}

//============================================================================
// �v���C�I���e�B�w��R���X�g���N�^
//============================================================================
CBlockDestructible::CBlockDestructible(LAYER priority) : CObject_X{ static_cast<int>(priority) }
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CBlockDestructible::~CBlockDestructible()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CBlockDestructible::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CBlockDestructible::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CBlockDestructible::Update()
{
	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CBlockDestructible::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// ����
//============================================================================
CBlockDestructible* CBlockDestructible::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X�𐶐�
	CBlockDestructible* pBlockDestructible = DBG_NEW CBlockDestructible{ LAYER::FRONT_MIDDLE };

	if (pBlockDestructible == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pBlockDestructible->SetType(TYPE::DESTRUCTIBLE);

	// ���N���X�̏����ݒ�
	pBlockDestructible->Init();

	// ���W�̐ݒ�
	pBlockDestructible->SetPos(pos);

	// ���f�����擾
	auto model = CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::DESTRUCTIBLE);

	// ���f����ݒ�
	pBlockDestructible->BindModel(model);

	// �T�C�Y��ݒ�
	pBlockDestructible->SetSize(model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pBlockDestructible->Update();

	return pBlockDestructible;
}

//============================================================================
// �_�E���L���X�g
//============================================================================
CBlockDestructible* CBlockDestructible::DownCast(CObject* pObject)
{
	CBlockDestructible* pBlockDestructible = dynamic_cast<CBlockDestructible*>(pObject);

	if (pBlockDestructible == nullptr)
	{ // �_�E���L���X�g���s
		assert(false);
	}

	return pBlockDestructible;
}