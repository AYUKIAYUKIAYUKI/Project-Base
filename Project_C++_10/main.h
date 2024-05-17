//============================================================================
// 
// ポリゴンの描画 5_16 [main.cpp]
// Author : 福田歩希
// 
//============================================================================

#ifndef _MAIN_H_
#define _MAIN_H_	// 二重インクルード防止

// インクルードファイル
#include <windows.h>
#include "d3dx9.h"

// ライブラリのリンク
#pragma	comment(lib,"d3d9.lib")		// 描画処理用
#pragma	comment(lib,"d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma	comment(lib,"dxguid.lib")	// DirectXのコーポネント使用のため

// マクロ定義
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)	//頂点フォーマット
#define SCREEN_WIDTH	1280	// ウインドウの幅
#define SCREEN_HEIGHT	720		// ウインドウの高さ


// ポリゴンクラス
class CPolygon
{
public:

	CPolygon();						// コンストラクタ
	~CPolygon();					// デストラクタ
	void Init();					// 初期処理
	void Uninit();					// 終了処理
	void Update();					// 更新処理
	void Draw();					// 描画処理
	static CPolygon* GetInstance();	// 情報取得

private:

	// 頂点情報の構造体
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;	// 頂点座標
		float rhw;			// 除算数
		D3DCOLOR col;		// 頂点カラー
	};

	static CPolygon* m_pPolygon;		// ポリゴン情報格納
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	VERTEX_2D m_Vtx;					// 頂点情報
};

#endif // _MAIN_H_
