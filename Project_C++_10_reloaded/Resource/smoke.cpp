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

// �f�o�C�X�擾�p
#include "renderer.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CSmoke::CSmoke() :
	CObject_X(static_cast<int>(LAYER::FRONT_MIDDLE)),	// �v���C�I���e�B�̐ݒ�
	m_velocity{ 0.0f, 0.0f, 0.0f }						// �����x
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
	rot += m_velocity;
	SetRot(rot);

	// �ړ�
	D3DXVECTOR3 pos = GetPos();
	pos += m_velocity;
	SetPos(pos);

	// �����x������
	m_velocity *= 0.9f;

	// �g��
	CUtility::GetInstance()->DecrementUntilGone(GetScale(), 0.01f);

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
void CSmoke::Draw()
{
	auto pDev{ CRenderer::GetInstance()->GetDeviece() };

	// �[�x�o�b�t�@�ւ̏������݂𖳌���
	pDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���_�@���̎������K����L����
	//pDev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// ���N���X�̕`�揈��
	CObject_X::Draw();

	// ���_�@���̎������K���𖳌���
	//pDev->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	// �[�x�o�b�t�@�ւ̏������݂𖳌���
	pDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
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

	// ���f�����擾
	auto model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PARTICLE02) };

	// ���f����ݒ�
	pSmoke->BindModel(model);

	// �T�C�Y��ݒ�
	pSmoke->SetSize(model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pSmoke->Update();

	return pSmoke;
}