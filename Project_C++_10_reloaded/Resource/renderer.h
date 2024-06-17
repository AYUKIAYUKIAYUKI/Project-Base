//============================================================================
// 
// レンダラー管理、ヘッダファイル [renderer.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _RENDERER_H_
#define _RENDERER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "texture.h"
#include "model_X.h"

//****************************************************
// レンダラークラス
//****************************************************
class CRenderer
{
public:

	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ

	HRESULT Init(HWND hWnd, BOOL bWindiw);	// 初期設定
	void Uninit();							// 終了処理
	void Update();							// 更新処理
	void Draw();							// 描画処理

	LPDIRECT3DDEVICE9 GetDeviece();	// デバイスの取得
	CTexture* GetTextureInstane();	// テクスチャ管理の取得
	CModel_X* GetModelInstane();		// モデル管理の取得

private:

	LPDIRECT3D9 m_pD3D;				// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// デバイス
	CTexture* m_pTexture;			// テクスチャ管理
	CModel_X* m_pModel_X;			// Xモデル管理
};

#endif // _RENDERER_H_