//============================================================================
// 
// 数字 [number.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "number.h"

// テクスチャ設定用
#include "texture_manager.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CNumber::CNumber() : 
	CObject_2D{ static_cast<int>(LAYER::FRONT) },	// 基底クラスのコンストラクタ
	m_nNum{ 0 }										// 数字の割り当て
{

}

//============================================================================
// デストラクタ
//============================================================================
CNumber::~CNumber()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CNumber::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_2D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CNumber::Uninit()
{
	// 基底クラスの終了処理
	CObject_2D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CNumber::Update()
{
	// アニメーション
	Animation();

	// 基底クラスの更新
	CObject_2D::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CNumber::Draw()
{
	// 基底クラスの描画処理
	CObject_2D::Draw();
}

//============================================================================
// 生成
//============================================================================
CNumber* CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// インスタンスを生成
	CNumber* pNumber = DBG_NEW CNumber;

	if (pNumber == nullptr)
	{ // 生成失敗
		assert(false);
	}

	pNumber->SetType(TYPE::NONE);	// タイプを設定

	pNumber->Init();		// 基底クラスの初期設定
	pNumber->SetPos(pos);	// 位置の設定
	pNumber->SetSize(size);	// サイズの設定

	pNumber->SetTexWidth(0.1f);		// 横テクスチャ分割幅
	pNumber->SetTexHeight(1.0f);	// 縦テクスチャ分縦幅

	// テクスチャを設定
	pNumber->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::NUMBER_00));

	return pNumber;
}

//============================================================================
// 数字を設定
//============================================================================
void CNumber::SetNumber(int nNum)
{
	m_nNum = nNum;
}

//============================================================================
// アニメーション
//============================================================================
void CNumber::Animation()
{
	// 横テクスチャ種類情報取得
	int nTexPatternU = GetNowPatternU();

	// 横テクスチャ種類を割り当て
	nTexPatternU = m_nNum;

	// 横テクスチャ種類情報設定
	SetNowPatternU(nTexPatternU);
}