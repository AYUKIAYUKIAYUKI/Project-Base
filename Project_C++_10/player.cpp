//============================================================================
// 
// プレイヤー [player.cpp]
// Author : 福田歩希
// 
//============================================================================

// インクルードファイル
#include "player.h"
#include "main.h"

//****************************************************************************
// コンストラクタ
//****************************************************************************
CPlayer::CPlayer() : CObject2D::CObject2D()
{

}

//****************************************************************************
// デストラクタ
//****************************************************************************
CPlayer::~CPlayer()
{
	Uninit();
}

//****************************************************************************
// 初期設定
//****************************************************************************
HRESULT CPlayer::Init()
{
	// デバイスを取得
	CRenderer* pRenderer = GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDev,
		"data\\TEXTURE\\runningman000.png",
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
void CPlayer::Uninit()
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
void CPlayer::Update()
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

	// テクスチャの設定
	pVtx[0].tex = { m_nCntTexPattern / 8.0f, 0.0f };
	pVtx[1].tex = { (m_nCntTexPattern + 1) / 8.0f, 0.0f };
	pVtx[2].tex = { m_nCntTexPattern / 8.0f, 1.0f };
	pVtx[3].tex = { (m_nCntTexPattern + 1) / 8.0f, 1.0f };

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// 回転
	Rotation();

	// 移動
	Translation();

	// アニメーション
	Animation();
}

//****************************************************************************
// 拡縮
//****************************************************************************
void CPlayer::Scaling()
{
	m_size *= 2.0f;
}

//****************************************************************************
// 回転
//****************************************************************************
void CPlayer::Rotation()
{
	m_rot.z += 0.05f;
}

//****************************************************************************
// 移動
//****************************************************************************
void CPlayer::Translation()
{
	m_pos.x += 2.0f;

	if ((m_pos.x - m_fLength) > SCREEN_WIDTH)
	{
		m_pos.x = 0.0f - m_fLength;

		// 拡縮
		Scaling();
	}
}

//****************************************************************************
// アニメーション
//****************************************************************************
void CPlayer::Animation()
{
	// テクスチャ変更管理カウントアップ
	m_nCntTexChange++;

	if (m_nCntTexChange >= 15)
	{
		// テクスチャパターン変更
		m_nCntTexPattern++;

		if (m_nCntTexPattern >= 8)
		{
			// テクスチャパターンをリセっト
			m_nCntTexPattern = 0;
		}

		// 変更管理カウントをリセット
		m_nCntTexChange = 0;
	}
}

//****************************************************************************
// 描画処理
//****************************************************************************
void CPlayer::Draw()
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
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer* pPlayer = new CPlayer;

	// 生成出来ていたら初期設定
	if (pPlayer != nullptr)
	{
		pPlayer->Init();
		pPlayer->m_pos = pos;
		pPlayer->m_size = size;
	}

	return pPlayer;
}