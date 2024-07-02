//============================================================================
// 
// ステージデバッグ [stage_debug.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "stage_debug.h"
#include "stagemaker.h"

#include "manager.h"
#include "dummy.h"

//============================================================================
// コンストラクタ
//============================================================================
CStage_Debug::CStage_Debug()
{

}

//============================================================================
// デストラクタ
//============================================================================
CStage_Debug::~CStage_Debug()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CStage_Debug::Init()
{
	// ステージ作成クラスのインスタンス生成
	if (FAILED(CStageMaker::Create()))
	{
		return E_FAIL;
	}

	// ダミーの生成
	CDummy::Create({ 0.0f, 0.0f, 0.0f });

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CStage_Debug::Uninit()
{
	// ステージ作成クラスのインスタンス破棄
	CStageMaker::Release();

	// 基底クラスの終了処理
	CScene::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CStage_Debug::Update()
{
	// ゲームモードへ戻る
	if (CManager::GetKeyboard()->GetTrigger(DIK_F1))
	{
		CManager::GetFade()->SetFade(MODE::GAME);
	}

	// ステージ作成の更新
	CStageMaker::GetInstance()->Update();
}

//============================================================================
// 描画処理
//============================================================================
void CStage_Debug::Draw()
{

}