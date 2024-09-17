//============================================================================
// 
// �A�`�[�u [achievement.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "achievement.h"
#include "utility.h"

// �X�e�[�W���擾�p
#include "game_manager.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CAchieve::CAchieve() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) }	// �`��D��x���w��
{

}

//============================================================================
// �v���C�I���e�B�w��R���X�g���N�^
//============================================================================
CAchieve::CAchieve(LAYER priority) :
	CObject_X{ static_cast<int>(priority) }	// �`��D��x���w��
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CAchieve::~CAchieve()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CAchieve::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CAchieve::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CAchieve::Update()
{
	// ��]
	D3DXVECTOR3 rotTarget =  GetRot();
	rotTarget.y += 0.05f;
	SetRot(rotTarget);

	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CAchieve::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// ����
//============================================================================
CAchieve* CAchieve::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X�𐶐�
	CAchieve* pAchieve = DBG_NEW CAchieve{};

	if (pAchieve == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pAchieve->SetType(TYPE::ACHIEVE);

	// ���N���X�̏����ݒ�
	pAchieve->Init();

	// �ʒu�̐ݒ�
	pAchieve->SetPos(pos);

	// ���ݑI�����Ă��郌�x�����擾
	int nSelectLevel{ CGameManager::GetInstance()->GetSelectLevel() };

	// �A�`�[�u�����g�̉����Ԃ��擾
	std::vector<bool> vbCollectAchieve{ CGameManager::GetInstance()->GetCollectAchieve() };

	CModel_X_Manager::TYPE Type{ CModel_X_Manager::TYPE::ACHIEVE };

	// ���̃��x���̃A�`�[�u�����g��������Ă�����
	if (vbCollectAchieve[nSelectLevel])
	{
		Type = CModel_X_Manager::TYPE::ACHIEVE_LOST;
	}

	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(Type) };

	// ���f����ݒ�
	pAchieve->BindModel(Model);

	// �T�C�Y��ݒ�
	pAchieve->SetSize(Model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pAchieve->Update();

	return pAchieve;
}