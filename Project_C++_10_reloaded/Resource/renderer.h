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
class CRenderer final
{
public:

	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ

	HRESULT Init(HWND hWnd, BOOL bWindiw);	// 初期設定
	void Release();							// 解放
	void Update();							// 更新処理
	void Draw();							// 描画処理
	void PrintDebug();						// デバッグ表示

	static CRenderer* GetInstance();	// レンダラーを取得

	LPDIRECT3DDEVICE9 GetDeviece();		// デバイスの取得
	CTexture* GetTextureInstane();		// テクスチャマネージャーの取得
	CModel_X* GetModelInstane();		// モデルマネージャーの取得

	void SetDebugString(std::string str);			// デバッグ文字列に追加
	void SetTimeString(std::string str, int nCnt);	// 時限式デバッグ文字列に追加

private:

	void Create();	// 生成
	void Uninit();	// 終了処理

	static CRenderer* m_pRenderer;	// レンダラー

	LPDIRECT3D9 m_pD3D;									// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;						// デバイス
	LPD3DXFONT m_pFont;									// フォント
	std::string m_debugStr;								// 表示用文字列
	std::vector<std::pair<std::string, int>> m_timeStr;	// 時限式文字列
	CTexture* m_pTexture;								// テクスチャ管理
	CModel_X* m_pModel_X;								// Xモデル管理
};

#endif // _RENDERER_H_