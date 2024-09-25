//============================================================================
// 
// ゲーム [game.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "game.h"
#include "game_manager.h"
#include "stagemaker.h"
#include "fakescreen.h"

// インプット取得用
#include "manager.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CGame::CGame()
{

}

//============================================================================
// デストラクタ
//============================================================================
CGame::~CGame()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CGame::Init()
{
	// ゲームマネージャーの初期設定
	CGameManager::GetInstance()->Init(CGameManager::PHASE::START);

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CGame::Uninit()
{
	// ステージメーカーの解放
	CStageMaker::GetInstance()->Release();

	// ゲームマネージャーの解放
	CGameManager::GetInstance()->Release();

	// 基底クラスの終了処理
	CScene::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CGame::Update()
{
	// ゲームマネージャーの更新処理
	CGameManager::GetInstance()->Update();

#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetTrigger(DIK_F1))
	{
		// ステージデバッグ画面へ
		CFakeScreen::GetInstance()->SetFade(MODE::STAGE);
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_DELETE))
	{
		// タイトル画面へ
		CFakeScreen::GetInstance()->SetFade(MODE::TITLE);
	}
#endif	// _DEBUG
}

//============================================================================
// 描画処理
//============================================================================
void CGame::Draw()
{

}