//=============================================================================
//
// �C���v�b�gUI [input_ui.cpp]
// Author : ���c����
//
//=============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "input_ui.h"
#include "utility.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �J�����擾�p
#include "manager.h"

// �t�F�[�Y�擾�p
#include "tutorial_manager.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CInput_UI::CInput_UI() :
	CObject_3D{ static_cast<int>(LAYER::BG) },
	m_nType{ 0 },
	m_TexType{ CTexture_Manager::TYPE::CROWN },
	m_nDuration{ 0 },
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
CInput_UI::~CInput_UI()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CInput_UI::Init()
{
	if (m_nType == 0)
	{
		// ���W�ݒ�
		SetPos({ -3.0f, -10.0f + -50.0f, -10.0f });
		SetPosTarget({ -3.0f, -10.0f, -10.0f });

		// �T�C�Y�ݒ�
		SetSize({ 10.0f, 10.0f, 0.0f });
		SetSizeTarget({ 10.0f, 10.0f, 0.0f });
	}
	else if (m_nType == 1)
	{
		// ���W�ݒ�
		SetPos({ -16.5f, 3.0f + 50.0f, -10.0f });
		SetPosTarget({ -16.5f, 3.0f, -10.0f });

		// �T�C�Y�ݒ�
		SetSize({ 5.5f, 5.5f, 0.0f });
		SetSizeTarget({ 5.5f, 5.5f, 0.0f });
	}
	else if (m_nType == 2)
	{
		// ���W�ݒ�
		SetPos({ 11.0f + 50.0f, 1.0f, -10.0f });
		SetPosTarget({ 11.f, 1.0f, -10.0f });

		// �T�C�Y�ݒ�
		SetSize({ 5.5f, 5.5f, 0.0f });
		SetSizeTarget({ 5.5f, 5.5f, 0.0f });
	}

	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_3D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CInput_UI::Uninit()
{
	// ���N���X�̏I������
	CObject_3D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CInput_UI::Update()
{
	if (!m_bDisappear)
	{
		// ���ʂɉ����čX�V��ύX
		if (m_nType == 0)
		{
			UpdateCNT();
		}
		else if (m_nType == 1)
		{
			UpdateBoard();
		}
		else if (m_nType == 2)
		{
			UpdateSpeech();
		}
	}

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
void CInput_UI::Draw()
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
void CInput_UI::SetAppear()
{
	m_bAppear = true;
}

//============================================================================
// ���Őݒ�
//============================================================================
void CInput_UI::SetDisappear()
{
	m_bDisappear = true;
}

//============================================================================
// �ڕW���W�擾
//============================================================================
D3DXVECTOR3 CInput_UI::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// �ڕW���W�ݒ�
//============================================================================
void CInput_UI::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// �ڕW�����擾
//============================================================================
D3DXVECTOR3 CInput_UI::GetRotTarget()
{
	return m_rotTarget;
}

//============================================================================
// �ڕW�����ݒ�
//============================================================================
void CInput_UI::SetRotTarget(D3DXVECTOR3 rotTarget)
{
	m_rotTarget = rotTarget;
}

//============================================================================
// �ڕW�T�C�Y�擾
//============================================================================
D3DXVECTOR3 CInput_UI::GetSizeTarget()
{
	return m_sizeTarget;
}

//============================================================================
// �ڕW�T�C�Y�ݒ�
//============================================================================
void CInput_UI::SetSizeTarget(D3DXVECTOR3 sizeTarget)
{
	m_sizeTarget = sizeTarget;
}

//============================================================================
// ����
//============================================================================
CInput_UI* CInput_UI::Create(CTexture_Manager::TYPE TexType)
{
	// �C���X�^���X�𐶐�
	CInput_UI* pInput_UI = DBG_NEW CInput_UI{};

	if (pInput_UI == nullptr)
	{ // �������s
		assert(false);
	}

	// �e�N�X�`���^�C�v��ێ�
	pInput_UI->m_TexType = TexType;

	if (TexType == CTexture_Manager::TYPE::CNT)
	{
		pInput_UI->m_nType = 0;
	}
	else if (TexType == CTexture_Manager::TYPE::BOARD)
	{
		pInput_UI->m_nType = 1;
	}
	else if (TexType == CTexture_Manager::TYPE::SPEECH)
	{
		pInput_UI->m_nType = 2;
	}

	// �^�C�v��ݒ�
	pInput_UI->SetType(TYPE::NONE);

	// ���N���X�̏����ݒ�
	pInput_UI->Init();

	// �e�N�X�`����ݒ�
	pInput_UI->BindTex(CTexture_Manager::GetInstance()->GetTexture(TexType));

	// �A���t�@�l��ݒ�
	pInput_UI->SetAlpha(0.0f);

	// �o���ݒ�
	pInput_UI->SetAppear();

	return pInput_UI;
}

//============================================================================
// �o��
//============================================================================
void CInput_UI::Appear()
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
void CInput_UI::Disappear()
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

//============================================================================
// CNT�̍X�V
//============================================================================
void CInput_UI::UpdateCNT()
{
	// BG�J�����̊ԋ�����ݒ�
	CManager::GetCamera()->SetDistanceBG(CUtility::GetInstance()->AdjustToTarget(CManager::GetCamera()->GetDistanceBG(), 35.0f, 0.025f));

	// BG�J�����̖ڕW���W��ݒ�
	CManager::GetCamera()->SetPosBG(CUtility::GetInstance()->AdjustToTarget(CManager::GetCamera()->GetPosBG(), D3DXVECTOR3{ -3.0f, -12.5f, 0.0f }, 0.025f));

	// �e�N�X�`�����f
	if (m_nDuration < 5)
	{
		m_nDuration++;

	}
	else
	{
		m_nDuration = 0;

		// �t�F�[�Y�ɉ����č����ւ��ύX
		switch (CTutorial_Manager::GetTexType())
		{
		case CTexture_Manager::TYPE::TEXT00:
			if (m_TexType != CTexture_Manager::TYPE::CNT_M0)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_M0;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			else if (m_TexType != CTexture_Manager::TYPE::CNT_M1)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_M1;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			break;

		case CTexture_Manager::TYPE::TEXT01:
			if (m_TexType != CTexture_Manager::TYPE::CNT_B0)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_B0;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			else if (m_TexType != CTexture_Manager::TYPE::CNT_B1)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_B1;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			break;

		case CTexture_Manager::TYPE::TEXT05:
			if (m_TexType != CTexture_Manager::TYPE::CNT_M2)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_M2;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			else if (m_TexType != CTexture_Manager::TYPE::CNT_M3)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_M3;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			break;

		default:
			m_TexType = CTexture_Manager::TYPE::CNT;
			BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			break;
		}
	}
}

//============================================================================
// �{�[�h�̍X�V
//============================================================================
void CInput_UI::UpdateBoard()
{
	// �V���������쐬
	D3DXVECTOR3 NewPosTarget{ GetPosTarget() };

	// �؂�ւ��X�C�b�`
	static bool bSwitch{ false };

	if (bSwitch)
	{
		NewPosTarget.x = CUtility::GetInstance()->AdjustToTarget(NewPosTarget.x, -16.6f, 0.03f);
		
		if (NewPosTarget.x <= -16.59f)
		{
			bSwitch = !bSwitch;
		}
	}
	else
	{
		NewPosTarget.x = CUtility::GetInstance()->AdjustToTarget(NewPosTarget.x, -16.4f, 0.03f);

		if (NewPosTarget.x >= -16.41f)
		{
			bSwitch = !bSwitch;
		}
	}

	// ���W�𔽉f
	SetPosTarget(NewPosTarget);
}

//============================================================================
// �ӂ������̍X�V
//============================================================================
void CInput_UI::UpdateSpeech()
{
	// �V���������쐬
	D3DXVECTOR3 NewPosTarget{ GetPosTarget() };

	// ������
	static float fAdder{ 0.0035f };

	// ��������
	NewPosTarget.y += fAdder;

	if (NewPosTarget.y >= 1.0f + 0.2f || NewPosTarget.y <= 1.0f + -0.2f)
	{
		fAdder *= -1.0f;
	}

	// ���W�𔽉f
	SetPosTarget(NewPosTarget);
}