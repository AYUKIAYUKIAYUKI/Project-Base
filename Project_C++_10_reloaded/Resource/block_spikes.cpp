//============================================================================
// 
// とげブロック [block_spikes.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "block_spikes.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CBlockSpikes::CBlockSpikes() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) }	// 描画優先度を指定
{

}

//============================================================================
// プライオリティ指定コンストラクタ
//============================================================================
CBlockSpikes::CBlockSpikes(LAYER priority) :
	CObject_X{ static_cast<int>(priority) }	// 基底クラスのコンストラクタ
{

}

//============================================================================
// デストラクタ
//============================================================================
CBlockSpikes::~CBlockSpikes()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CBlockSpikes::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBlockSpikes::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBlockSpikes::Update()
{
	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CBlockSpikes::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 生成
//============================================================================
CBlockSpikes* CBlockSpikes::Create(D3DXVECTOR3 pos)
{
	// インスタンスを生成
	CBlockSpikes* pBlockSpikes = DBG_NEW CBlockSpikes{ LAYER::MIDDLE };

	if (pBlockSpikes == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pBlockSpikes->SetType(TYPE::SPIKES);

	// 基底クラスの初期設定
	pBlockSpikes->Init();

	// 座標の設定
	pBlockSpikes->SetPos(pos);

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::SPIKES);

	// モデルを設定
	pBlockSpikes->BindModel(model);

	// サイズを設定
	pBlockSpikes->SetSize(model->size);

	// 描画される前に一度更新しておく
	pBlockSpikes->Update();

	return pBlockSpikes;
}