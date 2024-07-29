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

	// タイプを設定
	pGoal->SetType(TYPE::GOAL);

	// 基底クラスの初期設定
	pGoal->Init();

	// 位置の設定
	pGoal->SetPos(pos);	

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::GOAL);

	// モデルを設定
	pGoal->BindModel(model);

	// サイズを設定
	pGoal->SetSize(model->size);

	// 描画される前に一度更新しておく
	pGoal->Update();

	return pGoal;
}

//============================================================================
// ダウンキャスト
//============================================================================
CGoal* CGoal::DownCast(CObject* pObject)
{
	CGoal* pGoal = dynamic_cast<CGoal*>(pObject);

	if (pGoal == nullptr)
	{ // ダウンキャスト失敗
		assert(false);
	}

	return pGoal;
}