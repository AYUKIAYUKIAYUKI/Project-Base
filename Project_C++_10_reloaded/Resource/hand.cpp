//=============================================================================
//
// 手とか [hand.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "hand.h"
#include "utility.h"

// デバッグ表示用
#include "renderer.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CHand::CHand() :
	CObject_3D{ static_cast<int>(LAYER::BG) },
	m_TexType{ CTexture_Manager::TYPE::CROWN },
	m_bAppear{ false },
	m_bDisappear{ false },
	m_posTarget{ 0.0f, 0.0f, 0.0f },
	m_rotTarget{ 0.0f, 0.0f, 0.0f },
	m_sizeTarget{ 0.0f, 0.0f, 0.0f },
	m_colTarget{ 0.0f, 0.0f, 0.0f, 0.0f }
{

}

//============================================================================
// デストラクタ
//============================================================================
CHand::~CHand()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CHand::Init()
{
	if (m_TexType == CTexture_Manager::TYPE::LHAND)
	{
		// 座標設定
		SetPos({ -3.0f + -50.0f, -10.0f + -50.0f, -10.0f, });
		SetPosTarget({ -3.0f, -10.0f, -10.0f, });

		// サイズ設定
		SetSize({ 10.0f, 10.0f, 0.0f, });
		SetSizeTarget({ 10.0f, 10.0f, 0.0f, });
	}
	else if (m_TexType == CTexture_Manager::TYPE::RHAND)
	{
		// 座標設定
		SetPos({ -3.0f + 50.0f, -10.0f + -50.0f, -10.0f, });
		SetPosTarget({ -3.0f, -10.0f, -10.0f, });

		// サイズ設定
		SetSize({ 10.0f, 10.0f, 0.0f, });
		SetSizeTarget({ 10.0f, 10.0f, 0.0f, });
	}

	// 基底クラスの初期設定
	HRESULT hr = CObject_3D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CHand::Uninit()
{
	// 基底クラスの終了処理
	CObject_3D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CHand::Update()
{
	// 出現
	Appear();

	// 消滅
	Disappear();

	// 目標座標へ
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), m_posTarget, 0.1f));

	// 目標向きへ
	SetRot(CUtility::GetInstance()->AdjustToTarget(GetRot(), m_rotTarget, 0.1f));

	// 目標サイズへ
	SetSize(CUtility::GetInstance()->AdjustToTarget(GetSize(), m_sizeTarget, 0.1f));

#ifdef _DEBUG

	// 向きを表示
	CRenderer::GetInstance()->SetDebugString(std::to_string(GetRot().z));

#endif // _DEBUG

	// 基底クラスの更新
	CObject_3D::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CHand::Draw()
{
	auto pDev{ CRenderer::GetInstance()->GetDeviece() };

	//// 深度テストの比較方法の変更
	//pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//// 深度バッファに描画しない
	//pDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ライト反映を無効にする
	pDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 基底クラスの描画処理
	CObject_3D::Draw();

	// ライト反映を有効にする
	pDev->SetRenderState(D3DRS_LIGHTING, TRUE);

	//// 深度テストの比較方法の変更
	//pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//// 深度バッファに書き込む
	//pDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//============================================================================
// 出現設定
//============================================================================
void CHand::SetAppear()
{
	m_bAppear = true;
}

//============================================================================
// 消滅設定
//============================================================================
void CHand::SetDisappear()
{
	m_bDisappear = true;
}

//============================================================================
// 目標座標取得
//============================================================================
D3DXVECTOR3 CHand::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// 目標座標設定
//============================================================================
void CHand::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// 目標向き取得
//============================================================================
D3DXVECTOR3 CHand::GetRotTarget()
{
	return m_rotTarget;
}

//============================================================================
// 目標向き設定
//============================================================================
void CHand::SetRotTarget(D3DXVECTOR3 rotTarget)
{
	m_rotTarget = rotTarget;
}

//============================================================================
// 目標サイズ取得
//============================================================================
D3DXVECTOR3 CHand::GetSizeTarget()
{
	return m_sizeTarget;
}

//============================================================================
// 目標サイズ設定
//============================================================================
void CHand::SetSizeTarget(D3DXVECTOR3 sizeTarget)
{
	m_sizeTarget = sizeTarget;
}

//============================================================================
// 生成
//============================================================================
CHand* CHand::Create(CTexture_Manager::TYPE TexType)
{
	// インスタンスを生成
	CHand* pHand = DBG_NEW CHand{};

	if (pHand == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// テクスチャタイプを保持
	pHand->m_TexType = TexType;

	// タイプを設定
	pHand->SetType(TYPE::NONE);

	// 基底クラスの初期設定
	pHand->Init();

	// テクスチャを設定
	pHand->BindTex(CTexture_Manager::GetInstance()->GetTexture(TexType));

	// アルファ値を設定
	pHand->SetAlpha(0.0f);

	// 出現設定
	pHand->SetAppear();
	
	return pHand;
}

//============================================================================
// 出現
//============================================================================
void CHand::Appear()
{
	if (!m_bAppear)
	{
		return;
	}

	// アルファ値を取得
	float& fAlpha{ GetAlpha() };

	// 徐々に登場
	fAlpha += 0.05f;

	// 最大値に到達で固定
	if (fAlpha > 1.0f)
	{
		fAlpha = 1.0f;

		// 出現終了
		m_bAppear = false;
	}
}

//============================================================================
// 消滅
//============================================================================
void CHand::Disappear()
{
	if (!m_bDisappear)
	{
		return;
	}

	// アルファ値を取得
	float& fAlpha{ GetAlpha() };

	// 徐々に消滅
	fAlpha += -0.1f;

	// 最低値に到達で固定
	if (fAlpha < 0.0f)
	{
		fAlpha = 0.0f;

		// 出現終了
		m_bDisappear = false;

		// 破棄予約
		SetRelease();
	}
}