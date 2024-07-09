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
class CGameManager
{
public:

	//****************************************************
	// ゲームフェーズ識別
	//****************************************************
	enum class PHASE
	{
		NONE = 0,	// 無し
		BEGIN,		// 開始
		PLAY,		// ゲーム中
		END,		// 終了
		MAX,
	};

	CGameManager();		// コンストラクタ
	~CGameManager();	// デストラクタ

	void Init();	// 初期設定
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Create();	// 生成
	void Release();	// 解放

	void SetPhase(PHASE phase);	// フェーズを設定

	static CGameManager* GetInstance();	// 取得

private:

	void ImportLevel();	// レベル読み込み

	PHASE m_phase;		// フェーズ識別
	int m_nMaxStage;	// ステージ数
	std::vector<std::string> m_stagePath;	// ステージパス

	static CGameManager* m_pGameManager;	// 自クラス情報
};

#endif // _GAME_MANAGERH_