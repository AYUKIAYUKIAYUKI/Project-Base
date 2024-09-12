//============================================================================
// 
// ���G�t�F�N�g [star.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "star.h"
#include "utility.h"

// �f�o�C�X�擾�p
#include "renderer.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CStar::CStar() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },	// �`��D��x���w��
	m_velocity{ 0.0f, 0.0f, 0.0f }					// �����x
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CStar::~CStar()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CStar::Init()
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
void CStar::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CStar::Update()
{
	// ���N���X�̍X�V����
	CObject_X::Update();

	// ��]
	//auto rot{ GetRot() };
	//rot = m_velocity * 0.1f;
	//SetRot(rot);

	// �ړ�
	D3DXVECTOR3 pos = GetPos();
	pos += m_velocity;
	m_velocity.x += CUtility::GetInstance()->GetRandomValue<float>() * 0.01f;
	m_velocity.y += CUtility::GetInstance()->GetRandomValue<float>() * 0.01f;
	SetPos(pos);

	// �����x������
	m_velocity *= 0.5f;

	// �A���t�@�l������
	if (CUtility::GetInstance()->DecrementUntilGone(GetAlpha(), -0.01f))
	{
		// ���g��j��
		CObject::SetRelease();
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CStar::Draw()
{
	auto pDev{ CRenderer::GetInstance()->GetDeviece() };

	//// �[�x�o�b�t�@�ւ̏������݂𖳌���
	//pDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���N���X�̕`�揈��
	CObject_X::Draw();

	//// �[�x�o�b�t�@�ւ̏������݂𖳌���
	//pDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//============================================================================
// �����x���擾
//============================================================================
D3DXVECTOR3& CStar::GetVelocity()
{
	return m_velocity;
}

//============================================================================
// �����x��ݒ�
//============================================================================
void CStar::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

//============================================================================
// ����
//============================================================================
CStar* CStar::Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity)
{
	CStar* pStar = DBG_NEW CStar{};

	// �������s
	if (!pStar)
	{
		assert(false);
	}

	// �^�C�v��ݒ�
	pStar->SetType(CObject::TYPE::NONE);

	// �����ݒ�
	pStar->Init();

	// ���W�̐ݒ�
	pStar->SetPos(pos);

	// �����x��ݒ�
	pStar->SetVelocity(velocity);

	// ���f�����擾
	CModel_X_Manager::MODEL* model{ nullptr };

	switch (rand() % 2)
	{
	case 0:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::STAR00);
		break;

	case 1:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::STAR01);
		break;

	default:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::STAR00);
		break;
	}

	// ���f����ݒ�
	pStar->BindModel(model);

	// �T�C�Y��ݒ�
	pStar->SetSize(model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pStar->Update();

	return pStar;
}