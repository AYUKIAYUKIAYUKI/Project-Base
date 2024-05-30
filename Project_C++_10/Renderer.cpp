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
#include "object.h"

// 仮
#include "bg.h"
#include "block.h"
#include "enemy.h"
#include "item.h"
#include "player.h"
#include "score.h"

//============================================================================
// コンストラクタ
//============================================================================
CRenderer::CRenderer() : m_pD3D(nullptr), m_pD3DDevice(nullptr), m_pTexture(nullptr)
{

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

	// Direct3Dデバイスの生成行程�@
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		// Direct3Dデバイスの生成行程�A
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			// Direct3Dデバイスの生成行程�B
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

	// テクスチャインスタンスを生成
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture;
	}

	if (m_pTexture == nullptr)
	{ //  テクスチャインスタンス生成失敗
		return E_FAIL;
	}

	// テクスチャ読み込み
	m_pTexture->Load();

	// 背景の生成 (仮)
	CBg::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// 中心位置
		{ SCREEN_HEIGHT * 0.5f,  SCREEN_HEIGHT * 0.5f, 0.0f });	// サイズ

	// ブロックの生成 (仮)
	CBlock::Create(
		{ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.7f, 0.0f },	// 中心位置
		{ 50.0f, 100.0f, 0.0f });								// サイズ

	// ブロックの生成 (仮)
	CBlock::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// 中心位置
		{ 75.0f, 75.0f, 0.0f });								// サイズ

	// ブロックの生成 (仮)
	CBlock::Create(
		{ SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.3f, 0.0f },	// 中心位置
		{ 100.0f, 50.0f, 0.0f });								// サイズ

	// エネミーの生成 (仮)
	CEnemy::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// 中心位置
		{ 50.0f, 50.0f, 0.0f });								// サイズ

	// アイテムの生成 (仮)
	CItem::Create(
		{ SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f, 0.0f },	// 中心位置
		{ 80.0f, 80.0f, 0.0f });								// サイズ

	// プレイヤーの生成 (仮)
	CPlayer::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT, 0.0f },	// 中心位置
		{ 40.0f, 50.0f, 0.0f });				// サイズ

	// スコアの生成 (仮)
	CScore::Create(
		{ 680.0f, 145.0f, 0.0f },	// 中心位置
		25.0f);						// 数列の配置間隔

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
	// 全オブジェクト更新処理
	CObject::UpdateAll();
}

//============================================================================
// 描画処理
//============================================================================
void CRenderer::Draw()
{
	// 画面クリア
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// 全オブジェクト描画処理
		CObject::DrawAll();

		// 描画終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
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