//=============================================================================
//
// タイム [timer.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "timer.h"
#include "utility.h"

// デバッグ表示用
#include "renderer.h"

// テクスチャ取得用
#include "texture_manager.h"

// プレイヤーの状態取得用
#include "player.h"
#include "player_state.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CTimer::CTimer() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_nCntFrame{ 0 },
	m_nTimer{ 0 }
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 数字情報のポインタを初期化
		m_apNumber[nCntNum] = nullptr;

		// 数字を生成
		m_apNumber[nCntNum] = CNumber::Create();

		// ランダムな座標
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f), 0.0f, 0.0f };

		// 初期座標の設定
		m_apNumber[nCntNum]->SetPos(pos);

		// 初期向きの設定
		m_apNumber[nCntNum]->SetRot({ 0.0f, 0.0f, D3DX_PI * 2.0f });

		// 数字の出現予約
		m_apNumber[nCntNum]->SetAppear(true);
	}

	// 出現予約
	SetAppear(true);
}

//============================================================================
// デストラクタ
//============================================================================
CTimer::~CTimer()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CTimer::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CTimer::Uninit()
{
	// 基底クラスの終了処理
	CObject_UI::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CTimer::Update()
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
void CTimer::Draw()
{
	// 基底クラスの描画処理
	CObject_UI::Draw();
}

//============================================================================
// フェーズによる動作切替
//============================================================================
void CTimer::SwitchControlByPahse(int nSelect)
{
	// タイムを検索
	CObject* pObj = CObject::FindObject(CObject::TYPE::TIMER);
	CTimer* pTimer = CUtility::GetInstance()->DownCast<CTimer, CObject>(pObj);

	if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::SELECT)
	{
		// 目標座標を設定し、震わす
		pTimer->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f, });
		
		// 数字を並べる
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// 中心座標から、相対的な先頭の位置を設定
			D3DXVECTOR3 pos = pTimer->GetPosTarget();
			pos.x = pTimer->GetPosTarget().x + (25.0f * MAX_DIGIT * 0.5f) - (25.0f * 0.5f);

			// 先頭座標から数字が並ぶように調整
			pos.x += -25.0f * nCntNum;
			pTimer->m_apNumber[nCntNum]->SetPosTarget(pos);

			// 数字の目標サイズを設定
			pTimer->m_apNumber[nCntNum]->SetSizeTarget({ 25.0f, 20.0f, 0.0f });
		}

		// タイムの読み込み
		pTimer->m_nTimer = pTimer->ImportTimer(nSelect);
	}
	else if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::INGAME)
	{
		// 目標座標を設定し、震わす
		pTimer->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.15f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f, });

		// 数字を並べる
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// 中心座標から、相対的な先頭の位置を設定
			D3DXVECTOR3 pos = pTimer->GetPosTarget();
			pos.x = pTimer->GetPosTarget().x + (37.5f * MAX_DIGIT * 0.5f) - (37.5f * 0.5f);

			// 先頭座標から数字が並ぶように調整
			pos.x += -37.5f * nCntNum;
			pTimer->m_apNumber[nCntNum]->SetPosTarget(pos);

			// 数字の目標サイズを設定
			pTimer->m_apNumber[nCntNum]->SetSizeTarget({ 37.5f, 30.0f, 0.0f });
		}

		// プレイヤーを検索
		CObject* pFind = CObject::FindObject(CObject::TYPE::PLAYER);
		CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(pFind);

		// ゴール状態でなければ
		if (typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerState::STATE::GOAL))
		{
			// フレームカウント
			pTimer->m_nCntFrame++;

			if (pTimer->m_nCntFrame > 60)
			{
				// カウントリセット
				pTimer->m_nCntFrame = 0;
			
				// タイマー進行
				pTimer->m_nTimer++;
			}
		}
		//else
		//{
		//	// タイムを書き出す
		//	ExportTimer(pTimer->m_nTimer);
		//}
	}

	// カウント数のコピー
	int nCopy{ pTimer->m_nTimer };

	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 数字を設定
		pTimer->m_apNumber[nCntNum]->SetNumber(nCopy % 10);

		// 桁を減らす
		nCopy /= 10;
	}
}

//============================================================================
// 時間リセット (仮)
//============================================================================
void CTimer::TimerReset()
{
	// タイムを検索
	CObject* pObj = CObject::FindObject(CObject::TYPE::TIMER);
	CTimer* pTimer = CUtility::GetInstance()->DownCast<CTimer, CObject>(pObj);

	// 時間をリセット
	pTimer->m_nCntFrame = 0;
	pTimer->m_nTimer = 0;
}

//============================================================================
// タイムの書き出し
//============================================================================
void CTimer::ExportTimer(int nTimer)
{
	//// ステージ配置情報を書き出し展開
	//std::ofstream Export("Data\\TXT\\stage.txt");
}

//============================================================================
// 生成
//============================================================================
CTimer* CTimer::Create()
{
	// インスタンスを生成
	CTimer* pTimer = DBG_NEW CTimer;

	if (pTimer == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pTimer->SetType(TYPE::TIMER);

	// 基底クラスの初期設定
	pTimer->Init();

	// ランダムな座標を設定
	pTimer->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					0.0f });

	// サイズの設定
	pTimer->SetSize({ 0.0f, 0.0f, 0.0f });

	return pTimer;
}

//============================================================================
// タイムの読み込み
//============================================================================
int CTimer::ImportTimer(int nSelect)
{
	std::ifstream Import("Data\\TXT\\timer.txt");

	if (!Import)
	{ // 展開失敗
#if 0
		assert(false);
#else
		CRenderer::GetInstance()->SetDebugString("【警告】タイム情報の読み込みに失敗しました");
		return 0;
#endif
	}
	else
	{
		// 文章格納先
		std::string str{};

		// テキストを読み取る
		for (int i = 0; i < nSelect + 1; i++)
		{
			std::getline(Import, str);
		}

		return std::stoi(str);
	}
}

//============================================================================
// 出現
//============================================================================
void CTimer::Appear()
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
void CTimer::Disappear()
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