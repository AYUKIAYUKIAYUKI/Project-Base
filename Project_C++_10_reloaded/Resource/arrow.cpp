//=============================================================================
//
// ��� [arrow.cpp]
// Author : ���c����
//
//=============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "arrow.h"
#include "utility.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �e�N�X�`���擾�p
#include "texture_manager.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CArrow::CArrow() :
	CObject_3D{ static_cast<int>(LAYER::MIDDLE) },
	m_bAppear{ false },
	m_bDisappear{ false },
	m_posTarget{ 0.0f, 0.0f, 0.0f },
	m_rotTarget{ 0.0f, 0.0f, 0.0f },
	m_sizeTarget{ 0.0f, 0.0f, 0.0f },
	m_colTarget{ 0.0f, 0.0f, 0.0f, 0.0f }
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CArrow::~CArrow()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CArrow::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_3D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CArrow::Uninit()
{
	// ���N���X�̏I������
	CObject_3D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CArrow::Update()
{
	// �o��
	Appear();

	// ����
	Disappear();

	// �ڕW���W��
	//SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), m_posTarget, 0.1f));

	// �ڕW������
	//SetRot(CUtility::GetInstance()->AdjustToTarget(GetRot(), m_rotTarget, 0.1f));

	// �ڕW�T�C�Y��
	SetSize(CUtility::GetInstance()->AdjustToTarget(GetSize(), m_sizeTarget, 0.1f));

	// ���݂̌���
	CRenderer::GetInstance()->SetDebugString("���̌���" + std::to_string(GetRot().z));

	// ���N���X�̍X�V
	CObject_3D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CArrow::Draw()
{
	auto pDev{ CRenderer::GetInstance()->GetDeviece() };

	// ���C�g���f�𖳌��ɂ���
	pDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���N���X�̕`�揈��
	CObject_3D::Draw();

	// ���C�g���f��L���ɂ���
	pDev->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================================================
// �o���ݒ�
//============================================================================
void CArrow::SetAppear()
{
	m_bAppear = true;
}

//============================================================================
// ���Őݒ�
//============================================================================
void CArrow::SetDisappear()
{
	m_bDisappear = true;
}

//============================================================================
// �ڕW���W�擾
//============================================================================
D3DXVECTOR3 CArrow::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// �ڕW���W�ݒ�
//============================================================================
void CArrow::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// �ڕW�����擾
//============================================================================
D3DXVECTOR3 CArrow::GetRotTarget()
{
	return m_rotTarget;
}

//============================================================================
// �ڕW�����ݒ�
//============================================================================
void CArrow::SetRotTarget(D3DXVECTOR3 rotTarget)
{
	m_rotTarget = rotTarget;
}

//============================================================================
// �ڕW�T�C�Y�擾
//============================================================================
D3DXVECTOR3 CArrow::GetSizeTarget()
{
	return m_sizeTarget;
}

//============================================================================
// �ڕW�T�C�Y�ݒ�
//============================================================================
void CArrow::SetSizeTarget(D3DXVECTOR3 sizeTarget)
{
	m_sizeTarget = sizeTarget;
}

//============================================================================
// ����
//============================================================================
CArrow* CArrow::Create()
{
	// �C���X�^���X�𐶐�
	CArrow* pArrow = DBG_NEW CArrow{};

	if (pArrow == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pArrow->SetType(TYPE::NONE);

	// ���N���X�̏����ݒ�
	pArrow->Init();

	// �e�N�X�`����ݒ�
	pArrow->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::ARROW));

	// �A���t�@�l��ݒ�
	pArrow->SetAlpha(0.0f);

	return pArrow;
}

//============================================================================
// �o��
//============================================================================
void CArrow::Appear()
{
	if (!m_bAppear)
	{
		return;
	}

	// �A���t�@�l���擾
	float& fAlpha{ GetAlpha() };

	// ���X�ɓo��
	fAlpha += 0.05f;

	// �ő�l�ɓ��B�ŌŒ�
	if (fAlpha > 1.0f)
	{
		fAlpha = 1.0f;

		// �o���I��
		m_bAppear = false;
	}
}

//============================================================================
// ����
//============================================================================
void CArrow::Disappear()
{
	if (!m_bDisappear)
	{
		return;
	}

	// �A���t�@�l���擾
	float& fAlpha{ GetAlpha() };

	// ���X�ɏ���
	fAlpha += -0.1f;

	// �Œ�l�ɓ��B�ŌŒ�
	if (fAlpha < 0.0f)
	{
		fAlpha = 0.0f;

		// �o���I��
		m_bDisappear = false;

		// �j���\��
		SetRelease();
	}
}