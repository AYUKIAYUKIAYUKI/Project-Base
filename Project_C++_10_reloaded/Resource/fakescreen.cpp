//============================================================================
// 
// 疑似スクリーン [fakescreen.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "fakescreen.h"
#include "manager.h"

//****************************************************
// マクロ定義
//****************************************************
#define MESH_DBG 0	// メッシュ情報のデバッグ表示切り替え

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CFakeScreen* CFakeScreen::m_pInstance = nullptr;	// 自クラス情報
const int CFakeScreen::SPLIT_ALONG_X_AXIS = 50;		// X軸方向の分割数
const int CFakeScreen::SPLIT_ALONG_Y_AXIS = 50;		// Y軸方向の分割数

//============================================================================
// コンストラクタ
//============================================================================
CFakeScreen::CFakeScreen()
{
	m_pVtxBuff = nullptr;			// 頂点バッファのポインタ
	m_pIdxBuff = nullptr;			// インデックスバッファのポインタ
	m_pTex = nullptr;				// テクスチャ情報のポインタ
	m_pSurface = nullptr;			// サーフェイス情報のポインタ
	m_nNumVtx = 0;					// 頂点数
	m_nNumPolygon = 0;				// ポリゴン数
	m_nNumDegenerated = 0;			// 縮退ポリゴン数
	m_nNumIndex = 0;				// インデックス数
	m_pos = { 0.0f, 0.0f, 0.0f };	// 位置
	m_size = { 0.0f, 0.0f, 0.0f };	// サイズ
}

//============================================================================
// デストラクタ
//============================================================================
CFakeScreen::~CFakeScreen()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CFakeScreen::Init()
{
	// 位置を中心に設定
	m_pos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f };

	// サイズを設定
	float fSize = 0.3f;
	m_size = { SCREEN_WIDTH * fSize, SCREEN_HEIGHT * fSize, 0.0f };

	// メッシュ情報の計算
	CalcMesh();

	// 頂点バッファの生成
	if (FAILED(CreateVtxBuff()))
	{
		return E_FAIL;
	}

	// インデックスバッファの生成
	if (FAILED(CreateIdxBuff()))
	{
		return E_FAIL;
	}

	// テクスチャの生成
	if (FAILED(CreateTex()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CFakeScreen::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// インデックスバッファの破棄
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
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
void CFakeScreen::Update()
{
	// 移動
	//Move();
	 
	// 波打ち
	Wave();

	// 頂点情報の設定
	//SetVtx();
}

//============================================================================
// 描画処理
//============================================================================
void CFakeScreen::Draw()
{
#if 0
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
#else
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// 頂点バッファをデータストリームに設定
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点インデックスをデータストリームに設定
	pDev->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDev->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDev->SetTexture(0, m_pTex);

	// メッシュフィールドの描画
	pDev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_nNumVtx,
		0,
		m_nNumPolygon);
#endif
}

//============================================================================
// 生成
//============================================================================
void CFakeScreen::Create()
{
	if (m_pInstance != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// インスタンスを生成
	m_pInstance = DBG_NEW CFakeScreen;
}

//============================================================================
// 解放
//============================================================================
void CFakeScreen::Release()
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
// テクスチャ情報を取得
//============================================================================
LPDIRECT3DTEXTURE9 CFakeScreen::GetTexture()
{
	return m_pTex;
}

//============================================================================
// サーフェイス情報を取得
//============================================================================
LPDIRECT3DSURFACE9 CFakeScreen::GetSurface()
{
	return m_pSurface;
}

//============================================================================
// 取得
//============================================================================
CFakeScreen* CFakeScreen::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// 生成
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// 頂点バッファの生成
//============================================================================
HRESULT CFakeScreen::CreateVtxBuff()
{
	// 頂点バッファの生成
	CManager::GetRenderer()->GetDeviece()->CreateVertexBuffer(sizeof(VERTEX_2D) * m_nNumVtx,
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

	int nCntVtxX = 0, nCntVtxY = 0;								// 各方向の頂点数をカウントする
	float fEachSizeX = (m_size.x * 2.0f) / SPLIT_ALONG_X_AXIS;	// ポリゴン1枚あたりのX方向への頂点配置間隔
	float fEachSizeY = (m_size.y * 2.0f) / SPLIT_ALONG_Y_AXIS;	// ポリゴン1枚あたりのY方向への頂点配置間隔

	for (int i = 0; i < m_nNumVtx; i++)
	{
		// 頂点座標の設定 (サイズ値をもとにした左上の頂点位置に、変動位置を加算して矩形を形成)
		pVtx[i].pos = {
			m_pos.x - m_size.x + (fEachSizeX * nCntVtxX),
			m_pos.y - m_size.y + (fEachSizeY * nCntVtxY),
			0.0f };

#if MESH_DBG

		// 各頂点座標のデバッグ表示
		CManager::GetRenderer()->SetTimeString(std::to_string(i + 1) + "頂点:" + std::to_string(pVtx[i].pos.x) + ":" + std::to_string(pVtx[i].pos.y) + ":" + std::to_string(pVtx[i].pos.z), 30);

#endif	// MESH_DBG

		// 除算数の設定
		pVtx[i].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定 (分割数関わらずサイズに合わせて均等に設定)
		pVtx[i].tex = {
			(fEachSizeX * nCntVtxX) / (m_size.x * 2.0f),
			(fEachSizeY * nCntVtxY) / (m_size.y * 2.0f) };

#if MESH_DBG

		// 各UV座標のデバッグ表示
		CManager::GetRenderer()->SetTimeString(std::to_string(i + 1) + "UV:" + std::to_string(pVtx[i].tex.x) + " : " + std::to_string(pVtx[i].tex.y), 30);

#endif	// MESH_DBG

		// X方向頂点数のカウントを行う
		if (nCntVtxX >= SPLIT_ALONG_X_AXIS)
		{ // カウント数が分割数に達したら

			// X方向頂点数のカウントをリセット
			nCntVtxX = 0;

			// Y方向頂点数をカウントアップ
			nCntVtxY++;
		}
		else
		{
			// X方向頂点数をカウントアップ
			nCntVtxX++;
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================================================
// インデックス情報の生成
//============================================================================
HRESULT CFakeScreen::CreateIdxBuff()
{
	// インデックスバッファの生成
	CManager::GetRenderer()->GetDeviece()->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	if (m_pIdxBuff == nullptr)
	{ // 生成失敗
		return E_FAIL;
	}

	// インデックス情報へのポインタ
	WORD* pIdx;

	// インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, reinterpret_cast<void**>(&pIdx), 0);

	int columnCnt = 0, rowCnt = 0;	// 動作制御用

	for (int i = 0; i < m_nNumIndex / 2; i++, pIdx += 2)
	{
		int id_vtx[2] = { 0, 0 };	// 頂点番号

		if (columnCnt < SPLIT_ALONG_Y_AXIS + 1)
		{ // 列カウントが実際の列数を超えるまで

			// カウントに応じて、2頂点ごとに番号を振っていく
			id_vtx[0] = (columnCnt + SPLIT_ALONG_Y_AXIS + 1) + rowCnt;
			id_vtx[1] = columnCnt + rowCnt;

			columnCnt++;	// 列カウント増加
		}
		else
		{ // 列カウントが列数を超えると

			// 縮退ポリゴンの分を振り分け
			id_vtx[0] = (columnCnt - 1) + rowCnt;
			id_vtx[1] = (columnCnt + SPLIT_ALONG_Y_AXIS + 1) + rowCnt;

			columnCnt = 0;	// 列カウントリセット

			rowCnt += SPLIT_ALONG_Y_AXIS + 1;	// 行カウント増加
		}

		// インデックスに反映
		pIdx[0] = static_cast<WORD>(id_vtx[0]);
		pIdx[1] = static_cast<WORD>(id_vtx[1]);
	}

	// インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//============================================================================
// テクスチャの生成
//============================================================================
HRESULT CFakeScreen::CreateTex()
{
#if 1
	// テクスチャを作成
	CManager::GetRenderer()->GetDeviece()->CreateTexture(
		SCREEN_WIDTH,			// U
		SCREEN_HEIGHT,			// V
		0,						// ミップマップレベル
		D3DUSAGE_RENDERTARGET,	// テクスチャの性質
		D3DFMT_A8R8G8B8,		// ピクセルフォーマット
		D3DPOOL_DEFAULT,		// メモリ管理フラグ
		&m_pTex,				// テクスチャ保存先
		nullptr);				// ハンドル
#else
	// テクスチャの生成
	D3DXCreateTextureFromFileA(CManager::GetRenderer()->GetDeviece(),
		"Data\\TEXTURE\\AL-1S.png",
		&m_pTex);
#endif

	// テクスチャのサーフェイスを取得
	m_pTex->GetSurfaceLevel(0, &m_pSurface);

	return S_OK;
}

//============================================================================
// メッシュ情報の計算
//============================================================================
void CFakeScreen::CalcMesh()
{
	// 頂点数の算出
	m_nNumVtx = (SPLIT_ALONG_X_AXIS + 1) * (SPLIT_ALONG_Y_AXIS + 1);

	// 頂点数がポリゴン構成の最低数に満たない
	if (m_nNumVtx < 3)
	{
		assert(false);
	}

	// 縮退ポリゴン数の算出
	m_nNumDegenerated = (SPLIT_ALONG_X_AXIS - 1) * 4;

	// ポリゴン数の算出
	m_nNumPolygon = (SPLIT_ALONG_X_AXIS * SPLIT_ALONG_Y_AXIS * 2) + m_nNumDegenerated;

	// インデックス数の算出
	m_nNumIndex = m_nNumPolygon + 2;
}

//============================================================================
// 移動
//============================================================================
void CFakeScreen::Move()
{
	// 移動
	static D3DXVECTOR3 move = { 3.0f, 3.0f, 0.0f };
	m_pos += move;

	// 左右端に到達
	if (m_pos.x + m_size.x >= SCREEN_WIDTH || m_pos.x - m_size.x <= 0.0f)
	{
		move.x *= -1.0f;
	}

	// 上下端に到達
	if (m_pos.y + m_size.y >= SCREEN_HEIGHT || m_pos.y - m_size.y <= 0.0f)
	{
		move.y *= -1.0f;
	}
}

//============================================================================
// 波打ち
//============================================================================
void CFakeScreen::Wave()
{
	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	float fWavePosX = 0.0f;		// ゆがみ具合
	int nCntAdd = 0;
	static float fAdd = 0.00f;	// ゆがみ増加量
	static float fHoge = 50.0f;	// ゆがみ強度
	if (CManager::GetKeyboard()->GetPress(DIK_R))
	{
		fAdd += 0.01f;
	}
	else if	(CManager::GetKeyboard()->GetPress(DIK_F))
	{
		fAdd += -0.01f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_V))
	{
		fAdd = 0.0f;
	}
	CManager::GetRenderer()->SetDebugString("ゆがみ具合:" + std::to_string(fAdd));

	int nCntVtxX = 0, nCntVtxY = 0;								// 各方向の頂点数をカウントする
	float fEachSizeX = (m_size.x * 2.0f) / SPLIT_ALONG_X_AXIS;	// ポリゴン1枚あたりのX方向への頂点配置間隔
	float fEachSizeY = (m_size.y * 2.0f) / SPLIT_ALONG_Y_AXIS;	// ポリゴン1枚あたりのY方向への頂点配置間隔

	for (int i = 0; i < m_nNumVtx; i++)
	{
		// 頂点座標の設定 (サイズ値をもとにした左上の頂点位置に、変動位置を加算して矩形を形成)
		pVtx[i].pos = {
			m_pos.x - m_size.x + (fEachSizeX * nCntVtxX) + (sinf(fWavePosX) * fHoge),
			m_pos.y - m_size.y + (fEachSizeY * nCntVtxY),
			0.0f };

		// X方向頂点数のカウントを行う
		if (nCntVtxX >= SPLIT_ALONG_X_AXIS)
		{ // カウント数が分割数に達したら

			// X方向頂点数のカウントをリセット
			nCntVtxX = 0;

			// Y方向頂点数をカウントアップ
			nCntVtxY++;

			// ゆがみを増加
			fWavePosX += fAdd;
		}
		else
		{
			// X方向頂点数をカウントアップ
			nCntVtxX++;
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================================================================
// 頂点情報の設定
//============================================================================
void CFakeScreen::SetVtx()
{
	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	int nCntVtxX = 0, nCntVtxY = 0;								// 各方向の頂点数をカウントする
	float fEachSizeX = (m_size.x * 2.0f) / SPLIT_ALONG_X_AXIS;	// ポリゴン1枚あたりのX方向への頂点配置間隔
	float fEachSizeY = (m_size.y * 2.0f) / SPLIT_ALONG_Y_AXIS;	// ポリゴン1枚あたりのY方向への頂点配置間隔

	for (int i = 0; i < m_nNumVtx; i++)
	{
		// 頂点座標の設定 (サイズ値をもとにした左上の頂点位置に、変動位置を加算して矩形を形成)
		pVtx[i].pos = {
			m_pos.x - m_size.x + (fEachSizeX * nCntVtxX),
			m_pos.y - m_size.y + (fEachSizeY * nCntVtxY),
			0.0f };

		// X方向頂点数のカウントを行う
		if (nCntVtxX >= SPLIT_ALONG_X_AXIS)
		{ // カウント数が分割数に達したら

			// X方向頂点数のカウントをリセット
			nCntVtxX = 0;

			// Y方向頂点数をカウントアップ
			nCntVtxY++;
		}
		else
		{
			// X方向頂点数をカウントアップ
			nCntVtxX++;
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}