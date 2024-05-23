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
#include "main.h"
#include "manager.h"
#include "bullet.h"

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer() : CObject2D::CObject2D()
{
	m_nCntTexChange = 0;			// テクスチャ変更管理
	m_nCntTexPattern = 0;			// テクスチャパターン管理
	m_pos = { 0.0f, 0.0f, 0.0f };	// 中心位置
	m_rot = { 0.0f, 0.0f, 0.0f };	// 回転量
	m_fAngle = 0.0f;				// 角度
	m_size = { 0.0f, 0.0f, 0.0f };	// サイズ
	m_fLength = 0.0f;				// 対角線
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
	// 必要な数値を算出
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.y);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファを取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置の設定
	pVtx[0].pos = {
		m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength,
		m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	};

	pVtx[1].pos = {
		m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	};

	pVtx[2].pos = {
		m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength,
		m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength,
		0.0f
	};

	pVtx[3].pos = {
		m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength,
		m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength,
		0.0f
	};

	// テクスチャの設定
	pVtx[0].tex = { m_nCntTexPattern / 8.0f, 0.0f };
	pVtx[1].tex = { (m_nCntTexPattern + 1) / 8.0f, 0.0f };
	pVtx[2].tex = { m_nCntTexPattern / 8.0f, 1.0f };
	pVtx[3].tex = { (m_nCntTexPattern + 1) / 8.0f, 1.0f };

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();

	// 拡縮
	Scaling();

	// 回転
	Rotation();

	// 移動
	Translation();

	// アニメーション
	Animation();
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
	CPlayer* pPlayer = new CPlayer;

	// 生成出来ていたら初期設定
	if (pPlayer != nullptr)
	{
		pPlayer->Init();
		pPlayer->m_pos = pos;
		pPlayer->m_size = size;
	}

	// デバイスを取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();

	// テクスチャのポインタ
	LPDIRECT3DTEXTURE9 pTex = nullptr;

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDev,
		"data\\TEXTURE\\runningman000.png",
		&pTex);

	// テクスチャを設定
	pPlayer->BindTex(pTex);

	return pPlayer;
}

//============================================================================
// 拡縮
//============================================================================
void CPlayer::Scaling()
{
	if ((m_pos.x - m_fLength) > SCREEN_WIDTH)
	{ // 画面の右端に到達で拡大しループ
		m_pos.x = 0.0f - m_fLength;
		m_size *= 3.0f;
	}
	else if ((m_pos.x + m_fLength) < 0.0f)
	{ // 画面の右端に到達で縮小しループ
		m_pos.x = SCREEN_WIDTH;
		m_size /= 3.0f;
	}
}

//============================================================================
// 回転
//============================================================================
void CPlayer::Rotation()
{
	// ブレーキ力
	float fStopEnergy = 0.1f;

	// 回転反映と回転量の減衰
	if (m_rot_tgt.z - m_rot.z > D3DX_PI)
	{
		m_rot.z += ((m_rot_tgt.z - m_rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (m_rot_tgt.z - m_rot.z < -D3DX_PI)
	{
		m_rot.z += ((m_rot_tgt.z - m_rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		m_rot.z += ((m_rot_tgt.z - m_rot.z) * fStopEnergy);
	}
}

//============================================================================
// 移動
//============================================================================
void CPlayer::Translation()
{
	// 左スティック取得
	CInputPad* pPad = CManager::GetPad();
	CInputPad::JOYSTICK Stick = pPad->GetJoyStickL();

	// 入力があれば移動
	if (Stick.X != 0 || Stick.Y != 0)
	{
		// 移動量と目標回転量を設定
		m_pos.x += sinf(atan2f(Stick.X, -Stick.Y)) * 5.0f;
		m_pos.y += cosf(atan2f(Stick.X, -Stick.Y)) * 5.0f;
		m_rot_tgt.z = atan2f(Stick.X, -Stick.Y);
	}

	// デバッグ用にサウンド再生 (パッド取得があるのでここで)
	if (pPad->GetTrigger(CInputPad::JOYKEY_B))
	{
		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_00);
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
		m_pos.x += sinf(atan2f(X, Y)) * 5.0f;
		m_pos.y += cosf(atan2f(X, Y)) * 5.0f;
		m_rot_tgt.z = atan2f(-X, -Y);
	}

	// 弾を発射 (キーボード取得があるのでここで)
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		// 弾の生成
		CBullet::Create(
			m_pos,					// 中心位置
			{ 30.0f, 30.0f, 0.0f },	// サイズ
			50);					// 使用期間
	}

	// デバッグ用にサウンド再生 (キーボード取得があるのでここで)
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_00);
	}
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
		// テクスチャパターン変更
		m_nCntTexPattern++;

		if (m_nCntTexPattern >= 8)
		{
			// テクスチャパターンをリセっト
			m_nCntTexPattern = 0;
		}

		// 変更管理カウントをリセット
		m_nCntTexChange = 0;
	}
}