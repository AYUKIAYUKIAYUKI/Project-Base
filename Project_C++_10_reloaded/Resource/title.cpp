//============================================================================
// 
// タイトル [title.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "title.h"
#include "fakescreen.h"

// インプット取得用
#include "manager.h"

// テクスチャ取得用
#include "texture_manager.h"

//============================================================================
// コンストラクタ
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
// デストラクタ
//============================================================================
CTitle::~CTitle()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CTitle::Init()
{
	// 背景の生成
	m_pBg = CBg::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// 位置
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// サイズ
		CTexture_Manager::TYPE::BG_000);						// テクスチャ

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CTitle::Uninit()
{
	// 基底クラスの終了処理
	CScene::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CTitle::Update()
{
	// 応急処置
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
			// ノーマルゲームへ
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
			// チャレンジゲームへ
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
// 描画処理
//============================================================================
void CTitle::Draw()
{

}