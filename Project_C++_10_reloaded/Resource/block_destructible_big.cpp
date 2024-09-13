//============================================================================
// 
// 可壊でかブロック [block_destructible_big.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "block_destructible_big.h"
#include "utility.h"
#include "sound.h"

// オブジェクト取得用
#include "smoke.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CBlockDestructibleBig::CBlockDestructibleBig() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },
	m_nLife{ 0 }
{

}

//============================================================================
// プライオリティ指定コンストラクタ
//============================================================================
CBlockDestructibleBig::CBlockDestructibleBig(LAYER priority) :
	CObject_X{ static_cast<int>(priority) }
{

}

//============================================================================
// デストラクタ
//============================================================================
CBlockDestructibleBig::~CBlockDestructibleBig()
{
	for (int i = 0; i < 5; i++)
	{
		// ランダムな加速度を生成
		D3DXVECTOR3 velocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

		// 煙を生成
		CSmoke::Create(
			GetPos(),			// 座標
			velocity * 0.005f);	// 加速度
	}
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CBlockDestructibleBig::Init()
{
	// ライフを設定
	m_nLife = 2;

	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBlockDestructibleBig::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBlockDestructibleBig::Update()
{
	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CBlockDestructibleBig::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// ダメージ処理
//============================================================================
bool CBlockDestructibleBig::Damage(int nAtk)
{
	// 体力を減らす
	m_nLife += nAtk;

	// 体力が無くなると
	if (m_nLife <= 0)
	{
		// 破棄する
		SetRelease();

		return false;
	}

	return true;
}

//============================================================================
// 生成
//============================================================================
CBlockDestructibleBig* CBlockDestructibleBig::Create(D3DXVECTOR3 pos)
{
	// インスタンスを生成
	CBlockDestructibleBig* pBlockDestructible = DBG_NEW CBlockDestructibleBig{ LAYER::MIDDLE };

	if (pBlockDestructible == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pBlockDestructible->SetType(TYPE::DEST_BIG);

	// 基底クラスの初期設定
	pBlockDestructible->Init();

	// 座標の設定
	pBlockDestructible->SetPos(pos);

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::DEST_BIG);

	// モデルを設定
	pBlockDestructible->BindModel(model);

	// サイズを設定
	pBlockDestructible->SetSize(model->size);

	// 描画される前に一度更新しておく
	pBlockDestructible->Update();

	return pBlockDestructible;
}