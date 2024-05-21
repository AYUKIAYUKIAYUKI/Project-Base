//============================================================================
// 
// プリコンパイル済みヘッダー [pch.h]
// Author : 福田歩希
// 
//============================================================================
#pragma once	// 二重インクルード防止

// インクルードファイル
#include <windows.h>
#include "d3dx9.h"

// ライブラリのリンク
#pragma	comment(lib,"d3d9.lib")		// 描画処理用
#pragma	comment(lib,"d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma	comment(lib,"dxguid.lib")	// DirectXのコーポネント使用のため

// マクロ定義
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 頂点フォーマット
#define SCREEN_WIDTH	1280	// ウインドウの幅
#define SCREEN_HEIGHT	720		// ウインドウの高さ