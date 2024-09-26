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
	// ���}���u
	if (m_nSelect == 0)
	{
		if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::START) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::A) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::B) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::X) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::Y))
		{
			m_nSelect = 1;

			if (!m_pUI[0])
			{
				m_pUI[0] = CText::Create(CTexture_Manager::TYPE::CROWN);
				m_pUI[0]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f });
				m_pUI[0]->SetSizeTarget({ 50.0f, 50.0f, 0.0f });
				m_pUI[0]->SetAppear(true);
			}

			if (!m_pUI[1])
			{
				m_pUI[1] = CText::Create(CTexture_Manager::TYPE::CROWN);
				m_pUI[1]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.75f, 0.0f });
				m_pUI[1]->SetSizeTarget({ 50.0f, 50.0f, 0.0f });
				m_pUI[1]->SetAppear(true);
			}

			if (!m_pUI[2])
			{
				m_pUI[2] = CText::Create(CTexture_Manager::TYPE::CROWN);
				m_pUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f, 0.0f });
				m_pUI[2]->SetSizeTarget({ 30.0f, 30.0f, 0.0f });
				m_pUI[2]->SetAppear(true);
			}
		}
	}
	else if (m_nSelect == 1)
	{
		if (m_pUI[2])
		{
			m_pUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f, 0.0f });
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::START) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::A) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::B) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::X) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::Y))
		{
			// �m�[�}���Q�[����
			CFakeScreen::GetInstance()->SetFade(MODE::GAME);
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_S) ||
			CManager::GetKeyboard()->GetTrigger(DIK_DOWN) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::DOWN))
		{
			m_nSelect = 2;
		}
	}
	else if (m_nSelect == 2)
	{
		if (m_pUI[2])
		{
			m_pUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.75f, 0.0f });
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::START) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::A) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::B) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::X) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::Y))
		{
			// �`�������W�Q�[����
			CFakeScreen::GetInstance()->SetFade(MODE::CHALLENGE);
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_W) ||
			CManager::GetKeyboard()->GetTrigger(DIK_UP) ||
			CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::UP))
		{
			m_nSelect = 1;
		}
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CTitle::Draw()
{

}