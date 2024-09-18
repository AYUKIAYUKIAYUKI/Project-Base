//============================================================================
// 
// バリア [barrier.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "barrier.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CBarrier::CBarrier() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) }
{

}

//============================================================================
// デストラクタ
//============================================================================
CBarrier::~CBarrier()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CBarrier::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBarrier::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBarrier::Update()
{
	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CBarrier::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 生成
//============================================================================
CBarrier* CBarrier::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot)
{
	// インスタンスを生成
	CBarrier* pBarrier = DBG_NEW CBarrier{};

	if (pBarrier == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pBarrier->SetType(TYPE::BARRIER);

	// 基底クラスの初期設定
	pBarrier->Init();

	// 座標の設定
	pBarrier->SetPos(Pos);

	// 向きの設定
	pBarrier->SetRot(Rot);

	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::BARRIER) };

	// モデルを設定
	pBarrier->BindModel(Model);

	// サイズを設定
	pBarrier->SetSize(D3DXVECTOR3{ 2.0f, 2.0f, 0.0f, });

	// 描画される前に一度更新しておく
	pBarrier->Update();

	return pBarrier;
}