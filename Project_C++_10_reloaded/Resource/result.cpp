//============================================================================
// 
// リザルト [result.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "result.h"
#include "manager.h"
#include "object.h"

// オブジェクト生成用
#include "item.h"

//============================================================================
// コンストラクタ
//============================================================================
CResult::CResult()
{

}

//============================================================================
// デストラクタ
//============================================================================
CResult::~CResult()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CResult::Init()
{
	// アイテムの生成 (仮)
	CItem::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// 位置
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f });	// サイズ

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CResult::Uninit()
{
	// 基底クラスの終了処理
	CScene::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CResult::Update()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(MODE::TITLE);
	}
}

//============================================================================
// 描画処理
//============================================================================
void CResult::Draw()
{

}