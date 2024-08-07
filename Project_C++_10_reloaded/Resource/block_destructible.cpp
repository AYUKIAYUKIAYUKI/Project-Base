//============================================================================
// 
// 可壊ブロック [block_destructible.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "block_destructible.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CBlockDestructible::CBlockDestructible() : CObject_X{ static_cast<int>(LAYER::FRONT_MIDDLE) }
{

}

//============================================================================
// プライオリティ指定コンストラクタ
//============================================================================
CBlockDestructible::CBlockDestructible(LAYER priority) : CObject_X{ static_cast<int>(priority) }
{

}

//============================================================================
// デストラクタ
//============================================================================
CBlockDestructible::~CBlockDestructible()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CBlockDestructible::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBlockDestructible::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBlockDestructible::Update()
{
	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CBlockDestructible::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 生成
//============================================================================
CBlockDestructible* CBlockDestructible::Create(D3DXVECTOR3 pos)
{
	// インスタンスを生成
	CBlockDestructible* pBlockDestructible = DBG_NEW CBlockDestructible{ LAYER::FRONT_MIDDLE };

	if (pBlockDestructible == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pBlockDestructible->SetType(TYPE::DESTRUCTIBLE);

	// 基底クラスの初期設定
	pBlockDestructible->Init();

	// 座標の設定
	pBlockDestructible->SetPos(pos);

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::DESTRUCTIBLE);

	// モデルを設定
	pBlockDestructible->BindModel(model);

	// サイズを設定
	pBlockDestructible->SetSize(model->size);

	// 描画される前に一度更新しておく
	pBlockDestructible->Update();

	return pBlockDestructible;
}

//============================================================================
// ダウンキャスト
//============================================================================
CBlockDestructible* CBlockDestructible::DownCast(CObject* pObject)
{
	CBlockDestructible* pBlockDestructible = dynamic_cast<CBlockDestructible*>(pObject);

	if (pBlockDestructible == nullptr)
	{ // ダウンキャスト失敗
		assert(false);
	}

	return pBlockDestructible;
}