//============================================================================
// 
// ブロック [block.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "block.h"

#include "renderer.h"

//============================================================================
// コンストラクタ
//============================================================================
CBlock::CBlock() : CObject_X(static_cast<int>(LAYER::FRONT_MIDDLE))
{

}

//============================================================================
// デストラクタ
//============================================================================
CBlock::~CBlock()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CBlock::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBlock::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBlock::Update()
{
	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CBlock::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 生成
//============================================================================
CBlock* CBlock::Create(D3DXVECTOR3 pos)
{
	// インスタンスを生成
	CBlock* pBlock = DBG_NEW CBlock;

	if (pBlock == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pBlock->SetType(TYPE::BLOCK);

	// 基底クラスの初期設定
	pBlock->Init();

	// 座標の設定
	pBlock->SetPos(pos);

	// モデルを取得
	auto model = CRenderer::GetInstance()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::BLOCK_000);

	// モデルを設定
	pBlock->BindModel(model);

	// サイズを設定
	pBlock->SetSize(model->size);

	// 描画される前に一度更新しておく
	pBlock->Update();

	return pBlock;
}

//============================================================================
// ダウンキャスト
//============================================================================
CBlock* CBlock::DownCast(CObject* pObject)
{
	CBlock* pBlock = dynamic_cast<CBlock*>(pObject);

	if (pBlock == nullptr)
	{ // ダウンキャスト失敗
		assert(false);
	}

	return pBlock;
}