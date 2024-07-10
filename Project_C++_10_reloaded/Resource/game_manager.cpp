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
#include "manager.h"

// オブジェクト生成用
#include "player.h"
#include "score.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CGameManager* CGameManager::m_pGameManager = nullptr;	// 自クラス情報

//============================================================================
// コンストラクタ
//============================================================================
CGameManager::CGameManager()
{
	m_phase = PHASE::NONE;		// フェーズ識別
	m_nMaxStage = 0;			// ステージ数
	m_pGameManager = nullptr;	// 自クラス情報の初期化
}

//============================================================================
// デストラクタ
//============================================================================
CGameManager::~CGameManager()
{

}

//============================================================================
// 初期設定
//============================================================================
void CGameManager::Init()
{
	// 開始フェーズへ
	m_phase = PHASE::BEGIN;

	// レベルを読み込む
	ImportLevel();
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
	CManager::GetRenderer()->SetDebugString(str);

	switch (m_phase)
	{
	case PHASE::NONE:

		// ここデバッグ

		break;

	case PHASE::BEGIN:

		if (!m_stagePath.size())
		{ // 読み込むステージがなくなったら

			// リザルト画面へ遷移
			CManager::GetFade()->SetFade(CScene::MODE::RESULT);

			// フェーズ処理を行わない
			m_phase = PHASE::NONE;

			// 以降の処理を行わない
			return;
		}

		// 全オブジェクト解放処理
		CObject::ReleaseAll();

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
		m_phase = PHASE::PLAY;

		break;

	case PHASE::PLAY:

		break;

	case PHASE::END:
	
		// 再開始
		m_phase = PHASE::BEGIN;

		break;

	default:

		// フェーズエラー
		assert(false);
		
		break;
	}
}

//============================================================================
// 生成
//============================================================================
void CGameManager::Create()
{
	if (m_pGameManager != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// インスタンスを生成
	m_pGameManager = DBG_NEW CGameManager;
}

//============================================================================
// 解放
//============================================================================
void CGameManager::Release()
{
	if (m_pGameManager != nullptr)
	{
		// 終了処理
		m_pGameManager->Uninit();

		// メモリを解放
		delete m_pGameManager;

		// ポインタを初期化
		m_pGameManager = nullptr;
	}
}

//============================================================================
// フェーズを設定
//============================================================================
void CGameManager::SetPhase(PHASE phase)
{
	m_phase = phase;
}

//============================================================================
// 取得
//============================================================================
CGameManager* CGameManager::GetInstance()
{
	if (m_pGameManager == nullptr)
	{
		// 生成
		m_pGameManager->Create();
	}

	return m_pGameManager;
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