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
CDummy::CDummy()
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
CDummy* CDummy::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X�𐶐�
	CDummy* pDummy = DBG_NEW CDummy;

	if (pDummy == nullptr)
	{ // �������s
		assert(false);
	}

	pDummy->SetType(TYPE::DUMMY);	// �^�C�v��ݒ�

	pDummy->Init();			// ���N���X�̏����ݒ�
	pDummy->SetPos(pos);	// �ʒu�̐ݒ�
	pDummy->SetAlpha(0.5f);	// �A���t�@�l�̐ݒ�

	// ��U�u���b�N���f����ݒ�
	pDummy->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::BLOCK_000));

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