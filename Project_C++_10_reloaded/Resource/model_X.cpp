//============================================================================
// 
// Xモデル管理 [model_X.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "model_X.h"
#include "manager.h"

//****************************************************
// 静的メンバの初期化
//****************************************************
CModel_X::MODEL CModel_X::m_apModelTemp[static_cast<int>(MODEL_TYPE::MAX)];	// モデル管理

//============================================================================
// コンストラクタ
//============================================================================
CModel_X::CModel_X()
{
	for (int i = 0; i < static_cast<int>(MODEL_TYPE::MAX); i++)
	{
		// モデル情報の初期化
		m_apModelTemp[i].pMesh = nullptr;
		m_apModelTemp[i].pBuffMat = nullptr;
		m_apModelTemp[i].dwNumMat = 0;
		m_apModelTemp[i].ppTex = nullptr;
	}
}

//============================================================================
// デストラクタ
//============================================================================
CModel_X::~CModel_X()
{

}

//============================================================================
// モデル読み込み
//============================================================================
HRESULT CModel_X::Load()
{
	// モデル名管理ファイルを展開
	std::ifstream file("data\\TXT\\model_path.txt");

	if (!file)
	{ // 展開に失敗
		assert(false);
	}

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	for (int nCntModel = 0; nCntModel < static_cast<int>(MODEL_TYPE::MAX); nCntModel++)
	{
		// モデル名格納先
		std::string filename;

		// モデル名を取得する
		std::getline(file, filename);

		// モデルファイルの取得
		HRESULT hr = D3DXLoadMeshFromX(filename.c_str(),
			D3DXMESH_SYSTEMMEM,
			pDev,
			nullptr,
			&m_apModelTemp[nCntModel].pBuffMat,
			nullptr,
			&m_apModelTemp[nCntModel].dwNumMat,
			&m_apModelTemp[nCntModel].pMesh);

		if (FAILED(hr))
		{ // 取得失敗
			file.close();	// ファイルを閉じる
			assert(false);
		}

		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_apModelTemp[nCntModel].pBuffMat->GetBufferPointer();

		// マテリアルの数分のテクスチャポインタを確保
		m_apModelTemp[nCntModel].ppTex = DBG_NEW LPDIRECT3DTEXTURE9 [static_cast<int>(m_apModelTemp[nCntModel].dwNumMat)];

		// マテリアル分テクスチャの有無を確認
		for (int nCntMat = 0; nCntMat < static_cast<int>(m_apModelTemp[nCntModel].dwNumMat); nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != nullptr)
			{
				// テクスチャを読み取れたら生成
				hr = D3DXCreateTextureFromFileA(pDev,
					pMat[nCntMat].pTextureFilename,
					&m_apModelTemp[nCntModel].ppTex[nCntMat]);

				if (FAILED(hr))
				{ // 生成失敗
					assert(false);
				}
			}
			else
			{
				// 読み取れなければ初期化
				m_apModelTemp[nCntModel].ppTex[nCntMat] = nullptr;
			}
		}
	}

	file.close();	// ファイルを閉じる

	return S_OK;
}

//============================================================================
// モデル破棄
//============================================================================
void CModel_X::Unload()
{
	for (int i = 0; i < static_cast<int>(MODEL_TYPE::MAX); i++)
	{
		// テクスチャポインタの破棄
		if (m_apModelTemp[i].ppTex != nullptr)
		{
			// テクスチャの破棄
			for (int nCntMat = 0; nCntMat < static_cast<int>(m_apModelTemp[i].dwNumMat); nCntMat++)
			{
				if (m_apModelTemp[i].ppTex[nCntMat] != nullptr)
				{
					m_apModelTemp[i].ppTex[nCntMat]->Release();
					m_apModelTemp[i].ppTex[nCntMat] = nullptr;
				}
			}

			delete[] m_apModelTemp[i].ppTex;
			m_apModelTemp[i].ppTex = nullptr;
		}

		// メッシュの破棄
		if (m_apModelTemp[i].pMesh != nullptr)
		{
			m_apModelTemp[i].pMesh->Release();
			m_apModelTemp[i].pMesh = nullptr;
		}

		// マテリアルの破棄
		if (m_apModelTemp[i].pBuffMat != nullptr)
		{
			m_apModelTemp[i].pBuffMat->Release();
			m_apModelTemp[i].pBuffMat = nullptr;
		}
	}
}

//============================================================================
// モデルを取得
//============================================================================
CModel_X::MODEL* CModel_X::GetModel(MODEL_TYPE type)
{
	if (&m_apModelTemp[static_cast<int>(type)].pMesh == nullptr)
	{ // モデル取得不能
		assert(false);
	}

	return &m_apModelTemp[static_cast<int>(type)];
}