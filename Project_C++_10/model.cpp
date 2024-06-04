//============================================================================
// 
// モデル管理 [model.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "model.h"
#include "manager.h"

// ファイル読み取り用
#include <fstream>
#include <string>

//****************************************************
// 静的メンバの初期化
//****************************************************
MODEL CModel::m_aModelTemp[static_cast<int>(MODEL_TYPE::MAX)];	// モデル管理

//============================================================================
// コンストラクタ
//============================================================================
CModel::CModel()
{
	for (int i = 0; i < static_cast<int>(MODEL_TYPE::MAX); i++)
	{
		// モデル情報の初期化
		m_aModelTemp[i].pMesh = nullptr;
		m_aModelTemp[i].pBuffMat = nullptr;
		m_aModelTemp[i].dwNumMat = 0;
		m_aModelTemp[i].pTex = nullptr;
	}
}

//============================================================================
// デストラクタ
//============================================================================
CModel::~CModel()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CModel::Load()
{
	// モデル名管理ファイルを展開
	std::ifstream file("data\\TXT\\model_path.txt");

	if (!file)
	{ // 展開に失敗
		assert(false);
	}

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	for (int i = 0; i < static_cast<int>(MODEL_TYPE::MAX); i++)
	{
		// モデル名格納先
		std::string filename;

		// モデル名を取得する
		std::getline(file, filename);

		// モデルファイルの取得
		D3DXLoadMeshFromX(filename.c_str(),
			D3DXMESH_SYSTEMMEM,
			pDev,
			nullptr,
			&m_aModelTemp[i].pBuffMat,
			nullptr,
			&m_aModelTemp[i].dwNumMat,
			&m_aModelTemp[i].pMesh);

		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_aModelTemp[i].pBuffMat->GetBufferPointer();

		// マテリアル分テクスチャの有無を確認
		for (int nCntMat = 0; nCntMat < static_cast<int>(m_aModelTemp[i].dwNumMat); nCntMat++)
		{
			// テクスチャを読み取れたら生成
			if (pMat[nCntMat].pTextureFilename != nullptr)
			{
				D3DXCreateTextureFromFileA(pDev,
					pMat[nCntMat].pTextureFilename,
					&m_aModelTemp[i].pTex);
			}
			else
			{  
				m_aModelTemp[i].pTex = nullptr;
			}
		}

		if (&m_aModelTemp[i].pMesh == nullptr)
		{ // モデルファイル取得失敗
			file.close();	// ファイルを閉じる
			assert(false);
		}
	}

	file.close();	// ファイルを閉じる

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CModel::Unload()
{
	for (int i = 0; i < static_cast<int>(MODEL_TYPE::MAX); i++)
	{
		// テクスチャの破棄
		if (m_aModelTemp[i].pTex != nullptr)
		{
			m_aModelTemp[i].pTex->Release();
			m_aModelTemp[i].pTex = nullptr;
		}

		// メッシュの破棄
		if (m_aModelTemp[i].pMesh != nullptr)
		{
			m_aModelTemp[i].pMesh->Release();
			m_aModelTemp[i].pMesh = nullptr;
		}

		// マテリアルの破棄
		if (m_aModelTemp[i].pBuffMat != nullptr)
		{
			m_aModelTemp[i].pBuffMat->Release();
			m_aModelTemp[i].pBuffMat = nullptr;
		}
	}
}

//============================================================================
// モデルを取得
//============================================================================
MODEL* CModel::GetModel(MODEL_TYPE type)
{
	if (&m_aModelTemp[static_cast<int>(type)].pMesh == nullptr)
	{ // モデル取得不能
		assert(false);
	}

	return &m_aModelTemp[static_cast<int>(type)];
}