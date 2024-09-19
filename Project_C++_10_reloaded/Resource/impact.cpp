//============================================================================
// 
// �Փ˃G�t�F�N�g [impact.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "impact.h"
#include "utility.h"

// �f�o�C�X�擾�p
#include "renderer.h"

// �L�����W�擾�p
#include "barrier_manager.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CImpact::CImpact() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },
	m_Velocity{ 0.0f, 0.0f, 0.0f }
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CImpact::~CImpact()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CImpact::Init()
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
void CImpact::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CImpact::Update()
{
	// ���N���X�̍X�V����
	CObject_X::Update();

	// ��]
	D3DXVECTOR3 NewRot{ GetRot() };
	NewRot = m_Velocity;
	SetRot(NewRot);

	// �����x������
	m_Velocity = CUtility::GetInstance()->AdjustToTarget(m_Velocity, D3DXVECTOR3{ 0.0f, 0.0f, 0.0f }, 0.05f);

	// �ړ�
	D3DXVECTOR3 NewPos = GetPos();
	NewPos += m_Velocity;
	SetPos(NewPos);

	// �k��
	if (CUtility::GetInstance()->DecrementUntilGone(GetScale(), -0.025f))
	{
		// ���g��j��
		CObject::SetRelease();
	}

	// ���ł��邩�`�F�b�N
	//CheckDisappear();
}

//============================================================================
// �`�揈��
//============================================================================
void CImpact::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// �����x���擾
//============================================================================
D3DXVECTOR3& CImpact::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// �����x��ݒ�
//============================================================================
void CImpact::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// ����
//============================================================================
CImpact* CImpact::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Velocity)
{
	CImpact* pImpact = DBG_NEW CImpact{};

	// �������s
	if (!pImpact)
	{
		assert(false);
	}

	// �^�C�v��ݒ�
	pImpact->SetType(CObject::TYPE::NONE);

	// �����ݒ�
	pImpact->Init();

	// ���W�̐ݒ�
	pImpact->SetPos(Pos);

	// �����x��ݒ�
	pImpact->SetVelocity(Velocity);

	// ���f���p�|�C���^
	CModel_X_Manager::MODEL* Model{ nullptr };

	// ���f�����擾
	Model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::IMPACT);

	// ���f����ݒ�
	pImpact->BindModel(Model);

	// �T�C�Y��ݒ�
	pImpact->SetSize(Model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pImpact->Update();

	return pImpact;
}

//============================================================================
// ���ł��邩�`�F�b�N
//============================================================================
void CImpact::CheckDisappear()
{
	// �o���A�̍ł��Ⴂ���W�����������
	if (GetPos().y < CBarrier_Manager::GetCurrentMinPosY())
	{
		// �j��
		SetRelease();
	}
}