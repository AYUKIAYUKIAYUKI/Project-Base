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
#include "sound.h"

// フェード取得用
#include "manager.h"

// デバッグ表示用
#include "renderer.h"

// オブジェクト生成用
#include "block_destructible.h"
#include "leaf.h"
#include "player.h"
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
#ifdef _DEBUG
	// ステージ数を表示
	std::string str = "【現在のステージ:" + std::to_string(m_nMaxStage - m_stagePath.size()) + "/" + std::to_string(m_nMaxStage) + "】";
	CRenderer::GetInstance()->SetDebugString(str);
#endif	// _DEBUG

	switch (m_phase)
	{
	case PHASE::SELECT:
	
		// 葉っぱ生成の更新
		CLeaf::UpdateToCreate();

		if (CManager::GetKeyboard()->GetTrigger(DIK_A) && m_nSelectLevel > 0)
		{
			m_nSelectLevel--;

			// 選択音
			CSound::GetInstance()->Play(CSound::LABEL::SELECT);
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_D) && m_nSelectLevel < m_nMaxStage - 1)
		{
			m_nSelectLevel++;

			// 選択音
			CSound::GetInstance()->Play(CSound::LABEL::SELECT);
		}

		// マス目を動作
		CSquare::ControlAll(m_nSelectLevel);

		// タイムを動作
		CTimer::SwitchControlByPahse(m_nSelectLevel);

		if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
		{
			// ウェーブを停止し、スタートフェーズへ移行
			CFakeScreen::GetInstance()->StopWave(PHASE::START);

			// マス目を全消去予約
			CSquare::DisappearAll();

			// タイマーリセット
			CTimer::TimerReset();

			// 決定音
			CSound::GetInstance()->Play(CSound::LABEL::DEFINE);
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
		CPlayer::Create({ 0.0f, 0.0f, 0.0f });	// 位置

		// レベル進行フェーズへ
		m_phase = PHASE::INGAME;

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("レベル開始");
#endif	// _DEBUG

		break;

	case PHASE::INGAME:

		// 葉っぱ生成の更新
		CLeaf::UpdateToCreate();

		// タイムの動作
		CTimer::SwitchControlByPahse(m_nSelectLevel);

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("インゲーム");
#endif	// _DEBUG

		break;

	case PHASE::FINISH:

		// マス目をステージ分生成
		for (int i = 0; i < m_nMaxStage; i++)
		{
			CSquare::Create({ 0.0f, 0.0f, 0.0f });
		}

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