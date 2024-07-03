//============================================================================
// 
// タイトル未定ゲーム [main.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _MAIN_H_
#define _MAIN_H_	// 二重インクルード防止

//****************************************************
// 2Dポリゴン頂点情報の構造体の定義
//****************************************************
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 除算数
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
};

//****************************************************
// 3Dポリゴン頂点情報の構造体の定義
//****************************************************
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標用
};

#endif // _MAIN_H_
