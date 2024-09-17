//============================================================================
// 
// ��ł��u���b�N [block_destructible_big.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "block_destructible_big.h"
#include "utility.h"
#include "sound.h"

// �I�u�W�F�N�g�擾�p
#include "smoke.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CBlockDestructibleBig::CBlockDestructibleBig() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },
	m_nLife{ 0 }
{

}

//============================================================================
// �v���C�I���e�B�w��R���X�g���N�^
//============================================================================
CBlockDestructibleBig::CBlockDestructibleBig(LAYER priority) :
	CObject_X{ static_cast<int>(priority) }
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CBlockDestructibleBig::~CBlockDestructibleBig()
{
	for (int i = 0; i < 5; i++)
	{
		// �����_���ȉ����x�𐶐�
		D3DXVECTOR3 velocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

		// ���𐶐�
		CSmoke::Create(
			GetPos(),			// ���W
			velocity * 0.005f);	// �����x
	}
}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CBlockDestructibleBig::Init()
{
	// ���C�t��ݒ�
	m_nLife = 2;

	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CBlockDestructibleBig::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CBlockDestructibleBig::Update()
{
	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CBlockDestructibleBig::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// �_���[�W����
//============================================================================
bool CBlockDestructibleBig::Damage(int nAtk)
{
	// �̗͂����炷
	m_nLife += nAtk;

	// �̗͂������Ȃ��
	if (m_nLife <= 0)
	{
		// �j������
		SetRelease();

		return false;
	}

	// ���f�����擾
	auto model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::DEST_BIG_DAMAGE) };

	// ���f����ݒ�
	BindModel(model);

	return true;
}

//============================================================================
// ����
//============================================================================
CBlockDestructibleBig* CBlockDestructibleBig::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X�𐶐�
	CBlockDestructibleBig* pBlockDestructible = DBG_NEW CBlockDestructibleBig{ LAYER::MIDDLE };

	if (pBlockDestructible == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pBlockDestructible->SetType(TYPE::DEST_BIG);

	// ���N���X�̏����ݒ�
	pBlockDestructible->Init();

	// ���W�̐ݒ�
	pBlockDestructible->SetPos(pos);

	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::DEST_BIG);

	// ���f����ݒ�
	pBlockDestructible->BindModel(model);

	// �T�C�Y��ݒ�
	pBlockDestructible->SetSize(model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pBlockDestructible->Update();

	return pBlockDestructible;
}