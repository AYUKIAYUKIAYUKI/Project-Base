//============================================================================
// 
// テクスチャ管理 [texture.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "texture.h"
#include "manager.h"

//****************************************************
// 静的メンバの初期化
//****************************************************
LPDIRECT3DTEXTURE9 CTexture::m_apTexTemp[TEX_TYPE::MAX];	// テクスチャ管理

//============================================================================
// コンストラクタ
//============================================================================
CTexture::CTexture()
{
	for (int i = 0; i < TEX_TYPE::MAX; i++)
	{
		m_apTexTemp[i] = nullptr;	// テクスチャ情報の初期化
	}
}

//============================================================================
// デストラクタ
//============================================================================
CTexture::~CTexture()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CTexture::Load()
{
	// ファイルポインタ
	FILE* pF = nullptr;

	// ファイルを読み取りで展開
	if (fopen_s(&pF, "data\\TXT\\texture_path.txt", "r") != 0)
	{ // ファイル展開失敗
		assert(false);
	}

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	for (int i = 0; i < TEX_TYPE::MAX; i++)
	{
		// ファイル名格納
		char aFilename[64] = {};

		// ファイル名読み取り
		fscanf_s(pF, "%s", &aFilename[0], sizeof(aFilename));

		// テクスチャの生成
		D3DXCreateTextureFromFile(pDev,
			&aFilename[0],
			&m_apTexTemp[i]);

		if (m_apTexTemp[i] == nullptr)
		{ // テクスチャ生成失敗
			fclose(pF);	// ファイルを閉じる
			assert(false);
		}
	}

	fclose(pF);	// ファイルを閉じる

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CTexture::Unload()
{
	for (int i = 0; i < TEX_TYPE::MAX; i++)
	{
		// テクスチャの破棄
		if (m_apTexTemp[i] != nullptr)
		{
			m_apTexTemp[i]->Release();
			m_apTexTemp[i] = nullptr;
		}
	}
}

//============================================================================
// テクスチャを取得
//============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEX_TYPE type)
{
	if (m_apTexTemp[type] == nullptr)
	{ // テクスチャ取得不能
		assert(false);
	}

	return m_apTexTemp[type];
}