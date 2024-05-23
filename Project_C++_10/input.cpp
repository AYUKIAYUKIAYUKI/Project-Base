//============================================================================
// 
// 入力処理管理 [input.cpp]
// Author : 福田歩希
// 
//============================================================================

// インクルードファイル
#include "input.h"

// 静的メンバの初期化
LPDIRECTINPUT8 CInput::m_Input = nullptr;	// // DirectInputオブジェクト

//****************************************************************************
// コンストラクタ
//****************************************************************************
CInput::CInput()
{

}

//****************************************************************************
// デストラクタ
//****************************************************************************
CInput::~CInput()
{

}

//****************************************************************************
// 初期設定
//****************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_Input == nullptr)
	{
		// DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_Input, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//****************************************************************************
// 終了処理
//****************************************************************************
void CInput::Uninit()
{
	// 入力デバイスの破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// DirectInputオブジェクトの破棄
	if (m_Input != nullptr)
	{
		m_Input->Release();
		m_Input = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//****************************************************************************
// コンストラクタ
//****************************************************************************
CInputKeyboard::CInputKeyboard()
{

}

//****************************************************************************
// デストラクタ
//****************************************************************************
CInputKeyboard::~CInputKeyboard()
{

}

//****************************************************************************
// 初期設定
//****************************************************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_Input == nullptr)
	{
		// DirectInputオブジェクトの生成
		if (FAILED(CInput::Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	// 入力デバイス(キーボード)の生成
	if (m_pDevice == nullptr)
	{
		if (FAILED(m_Input->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}
	}

	// データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定：フォアグラウンド
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//****************************************************************************
// 終了処理
//****************************************************************************
void CInputKeyboard::Uninit()
{
	// 基底クラスの終了処理
	CInput::Uninit();
}

//****************************************************************************
// 更新処理
//****************************************************************************
void CInputKeyboard::Update()
{
	BYTE state_keyboard[MAX_KEY] = {};	// キー入力情報

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(state_keyboard), &state_keyboard[0])))
	{
		for (int i = 0; i < MAX_KEY; i++)
		{
			// キーボードのプレス情報を保存
			m_aKeyState[i] = state_keyboard[i];

			// キーボードのトリガー情報を保存
			m_aKeyStateTrigger[i] = (m_aKeyState[i] ^ state_keyboard[i]) & state_keyboard[i];
		}
	}
	else
	{
		// キーボードのアクセス権を獲得
		m_pDevice->Acquire();
	}
}

//****************************************************************************
// プレス情報取得
//****************************************************************************
bool CInputKeyboard::GetPress(int nKey)
{
	return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//****************************************************************************
// トリガー情報取得
//****************************************************************************
bool CInputKeyboard::GetTrigger(int nKey)
{
	return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}