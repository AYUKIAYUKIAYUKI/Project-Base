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
#include "fakescreen.h"

// インプット取得用
#include "manager.h"

// オブジェクト用
#include "dummy.h"
#include "goal.h"
#include "line.h"
#include "start.h"

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
	// ステージメーカーの初期化
	CStageMaker::GetInstance()->Init();

	// グリッドライン生成
	CLine::CreateGrid();

	// ダミーの生成
	CDummy::Create({ 0.0f, 0.0f, 0.0f }, CStageMaker::GetInstance()->GetPatternRef());

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CStage_Debug::Uninit()
{
	// ステージメーカーの解放
	CStageMaker::GetInstance()->Release();

	// 基底クラスの終了処理
	CScene::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CStage_Debug::Update()
{
	// ステージメーカーの更新
	CStageMaker::GetInstance()->Update();

	// ゲームモードへ戻る
	if (CManager::GetKeyboard()->GetTrigger(DIK_F1))
	{
		CFakeScreen::GetInstance()->SetFade(MODE::GAME);
	}
}

//============================================================================
// 描画処理
//============================================================================
void CStage_Debug::Draw()
{

}