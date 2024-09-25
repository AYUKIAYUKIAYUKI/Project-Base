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

// 仮タイトル表示用
#include "bg.h"

// インプット取得用
#include "manager.h"

// テクスチャ取得用
#include "texture_manager.h"

//============================================================================
// コンストラクタ
//============================================================================
CTitle::CTitle()
{

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
	// 全てのサウンドを停止
	//CSound::GetInstance()->Stop();

	// 背景の生成
	CBg::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// 位置
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// サイズ
		CTexture_Manager::TYPE::BG_000);						// テクスチャ

	// BGMをかける
	//CSound::GetInstance()->Play(CSound::LABEL::BGM);

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
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) ||
		CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::START) ||
		CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::A) ||
		CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::B) ||
		CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::X) ||
		CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::Y))
	{ 
		// レベルゲームへ
		CFakeScreen::GetInstance()->SetFade(MODE::GAME);
	}
	else if (CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::BACK) ||
		CManager::GetKeyboard()->GetTrigger(DIK_BACK))
	{
		// チャレンジゲームへ
		CFakeScreen::GetInstance()->SetFade(MODE::CHALLENGE);
	}
}

//============================================================================
// 描画処理
//============================================================================
void CTitle::Draw()
{

}