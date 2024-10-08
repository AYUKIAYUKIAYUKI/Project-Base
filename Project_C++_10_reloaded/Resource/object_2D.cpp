//============================================================================
// 
// 2Dオブジェクト管理 [object_2D.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"

// デバイスを取得
#include "renderer.h"

//============================================================================
// コンストラクタ
//============================================================================
CObject_2D::CObject_2D(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;	// 頂点バッファのポインタを初期化
	m_pTex = nullptr;		// テクスチャのポインタを初期化

	m_pos = { 0.0f, 0.0f, 0.0f };		// 位置
	m_rot = { 0.0f, 0.0f, 0.0f };		// 向き
	m_size = { 0.0f, 0.0f, 0.0f };		// サイズ
	m_col = { 1.0f, 1.0f, 1.0f, 1.0f };	// 色
	m_fLength = 0.0f;					// 展開用対角線
	m_fAngle = 0.0f;					// 対角線用角度
	m_fTexWidth = 1.0f;					// 横テクスチャ分割幅
	m_fTexHeight = 1.0f;				// 縦テクスチャ分縦幅
	m_nNowPatternU = 0;					// 現在の横テクスチャ種類
	m_nNowPatternV = 0;					// 現在の縦テクスチャ種類
}

//============================================================================
// デストラクタ
//============================================================================
CObject_2D::~CObject_2D()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CObject_2D::Init()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

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

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

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

//============================================================================
// 終了処理
//============================================================================
void CObject_2D::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================================================================
// 更新処理
//============================================================================
void CObject_2D::Update()
{
	if (m_pVtxBuff == nullptr)
	{ // 頂点バッファが消失
		assert(false);
	}

	// 必要な数値を算出
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y);
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

	// 色の設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャの設定
	pVtx[0].tex = { m_fTexWidth * m_nNowPatternU, m_fTexHeight * m_nNowPatternV };
	pVtx[1].tex = { m_fTexWidth * (m_nNowPatternU + 1), m_fTexHeight * m_nNowPatternV };
	pVtx[2].tex = { m_fTexWidth * (m_nNowPatternU), m_fTexHeight * (m_nNowPatternV + 1) };
	pVtx[3].tex = { m_fTexWidth * (m_nNowPatternU + 1), m_fTexHeight * (m_nNowPatternV + 1) };

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================================================================
// 描画処理
//============================================================================
void CObject_2D::Draw()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

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
// テクスチャ割当
//============================================================================
void CObject_2D::BindTex(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}

//============================================================================
// 位置取得
//============================================================================
D3DXVECTOR3 CObject_2D::GetPos()
{
	return m_pos;
}

//============================================================================
// 位置設定
//============================================================================
void CObject_2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================================================
// 向き取得
//============================================================================
D3DXVECTOR3 CObject_2D::GetRot()
{
	return m_rot;
}

//============================================================================
// 向き設定
//============================================================================
void CObject_2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================================================
// サイズ取得
//============================================================================
D3DXVECTOR3 CObject_2D::GetSize()
{
	return m_size;
}

//============================================================================
// サイズ設定
//============================================================================
void CObject_2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//============================================================================
// 色を取得
//============================================================================
D3DXCOLOR CObject_2D::GetCol()
{
	return m_col;
}

//============================================================================
// 色を設定
//============================================================================
void CObject_2D::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//============================================================================
// アルファ値を取得
//============================================================================
float& CObject_2D::GetAlpha()
{
	return m_col.a;
}

//============================================================================
// アルファ値を設定
//============================================================================
void CObject_2D::SetAlpha(float fAlpha)
{
	m_col.a = fAlpha;
}

//============================================================================
// 展開用対角線取得
//============================================================================
float CObject_2D::GetLength()
{
	return m_fLength;
}

//============================================================================
// 横テクスチャ分割幅設定
//============================================================================
void CObject_2D::SetTexWidth(float fWidth)
{
	m_fTexWidth = fWidth;
}

//============================================================================
// 縦テクスチャ分割幅設定
//============================================================================
void CObject_2D::SetTexHeight(float fHeight)
{
	m_fTexHeight = fHeight;
}

//============================================================================
// 現在のテクスチャ横分割幅取得
//============================================================================
int CObject_2D::GetNowPatternU()
{
	return m_nNowPatternU;
}

//============================================================================
// 現在のテクスチャ横分割幅設定
//============================================================================
void CObject_2D::SetNowPatternU(int nNowPatternU)
{
	m_nNowPatternU = nNowPatternU;
}

//============================================================================
// 現在のテクスチャ縦分割幅取得
//============================================================================
int CObject_2D::GetNowPatternV()
{
	return m_nNowPatternV;
}

//============================================================================
// 現在のテクスチャ縦分割幅設定
//============================================================================
void CObject_2D::SetNowPatternV(int nNowPatternV)
{
	m_nNowPatternV = nNowPatternV;
}

//============================================================================
// 生成
//============================================================================
CObject_2D* CObject_2D::Create()
{
	CObject_2D* pObject2D = DBG_NEW CObject_2D;

	// 生成出来ていたら初期設定
	if (pObject2D != nullptr)
	{
		pObject2D->Init();
	}

	return pObject2D;
}