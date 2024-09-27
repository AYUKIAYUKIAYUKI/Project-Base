//=============================================================================
//
// 破壊記録 [record_dest.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "record_dest.h"
#include "utility.h"

// デバッグ表示用
#include "renderer.h"

// テクスチャ取得用
#include "texture_manager.h"

// ゲームマネージャー取得
#include "game_manager.h"

// プレイヤーの状態取得用
#include "player.h"
#include "player_state.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CRecord_Dest::CRecord_Dest() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_nCntDest{ 0 },
	m_pDestText{ nullptr },
	m_pBestText{ nullptr }
{
	// 初期座標用
	D3DXVECTOR3 InitPos{ (SCREEN_WIDTH * 0.5f), -100.0f, 0.0f };

	// テキストを生成
	m_pDestText = CText::Create(CTexture_Manager::TYPE::RECORDDEST);
	m_pDestText->SetPos(InitPos);
	m_pDestText->SetAppear(true);

	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 数字情報のポインタを初期化
		m_apDestNum[nCntNum] = nullptr;
		m_apBestNum[nCntNum] = nullptr;

		// 数字を生成
		m_apDestNum[nCntNum] = CNumber::Create();
		m_apDestNum[nCntNum]->SetPos(InitPos);
		m_apDestNum[nCntNum]->SetAppear(true);
	}

	// 出現予約
	SetAppear(true);
}

//============================================================================
// デストラクタ
//============================================================================
CRecord_Dest::~CRecord_Dest()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CRecord_Dest::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CRecord_Dest::Uninit()
{
	// 基底クラスの終了処理
	CObject_UI::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CRecord_Dest::Update()
{
	// 基底クラスの更新
	CObject_UI::Update();

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	/* 設定系統 */

	m_pDestText->SetPosTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.15f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
	m_pDestText->SetSizeTarget({ 140.0f, 30.0f, 0.0f });

	// 設定用共通情報
	D3DXVECTOR3 CopyPosTarget{ m_pDestText->GetPosTarget() };
	float fSizeX{ 42.5f };	// 共通横サイズ

	// 数字を並べる
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 中心座標から、相対的な先頭の位置を設定
		CopyPosTarget.x = m_pDestText->GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f) + 210.0f;

		// 先頭座標から数字が並ぶように調整
		CopyPosTarget.x += -fSizeX * nCntNum;
		m_apDestNum[nCntNum]->SetPosTarget(CopyPosTarget);

		// 数字の目標サイズを設定
		m_apDestNum[nCntNum]->SetSizeTarget({ fSizeX, 30.0f, 0.0f });
	}

	// カウント数のコピー
	int nCopy{ m_nCntDest };

	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 数字を設定
		m_apDestNum[nCntNum]->SetNumber(nCopy % 10);

		// 桁を減らす
		nCopy /= 10;
	}

	// 終了フェーズなら最高記録を生成
	if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::C_FINISH)
	{
		if (!m_pBestText)
		{
			// 初期座標用
			D3DXVECTOR3 InitPos{ (SCREEN_WIDTH * 0.5f), -100.0f, 0.0f };

			// テキストを生成
			m_pBestText = CText::Create(CTexture_Manager::TYPE::RECORDBEST);
			m_pBestText->SetPos(InitPos);
			m_pBestText->SetAppear(true);

			for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
			{
				// 数字を生成
				m_apBestNum[nCntNum] = CNumber::Create();
				m_apBestNum[nCntNum]->SetPos(InitPos);
				m_apBestNum[nCntNum]->SetAppear(true);
			}
		}
		else
		{ // 生成済みの場合は目標値設定

			m_pBestText->SetPosTarget({ SCREEN_WIDTH * 0.625f, SCREEN_HEIGHT * 0.15f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
			m_pBestText->SetSizeTarget({ 140.0f, 30.0f, 0.0f });

			// 設定用共通情報
			CopyPosTarget = m_pBestText->GetPosTarget();
			fSizeX = 42.5f;	// 共通横サイズ

			// カウント数のコピー
			nCopy = CRecord_Dest::ImportBestRecord();

			// 数字を並べる
			for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
			{
				// 中心座標から、相対的な先頭の位置を設定
				CopyPosTarget.x = m_pBestText->GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f) + 210.0f;

				// 先頭座標から数字が並ぶように調整
				CopyPosTarget.x += -fSizeX * nCntNum;
				m_apBestNum[nCntNum]->SetPosTarget(CopyPosTarget);

				// 数字の目標サイズを設定
				m_apBestNum[nCntNum]->SetSizeTarget({ fSizeX, 30.0f, 0.0f });

				// 数字を設定
				m_apBestNum[nCntNum]->SetNumber(nCopy % 10);

				// 桁を減らす
				nCopy /= 10;
			}
		}
	}

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	/* 反映系統 */

	// 数字系統
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		if (m_apDestNum[nCntNum])
		{
			m_apDestNum[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apDestNum[nCntNum]->GetPos(), m_apDestNum[nCntNum]->GetPosTarget(), 0.075f));
			m_apDestNum[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apDestNum[nCntNum]->GetRot(), m_apDestNum[nCntNum]->GetRotTarget(), 0.075f));
			m_apDestNum[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apDestNum[nCntNum]->GetSize(), m_apDestNum[nCntNum]->GetSizeTarget(), 0.05f));
		}

		if (m_apBestNum[nCntNum])
		{
			m_apBestNum[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apBestNum[nCntNum]->GetPos(), m_apBestNum[nCntNum]->GetPosTarget(), 0.075f));
			m_apBestNum[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apBestNum[nCntNum]->GetRot(), m_apBestNum[nCntNum]->GetRotTarget(), 0.075f));
			m_apBestNum[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apBestNum[nCntNum]->GetSize(), m_apBestNum[nCntNum]->GetSizeTarget(), 0.05f));
		}
	}
}

//============================================================================
// 描画処理
//============================================================================
void CRecord_Dest::Draw()
{
	// 基底クラスの描画処理
	CObject_UI::Draw();
}

//============================================================================
// 破壊記録をリセット
//============================================================================
void CRecord_Dest::ResetCntDest()
{
	m_nCntDest = 0;
}

//============================================================================
// 最高記録表記を消去予定
//============================================================================
void CRecord_Dest::SetDisappearBest()
{
	m_pBestText->SetDisappear(true);
	m_pBestText = nullptr;
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++) {
		m_apBestNum[nCntNum]->SetDisappear(true);
		m_apBestNum[nCntNum] = nullptr;
	}
}

//============================================================================
// 生成
//============================================================================
CRecord_Dest* CRecord_Dest::Create()
{
	// インスタンスを生成
	CRecord_Dest* pRecord{ DBG_NEW CRecord_Dest() };

	if (pRecord == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pRecord->SetType(TYPE::RECORD);

	// 初期設定
	pRecord->Init();

	//// ランダムな座標を設定
	//pRecord->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
	//				(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
	//				0.0f });

	//// サイズの設定
	//pRecord->SetSize({ 0.0f, 0.0f, 0.0f });

	return pRecord;
}

//============================================================================
// 破壊記録の増加
//============================================================================
void CRecord_Dest::AddDest()
{
	// 破壊記録を取得
	CObject* pFind{ CObject::FindObject(CObject::TYPE::RECORD) };
	CRecord_Dest* pRecord{ CUtility::GetInstance()->DownCast<CRecord_Dest, CObject>(pFind) };

	// 増加
	pRecord->m_nCntDest++;
}

//============================================================================
// 破壊記録の書き出し
//============================================================================
void CRecord_Dest::ExportRecord()
{
	// テキストを行ごとに保持する
	std::vector<std::string> vStr;

	// レベルファイルを展開
	std::ifstream Import{ "Data\\TXT\\dest_record.txt" };

	if (!Import)
	{ // 展開失敗
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("【警告】破壊記録に失敗しました", 300);
#endif	// _DEBUG

		return;
#endif
	}

	// テキストを格納
	std::string str;

	// ファイルを一行ずつ、情報を全て取得する
	while (std::getline(Import, str))
	{
		vStr.push_back(str);
	}

	// ファイルを閉じる
	Import.close();

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	// 破壊記録を取得
	CObject* pFind{ CObject::FindObject(CObject::TYPE::RECORD) };
	CRecord_Dest* pRecord{ CUtility::GetInstance()->DownCast<CRecord_Dest, CObject>(pFind) };

	// ベスト情報を抜き出す
	int nBestTime{ std::stoi(vStr.front().substr(vStr.front().find("b") + 2, vStr.front().find(","))) };

	// ベスト情報とラスト情報を比べる
	if (pRecord->m_nCntDest > nBestTime)
	{
		// ベストを上回っていたなら更新
		nBestTime = pRecord->m_nCntDest;
	}

	// ラスト情報を書き換える
	vStr.front() = "b:" + std::to_string(nBestTime) + ",";

	// レベルファイルを展開
	std::ofstream Export{ "Data\\TXT\\dest_record.txt" };

	if (!Export)
	{ // 展開失敗
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("【警告】破壊記録の書き出しに失敗しました", 300);
#endif	// _DEBUG

		return;
#endif
	}

	// 変更を加えた情報でもとのファイルを更新する
	for (auto&& it : vStr)
	{
		Export << it.c_str() << std::endl;
	}

	// ファイルを閉じる
	Export.close();
}

//============================================================================
// 破壊記録の読み込み
//============================================================================
int CRecord_Dest::ImportBestRecord()
{
	// 破壊記録ファイルを展開
	std::ifstream Import{ "Data\\TXT\\dest_record.txt" };

	if (!Import)
	{ // 展開失敗
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("破壊記録の読み込みに失敗しました", 300);
#endif	// _DEBUG

		return 0;
#endif
	}

	// 文章格納先
	std::string str{ };

	// テキストを読み取る
	std::getline(Import, str);

	// ファイルのベスト部分を抽出
	std::string best = str.substr(str.find("b:") + 2, str.find(","));

	// 整数値に変換
	return std::stoi(best);
}

//============================================================================
// 出現
//============================================================================
void CRecord_Dest::Appear()
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
void CRecord_Dest::Disappear()
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