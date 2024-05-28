//============================================================================
// 
// エフェクト [effect.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "effect.h"
#include "manager.h"

//============================================================================
// コンストラクタ
//============================================================================
CEffect::CEffect() : CObject2D(LAYER::BACK_MIDDLE)
{

}

//============================================================================
// デストラクタ
//============================================================================
CEffect::~CEffect()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CEffect::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CEffect::Uninit()
{
	// 基底クラスの終了処理
	CObject2D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CEffect::Update()
{
	// 期間経過
	Progress();

	// 基底クラスの更新
	CObject2D::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CEffect::Draw()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// アルファブレンディングを加算合成に設定
	pDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 基底クラスの描画処理
	CObject2D::Draw();

	// アルファブレンディングをの設定を戻す
	pDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//============================================================================
// 生成
//============================================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEffect* pEffect = new CEffect;

	// 生成出来ていたら初期設定
	if (pEffect != nullptr)
	{
		pEffect->SetType(TYPE::NONE);	// タイプを設定

		pEffect->Init();		// 基底クラスの初期設定
		pEffect->SetPos(pos);	// 中心位置の設定
		pEffect->SetSize(size);	// サイズの設定
	}

	// テクスチャを取得
	LPDIRECT3DTEXTURE9 pTex = CManager::GetTexture()->GetTex(CTexture::TEX_TYPE::EFFECT_000);

	// テクスチャを設定
	pEffect->BindTex(pTex);

	return pEffect;
}

//============================================================================
// 期間経過
//============================================================================
void CEffect::Progress()
{
	// サイズ情報を取得
	D3DXVECTOR3 size = CObject2D::GetSize();

	// 縮小
	size.x += size.x * -0.05f;
	size.y += size.y * -0.05f;

	// 見えなくなったタイミングで消滅
	if (size.x <= 0.25f)
	{
		CObject::Release();	// 自身を破棄
	}

	// サイズ情報を設定
	CObject2D::SetSize(size);
}