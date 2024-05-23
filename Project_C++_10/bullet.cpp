//============================================================================
// 
// 弾 [bullet.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "bullet.h"
#include "main.h"
#include "manager.h"

//============================================================================
// コンストラクタ
//============================================================================
CBullet::CBullet() : CObject2D::CObject2D()
{
	m_nCntTexChange = 0;			// テクスチャ変更管理
	m_nCntTexPattern = 0;			// テクスチャパターン管理
	m_pos = { 0.0f, 0.0f, 0.0f };	// 中心位置
	m_rot = { 0.0f, 0.0f, 0.0f };	// 回転量
	m_fAngle = 0.0f;				// 角度
	m_size = { 0.0f, 0.0f, 0.0f };	// サイズ
	m_fLength = 0.0f;				// 対角線
	m_nRemain = 0;					// 使用期間
}

//============================================================================
// デストラクタ
//============================================================================
CBullet::~CBullet()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CBullet::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBullet::Uninit()
{
	// 基底クラスの終了処理
	CObject2D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBullet::Update()
{
	// 必要な数値を算出
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.y);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファを取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtxBuff->Unlock();

	// 移動
	Translation();

	// 期間経過
	Progress();
}

//============================================================================
// 描画処理
//============================================================================
void CBullet::Draw()
{
	// 基底クラスの描画処理
	CObject2D::Draw();
}

//============================================================================
// 生成
//============================================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int m_nRemain)
{
	CBullet* pBullet = new CBullet;

	// 生成出来ていたら初期設定
	if (pBullet != nullptr)
	{
		pBullet->Init();
		pBullet->m_pos = pos;
		pBullet->m_size = size;
		pBullet->m_nRemain = m_nRemain;
	}

	// デバイスを取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();

	// テクスチャのポインタ
	LPDIRECT3DTEXTURE9 pTex = nullptr;

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDev,
		"data\\TEXTURE\\bullet000.png",
		&pTex);

	// テクスチャを設定
	pBullet->BindTex(pTex);

	return pBullet;
}

//============================================================================
// 移動
//============================================================================
void CBullet::Translation()
{

}

//============================================================================
// 期間経過
//============================================================================
void CBullet::Progress()
{
	// 使用期間カウントダウン
	m_nRemain--;

	// 使用期間がなくなると消滅
	if (m_nRemain <= 0)
	{
		CObject::Release();	// 自信を破棄
	}
}