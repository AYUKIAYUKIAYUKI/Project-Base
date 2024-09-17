//============================================================================
// 
// ゲームマネージャー、ヘッダファイル [game_manager.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_	// 二重インクルード防止

//****************************************************
// ゲームマネージャークラス
//****************************************************
class CGameManager final
{
public:

	//****************************************************
	// ゲームフェーズ識別
	//****************************************************
	enum class PHASE
	{
		NONE = 0,	// 無し
		SELECT,		// レベル選択
		START,		// レベル開始
		INGAME,		// レベル進行
		FINISH,		// レベル終了
		RETIRE,		// リタイア
		MAX,
	};

	void Create();	// 生成
	void Init();	// 初期設定
	void Release();	// 解放
	void Uninit();	// 終了処理
	void Update();	// 更新処理

	PHASE GetPhase();			// フェーズ取得
	void SetPhase(PHASE phase);	// フェーズ設定

	int GetMaxStage();						// ステージ数を取得
	int GetSelectLevel();					// 選択レベル番号を取得
	std::vector<bool> GetCollectAchieve();	// アチーブ回収状態

	static CGameManager* GetInstance();	// ゲームマネージャーを取得

private:

	CGameManager();		// デフォルトコンストラクタ
	~CGameManager();	// デストラクタ

	void ImportLevel();	// レベル読み込み

	PHASE m_phase;							// フェーズ識別
	int m_nMaxStage;						// ステージ数
	int m_nSelectLevel;						// レベル選択
	std::vector<std::string> m_stagePath;	// ステージパス
	std::vector<bool> m_vbCollectAchieve;	// アチーブ回収状態

	static CGameManager* m_pInstance;	// ゲームマネージャー
};

#endif // _GAME_MANAGER_H_