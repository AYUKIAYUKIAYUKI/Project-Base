//============================================================================
// 
// オブジェクト管理、ヘッダファイル [Object.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_	// 二重インクルード防止

// インクルードファイル
#include "main.h"

// オブジェクトクラス
class CObject
{
private:
	static const int MAX_OBJ = 64;		// オブジェクト最大数

public:
	CObject();					// コンストラクタ
	virtual ~CObject() = 0;		// デストラクタ
	virtual HRESULT Init() = 0;	// 初期設定
	virtual void Uninit() = 0;	// 終了処理
	virtual void Update() = 0;	// 更新処理
	virtual void Draw() = 0;	// 描画処理
	static void ReleaseAll();	// 全オブジェクト解放処理
	static void UpdateAll();	// 全オブジェクト更新処理
	static void DrawAll();		// 全オブジェクト描画処理

protected:
	void Release();	// 個別解放処理

private:
	static CObject* m_apObject[MAX_OBJ];	// オブジェクト管理
	int m_nID;								// 自分自身のID
	static int m_nNumAll;					// オブジェクト総数
};

#endif // _RENDERER_H_