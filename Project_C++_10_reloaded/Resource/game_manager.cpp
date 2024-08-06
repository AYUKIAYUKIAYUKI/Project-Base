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

// フェード取得用
#include "manager.h"

// デバッグ表示用
#include "renderer.h"

// オブジェクト生成用
#include "block_destructible.h"
#include "player.h"
#include "score.h"

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
	// ステージ数を表示
	std::string str = "【現在のステージ:" + std::to_string(m_nMaxStage - m_stagePath.size()) + "/" + std::to_string(m_nMaxStage) + "】";
	CRenderer::GetInstance()->SetDebugString(str);

	switch (m_phase)
	{
	case PHASE::NONE:

		// ここデバッグ

		break;

	case PHASE::START:

		// 全オブジェクト解放処理
		CObject::ReleaseAll();

		// KARIHAIKEIの生成
		KARIHAIKEI::Create();

		// ステージを読み込む
		CStageMaker::GetInstance()->Import(m_stagePath[0]);

		// 先頭要素を削除する
		m_stagePath.erase(m_stagePath.begin());

		// プレイヤーの生成
		CPlayer::Create({ 0.0f, 0.0f, 0.0f });	// 位置

		// スコアの生成
		CScore::Create(
			{ 25.0f, 30.0f, 0.0f },	// 位置
			25.0f);					// 数列の配置間隔

		// プレイフェーズへ
		m_phase = PHASE::INGAME;

		break;

	case PHASE::INGAME:

		break;

	case PHASE::FINISH:

		m_phase = PHASE::END;
		
		break;

	case PHASE::END:

		if (!m_stagePath.size())
		{ // 読み込むステージがなくなったら

			// リザルト画面へ遷移
			CFakeScreen::GetInstance()->SetFade(CScene::MODE::RESULT);

			// フェーズ処理を行わない
			m_phase = PHASE::NONE;

			// 以降の処理を行わない
			return;
		}

		m_phase = PHASE::START;

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
// コンストラクタ
//============================================================================
CGameManager::CGameManager() : 
	m_phase{ PHASE::NONE },	// フェーズ識別
	m_nMaxStage{ 0 },		// ステージ数
	m_nCntGoal{ 0 },		// ゴール後カウント
	m_stagePath{}			// ステージパス
{

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
		// ステージのパスを保持
		m_stagePath.push_back(str);

		// ステージ数をカウントアップ
		nCntStage++;
	}

	// ステージ数を保持
	m_nMaxStage = nCntStage;
}