//============================================================================
// 
// 入力処理管理、ヘッダファイル [input.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _INPUT_H_
#define _INPUT_H_	// 二重インクルード防止

// マクロ定義
#define MAX_KEY	256	// キー最大数

// インプットクラス
class CInput
{
public:
	CInput();					// コンストラクタ
	~CInput();					// デストラクタ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期設定
	virtual void Uninit();		// 終了処理
	virtual void Update() = 0;	// 更新処理

protected:
	static LPDIRECTINPUT8 m_Input;	// DirectInputオブジェクト
	LPDIRECTINPUTDEVICE8 m_pDevice;	// 入力デバイス
};

// キーボードクラス
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();			// コンストラクタ
	~CInputKeyboard();			// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	bool GetPress(int nKey);	// プレス情報取得
	bool GetTrigger(int nKey);	// トリガー情報取得

private:
	BYTE m_aKeyState[MAX_KEY];			// プレス情報
	BYTE m_aKeyStateTrigger[MAX_KEY];	// トリガー情報
};

#endif // _INPUT_H_