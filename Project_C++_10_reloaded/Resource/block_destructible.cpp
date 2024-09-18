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
#include "utility.h"
#include "sound.h"

// �I�u�W�F�N�g�擾�p
#include "player.h"
#include "smoke.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CBlockDestructible::CBlockDestructible() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) }	// �`��D��x���w��
{

}

//============================================================================
// �v���C�I���e�B�w��R���X�g���N�^
//============================================================================
CBlockDestructible::CBlockDestructible(LAYER priority) :
	CObject_X{ static_cast<int>(priority) }	// ���N���X�̃R���X�g���N�^
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CBlockDestructible::~CBlockDestructible()
{
	// �v���C���[�^�O�̃I�u�W�F�N�g���擾
	CObject* pObject{ CObject::FindObject(CObject::TYPE::PLAYER) };

	// �擾�o������
	if (pObject)
	{
		// �v���C���[�N���X�Ƀ_�E���L���X�g
		CPlayer* pPlayer{ CUtility::GetInstance()->DownCast<CPlayer, CObject>(pObject) };

		// �G�t�F�N�g���쐬
		for (int i = 0; i < 5; i++)
		{
			// �����_���ȉ����x�𐶐�
			//D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), 0.0f };

			// ���𐶐�
			CSmoke* pSmoke{ CSmoke::Create(
				GetPos(),							// ���W
				-pPlayer->GetVelocity() * 0.5f) };	// �����x

			// �����߂�
			//pSmoke->SetScale(0.5f);
		}
	}
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
	CBlockDestructible* pBlockDestructible = DBG_NEW CBlockDestructible{ LAYER::MIDDLE };

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
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::DESTRUCTIBLE);

	// ���f����ݒ�
	pBlockDestructible->BindModel(model);

	// �T�C�Y��ݒ�
	pBlockDestructible->SetSize(model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pBlockDestructible->Update();

	return pBlockDestructible;
}