//============================================================================
// 
// 3Dブロック [block3D.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "block3D.h"
#include "manager.h"

//============================================================================
// コンストラクタ
//============================================================================
CBlock3D::CBlock3D() : CObjectX(static_cast<int>(LAYER::FRONT_MIDDLE))
{

}

//============================================================================
// デストラクタ
//============================================================================
CBlock3D::~CBlock3D()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CBlock3D::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObjectX::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBlock3D::Uninit()
{
	// 基底クラスの終了処理
	CObjectX::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBlock3D::Update()
{
	// 基底クラスの更新
	CObjectX::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CBlock3D::Draw()
{
	// 基底クラスの描画処理
	CObjectX::Draw();
}

//============================================================================
// 生成
//============================================================================
CBlock3D* CBlock3D::Create(D3DXVECTOR3 pos)
{
	// インスタンスを生成
	CBlock3D* pBlock3D = DBG_NEW CBlock3D;

	if (pBlock3D == nullptr)
	{ // 生成失敗
		assert(false);
	}

	pBlock3D->SetType(TYPE::BLOCK);	// タイプを設定

	pBlock3D->Init();		// 基底クラスの初期設定
	pBlock3D->SetPos(pos);	// 中心位置の設定

	// モデルを設定
	pBlock3D->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel::MODEL_TYPE::MODEL_BLOCK));

	return pBlock3D;
}