//=============================================================================
//
// レコード [record.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "record.h"
#include "utility.h"

// デバッグ表示用
#include "renderer.h"

// テクスチャ取得用
#include "texture_manager.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CRecord::CRecord() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_pText{ nullptr }
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 数字情報のポインタを初期化
		m_apNumber[nCntNum] = nullptr;

		// 数字を生成
		m_apNumber[nCntNum] = CNumber::Create();

		// ランダムな座標
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f), -100.0f, 0.0f };

		// 初期座標の設定
		m_apNumber[nCntNum]->SetPos(pos);

		// 初期向きの設定
		//m_apNumber[nCntNum]->SetRot({ 0.0f, 0.0f, D3DX_PI * 2.0f });

		// 数字の出現予約
		m_apNumber[nCntNum]->SetAppear(true);
	}

	// 出現予約
	SetAppear(true);
}

//============================================================================
// デストラクタ
//============================================================================
CRecord::~CRecord()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CRecord::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CRecord::Uninit()
{
	// 基底クラスの終了処理
	CObject_UI::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CRecord::Update()
{
	// 目標座標へ
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), GetPosTarget(), 0.05f));

	// 基底クラスの更新
	CObject_UI::Update();

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	// 数字のみ
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 目標座標へ
		m_apNumber[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetPos(), m_apNumber[nCntNum]->GetPosTarget(), 0.075f));

		// 目標向きへ
		m_apNumber[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetRot(), m_apNumber[nCntNum]->GetRotTarget(), 0.075f));

		// 目標サイズへ
		m_apNumber[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetSize(), m_apNumber[nCntNum]->GetSizeTarget(), 0.05f));
	}
}

//============================================================================
// 描画処理
//============================================================================
void CRecord::Draw()
{
	// 基底クラスの描画処理
	CObject_UI::Draw();
}

//============================================================================
// 生成
//============================================================================
CRecord* CRecord::Create()
{
	// インスタンスを生成
	CRecord* pRecord = DBG_NEW CRecord;

	if (pRecord == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pRecord->SetType(TYPE::TIMER);

	// 基底クラスの初期設定
	pRecord->Init();

	// ランダムな座標を設定
	pRecord->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					0.0f });

	// サイズの設定
	pRecord->SetSize({ 0.0f, 0.0f, 0.0f });

	return pRecord;
}

//============================================================================
// タイムの読み込み
//============================================================================
int CRecord::ImportTimer(int nSelect)
{
	return nSelect;
}

//============================================================================
// 出現
//============================================================================
void CRecord::Appear()
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
void CRecord::Disappear()
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