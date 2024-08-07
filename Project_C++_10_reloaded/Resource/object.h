//============================================================================
// 
// オブジェクト管理、ヘッダファイル [object.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_	// 二重インクルード防止

//****************************************************
// オブジェクトクラス
//****************************************************
class CObject
{
public:

	static const int MAX_OBJ = 512;	// オブジェクトの最大数

	//****************************************************
	// オブジェクトの種類識別
	//****************************************************
	enum class TYPE
	{
		NONE = 0,		// 無し
		PLAYER,			// プレイヤー
		DUMMY,			// ダミー
		ENEMY,			// エネミー
		BLOCK,			// ブロック
		DESTRUCTIBLE,	// 可壊ブロック
		ITEM,			// アイテム
		START,			// スタート
		GOAL,			// ゴール
		SCORE,			// スコア
		MAX,
	};

	//****************************************************
	// オブジェクトのレイヤー識別
	//****************************************************
	enum class LAYER
	{
		NONE = 0,		// 無し
		BACK,			// 背景
		BACK_MIDDLE,	// 後ろ側
		FRONT_MIDDLE,	// 前側
		FRONT,			// 前景
		UI,				// UI
		MAX,
	};

	CObject(int nPriority = static_cast<int>(LAYER::MAX) - 1);	// コンストラクタ
	virtual ~CObject() = 0;										// デストラクタ

	virtual HRESULT Init() = 0;	// 初期設定
	virtual void Uninit() = 0;	// 終了処理
	virtual void Update() = 0;	// 更新処理
	virtual void Draw() = 0;	// 描画処理
	void Release();				// 個別解放処理

	TYPE GetType();				// タイプを取得
	void SetType(TYPE type);	// タイプを設定

	bool GetDeath();				// 死亡フラグ取得
	void SetDeath(bool bDetected);	// 死亡フラグ設定

	static void ReleaseAll();	// 全オブジェクト解放処理
	static void UpdateAll();	// 全オブジェクト更新処理
	static void DrawAll();		// 全オブジェクト描画処理

	static CObject* GetObject(int nPriority);	// 先頭オブジェクトのポインタ取得
	static CObject* FindObject(TYPE type);		// 特定タイプのオブジェクト探す
	static CObject** FindAllObject(TYPE type);	// 特定タイプのオブジェクトをすべて探す

private:

	static CObject* m_apFind[MAX_OBJ];							// 検索されたオブジェクト保持用
	static int m_nNumAll;										// オブジェクト総数
	static CObject* m_pTop[static_cast<int>(LAYER::MAX)];		// 先頭オブジェクトのポインタ
	static CObject* m_pCur[static_cast<int>(LAYER::MAX)];		// 終端オブジェクトのポインタ

	int m_nPriority;	// 描画優先度
	CObject* m_pPrev;	// 前のオブジェクトのポインタ
	CObject* m_pNext;	// 次のオブジェクトのポインタ
	TYPE m_type;		// タイプ識別 
	bool m_bDeath;		// 死亡フラグ
};

#endif // _OBJECT_H_