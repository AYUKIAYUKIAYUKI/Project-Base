//============================================================================
// 
// 爆発 [explosion.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "explosion.h"
#include "main.h"
#include "manager.h"
#include "bullet.h"

//============================================================================
// コンストラクタ
//============================================================================
CExplosion::CExplosion() : CObject2D::CObject2D()
{
	m_nCntTexChange = 0;			// テクスチャ変更管理
	m_nCntTexPattern = 0;			// テクスチャパターン管理
	m_pos = { 0.0f, 0.0f, 0.0f };	// 中心位置
	m_rot = { 0.0f, 0.0f, 0.0f };	// 回転量
	m_fAngle = 0.0f;				// 角度
	m_size = { 0.0f, 0.0f, 0.0f };	// サイズ
	m_fLength = 0.0f;				// 対角線
}

//============================================================================
// デストラクタ
//============================================================================
CExplosion::~CExplosion()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CExplosion::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CExplosion::Uninit()
{
	// 基底クラスの終了処理
	CObject2D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CExplosion::Update()
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

	// テクスチャの設定
	pVtx[0].tex = { m_nCntTexPattern / 8.0f, 0.0f };
	pVtx[1].tex = { (m_nCntTexPattern + 1) / 8.0f, 0.0f };
	pVtx[2].tex = { m_nCntTexPattern / 8.0f, 1.0f };
	pVtx[3].tex = { (m_nCntTexPattern + 1) / 8.0f, 1.0f };

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();

	// アニメーション
	Animation();
}

//============================================================================
// 描画処理
//============================================================================
void CExplosion::Draw()
{
	// 基底クラスの描画処理
	CObject2D::Draw();
}

//============================================================================
// 生成
//============================================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion* pExplosion = new CExplosion;

	// 生成出来ていたら初期設定
	if (pExplosion != nullptr)
	{
		pExplosion->Init();
		pExplosion->m_pos = pos;
		pExplosion->m_size = size;
	}

	// デバイスを取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();

	// テクスチャのポインタ
	LPDIRECT3DTEXTURE9 pTex = nullptr;

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDev,
		"data\\TEXTURE\\explosion000.png",
		&pTex);

	// テクスチャを設定
	pExplosion->BindTex(pTex);

	return pExplosion;
}

//============================================================================
// アニメーション
//============================================================================
void CExplosion::Animation()
{
	// テクスチャ変更管理カウントアップ
	m_nCntTexChange++;

	if (m_nCntTexChange >= 15)
	{
		// テクスチャパターン変更
		m_nCntTexPattern++;

		if (m_nCntTexPattern >= 8)
		{
			// 自身を破棄
			CObject::Release();
		}

		// 変更管理カウントをリセット
		m_nCntTexChange = 0;
	}
}