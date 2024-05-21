//============================================================================
// 
// 2Dオブジェクト管理 [object2D.cpp]
// Author : 福田歩希
// 
//============================================================================

// インクルードファイル
#include "object2D.h"
#include "main.h"

//****************************************************************************
// コンストラクタ
//****************************************************************************
CObject2D::CObject2D()
{
	m_pVtxBuff = nullptr;			// 頂点バッファのポインタを初期化
	m_pTex = nullptr;				// テクスチャのポインタを初期化
	m_nCntTexChange = 0;			// テクスチャ変更管理
	m_nCntTexPattern = 0;			// テクスチャパターン管理
	m_pos = { 0.0f, 0.0f, 0.0f };	// 中心位置
	m_rot = { 0.0f, 0.0f, 0.0f };	// 回転量
	m_fAngle = 0.0f;				// 角度
	m_size = { 0.0f, 0.0f, 0.0f };	// サイズ
	m_fLength = 0.0f;				// 対角線
}

//****************************************************************************
// デストラクタ
//****************************************************************************
CObject2D::~CObject2D()
{
	Uninit();
}

//****************************************************************************
// 初期設定
//****************************************************************************
HRESULT CObject2D::Init()
{
	// デバイスを取得
	CRenderer* pRenderer = GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();
	
	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDev,
		"data\\TEXTURE\\.png",
		&m_pTex);

	// 頂点バッファの生成
	pDev->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置の設定
	pVtx[0].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[1].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[2].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[3].pos = { 0.0f, 0.0f, 0.0f };

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

//****************************************************************************
// 終了処理
//****************************************************************************
void CObject2D::Uninit()
{
	// テクスチャの破棄
	if (m_pTex != nullptr)
	{
		m_pTex->Release();
		m_pTex = nullptr;
	}

	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//****************************************************************************
// 更新処理
//****************************************************************************
void CObject2D::Update()
{
	// 必要な数値を算出
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.y);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置の設定
	pVtx[0].pos = { 
		m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength,
		m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	};

	pVtx[1].pos = { 
		m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	};

	pVtx[2].pos = {
		m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength,
		m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength,
		0.0f
	};

	pVtx[3].pos = { 
		m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength,
		m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength,
		0.0f
	};

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//****************************************************************************
// 描画処理
//****************************************************************************
void CObject2D::Draw()
{
	CRenderer* pRenderer = GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();

	// 頂点バッファをデータストリームに設定
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDev->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDev->SetTexture(0, m_pTex);

	//ポリゴンの描画
	pDev->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,										// 頂点情報の先頭アドレス
		2);										// プリミティブ数
}

//****************************************************************************
// 生成
//****************************************************************************
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CObject2D* pObject2D = new CObject2D;

	// 生成出来ていたら初期設定
	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->m_pos = pos;
		pObject2D->m_size = size;
	}

	return pObject2D;
}