//============================================================================
// 
// エネミー [enemy.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "enemy.h"
#include "manager.h"
#include "bullet.h"
#include "particle.h"

//============================================================================
// コンストラクタ
//============================================================================
CEnemy::CEnemy() : CObject2D::CObject2D()
{
	m_rot_tgt = { 0.0f, 0.0f, 0.0f };	// 目標向き
}

//============================================================================
// デストラクタ
//============================================================================
CEnemy::~CEnemy()
{
	// パーティクルを生成
	for (int i = 0; i < 10; i++)
	{
		CParticle::Create(CObject2D::GetPos(),	// 中心位置
			CObject2D::GetSize(),				// サイズ
			atan2f((float)(rand() % 314), (float)(rand() % 314)) * (rand() % 314));	// 飛ぶ角度
	}
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CEnemy::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CEnemy::Uninit()
{
	// 基底クラスの終了処理
	CObject2D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CEnemy::Update()
{
	// 回転
	Rotation();

	// 移動
	Translation();

	// 基底クラスの更新
	CObject2D::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CEnemy::Draw()
{
	// 基底クラスの描画処理
	CObject2D::Draw();
}

//============================================================================
// 生成
//============================================================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEnemy* pEnemy = new CEnemy;

	// 生成出来ていたら初期設定
	if (pEnemy != nullptr)
	{
		pEnemy->SetType(TYPE::ENEMY);	// タイプを設定

		pEnemy->Init();			// 基底クラスの初期設定
		pEnemy->SetPos(pos);	// 中心位置の設定
		pEnemy->SetSize(size);	// サイズの設定
	}

	// テクスチャを取得
	LPDIRECT3DTEXTURE9 pTex = CManager::GetTexture()->GetTex(CTexture::TEX_TYPE::ENEMY_000);

	// テクスチャを設定
	pEnemy->BindTex(pTex);

	return pEnemy;
}

//============================================================================
// 回転
//============================================================================
void CEnemy::Rotation()
{
	// 向き情報取得
	D3DXVECTOR3 rot = CObject2D::GetRot();

	// ブレーキ力
	float fStopEnergy = 0.1f;

	// 回転反映と回転量の減衰
	if (m_rot_tgt.z - rot.z > D3DX_PI)
	{
		rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (m_rot_tgt.z - rot.z < -D3DX_PI)
	{
		rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy);
	}

	// 向き情報設定
	CObject2D::SetRot(rot);
}

//============================================================================
// 移動
//============================================================================
void CEnemy::Translation()
{
	// 中心位置情報を取得
	D3DXVECTOR3 pos = CObject2D::GetPos();

	pos.x += 0.5f;
	pos.y += -0.5f;

	// 端へ到達でループ
	if ((pos.x - CObject2D::GetSize().x) > SCREEN_WIDTH)
	{
		pos.x = 0.0f - CObject2D::GetSize().x;
	}
	else if ((pos.x + CObject2D::GetSize().x) < 0.0f)
	{
		pos.x = SCREEN_WIDTH;
	}

	if ((pos.y + CObject2D::GetSize().y) < 0.0f)
	{
		pos.y = SCREEN_HEIGHT + CObject2D::GetSize().y;
	}
	else if ((pos.y - CObject2D::GetSize().y) > SCREEN_HEIGHT)
	{
		pos.y = 0.0f;
	}

	// 中心位置を設定
	CObject2D::SetPos(pos);
}