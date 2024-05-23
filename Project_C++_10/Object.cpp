//============================================================================
// 
// オブジェクト管理 [object.cpp]
// Author : 福田歩希
// 
//============================================================================

// インクルードファイル
#include "object.h"
#include "main.h"

// 静的メンバの初期化
CObject* CObject::m_apObject[MAX_OBJ] = {};	// オブジェクト管理
int CObject::m_nNumAll = 0;					// オブジェクト総数

//****************************************************************************
// コンストラクタ
//****************************************************************************
CObject::CObject() : m_nID(0)
{
	int nCnt = 0;

	for (nCnt = 0; nCnt < MAX_OBJ; nCnt++)
	{
		if (m_apObject[nCnt] == nullptr)
		{
			m_apObject[nCnt] = this;	// 自分自身のポインタを代入
			m_nID = nCnt;				// 自分自身のIDを代入
			m_nNumAll++;				// 総数をカウントアップ
			break;
		}
	}
}

//****************************************************************************
// デストラクタ
//****************************************************************************
CObject::~CObject()
{

}

//****************************************************************************
// 初期設定
//****************************************************************************
HRESULT CObject::Init()
{
	return S_OK;
}

//****************************************************************************
// 終了処理
//****************************************************************************
void CObject::Uninit()
{

}

//****************************************************************************
// 更新処理
//****************************************************************************
void CObject::Update()
{

}

//****************************************************************************
// 描画処理
//****************************************************************************
void CObject::Draw()
{

}

//****************************************************************************
// 全解放処理
//****************************************************************************
void CObject::ReleaseAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJ; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			m_apObject[nCnt]->Release();	// 解放処理
		}
	}
}

//****************************************************************************
// 全更新処理
//****************************************************************************
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJ; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			m_apObject[nCnt]->Update();	// 更新処理
		}
	}
}

//****************************************************************************
// 全描画処理
//****************************************************************************
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJ; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			m_apObject[nCnt]->Draw();	// 描画処理
		}
	}
}

//****************************************************************************
// 解放処理
//****************************************************************************
void CObject::Release()
{
	int nID = m_nID;	// 自分自身のIDをコピーしておく

	if (m_apObject[nID] != nullptr)
	{
		m_apObject[nID]->Uninit();	// 終了処理
		delete m_apObject[nID];		// メモリを解放
		m_apObject[nID] = nullptr;	// ポインタを初期化
		m_nNumAll--;				// 総数をカウントダウン
	}
}