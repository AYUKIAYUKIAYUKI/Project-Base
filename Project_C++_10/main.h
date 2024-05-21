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
#include "renderer.h"

// ライブラリのリンク
#pragma	comment(lib,"d3d9.lib")		// 描画処理用
#pragma	comment(lib,"d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma	comment(lib,"dxguid.lib")	// DirectXのコーポネント使用のため

// マクロ定義
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 頂点フォーマット
#define SCREEN_WIDTH	1280	// ウインドウの幅
#define SCREEN_HEIGHT	720		// ウインドウの高さ

// 頂点情報の構造体
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 除算数
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
};

CRenderer* GetRenderer(void);	// 取得

#endif // _MAIN_H_
