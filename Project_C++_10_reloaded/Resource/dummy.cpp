//============================================================================
// 
// ダミー [dummy.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "dummy.h"

#include "manager.h"

//============================================================================
// コンストラクタ
//============================================================================
CDummy::CDummy(int& nPattern) : m_nPatternRef{ nPattern }
{

}

//============================================================================
// デストラクタ
//============================================================================
CDummy::~CDummy()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CDummy::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CDummy::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CDummy::Update()
{
	// 操作
	Control();

	// ダミーの種類を確認
	CheckPattern();

	// 位置をデバッグ表示
	CManager::GetRenderer()->SetDebugString("【ダミー位置】");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	CManager::GetRenderer()->SetDebugString(oss.str().c_str());

	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CDummy::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 生成
//============================================================================
CDummy* CDummy::Create(D3DXVECTOR3 pos, int& nPattern)
{
	// インスタンスを生成
	CDummy* pDummy = DBG_NEW CDummy{ nPattern };

	if (pDummy == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pDummy->SetType(TYPE::DUMMY);

	// 基底クラスの初期設定
	pDummy->Init();
	
	// 位置の設定
	pDummy->SetPos(pos);
	
	// アルファ値の設定
	pDummy->SetAlpha(0.8f);

	// モデルを取得
	auto model = CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::BLOCK_000);

	// 仮のモデルを設定
	pDummy->BindModel(model);

	return pDummy;
}

//============================================================================
// ダウンキャスト
//============================================================================
CDummy* CDummy::DownCast(CObject* pObject)
{
	CDummy* pDummy = dynamic_cast<CDummy*>(pObject);

	if (pDummy == nullptr)
	{ // ダウンキャスト失敗
		assert(false);
	}

	return pDummy;
}

//============================================================================
// 操作
//============================================================================
void CDummy::Control()
{
	// 位置を取得
	D3DXVECTOR3 pos = GetPos();

	if (CManager::GetKeyboard()->GetPress(DIK_RSHIFT))
	{
		// Y軸方向に移動
		if (CManager::GetKeyboard()->GetPress(DIK_W))
		{
			pos.y += 5.0f;
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_S))
		{
			pos.y += -5.0f;
		}

		// X方向に移動
		if (CManager::GetKeyboard()->GetPress(DIK_A))
		{
			pos.x += -5.0f;
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_D))
		{
			pos.x += 5.0f;
		}
	}
	else
	{
		// Y軸方向にグリッド移動
		if (CManager::GetKeyboard()->GetTrigger(DIK_W))
		{
			pos.y += 5.0f;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_S))
		{
			pos.y += -5.0f;
		}

		// X方向にグリッド移動
		if (CManager::GetKeyboard()->GetTrigger(DIK_A))
		{
			pos.x += -5.0f;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_D))
		{
			pos.x += 5.0f;
		}
	}

	// 最終的な位置を反映
	SetPos(pos);
}

//============================================================================
// ダミーの種類を確認
//============================================================================
void CDummy::CheckPattern()
{
	// 過去の種類を保持する
	static int nOld = 0;

	// 種類の変更を判別
	if (nOld != m_nPatternRef)
	{
		nOld = m_nPatternRef;
	}
	else
	{ // 変更が無ければリターン
		return;
	}

	CModel_X::MODEL* model;

	switch (m_nPatternRef)
	{
	case 0:

		// ブロックモデルに見た目を変更
		model = CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::BLOCK_000);
		BindModel(model);

		break;

	case 1:

		// 可壊ブロックモデルに見た目を変更
		model = CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::DESTRUCTIBLE);
		BindModel(model);

		break;

	case 2:

		// スタートモデルに見た目を変更
		model = CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::START);
		BindModel(model);

		break;

	case 3:

		// ゴールモデルに見た目を変更
		model = CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::GOAL);
		BindModel(model);

		break;

	default:
		assert(false);
		break;
	}
}