//============================================================================
// 
// �_�~�[ [dummy.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "dummy.h"

// �L�[�{�[�h�擾�p
#include "manager.h"

// �f�o�b�O�\���p
#include "renderer.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CDummy::CDummy() :
	CObject_X{ static_cast<int>(LAYER::FRONT) }	// �`��D��x���w��
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CDummy::~CDummy()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CDummy::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CDummy::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CDummy::Update()
{
	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CDummy::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// ����
//============================================================================
void CDummy::Control()
{
	// �ړ�
	Translate();

#ifdef _DEBUG
	// �ʒu���f�o�b�O�\��
	CRenderer::GetInstance()->SetDebugString("�y�_�~�[�ʒu�z");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());
#endif	// _DEBUG
}

//============================================================================
// ���f����ύX
//============================================================================
void CDummy::ChangeModel(int nPattern)
{
	switch (nPattern)
	{
	case -1:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::CURSOR));
		break;

	case 0:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::BLOCK_000));
		break;

	case 1:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::DESTRUCTIBLE));
		break;

	case 2:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::DEST_BIG));
		break;

	case 3:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::SPIKES));
		break;

	case 4:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::SPIKES_MOVE));
		break;

	case 5:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::ENEMY));
		break;

	case 6:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::START));
		break;

	case 7:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::GOAL));
		break;

	case 8:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::ACHIEVE));
		break;

	case 9:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::BARRIER_ANCHOR));
		break;

	default:
		assert(false);
		break;
	}
}

//============================================================================
// ����
//============================================================================
CDummy* CDummy::Create()
{
	// �C���X�^���X�𐶐�
	CDummy* pDummy = DBG_NEW CDummy{};

	if (pDummy == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pDummy->SetType(TYPE::DUMMY);

	// ���N���X�̏����ݒ�
	pDummy->Init();
	
	// �A���t�@�l�̐ݒ�
	pDummy->SetAlpha(0.5f);

	return pDummy;
}

//============================================================================
// �ړ�
//============================================================================
void CDummy::Translate()
{
	// �ʒu���擾
	D3DXVECTOR3 pos = GetPos();

	if (CManager::GetKeyboard()->GetPress(DIK_RSHIFT))
	{
		// Y�������Ɉړ�
		if (CManager::GetKeyboard()->GetPress(DIK_W))
		{
			pos.y += 5.0f;
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_S))
		{
			pos.y += -5.0f;
		}

		// X�����Ɉړ�
		if (CManager::GetKeyboard()->GetPress(DIK_A))
		{
			pos.x += -5.0f;
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_D))
		{
			pos.x += 5.0f;
		}
	}
	else
	{
		// Y�������ɃO���b�h�ړ�
		if (CManager::GetKeyboard()->GetTrigger(DIK_W))
		{
			pos.y += 5.0f;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_S))
		{
			pos.y += -5.0f;
		}

		// X�����ɃO���b�h�ړ�
		if (CManager::GetKeyboard()->GetTrigger(DIK_A))
		{
			pos.x += -5.0f;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_D))
		{
			pos.x += 5.0f;
		}
	}

	// �ŏI�I�Ȉʒu�𔽉f
	SetPos(pos);
}