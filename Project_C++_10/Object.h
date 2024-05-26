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

	//****************************************************
	// オブジェクトの種類識別
	//****************************************************
	enum TYPE
	{
		NONE = 0,	// 無し
		PLAYER,	// プレイヤー
		ENEMY,		// エネミー
		MAX
	};

	CObject();				// コンストラクタ
	virtual ~CObject() = 0;	// デストラクタ

	virtual HRESULT Init() = 0;	// 初期設定
	virtual void Uninit() = 0;	// 終了処理
	virtual void Update() = 0;	// 更新処理
	virtual void Draw() = 0;	// 描画処理

	static void ReleaseAll();	// 全オブジェクト解放処理
	static void UpdateAll();	// 全オブジェクト更新処理
	static void DrawAll();		// 全オブジェクト描画処理

	static CObject* GetObject(int nID);	// オブジェクト情報取得
	static int GetNumAll();				// オブジェクト総数取得

	TYPE GetType();	// タイプ取得

	void Release();	// 個別解放処理 (仮)

protected:

	void SetType(TYPE type);	// タイプ設定

private:

	static const int MAX_OBJ = 64;	// オブジェクト最大数

	static CObject* m_apObject[MAX_OBJ];	// オブジェクト管理
	static int m_nNumAll;					// オブジェクト総数

	int m_nID;		// 自分自身のID
	TYPE m_type;	// タイプ識別 

};

#endif // _RENDERER_H_