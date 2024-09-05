//============================================================================
// 
// 家具 [furniture.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "furniture.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CFurniture::CFurniture() :
	CObject_X{ static_cast<int>(LAYER::BG) }	// 描画優先度を指定
{

}

//============================================================================
// デストラクタ
//============================================================================
CFurniture::~CFurniture()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CFurniture::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CFurniture::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CFurniture::Update()
{
	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CFurniture::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 生成
//============================================================================
CFurniture* CFurniture::Create(D3DXVECTOR3 pos, float fScale, CModel_X_Manager::TYPE type)
{
	// インスタンスを生成
	CFurniture* pFurniture = DBG_NEW CFurniture;

	if (pFurniture == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pFurniture->SetType(TYPE::NONE);

	// 基底クラスの初期設定
	pFurniture->Init();

	// 座標の設定
	pFurniture->SetPos(pos);

	// 縮尺の設定
	pFurniture->SetScale(fScale);

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(type);

	// モデルを設定
	pFurniture->BindModel(model);

	// サイズを設定
	pFurniture->SetSize(model->size);

	// 描画される前に一度更新しておく
	pFurniture->Update();

	return pFurniture;
}