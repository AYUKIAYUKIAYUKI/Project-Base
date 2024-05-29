//============================================================================
// 
// プレイヤー [player.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "player.h"
#include "manager.h"
#include "bullet.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
const int CPlayer::TEXTURE_DIVIDE_U = 30;	// テクスチャのU方向分割数
const int CPlayer::TEXTURE_DIVIDE_V = 1;	// テクスチャのV方向分割数
const float CPlayer::MAX_VELOCITY = 5.0f;	// 加速度上限
const float CPlayer::JUMP_FORCE = -10.0f;	// ジャンプ力
const float CPlayer::BRAKING_FORCE = 0.9f;	// 制動力
const float CPlayer::GRAVITY_FORCE = 0.25f;	// 重力

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer() : CObject2D(FRONT_MIDDLE)
{
	m_nCntTexChange = 0;	// テクスチャ変更管理
	m_velocity = {};		// 加速度
	m_pos_tgt = {};			// 目標位置
	m_rot_tgt = {};			// 目標向き
}

//============================================================================
// デストラクタ
//============================================================================
CPlayer::~CPlayer()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CPlayer::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CPlayer::Uninit()
{
	// 基底クラスの終了処理
	CObject2D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CPlayer::Update()
{
	// 現在位置を取得、以降このコピーを目標位置として変更を加えていく
	m_pos_tgt = CObject2D::GetPos();

	// 操作
	Control();

	// 制動調整
	Braking();

	// 重力加速
	GravityFall();

	// 当たり判定
	Collision();

	// 位置を調整、この処理の終わりに目標位置を反映させる
	AdjustPos();

	// アニメーション
	Animation();

	// 基底クラスの更新
	CObject2D::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CPlayer::Draw()
{
	// 基底クラスの描画処理
	CObject2D::Draw();
}

//============================================================================
// 生成
//============================================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// プレイヤーを生成
	CPlayer* pPlayer = new CPlayer;

	// 生成出来ていたら初期設定
	if (pPlayer != nullptr)
	{
		pPlayer->SetType(TYPE::PLAYER);	// タイプを設定

		pPlayer->Init();		// 基底クラスの初期設定
		pPlayer->SetPos(pos);	// 中心位置の設定
		pPlayer->SetSize(size);	// サイズの設定

		pPlayer->SetTexWidth(1.0f / (float)TEXTURE_DIVIDE_U);	// 横テクスチャ分割幅
		pPlayer->SetTexHeight(1.0f / (float) TEXTURE_DIVIDE_V);	// 縦テクスチャ分縦幅
	}

	// テクスチャを取得
	LPDIRECT3DTEXTURE9 pTex = CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::PLAYER_000);

	// テクスチャを設定
	pPlayer->BindTex(pTex);

	return pPlayer;
}

//============================================================================
// 操作
//============================================================================
void CPlayer::Control()
{
	// 左スティック取得
	CInputPad* pPad = CManager::GetPad();
	CInputPad::JOYSTICK Stick = pPad->GetJoyStickL();

	// 入力があれば移動
	if (Stick.X != 0 || Stick.Y != 0)
	{
		// 移動量と目標回転量を設定
		m_velocity.x += sinf(atan2f((float)Stick.X, (float)-Stick.Y));
	}

	// キーボード取得
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// 移動方向用
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

	// Y軸
	if (pKeyboard->GetPress(DIK_W))
	{
		Y = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_S))
	{
		Y = 1.0f;
	}

	// X軸
	if (pKeyboard->GetPress(DIK_A))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{
		X = 1.0f;
	}

	// 何か入力していれば移動判定を出す
	if (X != 0.0f || Y != 0.0f)
	{
		bMove = true;
	}

	if (bMove)
	{
		// 移動量と目標回転量を設定
		m_velocity.x += sinf(atan2f(X, Y));
	}

	// ジャンプ
	if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY_X))
	{
		// Y軸方向の加速度を上方向へ固定
		m_velocity.y = JUMP_FORCE;
	}

	// デバッグ用にサウンド再生 (キーボード、パッド取得があるのでここで)
	if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY_B))
	{
		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_00);

		// おまけに弾の生成
		CBullet::Create(
			m_pos_tgt,				// 中心位置
			{ 15.0f, 15.0f, 0.0f },	// サイズ
			100,					// 使用期間
			0.0f);					// 飛ぶ角度
	}
}

////============================================================================
//// 拡縮
////============================================================================
//void CPlayer::Scaling()
//{
//
//}
//
////============================================================================
//// 回転
////============================================================================
//void CPlayer::Rotation()
//{
//	//// 向き情報取得
//	//D3DXVECTOR3 rot = CObject2D::GetRot();
//
//	//// ブレーキ力
//	//float fStopEnergy = 0.1f;
//
//	//// 回転反映と回転量の減衰
//	//if (m_rot_tgt.z - rot.z > D3DX_PI)
//	//{
//	//	rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
//	//}
//	//else if (m_rot_tgt.z - rot.z < -D3DX_PI)
//	//{
//	//	rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
//	//}
//	//else
//	//{
//	//	rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy);
//	//}
//
//	//// 向き情報設定
//	//CObject2D::SetRot(rot);
//}
//
////============================================================================
//// 移動
////============================================================================
//void CPlayer::Translation()
//{
//
//}

//============================================================================
// 制動調整
//============================================================================
void CPlayer::Braking()
{
	if (m_velocity.x > MAX_VELOCITY)
	{
		m_velocity.x = MAX_VELOCITY;
	}
	else if (m_velocity.x < -MAX_VELOCITY)
	{
		m_velocity.x = -MAX_VELOCITY;
	}

	// 少しずつX軸方向への加速度を失う
	m_velocity.x = m_velocity.x * BRAKING_FORCE;
}

//============================================================================
// 重力落下
//============================================================================
void CPlayer::GravityFall()
{
	// 重力分、下方向への加速度増加
	m_velocity.y = m_velocity.y + GRAVITY_FORCE;
}

//============================================================================
// 当たり判定
//============================================================================
void CPlayer::Collision()
{
	
}

//============================================================================
// 位置調整
//============================================================================
void CPlayer::AdjustPos()
{
	// 加速度分位置を変動
	m_pos_tgt += m_velocity;

	// サイズを取得
	D3DXVECTOR3 fSize = CObject2D::GetSize();

	// 画面の左右端に到達でそれぞれループ
	if (m_pos_tgt.x - fSize.x > SCREEN_WIDTH)
	{
		// 左端へ設定
		m_pos_tgt.x = 0.0f - fSize.x;
	}
	else if (m_pos_tgt.x + fSize.x < 0.0f)
	{
		// 右端へ設定
		m_pos_tgt.x = SCREEN_WIDTH + fSize.x;
	}

	// 画面の下端に到達で下降制限
	if (m_pos_tgt.y + fSize.y > SCREEN_HEIGHT)
	{
		// 下端に設定
		m_pos_tgt.y = SCREEN_HEIGHT - fSize.y;

		// Y軸方向の加速度をリセット
		m_velocity.y = 0.0f;
	}

	// 中心位置情報を設定
	CObject2D::SetPos(m_pos_tgt);
}

//============================================================================
// アニメーション
//============================================================================
void CPlayer::Animation()
{
	// テクスチャ変更管理カウントアップ
	m_nCntTexChange++;

	if (m_nCntTexChange >= 15)
	{
		// 横テクスチャ種類情報取得
		int nTexPatternU = CObject2D::GetNowPatternU();

		// 横テクスチャ種類変更
		nTexPatternU++;

		if (nTexPatternU >= TEXTURE_DIVIDE_U)
		{
			// テクスチャパターンをリセット
			nTexPatternU = 0;
		}

		// 横テクスチャ種類情報設定
		CObject2D::SetNowPatternU(nTexPatternU);

		// 変更管理カウントをリセット
		m_nCntTexChange = 0;
	}
}