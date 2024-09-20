//=============================================================================
//
// ��Ƃ� [hand.cpp]
// Author : ���c����
//
//=============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "hand.h"
#include "utility.h"

// �f�o�b�O�\���p
#include "renderer.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CHand::CHand() :
	CObject_3D{ static_cast<int>(LAYER::BG) },
	m_TexType{ CTexture_Manager::TYPE::CROWN },
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
CHand::~CHand()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CHand::Init()
{
	if (m_TexType == CTexture_Manager::TYPE::LHAND)
	{
		// ���W�ݒ�
		SetPos({ -3.0f + -50.0f, -10.0f + -50.0f, -10.0f, });
		SetPosTarget({ -3.0f, -10.0f, -10.0f, });

		// �T�C�Y�ݒ�
		SetSize({ 10.0f, 10.0f, 0.0f, });
		SetSizeTarget({ 10.0f, 10.0f, 0.0f, });
	}
	else if (m_TexType == CTexture_Manager::TYPE::RHAND)
	{
		// ���W�ݒ�
		SetPos({ -3.0f + 50.0f, -10.0f + -50.0f, -10.0f, });
		SetPosTarget({ -3.0f, -10.0f, -10.0f, });

		// �T�C�Y�ݒ�
		SetSize({ 10.0f, 10.0f, 0.0f, });
		SetSizeTarget({ 10.0f, 10.0f, 0.0f, });
	}

	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_3D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CHand::Uninit()
{
	// ���N���X�̏I������
	CObject_3D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CHand::Update()
{
#ifdef _DEBUG

	CRenderer::GetInstance()->SetDebugString("�y����W�z");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(6) << "X:" << GetPos().x << "\nY:" << GetPos().y << "\nY:" << GetPos().z;
	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());

#endif // _DEBUG

	// �o��
	Appear();

	// ����
	Disappear();

	// �ڕW���W��
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), m_posTarget, 0.1f));

	// �ڕW������
	SetRot(CUtility::GetInstance()->AdjustToTarget(GetRot(), m_rotTarget, 0.1f));

	// �ڕW�T�C�Y��
	SetSize(CUtility::GetInstance()->AdjustToTarget(GetSize(), m_sizeTarget, 0.1f));

#ifdef _DEBUG

	// ������\��
	CRenderer::GetInstance()->SetDebugString(std::to_string(GetRot().z));

#endif // _DEBUG

	// ���N���X�̍X�V
	CObject_3D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CHand::Draw()
{
	auto pDev{ CRenderer::GetInstance()->GetDeviece() };

	// �[�x�e�X�g�̔�r���@�̕ύX
	pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// �[�x�o�b�t�@�ɕ`�悵�Ȃ�
	pDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���C�g���f�𖳌��ɂ���
	pDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���N���X�̕`�揈��
	CObject_3D::Draw();

	// ���C�g���f��L���ɂ���
	pDev->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �[�x�e�X�g�̔�r���@�̕ύX
	pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// �[�x�o�b�t�@�ɏ�������
	pDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//============================================================================
// �o���ݒ�
//============================================================================
void CHand::SetAppear()
{
	m_bAppear = true;
}

//============================================================================
// ���Őݒ�
//============================================================================
void CHand::SetDisappear()
{
	m_bDisappear = true;
}

//============================================================================
// �ڕW���W�擾
//============================================================================
D3DXVECTOR3 CHand::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// �ڕW���W�ݒ�
//============================================================================
void CHand::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// �ڕW�����擾
//============================================================================
D3DXVECTOR3 CHand::GetRotTarget()
{
	return m_rotTarget;
}

//============================================================================
// �ڕW�����ݒ�
//============================================================================
void CHand::SetRotTarget(D3DXVECTOR3 rotTarget)
{
	m_rotTarget = rotTarget;
}

//============================================================================
// �ڕW�T�C�Y�擾
//============================================================================
D3DXVECTOR3 CHand::GetSizeTarget()
{
	return m_sizeTarget;
}

//============================================================================
// �ڕW�T�C�Y�ݒ�
//============================================================================
void CHand::SetSizeTarget(D3DXVECTOR3 sizeTarget)
{
	m_sizeTarget = sizeTarget;
}

//============================================================================
// ����
//============================================================================
CHand* CHand::Create(CTexture_Manager::TYPE TexType)
{
	// �C���X�^���X�𐶐�
	CHand* pHand = DBG_NEW CHand{};

	if (pHand == nullptr)
	{ // �������s
		assert(false);
	}

	// �e�N�X�`���^�C�v��ێ�
	pHand->m_TexType = TexType;

	// �^�C�v��ݒ�
	pHand->SetType(TYPE::NONE);

	// ���N���X�̏����ݒ�
	pHand->Init();

	// �e�N�X�`����ݒ�
	pHand->BindTex(CTexture_Manager::GetInstance()->GetTexture(TexType));

	// �A���t�@�l��ݒ�
	pHand->SetAlpha(0.0f);

	// �o���ݒ�
	pHand->SetAppear();
	
	return pHand;
}

//============================================================================
// �o��
//============================================================================
void CHand::Appear()
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
void CHand::Disappear()
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