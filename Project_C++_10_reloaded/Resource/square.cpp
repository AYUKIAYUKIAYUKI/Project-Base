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
	CObject_2D{ static_cast<int>(LAYER::UI) },
	m_bAppear{ false },
	m_bDisappear{ false },
	m_posTarget{ 0.0f, 0.0f, 0.0f }
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

	// 出現
	m_bAppear = true;
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
	HRESULT hr = CObject_2D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CSquare::Uninit()
{
	// 基底クラスの終了処理
	CObject_2D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CSquare::Update()
{
	// 出現
	Appear();

	// 消滅
	Disappear();

	// 基底クラスの更新
	CObject_2D::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CSquare::Draw()
{
	// 基底クラスの描画処理
	CObject_2D::Draw();
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

		// 選択しているマスを揺らす
		if (nSquareCnt == nSelect)
		{
			posNew = {
				(SCREEN_WIDTH * 0.5f),
				(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
				0.0f };
		}
		else
		{
			posNew = { 
				(SCREEN_WIDTH * 0.5f) + (150.0f * nSquareCnt) - (nSelect * 150.0f),
				SCREEN_HEIGHT * 0.75f + +CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
				0.0f };
		}

		// 目標座標を新しいものに
		pSquare->m_posTarget = posNew;
		
		// 目標座標へ迫る
		D3DXVECTOR3 pos{ pSquare->GetPos() };
		pos += (pSquare->m_posTarget - pos) * 0.05f;
		pSquare->SetPos(pos);


		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		// 数字を並べる
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			// 中心座標から、相対的な先頭の位置を設定
			pos.x = pSquare->GetPos().x + (25.0f * 0.5f) * (MAX_DIGIT * 0.5f);

			// 桁ごとに所定の座標へ補正
			pos.x +=  -25.0f * i;
			pSquare->m_apNumber[i]->SetPos(pos);
		}

		// カウント数のコピー
		int nCopy{ nSquareCnt };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
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
// マス目を並べる (不必要)
//============================================================================
void CSquare::LineUpAll(int nSelect)
{
	// マス目タグのオブジェクトを全て取得
	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);

	// マス数カウント
	int nSquareCnt{ 0 };

	// オブジェクトがなくなるまで
	while (pObj[nSquareCnt])
	{
		// マス目クラスにダウンキャスト
		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);

		// 目標座標を設定
		pSquare->m_posTarget = { (SCREEN_WIDTH * 0.5f) + (150.0f * nSquareCnt) - (nSelect * 150.0f), SCREEN_HEIGHT * 0.5f, 0.0f };

		// 次へ進める
		nSquareCnt++;
	}
}

//============================================================================
// 生成
//============================================================================
CSquare* CSquare::Create(D3DXVECTOR3 pos)
{
	// インスタンスを生成
	CSquare* pSquare = DBG_NEW CSquare;

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

	// 2Dオブジェクトにダウンキャスト
	CObject_2D* pObj2D = CUtility::GetInstance()->DownCast<CObject_2D, CObject>(pSquare);

	// アルファ値を設定
	pObj2D->SetAlpha(0.0f);

	return pSquare;
}

//============================================================================
// 出現
//============================================================================
void CSquare::Appear()
{
	if (!m_bAppear)
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
		m_bAppear = false;
	}
}

//============================================================================
// 消滅
//============================================================================
void CSquare::Disappear()
{
	if (!m_bDisappear)
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
		m_bDisappear = false;

		// 破棄予約
		SetRelease();
	}
}