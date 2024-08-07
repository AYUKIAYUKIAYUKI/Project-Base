//============================================================================
// 
// シーン管理 [scene.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "scene.h"
#include "object.h"

// シーン
#include "title.h"
#include "game.h"
#include "result.h"

//============================================================================
// コンストラクタ
//============================================================================
CScene::CScene() : m_mode(MODE::TITLE)
{

}

//============================================================================
// デストラクタ
//============================================================================
CScene::~CScene()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CScene::Init()
{
	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CScene::Uninit()
{
	// 全オブジェクト解放処理
	CObject::ReleaseAll();
}

//============================================================================
// 更新処理
//============================================================================
void CScene::Update()
{

}

//============================================================================
// 描画処理
//============================================================================
void CScene::Draw()
{

}

//============================================================================
// 生成
//============================================================================
CScene* CScene::Create(MODE mode)
{
	// 基底クラスのポインタを用意
	CScene* pScene = nullptr;

	switch (mode)
	{
	case CScene::MODE::TITLE:
		pScene = DBG_NEW CTitle;
		break;

	case CScene::MODE::GAME:
		pScene = DBG_NEW CGame;
		break;

	case CScene::MODE::RESULT:
		pScene = DBG_NEW CResult;
		break;

	default:
		assert(false);
		break;
	}

	if (pScene == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// 初期設定
	pScene->Init();

	return pScene;
}