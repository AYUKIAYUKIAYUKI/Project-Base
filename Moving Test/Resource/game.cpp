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

// オブジェクト生成用
#include "bg.h"
#include "block.h"
#include "block3D.h"
#include "enemy.h"
#include "field.h"
#include "item.h"
#include "player.h"
#include "player3D.h"
#include "score.h"

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
#if 0

	// 背景の生成 (仮)
	CBg::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// 中心位置
		{ SCREEN_HEIGHT * 0.5f,  SCREEN_HEIGHT * 0.5f, 0.0f });	// サイズ

	// ブロックの生成 (仮)
	CBlock::Create(
		{ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.7f, 0.0f },	// 中心位置
		{ 50.0f, 100.0f, 0.0f });								// サイズ

	// ブロックの生成 (仮)
	CBlock::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// 中心位置
		{ 75.0f, 75.0f, 0.0f });								// サイズ

	// ブロックの生成 (仮)
	CBlock::Create(
		{ SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.3f, 0.0f },	// 中心位置
		{ 100.0f, 50.0f, 0.0f });								// サイズ

	for (int i = 0; i < 5; i++)
	{
		// ブロックの生成 (仮)
		CBlock::Create(
			{ SCREEN_WIDTH * 0.95f, SCREEN_HEIGHT * 0.9f + (-70.0f * i), 0.0f },	// 中心位置
			{ 30.0f, 30.0f, 0.0f });												// サイズ

		// ブロックの生成 (仮)
		CBlock::Create(
			{ SCREEN_WIDTH * 0.95f + (-70.0f * i), SCREEN_HEIGHT * 0.9f, 0.0f },	// 中心位置
			{ 30.0f, 30.0f, 0.0f });												// サイズ
	}

	// エネミーの生成 (仮)
	CEnemy::Create(
		{ SCREEN_WIDTH * 0.0f, SCREEN_HEIGHT * 1.0f, 0.0f },	// 中心位置
		{ 50.0f, 50.0f, 0.0f });								// サイズ

	// プレイヤーの生成 (仮)
	CPlayer::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT, 0.0f },	// 中心位置
		{ 40.0f, 50.0f, 0.0f });						// サイズ

	// アイテムの生成 (仮)
	CItem::Create(
		{ SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f, 0.0f },	// 中心位置
		{ 80.0f, 80.0f, 0.0f });								// サイズ

#else

	// 3Dプレイヤーの生成 (仮)
	CPlayer3D::Create(
		{ 0.0f, 00.0f, 0.0f });	// 中心位置

	// 地面の生成 (仮)
	CField::Create(
		{ 0.0f, 0.0f, 0.0f },		// 中心位置
		{ 100.0f, 0.0f, 100.0f });	// サイズ

	for (int i = 0; i < 5; i++)
	{
		// 3Dブロックの生成 (仮)
		CBlock3D::Create(
			{ 100.0f, 0.0f, 100.0f + (-25.0f * i) });	// 中心位置

		// 3Dブロックの生成 (仮)
		CBlock3D::Create(
			{ 100.0f + (-25.0f * i), 0.0f, 100.0f });	// 中心位置

		// 3Dブロックの生成 (仮)
		CBlock3D::Create(
			{ -100.0f, 0.0f, -100.0f + (25.0f * i) });	// 中心位置

		// 3Dブロックの生成 (仮)
		CBlock3D::Create(
			{ -100.0f + (25.0f * i), 0.0f, -100.0f });	// 中心位置

		// 3Dブロックの生成 (仮)
		CBlock3D::Create(
			{ 0.0f , 0.0f + (25.0f * i), -100.0f });	// 中心位置
	}

	// 3Dブロックの生成 (仮)
	CBlock3D::Create(
		{ -40.0f, 0.0f, 150.0f });	// 中心位置

	// 3Dブロックの生成 (仮)
	CBlock3D::Create(
		{ -20.0f, 20.0f, 150.0f });	// 中心位置

	// 3Dブロックの生成 (仮)
	CBlock3D::Create(
		{ 0.0f, 40.0f, 150.0f });	// 中心位置

		// 3Dブロックの生成 (仮)
	CBlock3D::Create(
		{ 20.0f, 60.0f, 150.0f });	// 中心位置

		// 3Dブロックの生成 (仮)
	CBlock3D::Create(
		{ 40.0f, 80.0f, 150.0f });	// 中心位置

#endif

	// スコアの生成 (仮)
	CScore::Create(
		{ 25.0f, 30.0f, 0.0f },	// 中心位置
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
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::SetScene(MODE::RESULT);
	}
}

//============================================================================
// 描画処理
//============================================================================
void CGame::Draw()
{

}