//============================================================================
// 
// ポリゴンの描画 5_16 [main.cpp]
// Author : 福田歩希
// 
//============================================================================

#ifndef _MAIN_H_
#define _MAIN_H_	// 二重インクルード防止

// インクルードファイル
#include "renderer.h"

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
