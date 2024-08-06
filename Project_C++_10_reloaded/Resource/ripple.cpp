//============================================================================
// 
// �g��G�t�F�N�g [ripple.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "ripple.h"
#include "utility.h"

// �f�o�C�X�擾�p
#include "renderer.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CRipple::CRipple() :
	CObject_X(static_cast<int>(LAYER::FRONT_MIDDLE)),	// �v���C�I���e�B�̐ݒ�
	m_velocity{ 0.0f, 0.0f, 0.0f }						// �����x
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CRipple::~CRipple()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CRipple::Init()
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
void CRipple::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CRipple::Update()
{
	// ���N���X�̍X�V����
	CObject_X::Update();

	// ��]
	auto rot{ GetRot() };
#if 1
	rot.x += CUtility::GetInstance()->GetRandomValue<float>() * 0.0001f;
	rot.y += CUtility::GetInstance()->GetRandomValue<float>() * 0.0001f;
	rot.z = atan2f(m_velocity.y, m_velocity.x);
#else
	//rot.x += fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.01f;
	//rot.y += fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.01f;
	rot.x += CUtility::GetInstance()->GetRandomValue<float>() * 0.0001f;
	rot.y += CUtility::GetInstance()->GetRandomValue<float>() * 0.0001f;
	rot.z = atan2f(m_velocity.y, m_velocity.x) + (D3DX_PI * 0.5f);
#endif
	SetRot(rot);

	//// �ړ�
	//D3DXVECTOR3 pos = GetPos();
	//pos += m_velocity;
	//SetPos(pos);

	//// �����x������
	//m_velocity *= 0.9f;

	// �k��
	CUtility::GetInstance()->DecrementUntilGone(GetScale(), -0.01f);

	// �A���t�@�l������
	if (CUtility::GetInstance()->DecrementUntilGone(GetAlpha(), -0.01f))
	{
		// ���g��j��
		CObject::Release();
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CRipple::Draw()
{
	auto pDev{ CRenderer::GetInstance()->GetDeviece() };

	// �[�x�o�b�t�@�ւ̏������݂𖳌���
	pDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���N���X�̕`�揈��
	CObject_X::Draw();

	// �[�x�o�b�t�@�ւ̏������݂𖳌���
	pDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//============================================================================
// �����x���擾
//============================================================================
D3DXVECTOR3& CRipple::GetVelocity()
{
	return m_velocity;
}

//============================================================================
// �����x��ݒ�
//============================================================================
void CRipple::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

//============================================================================
// ����
//============================================================================
CRipple* CRipple::Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity)
{
	CRipple* pRipple = DBG_NEW CRipple{};

	// �������s
	if (!pRipple)
	{
		assert(false);
	}

	// �^�C�v��ݒ�
	pRipple->SetType(CObject::TYPE::NONE);

	// �����ݒ�
	pRipple->Init();

	// ���W�̐ݒ�
	pRipple->SetPos(pos);

	// �����x��ݒ�
	pRipple->SetVelocity(velocity);

	// ���f�����擾
	CModel_X_Manager::MODEL* model{ nullptr };

	switch (rand() % 2)
	{
	case 0:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::RIPPLE02);
		break;

	case 1:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::RIPPLE03);
		break;

	default:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::STAR00);
		break;
	}

	// ���f����ݒ�
	pRipple->BindModel(model);

	// �T�C�Y��ݒ�
	pRipple->SetSize(model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pRipple->Update();

	return pRipple;
}