//============================================================================
// 
// 煙エフェクト [smoke.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "smoke.h"
#include "utility.h"

//============================================================================
// コンストラクタ
//============================================================================
CSmoke::CSmoke() :
	m_velocity{ 0.0f, 0.0f, 0.0f }	// 加速度
{

}

//============================================================================
// デストラクタ
//============================================================================
CSmoke::~CSmoke()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CSmoke::Init()
{
	// 基底クラスの初期設定
	if (FAILED(CObject_X::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CSmoke::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CSmoke::Update()
{
	// 基底クラスの更新処理
	CObject_X::Update();

	// 回転
	auto rot{ GetRot() };
	rot = m_velocity;
	SetRot(rot);

	// 移動
	D3DXVECTOR3 pos = GetPos();
	pos += m_velocity;
	SetPos(pos);

	// 加速度を減少
	m_velocity *= 0.97f;

	// アルファ値を減少
	if (CUtility::GetInstance()->DecrementUntilGone(GetAlpha(), 0.0f))
	//if (CUtility::GetInstance()->DecrementUntilGone(GetAlpha(), -0.005f))
	{
		// 自身を破棄
		CObject::Release();
	}
}

//============================================================================
// 描画処理
//============================================================================
void CSmoke::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 加速度を取得
//============================================================================
D3DXVECTOR3& CSmoke::GetVelocity()
{
	return m_velocity;
}

//============================================================================
// 加速度を設定
//============================================================================
void CSmoke::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

//============================================================================
// 生成
//============================================================================
CSmoke* CSmoke::Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity)
{
	CSmoke* pSmoke = DBG_NEW CSmoke{};

	// 生成失敗
	if (!pSmoke)
	{
		assert(false);
	}

	// タイプを設定
	pSmoke->SetType(CObject::TYPE::NONE);

	// 初期設定
	pSmoke->Init();

	// 座標の設定
	pSmoke->SetPos(pos);

	// 加速度を設定
	pSmoke->SetVelocity(velocity);

	// モデルのポインタ
	CModel_X_Manager::MODEL* model{ nullptr };

	// ランダムにモデルを取得
	switch (rand() % 3)
	{
	case 0:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::STAR00);
		break;

	case 1:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PARTICLE01);
		break;

	case 2:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PARTICLE02);
		break;

	default:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::STAR00);
		break;
	}

	// モデルを設定
	pSmoke->BindModel(model);

	// サイズを設定
	pSmoke->SetSize(model->size);

	// 描画される前に一度更新しておく
	pSmoke->Update();

	return pSmoke;
}