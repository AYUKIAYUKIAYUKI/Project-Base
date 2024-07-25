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

#include "manager.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CDummy::CDummy(int& nPattern) : m_nPatternRef{ nPattern }
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
	// ����
	Control();

	// �_�~�[�̎�ނ��m�F
	CheckPattern();

	// �ʒu���f�o�b�O�\��
	CManager::GetRenderer()->SetDebugString("�y�_�~�[�ʒu�z");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	CManager::GetRenderer()->SetDebugString(oss.str().c_str());

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
CDummy* CDummy::Create(D3DXVECTOR3 pos, int& nPattern)
{
	// �C���X�^���X�𐶐�
	CDummy* pDummy = DBG_NEW CDummy{ nPattern };

	if (pDummy == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pDummy->SetType(TYPE::DUMMY);

	// ���N���X�̏����ݒ�
	pDummy->Init();
	
	// �ʒu�̐ݒ�
	pDummy->SetPos(pos);
	
	// �A���t�@�l�̐ݒ�
	pDummy->SetAlpha(0.8f);

	// ���f�����擾
	auto model = CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::BLOCK_000);

	// ���̃��f����ݒ�
	pDummy->BindModel(model);

	return pDummy;
}

//============================================================================
// �_�E���L���X�g
//============================================================================
CDummy* CDummy::DownCast(CObject* pObject)
{
	CDummy* pDummy = dynamic_cast<CDummy*>(pObject);

	if (pDummy == nullptr)
	{ // �_�E���L���X�g���s
		assert(false);
	}

	return pDummy;
}

//============================================================================
// ����
//============================================================================
void CDummy::Control()
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

//============================================================================
// �_�~�[�̎�ނ��m�F
//============================================================================
void CDummy::CheckPattern()
{
	// �ߋ��̎�ނ�ێ�����
	static int nOld = 0;

	// ��ނ̕ύX�𔻕�
	if (nOld != m_nPatternRef)
	{
		nOld = m_nPatternRef;
	}
	else
	{ // �ύX��������΃��^�[��
		return;
	}

	CModel_X::MODEL* model;

	switch (m_nPatternRef)
	{
	case 0:

		// �u���b�N���f���Ɍ����ڂ�ύX
		model = CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::BLOCK_000);
		BindModel(model);

		break;

	case 1:

		// ��u���b�N���f���Ɍ����ڂ�ύX
		model = CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::DESTRUCTIBLE);
		BindModel(model);

		break;

	case 2:

		// �X�^�[�g���f���Ɍ����ڂ�ύX
		model = CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::START);
		BindModel(model);

		break;

	case 3:

		// �S�[�����f���Ɍ����ڂ�ύX
		model = CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::GOAL);
		BindModel(model);

		break;

	default:
		assert(false);
		break;
	}
}