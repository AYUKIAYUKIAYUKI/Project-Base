//============================================================================
// 
// レンダラー管理 [renderer.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "renderer.h"
#include "manager.h"
#include "object.h"

//============================================================================
// コンストラクタ
//============================================================================
CRenderer::CRenderer() : m_pD3D(nullptr), m_pD3DDevice(nullptr)
{
	m_pFont = nullptr;		// フォント
	m_debugString = {};		// デバッグ用文字列
	m_pTexture = nullptr;	// テクスチャ管理
	m_pModel_X = nullptr;	// Xモデル管理
}

//============================================================================
// デストラクタ
//============================================================================
CRenderer::~CRenderer()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindiw)
{
	D3DDISPLAYMODE d3ddm;			// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	// プレゼンテーションパラメータ

	// Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{ // 生成に失敗した場合
		return E_FAIL;
	}

	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{ // 現在のディスプレイモードを取得
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));	// パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲームサイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲームサイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// バックバッファの形式
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindiw;									// ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// Direct3Dデバイスの生成行程①
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		// Direct3Dデバイスの生成行程②
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			// Direct3Dデバイスの生成行程③
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ワイヤー描画
	//m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// ?
	//ID3DXAllocateHierarchy;

	// フォントを生成
	D3DXCreateFont(m_pD3DDevice, 22, 0, FW_HEAVY, 1,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont);

	// テクスチャ管理インスタンスを生成
	m_pTexture = DBG_NEW CTexture;

	if (m_pTexture == nullptr)
	{ // 生成失敗
		return E_FAIL;
	}

	// テクスチャ読み込み
	m_pTexture->Load();

	// Xモデル管理インスタンスを生成
	m_pModel_X = DBG_NEW CModel_X;

	if (m_pModel_X == nullptr)
	{ // 生成失敗
		return E_FAIL;
	}

	// Xモデル読み込み
	m_pModel_X->Load();

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CRenderer::Uninit()
{
	// 全オブジェクト解放処理
	CObject::ReleaseAll();
	
	//  テクスチャ破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// Xモデル破棄
	if (m_pModel_X != nullptr)
	{
		m_pModel_X->Unload();
		delete m_pModel_X;
		m_pModel_X = nullptr;
	}

	// フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}

	// Direct3Dデバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//============================================================================
// 更新処理
//============================================================================
void CRenderer::Update()
{
	// 文字列クリア
	m_debugString = {};

	// 全オブジェクト更新処理
	CObject::UpdateAll();
}

//============================================================================
// 描画処理
//============================================================================
void CRenderer::Draw()
{
	// 画面クリア
	m_pD3DDevice->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// カメラをセット
		CManager::GetCamera()->SetCamera();

		// 全オブジェクト描画処理
		CObject::DrawAll();

		// シーンの専用描画
		CManager::GetScene()->Draw();

		// フェードの描画処理
		CManager::GetFade()->Draw();

		// デバッグ表示
		PrintDebug();

		// 描画終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//============================================================================
// デバッグ表示
//============================================================================
void CRenderer::PrintDebug()
{
	// 表示位置
	RECT rect = { 0, 50, SCREEN_WIDTH, SCREEN_HEIGHT };

	//テキストの描画
	m_pFont->DrawText(NULL, m_debugString.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//============================================================================
// デバッグ用文字列に追加
//============================================================================
void CRenderer::SetDebugString(std::string str)
{
	m_debugString += str + "\n";
}

//============================================================================
// デバイスの取得
//============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDeviece()
{
	return m_pD3DDevice;
}

//============================================================================
// テクスチャ管理の取得
//============================================================================
CTexture* CRenderer::GetTextureInstane()
{
	return m_pTexture;
}

//============================================================================
// モデル管理の取得
//============================================================================
CModel_X* CRenderer::GetModelInstane()
{
	return m_pModel_X;
}