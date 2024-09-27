//============================================================================
// 
// �^�C�g�� [title.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "title.h"
#include "utility.h"
#include "fakescreen.h"

// �C���v�b�g�擾�p
#include "manager.h"

// �e�N�X�`���擾�p
#include "texture_manager.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CTitle::CTitle() : m_pBg { nullptr },
	m_nSelect{ 0 }
{
	for (int i = 0; i < static_cast<int>(UI_TYPE::MAX); i++)
	{
		m_pUI[i] = nullptr;
	}
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CTitle::~CTitle()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CTitle::Init()
{
	// �w�i�̐���
	m_pBg = CBg::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// �ʒu
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// �T�C�Y
		CTexture_Manager::TYPE::BG_000);						// �e�N�X�`��

	// �^�C�g�����S�̐���
	m_pUI[3] = CText::Create(CTexture_Manager::TYPE::LOGO);
	m_pUI[3]->SetPos({ SCREEN_WIDTH * 0.5f, 0.0f, 0.0f });
	m_pUI[3]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f });
	m_pUI[3]->SetSizeTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f });
	m_pUI[3]->SetAppear(true);

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CTitle::Uninit()
{
	// ���N���X�̏I������
	CScene::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CTitle::Update()
{
	// �p�b�h���擾
	CInputPad* pPad = CManager::GetPad();

	// ���E�̓��͏��
	static DWORD dwOldInput{ 0 };
	static bool bInputUp{ false };
	static bool bInputDown{ false };

	// ��^���g���K�[����
	if (pPad->GetJoyStickL().Y > 0 && dwOldInput == 0)
	{
		bInputUp = true;
	}
	else
	{
		bInputUp = false;
	}

	// ���^���g���K�[����
	if (pPad->GetJoyStickL().Y < 0 && dwOldInput == 0)
	{
		bInputDown = true;
	}
	else
	{
		bInputDown = false;
	}

	// �ߋ��̓��͏���ێ�
	dwOldInput = pPad->GetJoyStickL().Y;

	// ���}���u
	if (m_nSelect == 0)
	{
		if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) ||
			pPad->GetTrigger(CInputPad::JOYKEY::START) ||
			pPad->GetTrigger(CInputPad::JOYKEY::A) ||
			pPad->GetTrigger(CInputPad::JOYKEY::B) ||
			pPad->GetTrigger(CInputPad::JOYKEY::X) ||
			pPad->GetTrigger(CInputPad::JOYKEY::Y))
		{
			m_nSelect = 1;

			if (!m_pUI[0])
			{
				m_pUI[0] = CText::Create(CTexture_Manager::TYPE::NORMAL);
				m_pUI[0]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.55f, 0.0f });
				m_pUI[0]->SetSizeTarget({ 250.0f, 62.5f, 0.0f });
				m_pUI[0]->SetCol({ 0.5f, 0.5f, 0.5f, 0.0f });
				m_pUI[0]->SetAppear(true);
			}

			if (!m_pUI[1])
			{
				m_pUI[1] = CText::Create(CTexture_Manager::TYPE::CHALLENGE);
				m_pUI[1]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.75f, 0.0f });
				m_pUI[1]->SetSizeTarget({ 250.0f, 62.5f, 0.0f });
				m_pUI[1]->SetCol({ 0.5f, 0.5f, 0.5f, 0.0f });
				m_pUI[1]->SetAppear(true);
			}

			if (!m_pUI[2])
			{
				m_pUI[2] = CText::Create(CTexture_Manager::TYPE::CURSOR);
				m_pUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.55f, 0.0f });
				m_pUI[2]->SetSizeTarget({ 30.0f, 30.0f, 0.0f });
				m_pUI[2]->SetAppear(true);
			}

			m_pUI[3]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f });
			m_pUI[3]->SetSizeTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f, 0.0f });
		}
	}
	else
	{
		// BG�J�����̊ԋ�����ݒ�
		CManager::GetCamera()->SetDistanceBG(CUtility::GetInstance()->AdjustToTarget(CManager::GetCamera()->GetDistanceBG(), 25.0f, 0.025f));

		if (m_nSelect == 1)
		{
			if (m_pUI[0])
			{
				m_pUI[0]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.55f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
				m_pUI[0]->SetCol({ 1.0f, 1.0f, 1.0f, m_pUI[0]->GetAlpha() });
			}

			if (m_pUI[2])
			{
				m_pUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.55f, 0.0f });
			}

			if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) ||
				pPad->GetTrigger(CInputPad::JOYKEY::START) ||
				pPad->GetTrigger(CInputPad::JOYKEY::A) ||
				pPad->GetTrigger(CInputPad::JOYKEY::B) ||
				pPad->GetTrigger(CInputPad::JOYKEY::X) ||
				pPad->GetTrigger(CInputPad::JOYKEY::Y))
			{
				// �m�[�}���Q�[����
				CFakeScreen::GetInstance()->SetFade(MODE::GAME);
			}
			else if (CManager::GetKeyboard()->GetTrigger(DIK_S) ||
				CManager::GetKeyboard()->GetTrigger(DIK_DOWN) ||
				CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::DOWN) ||
				bInputDown)
			{
				m_nSelect = 2;

				m_pUI[0]->SetCol({ 0.5f, 0.5f, 0.5f, m_pUI[0]->GetAlpha() });
			}
		}
		else if (m_nSelect == 2)
		{
			if (m_pUI[1])
			{
				m_pUI[1]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.75f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
				m_pUI[1]->SetCol({ 1.0f, 1.0f, 1.0f, m_pUI[1]->GetAlpha() });
			}

			if (m_pUI[2])
			{
				m_pUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.75f, 0.0f });
			}

			if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) ||
				pPad->GetTrigger(CInputPad::JOYKEY::START) ||
				pPad->GetTrigger(CInputPad::JOYKEY::A) ||
				pPad->GetTrigger(CInputPad::JOYKEY::B) ||
				pPad->GetTrigger(CInputPad::JOYKEY::X) ||
				pPad->GetTrigger(CInputPad::JOYKEY::Y))
			{
				// �`�������W�Q�[����
				CFakeScreen::GetInstance()->SetFade(MODE::CHALLENGE);
			}
			else if (CManager::GetKeyboard()->GetTrigger(DIK_W) ||
				CManager::GetKeyboard()->GetTrigger(DIK_UP) ||
				CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::UP) ||
				bInputUp)
			{
				m_nSelect = 1;

				m_pUI[1]->SetCol({ 0.5f, 0.5f, 0.5f, m_pUI[1]->GetAlpha() });
			}
		}
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CTitle::Draw()
{

}

//============================================================================
// ���[�h�I�����擾
//============================================================================
int CTitle::GetSelect()
{
	// �V�[�������擾
	CScene* pScene{ CManager::GetScene() };

	if (!pScene)
	{
		return -1;
	}

	// �^�C�g���N���X�Ƀ_�E���L���X�g
	CTitle* pTitle{ CUtility::GetInstance()->DownCast<CTitle, CScene >(pScene) };

	return pTitle->m_nSelect;
}