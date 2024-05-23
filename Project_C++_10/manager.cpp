//============================================================================
// 
// マネージャー [manager.cpp]
// Author : 福田歩希
// 
//============================================================================

// インクルードファイル
#include "manager.h"

// 静的メンバの初期化
CRenderer* CManager::m_pRenderer = nullptr;			// レンダラー管理
CInputKeyboard* CManager::m_pKeyboard = nullptr;	// キーボード管理
CInputPad* CManager::m_pPad = nullptr;				// パッド管理
CSound* CManager::m_pSound = nullptr;				// サウンド管理

//****************************************************************************
// コンストラクタ
//****************************************************************************
CManager::CManager()
{
	m_pRenderer = nullptr;
	m_pKeyboard = nullptr;
	m_pPad = nullptr;
	m_pSound = nullptr;
}

//****************************************************************************
// デストラクタ
//****************************************************************************
CManager::~CManager()
{

}

//****************************************************************************
// 初期設定
//****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラーの生成
	m_pRenderer = new CRenderer;

	if (m_pRenderer == nullptr)
	{ // 生成失敗
		return E_FAIL;
	}

	// レンダラーの初期化
	m_pRenderer->Init(hWnd, bWindow);

	// キーボードの生成
	m_pKeyboard = new CInputKeyboard;

	if (m_pKeyboard == nullptr)
	{ // 生成失敗
		return E_FAIL;
	}

	// キーボードの初期化
	m_pKeyboard->Init(hInstance, hWnd);

	// パッドの生成
	m_pPad = new CInputPad;

	if (m_pPad == nullptr)
	{ // 生成失敗
		return E_FAIL;
	}

	// キーボードの初期化
	m_pPad->Init();

	// サウンドの生成
	m_pSound = new CSound;

	if (m_pSound == nullptr)
	{ // 生成失敗
		return E_FAIL;
	}

	// サウンドの初期化
	m_pSound->Init(hWnd);

	return S_OK;
}

//****************************************************************************
// 終了処理
//****************************************************************************
void CManager::Uninit()
{
	// レンダラーの破棄
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();	// 終了処理
		delete m_pRenderer;		// メモリを解放
		m_pRenderer = nullptr;	// ポインタを初期化
	}

	// キーボードの破棄
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();	// 終了処理
		delete m_pKeyboard;		// メモリを解放
		m_pKeyboard = nullptr;	// ポインタを初期化
	}

	// パッドの破棄
	if (m_pPad != nullptr)
	{
		m_pPad->Uninit();	// 終了処理
		delete m_pPad;		// メモリを解放
		m_pPad = nullptr;	// ポインタを初期化
	}

	// サウンドの破棄
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();	// 終了処理
		delete m_pSound;	// メモリを解放
		m_pSound = nullptr;	// ポインタを初期化
	}
}

//****************************************************************************
// 更新処理
//****************************************************************************
void CManager::Update()
{
	// レンダラーの更新
	m_pRenderer->Update();

	// キーボードの更新
	m_pKeyboard->Update();

	// パッドの更新
	m_pPad->Update();
}

//****************************************************************************
// 描画処理
//****************************************************************************
void CManager::Draw()
{
	// レンダラーの描画
	m_pRenderer->Draw();
}