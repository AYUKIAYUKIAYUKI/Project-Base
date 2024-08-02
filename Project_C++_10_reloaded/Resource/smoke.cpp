//============================================================================
// 
// ���G�t�F�N�g [smoke.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "smoke.h"
#include "utility.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CSmoke::CSmoke() :
	m_velocity{ 0.0f, 0.0f, 0.0f }	// �����x
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CSmoke::~CSmoke()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CSmoke::Init()
{
	// ���N���X�̏����ݒ�
	if (FAILED(CObject_X::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CSmoke::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CSmoke::Update()
{
	// ���N���X�̍X�V����
	CObject_X::Update();

	// ��]
	auto rot{ GetRot() };
	rot = m_velocity;
	SetRot(rot);

	// �ړ�
	D3DXVECTOR3 pos = GetPos();
	pos += m_velocity;
	SetPos(pos);

	// �����x������
	m_velocity *= 0.97f;

	// �A���t�@�l������
	if (CUtility::GetInstance()->DecrementUntilGone(GetAlpha(), 0.0f))
	//if (CUtility::GetInstance()->DecrementUntilGone(GetAlpha(), -0.005f))
	{
		// ���g��j��
		CObject::Release();
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CSmoke::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// �����x���擾
//============================================================================
D3DXVECTOR3& CSmoke::GetVelocity()
{
	return m_velocity;
}

//============================================================================
// �����x��ݒ�
//============================================================================
void CSmoke::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

//============================================================================
// ����
//============================================================================
CSmoke* CSmoke::Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity)
{
	CSmoke* pSmoke = DBG_NEW CSmoke{};

	// �������s
	if (!pSmoke)
	{
		assert(false);
	}

	// �^�C�v��ݒ�
	pSmoke->SetType(CObject::TYPE::NONE);

	// �����ݒ�
	pSmoke->Init();

	// ���W�̐ݒ�
	pSmoke->SetPos(pos);

	// �����x��ݒ�
	pSmoke->SetVelocity(velocity);

	// ���f���̃|�C���^
	CModel_X_Manager::MODEL* model{ nullptr };

	// �����_���Ƀ��f�����擾
	switch (rand() % 3)
	{
	case 0:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::STAR00);
		break;

	case 1:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PARTICLE01);
		break;

	case 2:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PARTICLE02);
		break;

	default:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::STAR00);
		break;
	}

	// ���f����ݒ�
	pSmoke->BindModel(model);

	// �T�C�Y��ݒ�
	pSmoke->SetSize(model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pSmoke->Update();

	return pSmoke;
}