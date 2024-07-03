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
#include "manager.h"

// オブジェクト生成用
#include "bg.h"

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
	// 背景の生成 (仮)
	CBg::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// 中心位置
		{ SCREEN_HEIGHT * 0.5f,  SCREEN_HEIGHT * 0.5f, 0.0f });	// サイズ

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
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::SetScene(MODE::GAME);
	}
}

//============================================================================
// 描画処理
//============================================================================
void CTitle::Draw()
{

}