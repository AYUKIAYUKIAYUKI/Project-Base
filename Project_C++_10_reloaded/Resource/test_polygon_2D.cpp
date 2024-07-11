//============================================================================
// 
// テスト用ポリゴン [test_polygon_2D.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "test_polygon_2D.h"
#include "manager.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CTestPolygon2D* CTestPolygon2D::m_pInstance = nullptr;	// 自クラス情報

//============================================================================
// コンストラクタ
//============================================================================
CTestPolygon2D::CTestPolygon2D()
{
	m_pVtxBuff = nullptr;	// 頂点バッファのポインタ
	m_pTex = nullptr;		// テクスチャ情報のポインタ
	m_pSurface = nullptr;	// サーフェイス情報のポインタ
}

//============================================================================
// デストラクタ
//============================================================================
CTestPolygon2D::~CTestPolygon2D()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CTestPolygon2D::Init()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// 頂点バッファの生成
	pDev->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	if (m_pVtxBuff == nullptr)
	{ // 生成失敗
		return E_FAIL;
	}

	// テクスチャを作成
	//pDev->CreateTexture(
	//	width,
	//	height,
	//	1,
	//	D3DUSAGE_RENDERTARGET,
	//	D3DFMT_A8R8G8B8,
	//	D3DPOOL_DEFAULT,
	//	&m_pTex,
	//	nullptr);

	// テクスチャの生成
	D3DXCreateTextureFromFileA(pDev,
		"Data\\TEXTURE\\AL-1S.png",
		&m_pTex);

	// テクスチャのサーフェイスを取得
	m_pTex->GetSurfaceLevel(0, &m_pSurface);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	float fSize = 32.0f;

	// 位置の設定
	pVtx[0].pos = { (SCREEN_WIDTH * 0.5f) - fSize, (SCREEN_HEIGHT * 0.5f) - fSize, 0.0f };
	pVtx[1].pos = { (SCREEN_WIDTH * 0.5f) + fSize, (SCREEN_HEIGHT * 0.5f) - fSize, 0.0f };
	pVtx[2].pos = { (SCREEN_WIDTH * 0.5f) - fSize, (SCREEN_HEIGHT * 0.5f) + fSize, 0.0f };
	pVtx[3].pos = { (SCREEN_WIDTH * 0.5f) + fSize, (SCREEN_HEIGHT * 0.5f) + fSize, 0.0f };

	// 除算数の設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 色の設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャの設定
	pVtx[0].tex = { 0.0f, 0.0f };
	pVtx[1].tex = { 1.0f, 0.0f };
	pVtx[2].tex = { 0.0f, 1.0f };
	pVtx[3].tex = { 1.0f, 1.0f };

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CTestPolygon2D::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// テクスチャ情報の破棄
	if (m_pTex != nullptr)
	{
		m_pTex->Release();
		m_pTex = nullptr;
	}

	// サーフェス情報の破棄
	if (m_pSurface != nullptr)
	{
		m_pSurface->Release();
		m_pSurface = nullptr;
	}
}

//============================================================================
// 更新処理
//============================================================================
void CTestPolygon2D::Update()
{

}

//============================================================================
// 描画処理
//============================================================================
void CTestPolygon2D::Draw()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// 頂点バッファをデータストリームに設定
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDev->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDev->SetTexture(0, m_pTex);

	// ポリゴンの描画
	pDev->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,										// 頂点情報の先頭アドレス
		2);										// プリミティブ数
}

//============================================================================
// 生成
//============================================================================
void CTestPolygon2D::Create()
{
	if (m_pInstance != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// インスタンスを生成
	m_pInstance = DBG_NEW CTestPolygon2D;
}

//============================================================================
// 解放
//============================================================================
void CTestPolygon2D::Release()
{
	if (m_pInstance != nullptr)
	{
		// 終了処理
		m_pInstance->Uninit();

		// メモリを解放
		delete m_pInstance;

		// ポインタを初期化
		m_pInstance = nullptr;
	}
}

//============================================================================
// 取得
//============================================================================
CTestPolygon2D* CTestPolygon2D::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// 生成
		m_pInstance->Create();
	}

	return m_pInstance;
}