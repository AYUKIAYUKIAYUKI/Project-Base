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
#include "manager.h"
#include "object.h"
#include "stagemaker.h"

// オブジェクト生成用
#include "bg.h"
#include "block.h"
#include "enemy.h"
#include "field.h"
#include "goal.h"
#include "item.h"
#include "player.h"
#include "score.h"
#include "start.h"

//============================================================================
// コンストラクタ
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
	// ステージ作成クラスのインスタンス生成
	if (FAILED(CStageMaker::Create()))
	{
		return E_FAIL;
	}

	// ステージ作成クラスの初期設定
	CStageMaker::GetInstance()->Init();

	// ステージの読み込み
	CStageMaker::GetInstance()->Import();

	// プレイヤーの生成 (仮)
	CPlayer::Create(
		{ 0.0f, 0.0f, 0.0f });	// 位置

	// スコアの生成 (仮)
	CScore::Create(
		{ 25.0f, 30.0f, 0.0f },	// 位置
		25.0f);					// 数列の配置間隔

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CGame::Uninit()
{
	// ステージ作成クラスのインスタンス破棄
	CStageMaker::Release();

	// 基底クラスの終了処理
	CScene::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CGame::Update()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_F1))
	{
		// ステージデバッグ画面へ
		CManager::GetFade()->SetFade(MODE::STAGE);
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		// リザルト画面へ
		CManager::GetFade()->SetFade(MODE::RESULT);
	}
}

//============================================================================
// 描画処理
//============================================================================
void CGame::Draw()
{

}