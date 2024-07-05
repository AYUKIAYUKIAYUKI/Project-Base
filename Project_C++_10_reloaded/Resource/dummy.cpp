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
CDummy::CDummy()
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

	// 位置をデバッグ表示
	CManager::GetRenderer()->SetDebugString("【ダミー位置】");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	CManager::GetRenderer()->SetDebugString(oss.str().c_str());

	// カメラ位置を設定
	//CManager::GetCamera()->SetPos(GetPos());

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
CDummy* CDummy::Create(D3DXVECTOR3 pos)
{
	// インスタンスを生成
	CDummy* pDummy = DBG_NEW CDummy;

	if (pDummy == nullptr)
	{ // 生成失敗
		assert(false);
	}

	pDummy->SetType(TYPE::DUMMY);	// タイプを設定

	pDummy->Init();			// 基底クラスの初期設定
	pDummy->SetPos(pos);	// 位置の設定
	pDummy->SetAlpha(0.5f);	// アルファ値の設定

	// 一旦ブロックモデルを設定
	pDummy->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::BLOCK_000));

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