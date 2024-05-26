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
#include "main.h"
#include "manager.h"
#include "enemy.h"
#include "explosion.h"

//============================================================================
// コンストラクタ
//============================================================================
CBullet::CBullet() : CObject2D::CObject2D()
{
	m_nRemain = 0;		// 使用期間
	m_fFlyAngle = 0;	// 飛ぶ角度
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
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBullet::Uninit()
{
	// 基底クラスの終了処理
 	CObject2D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBullet::Update()
{
	// 移動
	Translation();

	// 当たり判定
	if (CollisionEnemy())
	{
		return;
	}

	// 期間経過
	Progress();

	// 基底クラスの更新
	CObject2D::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CBullet::Draw()
{
	// 基底クラスの描画処理
	CObject2D::Draw();
}

//============================================================================
// 生成
//============================================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nRemain, float fFlyAngle)
{
	CBullet* pBullet = new CBullet;

	// 生成出来ていたら初期設定
	if (pBullet != nullptr)
	{
		pBullet->SetType(TYPE::NONE);	// タイプを設定

		pBullet->Init();		// 基底クラスの初期設定
		pBullet->SetPos(pos);	// 中心位置の設定
		pBullet->SetSize(size);	// サイズの設定

		pBullet->m_nRemain = nRemain;		// 使用期間の設定
		pBullet->m_fFlyAngle = fFlyAngle;	// 飛ぶ角度の設定
	}

	// テクスチャを取得
	LPDIRECT3DTEXTURE9 pTex = CManager::GetTexture()->GetTex(CTexture::TEX_TYPE::BULLET_000);

	// テクスチャを設定
	pBullet->BindTex(pTex);

	return pBullet;
}

//============================================================================
// 移動
//============================================================================
void CBullet::Translation()
{
	// 中心位置情報を取得
	D3DXVECTOR3 pos = CObject2D::GetPos();

	// 設定された角度に飛んでいく
	pos.x += sinf(m_fFlyAngle) * 10.0f;
	pos.y += cosf(m_fFlyAngle) * 10.0f;

	// 中心位置を設定
	CObject2D::SetPos(pos);
}

//============================================================================
// 当たり判定
//============================================================================
bool CBullet::CollisionEnemy()
{
	// オブジェクトの総数を取得
	//int nMaxObj = CObject::GetNumAll();

	for (int nCntObj = 0; nCntObj < 64; nCntObj++)
	{
		// オブジェクト情報を取得
		CObject* pObject = CObject::GetObject(nCntObj);

		if (pObject == nullptr)
		{ // カウントエラー
			continue;
		}

		// 敵との当たり判定を行う
		if (pObject->GetType() == CObject::TYPE::ENEMY)
		{
			// オブジェクトクラスをエネミークラスへダウンキャスト
			CEnemy* pEnemy = (CEnemy*)pObject;

			// 衝突したら
			if (CObject2D::GetPos().x + CObject2D::GetSize().x >= pEnemy->GetPos().x - pEnemy->GetSize().x &&
				CObject2D::GetPos().x - CObject2D::GetSize().x <= pEnemy->GetPos().x + pEnemy->GetSize().x &&
				CObject2D::GetPos().y + CObject2D::GetSize().y >= pEnemy->GetPos().y - pEnemy->GetSize().y &&
				CObject2D::GetPos().y - CObject2D::GetSize().y <= pEnemy->GetPos().y + pEnemy->GetSize().y)
			{
				// 自身を破棄
				CObject::Release();

				// エネミーを破棄
				pObject->Release();

				// 爆発を生成
				CExplosion::Create(
					CObject2D::GetPos(),		// 中心位置
					{ 25.0f, 25.0f, 0.0f });	// サイズ

				return true;
			}
		}
	}

	return false;
}

//============================================================================
// 期間経過
//============================================================================
void CBullet::Progress()
{
	// 使用期間カウントダウン
	m_nRemain--;

	// 使用期間がなくなると消滅
	if (m_nRemain <= 0)
	{
		// 自身を破棄
		CObject::Release();

		// 爆発を生成
		CExplosion::Create(
			CObject2D::GetPos(),		// 中心位置
			{ 25.0f, 25.0f, 0.0f });	// サイズ
	}
}