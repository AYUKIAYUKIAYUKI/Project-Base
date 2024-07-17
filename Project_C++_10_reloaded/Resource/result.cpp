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

// 仮リザルト表示用
#include "bg.h"

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
	// 背景の生成
	CBg::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// 位置
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// サイズ
		CTexture::TEX_TYPE::BG_001);							// テクスチャ

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