//============================================================================
// 
// マネージャー、ヘッダファイル [managaer.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _MANAGER_H_
#define _MANAGER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "sound.h"

//****************************************************
// マネージャークラス
//****************************************************
class CManager
{
public:

	CManager();		// コンストラクタ
	~CManager();	// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// 初期設定
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画処理

	static CRenderer* GetRenderer();		// レンダラー取得
	static CTexture* GetTexture();			// テクスチャ取得
	static CInputKeyboard* GetKeyboard();	// キーボード取得
	static CInputPad* GetPad();				// パッド取得
	static CSound* GetSound();				// サウド取得

private:

	static CRenderer* m_pRenderer;		// レンダラー管理
	static CTexture* m_pTexture;		// テクスチャ管理
	static CInputKeyboard* m_pKeyboard;	// キーボード管理
	static CInputPad* m_pPad;			// パッド管理
	static CSound* m_pSound;			// サウンド管理
};

#endif // _MANAGER_H_
