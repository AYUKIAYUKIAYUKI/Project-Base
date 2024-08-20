//============================================================================
// 
// 弾 [bullet.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "bullet.h"
#include "utility.h"

// テクスチャ取得用
#include "texture_manager.h"

// オブジェクト用
#include "player.h"

// デバッグ表示用
#include "renderer.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CBullet::CBullet() :
	CObject_billboard{ static_cast<int>(LAYER::BACK_MIDDLE) },	// プライオリティ指定
	m_posTarget{ 0.0f, 0.0f, 0.0f },							// 目標座標
	m_velocity{ 0.0f, 0.0f, 0.0f },								// 加速度
	m_nDuration{ 0 }											// 寿命
{

}

//============================================================================
// 寿命設定コンストラクタ
//============================================================================
CBullet::CBullet(int nDuration) :
	CObject_billboard{ static_cast<int>(LAYER::BACK_MIDDLE) },	// プライオリティ指定
	m_posTarget{ 0.0f, 0.0f, 0.0f },							// 目標座標
	m_velocity{ 0.0f, 0.0f, 0.0f },								// 加速度
	m_nDuration{ nDuration }									// 寿命
{

}

//============================================================================
// デストラクタ
//============================================================================
CBullet::~CBullet()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CBullet::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_billboard::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBullet::Uninit()
{
	// 基底クラスの終了処理
	CObject_billboard::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBullet::Update()
{
	// 寿命カウントダウン
	m_nDuration--;

	if (m_nDuration <= 0)
	{
		// 破棄予約
		SetRelease();
	}

	// 現在の座標を取得し、変更を加えていく
	m_posTarget = GetPos();

	// 移動
	Translate();

	// 当たり判定
	if (Collision())
	{
		// 破棄予約
		SetRelease();
	}

	// 座標を反映
	SetPos(m_posTarget);

	// 基底クラスの更新
	CObject_billboard::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CBullet::Draw()
{
	// 基底クラスの描画処理
	CObject_billboard::Draw();
}

//============================================================================
// 生成
//============================================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// インスタンスを生成
	CBullet* pBullet = DBG_NEW CBullet{ 60 };

	if (pBullet == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pBullet->SetType(TYPE::BULLET);

	// 基底クラスの初期設定
	pBullet->Init();

	// 位置の設定
	pBullet->SetPos(pos);

	// サイズの設定
	pBullet->SetSize(size);

	// テクスチャを設定
	pBullet->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::BULLET_00));

	// プレイヤーを取得
	CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(CObject::FindObject(TYPE::PLAYER));

	// プレイヤーへのベクトル正規化し、加速度に設定
	D3DXVECTOR3 pV{ (pPlayer->GetPos() - pos) };
	D3DXVec3Normalize(&pBullet->m_velocity, &pV);

	return pBullet;
}

//============================================================================
// 移動
//============================================================================
void CBullet::Translate()
{
	//// 座標を取得
	//D3DXVECTOR3 posTarget = GetPos();

	//// 目標座標に加速度を加算
	//posTarget += m_velocity;

	//// 目標座標を反映
	//SetPos(posTarget);

	m_posTarget += m_velocity;
}

//============================================================================
// 当たり判定
//============================================================================
bool CBullet::Collision()
{
	// 衝突判定
	bool bDetect = false;

	// いろんなタグ

	return bDetect;
}