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

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer() : CObject2D(FRONT_MIDDLE)
{
	m_nCntTexChange = 0;				// テクスチャ変更管理
	m_rot_tgt = { 0.0f, 0.0f, 0.0f };	// 目標向き
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
	// 拡縮
	Scaling();

	// 回転
	Rotation();

	// 移動
	Translation();

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

		pPlayer->SetTexWidth(1.0f / 8.0f);	// 横テクスチャ分割幅
		pPlayer->SetTexHeight(1.0f);		// 縦テクスチャ分縦幅
	}

	// テクスチャを取得
	LPDIRECT3DTEXTURE9 pTex = CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::PLAYER_000);

	// テクスチャを設定
	pPlayer->BindTex(pTex);

	return pPlayer;
}

//============================================================================
// 拡縮
//============================================================================
void CPlayer::Scaling()
{
	// 必要な情報を取得
	D3DXVECTOR3 pos = CObject2D::GetPos();		// 中心位置情報
	D3DXVECTOR3 size = CObject2D::GetSize();	// サイズ情報
	float fLength = CObject2D::GetLength();		// 展開用対角線情報

	if ((pos.x - fLength) > SCREEN_WIDTH)
	{ // 画面の右端に到達で拡大しループ
		pos.x = 0.0f - fLength;
		size *= 3.0f;
	}
	else if ((pos.x + fLength) < 0.0f)
	{ // 画面の右端に到達で縮小しループ
		pos.x = SCREEN_WIDTH;
		size /= 3.0f;
	}

	// 必要な情報を設定
	CObject2D::SetPos(pos);		// 中心位置を設定
	CObject2D::SetSize(size);	// サイズを設定
}

//============================================================================
// 回転
//============================================================================
void CPlayer::Rotation()
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
void CPlayer::Translation()
{
	// 中心位置情報を取得
	D3DXVECTOR3 pos = CObject2D::GetPos();

	// 左スティック取得
	CInputPad* pPad = CManager::GetPad();
	CInputPad::JOYSTICK Stick = pPad->GetJoyStickL();

	// 入力があれば移動
	if (Stick.X != 0 || Stick.Y != 0)
	{
		// 移動量と目標回転量を設定
		pos.x += sinf(atan2f(Stick.X, -Stick.Y)) * 5.0f;
		pos.y += cosf(atan2f(Stick.X, -Stick.Y)) * 5.0f;
		m_rot_tgt.z = atan2f(Stick.X, -Stick.Y);
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
		pos.x += sinf(atan2f(X, Y)) * 5.0f;
		pos.y += cosf(atan2f(X, Y)) * 5.0f;
		m_rot_tgt.z = atan2f(X, Y);
	}

	// 弾を発射 (キーボード、パッド取得があるのでここで)
	if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY_X))
	{
		// 弾の生成
		CBullet::Create(
			pos,					// 中心位置
			{ 15.0f, 15.0f, 0.0f },	// サイズ
			100,					// 使用期間
			CObject2D::GetRot().z);	// 飛ぶ角度
	}

	// デバッグ用にサウンド再生 (キーボード、パッド取得があるのでここで)
	if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY_B))
	{
		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_00);
	}

	// 中心位置を設定
	CObject2D::SetPos(pos);
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

		if (nTexPatternU >= 8)
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