//============================================================================
// 
// ゲームマネージャー [game_manager.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "game_manager.h"
#include "stagemaker.h"
#include "fakescreen.h"
#include "utility.h"
#include "sound.h"

// フェード取得用
#include "manager.h"

// デバッグ表示用
#include "renderer.h"

// オブジェクト生成用
#include "block_destructible.h"
#include "leaf.h"
#include "player.h"
#include "player_state.h"
#include "record.h"
#include "square.h"
#include "timer.h"

// テスト用
#include "KARIHAIKEI.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CGameManager* CGameManager::m_pInstance = nullptr;	// ゲームマネージャーのポインタ

//============================================================================
// 生成
//============================================================================
void CGameManager::Create()
{
	if (m_pInstance != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// ゲームマネージャーを生成
	m_pInstance = DBG_NEW CGameManager{};
}

//============================================================================
// 初期設定
//============================================================================
void CGameManager::Init()
{
	// レベル開始フェーズへ
	m_phase = PHASE::START;

	// レベルを読み込む
	ImportLevel();
}

//============================================================================
// 解放
//============================================================================
void CGameManager::Release()
{
	if (m_pInstance != nullptr)
	{
		// 終了処理
		m_pInstance->Uninit();

		// メモリを解放
		delete m_pInstance;

		// ポインタを初期化
		m_pInstance = nullptr;
	}
}

//============================================================================
// 終了処理
//============================================================================
void CGameManager::Uninit()
{

}

//============================================================================
// 更新処理
//============================================================================
void CGameManager::Update()
{
	// キーボードを取得
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// パッドを取得
	CInputPad* pPad = CManager::GetPad();

	// 左右の入力情報
	static DWORD dwOldInput{ 0 };
	static bool bInputLeft{ false };
	static bool bInputRight{ false };

	// 右疑似トリガー入力
	if (pPad->GetJoyStickL().X > 0 && dwOldInput == 0)
	{
		bInputRight = true;
	}
	else
	{
		bInputRight = false;
	}

	// 左疑似トリガー入力
	if (pPad->GetJoyStickL().X < 0 && dwOldInput == 0)
	{
		bInputLeft = true;
	}
	else
	{
		bInputLeft = false;
	}

	// 過去の入力情報を保持
	dwOldInput = pPad->GetJoyStickL().X;

	switch (m_phase)
	{
	case PHASE::SELECT:
	
		// 葉っぱ生成の更新
		//CLeaf::UpdateToCreate();

		if (pKeyboard->GetTrigger(DIK_A) && m_nSelectLevel > -1 ||
			pPad->GetTrigger(CInputPad::JOYKEY::LEFT) && m_nSelectLevel > -1 ||
			bInputLeft && m_nSelectLevel > -1)
		{
			m_nSelectLevel--;

			// 選択音
			CSound::GetInstance()->Play(CSound::LABEL::SELECT);
		}
		else if (pKeyboard->GetTrigger(DIK_D) && m_nSelectLevel < m_nMaxStage ||
			pPad->GetTrigger(CInputPad::JOYKEY::RIGHT) && m_nSelectLevel < m_nMaxStage ||
			bInputRight && m_nSelectLevel < m_nMaxStage)
		{
			m_nSelectLevel++;

			// 選択音
			CSound::GetInstance()->Play(CSound::LABEL::SELECT);
		}

		// マス目を動作
		CSquare::ControlAll(m_nSelectLevel);

		// タイムを動作
		CTimer::SwitchControlByPahse(m_nSelectLevel);

		if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::START) || pPad->GetTrigger(CInputPad::JOYKEY::A) ||
			pPad->GetTrigger(CInputPad::JOYKEY::B) || pPad->GetTrigger(CInputPad::JOYKEY::X) || pPad->GetTrigger(CInputPad::JOYKEY::Y))
		{
			// 決定音
			CSound::GetInstance()->Play(CSound::LABEL::DEFINE);

			// ステージの範囲外を選択していたら
			if (m_nSelectLevel < 0 || m_nSelectLevel >= m_nMaxStage)
			{
				// タイトル画面へ
				//CFakeScreen::GetInstance()->SetFade(CScene::MODE::RESULT);
				CFakeScreen::GetInstance()->SetFade(CScene::MODE::TITLE);

				return;
			}

			// ウェーブを停止し、スタートフェーズへ移行
			CFakeScreen::GetInstance()->StopWave(PHASE::START);

			// レコードを消去予約
			CObject* pObj = CObject::FindObject(CObject::TYPE::RECORD);
			CRecord* pRecord = CUtility::GetInstance()->DownCast<CRecord, CObject>(pObj);
			pRecord->SetDisappearExtra();

			// マス目を全消去予約
			CSquare::SetDisappearAll();

			// タイマーリセット
			CTimer::TimerReset();
		}

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("レベル選択 : " + std::to_string(m_nSelectLevel));
#endif	// _DEBUG

		break;

	case PHASE::START:

		// スクリーン画面内の解放処理
		CObject::ReleaseScreen();

		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////

		// KARIHAIKEIの生成
		KARIHAIKEI::Create();

		// ステージを読み込む
		CStageMaker::GetInstance()->Import(m_stagePath[m_nSelectLevel]);

		// プレイヤーの生成
		CPlayer::Create();

		// レベル進行フェーズへ
		m_phase = PHASE::INGAME;

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("レベル開始");
#endif	// _DEBUG

		break;

	case PHASE::INGAME:

		// 葉っぱ生成の更新
		//CLeaf::UpdateToCreate();

		// タイムの動作
		CTimer::SwitchControlByPahse(m_nSelectLevel);

		// ステージセレクトに戻る
		if (pKeyboard->GetTrigger(DIK_BACK) || pPad->GetTrigger(CInputPad::JOYKEY::START) || pPad->GetTrigger(CInputPad::JOYKEY::BACK))
		{
			// プレイヤーを検索
			CObject* pFind = CObject::FindObject(CObject::TYPE::PLAYER);
			CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(pFind);

			// ゴール状態でなければ
			if (typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerStateGoal))
			{
				// ウェーブを強制終了
				CFakeScreen::GetInstance()->StopWave();

				// レベル終了フェーズへ移行
				/* ウェーブを経由しないとバグります */
				CFakeScreen::GetInstance()->SetWave(CGameManager::PHASE::RETIRE);

				// プレイヤーをゴール後状態へ
				pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::GOAL);

				// タイマーリセット
				CTimer::TimerReset();

				// 死亡音
				CSound::GetInstance()->Play(CSound::LABEL::DIE);
			}
		}

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("インゲーム");
#endif	// _DEBUG

		break;

	case PHASE::FINISH:

		// レコードを生成
		CRecord::Create();

		// マス目をステージ分生成 + ゲーム終了マス
		for (int i = 0; i < m_nMaxStage + 2; i++)
		{
			CSquare::Create({ 0.0f, 0.0f, 0.0f });
		}

		// 先頭・末尾の色を設定する
		CSquare::SetColorFrontAndBack();

		// タイムを書き出す
		CTimer::ExportTimer(m_nSelectLevel);

		// レベル選択フェーズへ
		m_phase = PHASE::SELECT;

		// 表示音
		CSound::GetInstance()->Play(CSound::LABEL::DISPLAY);
		
#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("レベル終了");
#endif	// _DEBUG

		break;

	case PHASE::RETIRE:

		// レコードを生成
		CRecord::Create();

		// マス目をステージ分生成 + ゲーム終了マス
		for (int i = 0; i < m_nMaxStage + 2; i++)
		{
			CSquare::Create({ 0.0f, 0.0f, 0.0f });
		}

		// 先頭・末尾の色を設定する
		CSquare::SetColorFrontAndBack();

		// レベル選択フェーズへ
		m_phase = PHASE::SELECT;

		// 表示音
		CSound::GetInstance()->Play(CSound::LABEL::DISPLAY);

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("リタイア");
#endif	// _DEBUG

		break;

	default:

		// フェーズエラー
		assert(false);
		
		break;
	}
}

//============================================================================
// フェーズ取得
//============================================================================
CGameManager::PHASE CGameManager::GetPhase()
{
	return m_phase;
}

//============================================================================
// フェーズ設定
//============================================================================
void CGameManager::SetPhase(PHASE phase)
{
	m_phase = phase;
}

//============================================================================
// ステージ数を取得
//============================================================================
int CGameManager::GetMaxStage()
{
	return m_nMaxStage;
}

//============================================================================
// 選択レベル番号を取得
//============================================================================
int CGameManager::GetSelectLevel()
{
	return m_nSelectLevel;
}

//============================================================================
// ゲームマネージャーを取得
//============================================================================
CGameManager* CGameManager::GetInstance()
{
	// オブジェクトが無ければ
	if (m_pInstance == nullptr)
	{
		// 生成
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CGameManager::CGameManager() :
	m_phase{ PHASE::NONE },	// フェーズ識別
	m_nMaxStage{ 0 },		// ステージ数
	m_nSelectLevel{ 0 },	// レベル選択
	m_stagePath{}			// ステージパス
{
	// タイムを生成
	CTimer::Create();
}

//============================================================================
// デストラクタ
//============================================================================
CGameManager::~CGameManager()
{

}

//============================================================================
// レベル読み込み
//============================================================================
void CGameManager::ImportLevel()
{
	std::ifstream Import("Data\\TXT\\level.txt");

	if (!Import)
	{ // 展開失敗
		assert(false);
	}

	// 文章格納先
	std::string str;

	// ステージカウント
	int nCntStage = 0;

	// テキストを読み取る
	while (std::getline(Import, str))
	{
		// ステージファイルのパス部分を抽出し
		std::string path = str.substr(0, str.find(","));

		// パスを保持しておく
		m_stagePath.push_back(path);

		// ステージ数をカウントアップ
		nCntStage++;
	}

	// ステージ数を保持
	m_nMaxStage = nCntStage;
}