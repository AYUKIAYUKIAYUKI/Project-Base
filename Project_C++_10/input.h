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

// プリプロセッサディレクティブ
#define LEFT_JOYSTICK_CONVERT 0	// 左スティック入力を変換

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

// パッドクラス
class CInputPad : public CInput
{
public:
	// パッドのキー識別
	enum JOYKEY
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGHT,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_L3,
		JOYKEY_R3,
		JOYKEY_L,
		JOYKEY_R,
		JOYKEY_NONE1,
		JOYKEY_NONE2,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX,
	};

	// スティックの傾き情報
	typedef struct
	{
		SHORT X;
		SHORT Y;
	} JOYSTICK;

	CInputPad();					// コンストラクタ
	~CInputPad();					// デストラクタ
	HRESULT Init();					// 初期設定
	void Uninit() override;			// 終了処理
	void Update() override;			// 更新処理
	bool GetPress(JOYKEY Key);		// プレス情報取得
	bool GetTrigger(JOYKEY Key);	// トリガー情報取得
	JOYSTICK GetJoyStickL();		// 左スティックの傾き取得
	JOYSTICK GetJoyStickR();		// 右スティックの傾き取得

private:
	void AdjustJoyStick();	// スティックの調整

	XINPUT_STATE m_aKeyState;			// プレス情報
	XINPUT_STATE m_aKeyStateTrigger;	// トリガー情報
};

#endif // _INPUT_H_