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

	// レンダラー取得
	static CRenderer* GetRenderer() {
		return m_pRenderer;
	}

	// キーボード取得
	static CInputKeyboard* GetKeyboard() {
		return m_pKeyboard;
	}

	// パッド取得
	static CInputPad* GetPad() {
		return m_pPad;
	}

	// サウンド取得
	static CSound* GetSound() {
		return m_pSound;
	}

private:
	static CRenderer* m_pRenderer;		// レンダラー管理
	static CInputKeyboard* m_pKeyboard;	// キーボード管理
	static CInputPad* m_pPad;			// パッド管理
	static CSound* m_pSound;			// サウンド管理
};

#endif // _MANAGER_H_
