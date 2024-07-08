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

	CGameManager();		// コンストラクタ
	~CGameManager();	// デストラクタ

	void Init();	// 初期設定
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Create();	// 生成
	void Release();	// 解放

	static CGameManager* GetInstance();	// 取得

private:

	static CGameManager* m_pGameManager;	// 自クラス情報
};

#endif // _GAME_MANAGERH_