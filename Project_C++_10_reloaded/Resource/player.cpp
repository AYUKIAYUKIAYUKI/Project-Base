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
#include "block.h"
#include "explosion.h"
#include "explosion3D.h"
#include "particle.h"

// テスト
#include "physics.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
const float CPlayer::MAX_VELOCITY = 0.5f;	// 加速度上限
const float CPlayer::JUMP_FORCE = 6.0f;		// ジャンプ力
const float CPlayer::BRAKING_FORCE = 0.9f;	// 制動力

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer() : CObject_X(static_cast<int>(LAYER::FRONT_MIDDLE))
{
	m_state = STATE::NONE;					// 状態
	m_bMetamorphose = 0;					// 変身判定
	m_nCntMetamorphose = 0;					// 変身期間
	m_velocity = { 0.0f, 0.0f, 0.0f };		// 加速度
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// 目標位置
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// 目標向き
	m_fAngleFlying = 0.0f;					// 飛行向き

	m_nTestExplosionCnt = 0;	// これはテスト用です
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
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CPlayer::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CPlayer::Update()
{
	// 現在位置を取得、以降このコピーを目標位置として変更を加えていく
	m_posTarget = CObject_X::GetPos();
	
	if (!m_bMetamorphose)
	{
		// 歩行
		Walking();

		// 回転
		Rotation();

		// 制動調整
		Braking();

		// 重力落下
		CPhysics::GetInstance()->Gravity(m_velocity);
	}
	else
	{
		// 飛行
		Flying();

		// 旋回
		Rolling();

		// 空気抵抗
		AirResistance();
	}

	// 位置を調整、この処理の終わりに目標位置を反映させる
	AdjustPos();

	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CPlayer::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 生成
//============================================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	// インスタンスを生成
	CPlayer* pPlayer = DBG_NEW CPlayer;

	if (pPlayer == nullptr)
	{ // 生成失敗
		assert(false);
	}

	pPlayer->SetType(TYPE::PLAYER);	// タイプを設定

	pPlayer->Init();		// 基底クラスの初期設定
	pPlayer->SetPos(pos);	// 位置の設定

	// モデルを設定
	pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::MODEL_PLAYER_000));

	return pPlayer;
}

//============================================================================
// 歩行
//============================================================================
void CPlayer::Walking()
{
	// 左スティック取得
	CInputPad* pPad = CManager::GetPad();
	CInputPad::JOYSTICK Stick = pPad->GetJoyStickL();

	// 入力があれば移動
	if (Stick.X != 0 || Stick.Y != 0)
	{
		// 移動量と目標回転量を設定
		m_velocity.x += sinf(atan2f((float)Stick.X, 0.0f));
		m_rotTarget.y = atan2f((float)-Stick.X, 0.0f);
	}

	// キーボード取得
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// 移動方向用
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

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
	else
	{ // テスト用
		m_nTestExplosionCnt = 39;
	}

	if (bMove)
	{
		// 移動量と目標回転量を設定
		m_velocity.x += sinf(atan2f(X, 0.0f));
		m_rotTarget.y = atan2f(X, 0.0f);

		// テスト用
		m_nTestExplosionCnt > 40 ? m_nTestExplosionCnt = 0, (int)CExplosion3D::Create({ GetPos().x, GetPos().y + 3.0f, GetPos().z }, { 7.5f, 0.0f, 7.5f }) : m_nTestExplosionCnt++;
	}

	// 変身
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		if (!m_bMetamorphose)
		{
			// 変身判定を出す
			m_bMetamorphose = 1;

			// 変身期間を設定
			m_nCntMetamorphose = 30;

			// 加速度を初期化
			m_velocity = { 0.0f, 0.0f, 0.0f };

			// 飛行方向を初期化
			m_fAngleFlying = 0.0f;

			// Z軸回転を初期化
			m_rotTarget.z = 0.0f;
			SetRot({ GetRot().x, GetRot().y, 0.0f });

			// 見た目を変更
			BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::MODEL_PLAYER_001));

			// 爆発を生成
			CExplosion3D::Create(
				{ GetPos().x, GetPos().y, GetPos().z },	// 位置
				{ 30.0f, 0.0f, 30.0f });				// サイズ
		}
	}
}

//============================================================================
// 回転
//============================================================================
void CPlayer::Rotation()
{
	// 向き情報取得
	D3DXVECTOR3 rot = GetRot();

	// ブレーキ力
	float fStopEnergy = 0.1f;

	// 回転反映と回転量の減衰
	if (m_rotTarget.y - rot.y > D3DX_PI)
	{
		rot.y += ((m_rotTarget.y - rot.y) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (m_rotTarget.y - rot.y < -D3DX_PI)
	{
		rot.y += ((m_rotTarget.y - rot.y) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.y += ((m_rotTarget.y - rot.y) * fStopEnergy);
	}

	// 向き情報設定
	SetRot(rot);
}

//============================================================================
// 制動調整
//============================================================================
void CPlayer::Braking()
{
	// 加速度上限に到達で速度固定
	if (m_velocity.x > CPlayer::MAX_VELOCITY)
	{
		m_velocity.x = CPlayer::MAX_VELOCITY;
	}
	else if (m_velocity.x < -CPlayer::MAX_VELOCITY)
	{
		m_velocity.x = -CPlayer::MAX_VELOCITY;
	}

	// 少しずつ加速度を失う
	m_velocity = m_velocity * CPlayer::BRAKING_FORCE;
}

//============================================================================
// 飛行
//============================================================================
void CPlayer::Flying()
{
	// 左スティック取得
	CInputPad* pPad = CManager::GetPad();
	CInputPad::JOYSTICK Stick = pPad->GetJoyStickL();

	// 入力があれば移動
	if (Stick.X != 0 || Stick.Y != 0)
	{
		// 目標向きを設定
		m_rotTarget.z = atan2f((float)-Stick.X, (float)-Stick.Y);

		// 飛行方向を設定
		m_fAngleFlying = atan2f((float)Stick.X, (float)-Stick.Y);
	}

	// キーボード取得
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// 移動方向用
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

	// X軸
	if (pKeyboard->GetPress(DIK_A))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{
		X = 1.0f;
	}

	// Y軸
	if (pKeyboard->GetPress(DIK_W))
	{
		Y = 1.0f;
	}
	else if (pKeyboard->GetPress(DIK_S))
	{
		Y = -1.0f;
	}

	// 何か入力していれば移動判定を出す
	if (X != 0.0f || Y != 0.0f)
	{
		bMove = true;
	}
	else
	{ // テスト用
		m_nTestExplosionCnt = 2;
	}

	if (bMove)
	{
		// 目標向きを設定
		m_rotTarget.z = atan2f(-X, Y);

		// 飛行方向を設定
		m_fAngleFlying = atan2f(X, Y);

		// テスト用
		m_nTestExplosionCnt > 3 ? m_nTestExplosionCnt = 0, (int)CExplosion3D::Create({ GetPos().x, GetPos().y + 3.0f, GetPos().z }, { 7.5f, 0.0f, 7.5f }) : m_nTestExplosionCnt++;
	}

	// 飛行方向に突進
	m_velocity.x += sinf(m_fAngleFlying) * 0.1f;
	m_velocity.y += cosf(m_fAngleFlying) * 0.1f;
}

//============================================================================
// 旋回
//============================================================================
void CPlayer::Rolling()
{
	// 向き情報取得
	D3DXVECTOR3 rot = GetRot();

	// ブレーキ力
	float fStopEnergy = 0.1f;

	// 回転反映と回転量の減衰
	if (m_rotTarget.z - rot.z > D3DX_PI)
	{
		rot.z += ((m_rotTarget.z - rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (m_rotTarget.z - rot.z < -D3DX_PI)
	{
		rot.z += ((m_rotTarget.z - rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.z += ((m_rotTarget.z - rot.z) * fStopEnergy);
	}

	// 向き情報設定
	SetRot(rot);
}

//============================================================================
// 空気抵抗
//============================================================================
void CPlayer::AirResistance()
{
	float これはテスト用 = 2.0f;

	// 加速度上限に到達で速度固定
	if (m_velocity.x > これはテスト用)
	{
		m_velocity.x = これはテスト用;
	}
	else if (m_velocity.x < -これはテスト用)
	{
		m_velocity.x = -これはテスト用;
	}

	if (m_velocity.y > これはテスト用)
	{
		m_velocity.y = これはテスト用;
	}
	else if (m_velocity.y < -これはテスト用)
	{
		m_velocity.y = -これはテスト用;
	}
}

//============================================================================
// 位置調整
//============================================================================
void CPlayer::AdjustPos()
{
	if (m_nCntMetamorphose > 0)
	{
		m_nCntMetamorphose--;

		// 変身期間中は強制上昇
		m_posTarget.y += 1.0f;

		// Y軸を高速回転し、Z軸回転を初期化
		SetRot({ GetRot().x, m_posTarget.y * 0.25f, 0.0f });

		// どうしよう
		if (m_nCntMetamorphose == 0)
		{
			// 加速度を初期化
			m_velocity = { 0.0f, 0.0f, 0.0f };

			// 飛行方向を初期化
			m_fAngleFlying = 0.0f;

			// Z軸回転目標を初期化
			m_rotTarget.z = 0.0f;

			// Y軸回転を初期化
			SetRot({ GetRot().x, 0.0f, GetRot().z });
		}
	}
	else
	{	
		// 加速度分位置を変動
		m_posTarget += m_velocity;
	}

	// 当たり判定
	if (Collision())
	{
		// 変身解除
		FinishTransform();
	}

	// 画面の下端に到達で下降制限
	if (m_posTarget.y < 0.0f)
	{
		// 位置を下端に設定
		m_posTarget.y = 0.0f;

		// Y軸方向の加速度をリセット
		m_velocity.y = 0.0f;

		// 変身解除
		FinishTransform();
	}

	// 位置を設定
	SetPos(m_posTarget);
}

//============================================================================
// 当たり判定
//============================================================================
bool CPlayer::Collision()
{
	// 衝突判定
	bool bDetected = 0;

	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// オブジェクト情報を取得
			CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{ // 情報がなければコンティニュー
				continue;
			}

			if (pObject->GetType() == CObject::TYPE::BLOCK)
			{ // ブロックタイプなら

				// オブジェクトクラスをブロッククラスへダウンキャスト
				CBlock* pBlock = dynamic_cast<CBlock*>(pObject);

				if (pBlock == nullptr)
				{ // ダウンキャスト失敗
					assert(false);
				}

				// ブロックと衝突する場合
				if(CPhysics::GetInstance()->Cube(m_posTarget, { 10.0f, 10.0f ,10.0f }, pBlock->GetPos(), { 10.0f, 10.0f ,10.0f }))
				{
					// 押し出し処理
					CPhysics::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), { 10.0f, 10.0f ,10.0f }, pBlock->GetPos(), { 10.0f, 10.0f ,10.0f });

					// 衝突判定を出す
					bDetected = 1;
				}
			}
		}
	}

	return bDetected;
}

//============================================================================
// 変身解除
//============================================================================
void CPlayer::FinishTransform()
{
	if (m_bMetamorphose)
	{
		// 変身判定を解除
		m_bMetamorphose = 0;

		// 加速度を初期化
		m_velocity = { 0.0f, 0.0f, 0.0f };

		// Z軸回転を初期化
		m_rotTarget.z = 0.0f;
		SetRot({ GetRot().x, GetRot().y, 0.0f });

		// 見た目を変更
		BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::MODEL_PLAYER_000));

		// 爆発を生成
		CExplosion3D::Create(
			{ GetPos().x, GetPos().y, GetPos().z },	// 位置
			{ 30.0f, 0.0f, 30.0f });				// サイズ

		// 反動を生成
		Recoil();

		// 飛行方向を初期化
		m_fAngleFlying = 0.0f;
	}
}

//============================================================================
// 反動
//============================================================================
void CPlayer::Recoil()
{
	//// 飛行方向の逆に突進
	//m_velocity.x += sinf(m_fAngleFlying + D3DX_PI) * 10.0f;
	//m_velocity.y += cosf(m_fAngleFlying + D3DX_PI) * 10.0f;
}