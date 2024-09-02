//=============================================================================
//
// マス目 [square.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "square.h"
#include "utility.h"

// テクスチャ取得用
#include "texture_manager.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CSquare::CSquare() :
	CObject_UI{ static_cast<int>(LAYER::UI) }
{
	// 数字を生成
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// 数字のポインタを初期化
		m_apNumber[i] = nullptr;
	
		m_apNumber[i] = CNumber::Create(
			{ 0.0f, 0.0f, 0.0f },		// 座標
			{ 25.0f, 20.0f, 0.0f });	// サイズ
	}

	// 出現予約
	SetAppear(true);
}

//============================================================================
// デストラクタ
//============================================================================
CSquare::~CSquare()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CSquare::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CSquare::Uninit()
{
	// 基底クラスの終了処理
	CObject_UI::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CSquare::Update()
{
	// 基底クラスの更新
	CObject_UI::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CSquare::Draw()
{
	// 基底クラスの描画処理
	CObject_UI::Draw();
}

//============================================================================
// マス目を動作
//============================================================================
void CSquare::ControlAll(int nSelect)
{
	// マス目タグのオブジェクトを全て取得
	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);

	// マス数カウント
	int nSquareCnt{ 0 };

	// オブジェクトがなくなるまで
	while (pObj[nSquareCnt])
	{
		// マス目クラスへダウンキャスト
		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);

		// 新規座標情報
		D3DXVECTOR3 posNew{ 0.0f, 0.0f, 0.0f };

		// 新規向き情報
		D3DXVECTOR3 rotNew{ 0.0f, 0.0f, 0.0f };

		// 新規サイズ情報
		D3DXVECTOR3 sizeNew{ 0.0f, 0.0f, 0.0f };

		// 選択しているマスのみ特殊
		if (nSquareCnt == nSelect)
		{
			posNew = {
				(SCREEN_WIDTH * 0.5f),
				(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
				0.0f };

			rotNew = { 0.0f, 0.0f, D3DX_PI };

			sizeNew = { 60.0f, 60.0f, 0.0f };
		}
		else
		{
			posNew = { 
				(SCREEN_WIDTH * 0.5f) + (150.0f * nSquareCnt) - (nSelect * 150.0f),
				SCREEN_HEIGHT * 0.75f + +CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
				0.0f };

			sizeNew = { 40.0f, 40.0f, 0.0f };
		}

		// 目標座標を新しいものに
		pSquare->SetPosTarget(posNew);

		// 目標向きを新しいものに
		pSquare->SetRotTarget(rotNew);

		// 目標サイズを新しいものに
		pSquare->SetSizeTarget(sizeNew);
		
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		// カウント数のコピー
		int nCopy{ nSquareCnt };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// 中心座標から、相対的な先頭の位置を設定
			posNew = pSquare->GetPos();
			posNew.x = pSquare->GetPos().x + (25.0f * MAX_DIGIT * 0.5f) - (25.0f * 0.5f);

			// 桁ごとに所定の座標へ補正
			posNew.x += -25.0f * nCntNum;
			pSquare->m_apNumber[nCntNum]->SetPos(posNew);

			// 数字を設定
			pSquare->m_apNumber[nCntNum]->SetNumber(nCopy % 10);

			// 桁を減らす
			nCopy /= 10;
		}

		// 次へ進める
		nSquareCnt++;
	}
}

//============================================================================
// マス目を全消去
//============================================================================
void CSquare::DisappearAll()
{
	// マス目タグのオブジェクトを全て取得
	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);

	// マス数カウント
	int nSquareCnt{ 0 };

	// オブジェクトがなくなるまで
	while (pObj[nSquareCnt])
	{
		// マス目クラスへダウンキャスト
		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);

		// 新規向き情報
		D3DXVECTOR3 rotNew{ 0.0f, 0.0f, -D3DX_PI };

		// 新規サイズ情報
		D3DXVECTOR3 sizeNew{ 100.0f, 100.0f, 0.0f };

		// 目標向きを新しいものに
		pSquare->SetRotTarget(rotNew);

		// 目標サイズを新しいものに
		pSquare->SetSizeTarget(sizeNew);

		// 消去予約
		pSquare->SetDisappear(true);

		nSquareCnt++;
	}
}

////============================================================================
//// マス目を並べる (不必要)
////============================================================================
//void CSquare::LineUpAll(int nSelect)
//{
//	// マス目タグのオブジェクトを全て取得
//	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);
//
//	// マス数カウント
//	int nSquareCnt{ 0 };
//
//	// オブジェクトがなくなるまで
//	while (pObj[nSquareCnt])
//	{
//		// マス目クラスにダウンキャスト
//		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);
//
//		// 目標座標を設定
//		pSquare->SetPosTarget({ (SCREEN_WIDTH * 0.5f) + (150.0f * nSquareCnt) - (nSelect * 150.0f), SCREEN_HEIGHT * 0.5f, 0.0f });
//
//		// 次へ進める
//		nSquareCnt++;
//	}
//}

//============================================================================
// 生成
//============================================================================
CSquare* CSquare::Create(D3DXVECTOR3 pos)
{
	// インスタンスを生成
	CSquare* pSquare = DBG_NEW CSquare{};

	if (pSquare == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pSquare->SetType(TYPE::SQUARE);

	// 基底クラスの初期設定
	pSquare->Init();

	// ランダムな座標を設定
	pSquare->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					0.0f });

	// サイズの設定
	pSquare->SetSize({ 50.0f, 50.0f, 0.0f });

	// テクスチャを設定
	pSquare->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::SQUARE_00));

	// UIオブジェクトにダウンキャスト
	CObject_UI* pObjUI = CUtility::GetInstance()->DownCast<CObject_UI, CObject>(pSquare);

	// アルファ値を設定
	pObjUI->SetAlpha(0.0f);

	return pSquare;
}

//============================================================================
// 出現
//============================================================================
void CSquare::Appear()
{
	if (!GetAppear())
	{
		return;
	}

	// アルファ値を取得
	float& fAlpha{ GetAlpha() };

	// 徐々に登場
	fAlpha += 0.025f;

	// 最大値に到達で固定
	if (fAlpha > 1.0f)
	{
		fAlpha = 1.0f;

		// 出現終了
		SetAppear(false);
	}
}

//============================================================================
// 消滅
//============================================================================
void CSquare::Disappear()
{
	if (!GetDisappear())
	{
		return;
	}

	// アルファ値を取得
	float& fAlpha{ GetAlpha() };

	// 徐々に消滅
	fAlpha += -0.05f;

	// 最低値に到達で固定
	if (fAlpha < 0.0f)
	{
		fAlpha = 0.0f;

		// 出現終了
		SetDisappear(false);

		// 破棄予約
		SetRelease();
	}
}