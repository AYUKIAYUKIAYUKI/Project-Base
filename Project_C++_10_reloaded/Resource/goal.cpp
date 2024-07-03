//============================================================================
// 
// ゴール [goal.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "goal.h"
#include "manager.h"

//============================================================================
// コンストラクタ
//============================================================================
CGoal::CGoal() : CObject_X(static_cast<int>(LAYER::FRONT_MIDDLE))
{

}

//============================================================================
// デストラクタ
//============================================================================
CGoal::~CGoal()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CGoal::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CGoal::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CGoal::Update()
{
	// 回転
	D3DXVECTOR3 rot = GetRot();
	rot.z += 0.025f;
	SetRot(rot);

	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CGoal::Draw()
{
	// 基底クラスの描画
	CObject_X::Draw();
}

//============================================================================
// 生成
//============================================================================
CGoal* CGoal::Create(D3DXVECTOR3 pos)
{
	// インスタンスを生成
	CGoal* pGoal = DBG_NEW CGoal;

	if (pGoal == nullptr)
	{ // 生成失敗
		assert(false);
	}

	pGoal->SetType(TYPE::GOAL);	// タイプを設定

	pGoal->Init();		// 基底クラスの初期設定
	pGoal->SetPos(pos);	// 位置の設定

	// モデルを設定
	pGoal->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::GOAL));

	return pGoal;
}