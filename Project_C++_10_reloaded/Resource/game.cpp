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
	// スタートの生成 (仮)
	CStart::Create(
		{ -150.0f, 150.0f, 0.0f });	// 位置

	// ゴールの生成 (仮)
	CGoal::Create(
		{ 150.0f, 150.0f, 0.0f });	// 位置

	// プレイヤーの生成 (仮)
	CPlayer::Create(
		{ 0.0f, 0.0f, 0.0f });	// 位置

	for (int i = 0; i < 5; i++)
	{
		// ブロックの生成 (仮)
		CBlock::Create(
			{ 150.0f + (-20.0f * i), 100.0f, 0.0f });	// 位置

		// ブロックの生成 (仮)
		CBlock::Create(
			{ 150.0f , 0.0f + (20.0f * i), 0.0f });	// 位置

		// ブロックの生成 (仮)
		CBlock::Create(
			{ -150.0f + (20.0f * i), -100.0f, 0.0f });	// 位置

		// ブロックの生成 (仮)
		CBlock::Create(
			{ -150.0f , -100.0f + (20.0f * i), 0.0f });	// 位置
	}

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