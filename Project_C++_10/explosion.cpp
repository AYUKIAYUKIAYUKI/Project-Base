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
#include "manager.h"
#include "bullet.h"

//============================================================================
// コンストラクタ
//============================================================================
CExplosion::CExplosion() : CObject2D(LAYER::BACK_MIDDLE)
{
	m_nCntTexChange = 0;	// テクスチャ変更管理
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
	// アニメーション
	Animation();

	// 基底クラスの更新
	CObject2D::Update();
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
	// 爆発を生成
	CExplosion* pExplosion = new CExplosion;

	// 生成出来ていたら初期設定
	if (pExplosion != nullptr)
	{
		pExplosion->SetType(TYPE::NONE);	// タイプを設定

		pExplosion->Init();			// 基底クラスの初期設定
		pExplosion->SetPos(pos);	// 中心位置の設定
		pExplosion->SetSize(size);	// サイズの設定

		pExplosion->SetTexWidth(1.0f / 8.0f);	// 横テクスチャ分割幅
		pExplosion->SetTexHeight(1.0f);			// 縦テクスチャ分縦幅
	}

	// テクスチャを取得
	LPDIRECT3DTEXTURE9 pTex = CManager::GetTexture()->GetTex(CTexture::TEX_TYPE::EXPLOSION_000);

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

	if (m_nCntTexChange >= 10)
	{
		// 横テクスチャ種類情報取得
		int nTexPatternU = CObject2D::GetNowPatternU();

		// 横テクスチャ種類変更
		nTexPatternU++;

		if (nTexPatternU >= 8)
		{
			// 自身を破棄
			CObject::Release();
		}

		// 横テクスチャ種類情報設定
		CObject2D::SetNowPatternU(nTexPatternU);

		// 変更管理カウントをリセット
		m_nCntTexChange = 0;
	}
}