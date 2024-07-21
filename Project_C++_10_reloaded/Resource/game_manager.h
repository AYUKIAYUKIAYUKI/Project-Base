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
		START,		// レベル開始
		INGAME,		// ゲーム進行
		FINISH,		// レベル終了
		END,		// ゲーム終了
		MAX,
	};

	void Create();	// 生成
	void Init();	// 初期設定
	void Release();	// 解放
	void Uninit();	// 終了処理
	void Update();	// 更新処理

	PHASE GetPhase();			// フェーズ取得
	void SetPhase(PHASE phase);	// フェーズ設定

	static CGameManager* GetInstance();	// ゲームマネージャーを取得

private:

	CGameManager();		// コンストラクタ
	~CGameManager();	// デストラクタ

	void ImportLevel();	// レベル読み込み

	PHASE m_phase;							// フェーズ識別
	int m_nMaxStage;						// ステージ数
	int m_nCntGoal;							// ゴール後カウント
	std::vector<std::string> m_stagePath;	// ステージパス

	static CGameManager* m_pInstance;	// ゲームマネージャー
};

#endif // _GAME_MANAGER_H_