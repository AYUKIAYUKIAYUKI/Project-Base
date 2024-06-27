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
#include "physics.h"
#include "block.h"
#include "explosion.h"
#include "explosion3D.h"
#include "particle.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
const float CPlayerStateDefault::MAX_WALK_VELOCITY = 0.5f;	// 歩行時の最大加速度
const float CPlayerStateDefault::BRAKING_WALK_SPEED = 0.9f;	// 歩行時の制動力
const int CPlayerStateBeginning::BEGIN_CNT_MAX = 30;		// 変身必要時間
const float CPlayerStateFlying::MAX_FLY_VELOCITY = 1.5f;	// 飛行時の最大加速度
const int CPlayerStateStopping::STOP_CNT_MAX = 30;			// 変身停止必要時間

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer() : CObject_X(static_cast<int>(LAYER::FRONT_MIDDLE))
{
	m_pStateManager = nullptr;				// 状態管理
	m_velocity = { 0.0f, 0.0f, 0.0f };		// 加速度
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// 目標位置
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// 目標向き
	m_fAngleFlying = 0.0f;					// 飛行向き
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

	// 大きさを設定
	SetSize({ 10.0f, 10.0f, 10.0f });

	// 状態管理クラスの生成
	if (m_pStateManager == nullptr)
	{
		m_pStateManager = DBG_NEW CPlayerStateManager;

		// 初期化
		m_pStateManager->Init();
	}

	// プレイヤーのインスタンス情報を状態管理クラスに渡す
	m_pStateManager->SetPlayerInstance(this);

	// プレイヤーのインスタンス情報を状態クラスに渡す
	m_pStateManager->GetState()->SetPlayerInstance(this);

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CPlayer::Uninit()
{
	// 状態管理クラスの破棄
	if (m_pStateManager != nullptr)
	{
		// 終了処理
		m_pStateManager->Uninit();
	
		// メモリを解放
		delete m_pStateManager;

		// ポインタを初期化
		m_pStateManager = nullptr;
	}

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

	// 状態の更新処理
	m_pStateManager->GetState()->Update();

	// 位置を設定
	SetPos(m_posTarget);

	// 当たり判定や範囲制限など位置調整、この処理の終わりに目標位置を反映させる
	//AdjustPos();

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
// 加速度を取得
//============================================================================
D3DXVECTOR3 CPlayer::GetVelocity()
{
	return m_velocity;
}

//============================================================================
// 加速度を設定
//============================================================================
void CPlayer::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

//============================================================================
// 飛行方向を取得
//============================================================================
float CPlayer::GetAngleFlying()
{
	return m_fAngleFlying;
}

//============================================================================
// 飛行方向を設定
//============================================================================
void CPlayer::SetAngleFlying(float fAngleFlying)
{
	m_fAngleFlying = fAngleFlying;
}

//============================================================================
// 目標位置を取得
//============================================================================
D3DXVECTOR3 CPlayer::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// 目標位置を設定
//============================================================================
void CPlayer::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// 目標向きを取得
//============================================================================
D3DXVECTOR3 CPlayer::GetRotTarget()
{
	return m_rotTarget;
}

//============================================================================
// 目標向きを設定
//============================================================================
void CPlayer::SetRotTarget(D3DXVECTOR3 rotTarget)
{
	m_rotTarget = rotTarget;
}

//============================================================================
// 状態管理取得
//============================================================================
CPlayerStateManager* CPlayer::GetStateManager()
{
	return m_pStateManager;
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
	pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_000));

	return pPlayer;
}

//============================================================================
// 位置調整
//============================================================================
bool CPlayer::AdjustPos()
{
	// 何かへの衝突検出
	bool bDetected = false;

	// 加速度分位置を変動
	m_posTarget += m_velocity;

	// 当たり判定
	bDetected = Collision();

	//// 画面の下端に到達で下降制限
	//if (m_posTarget.y < 0.0f)
	//{
	//	// 位置を下端に設定
	//	m_posTarget.y = 0.0f;

	//	// Y軸方向の加速度をリセット
	//	m_velocity.y = 0.0f;

	//	// 地面を検出
	//	bDetected = true;
	//}

	// 位置を設定
	SetPos(m_posTarget);

	// 検出を返す
	return bDetected;
}

//============================================================================
// 当たり判定
//============================================================================
bool CPlayer::Collision()
{
	// 衝突判定
	bool bDetected = 0;

	// 仮サイズ
	D3DXVECTOR3 BlockSize = { 10.0f, 10.0f, 10.0f };

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
				if (CPhysics::GetInstance()->Cube(m_posTarget, GetSize(), pBlock->GetPos(), BlockSize))
				{
					// 押し出し処理
					CPhysics::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), GetSize(), pBlock->GetPos(), BlockSize);

					// 衝突判定を出す
					bDetected = 1;
				}
			}
		}
	}

	return bDetected;
}



//============================================================================
// 
// プレイヤー状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerState::CPlayerState() : m_pPlayer(nullptr)
{

}

//============================================================================
// デストラクタ
//============================================================================
CPlayerState::~CPlayerState()
{

}

//============================================================================
// 初期設定
//============================================================================
void CPlayerState::Init()
{

}

//============================================================================
// 更新
//============================================================================
void CPlayerState::Update()
{

}

//============================================================================
// プレイヤー情報の設定
//============================================================================
void CPlayerState::SetPlayerInstance(CPlayer* player)
{
	m_pPlayer = player;
}



//============================================================================
// 
// プレイヤー通常状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateDefault::CPlayerStateDefault()
{

}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateDefault::~CPlayerStateDefault()
{

}

//============================================================================
// 開始
//============================================================================
void CPlayerStateDefault::Init()
{
	// 基底クラスの初期設定
	CPlayerState::Init();
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateDefault::Update()
{
	// 操作
	if (!Walk())
	{
		return;
	}

	// 回転
	Rotation();

	// 重力落下
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();
	CPhysics::GetInstance()->Gravity(velocity);
	m_pPlayer->SetVelocity(velocity);

	// 制動調整
	Braking();

	// 加速度を位置に加算
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);

	// 位置調整
	m_pPlayer->AdjustPos();
}

//============================================================================
// 終了
//============================================================================
void CPlayerStateDefault::Exit()
{
	// 加速度を初期化
	m_pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });

	// 飛行方向を初期化
	m_pPlayer->SetAngleFlying(0.0f);

	// Z軸回転を初期化
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.z = 0.0f;
	m_pPlayer->SetRot(rot);

	// 見た目を変更
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_001));

	// 爆発を生成
	CExplosion3D::Create(
		m_pPlayer->GetPos(),		// 位置
		{ 30.0f, 0.0f, 30.0f });	// サイズ
}

//============================================================================
// 移動
//============================================================================
bool CPlayerStateDefault::Walk()
{
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

	if (bMove)
	{
		// 移動量と目標回転量を設定
		D3DXVECTOR3 veloctiy = m_pPlayer->GetVelocity();
		D3DXVECTOR3 rotTarget = m_pPlayer->GetRotTarget();

		veloctiy.x += sinf(atan2f(X, 0.0f));
		rotTarget.y = atan2f(X, 0.0f);

		m_pPlayer->SetVelocity(veloctiy);
		m_pPlayer->SetRotTarget(rotTarget);
	}

	// 状態変更
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		// 状態変更
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::BEGINNING);

		return false;
	}

	return true;
}

//============================================================================
// 回転
//============================================================================
void CPlayerStateDefault::Rotation()
{
	// 向き情報取得
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	D3DXVECTOR3 rotTarget = m_pPlayer->GetRotTarget();

	// ブレーキ力
	float fStopEnergy = 0.1f;

	// 回転反映と回転量の減衰
	if (rotTarget.y - rot.y > D3DX_PI)
	{
		rot.y += ((rotTarget.y - rot.y) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (rotTarget.y - rot.y < -D3DX_PI)
	{
		rot.y += ((rotTarget.y - rot.y) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.y += ((rotTarget.y - rot.y) * fStopEnergy);
	}

	// 向き情報設定
	m_pPlayer->SetRot(rot);
}

//============================================================================
// 制動調整
//============================================================================
void CPlayerStateDefault::Braking()
{
	// 加速度を取得
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();

	// 加速度上限に到達で速度固定
	if (velocity.x > MAX_WALK_VELOCITY)
	{
		velocity.x = MAX_WALK_VELOCITY;
	}
	else if (velocity.x < -MAX_WALK_VELOCITY)
	{
		velocity.x = -MAX_WALK_VELOCITY;
	}

	// 少しずつ加速度を失う
	velocity = velocity * BRAKING_WALK_SPEED;

	// 加速度を設定
	m_pPlayer->SetVelocity(velocity);
}


//============================================================================
// 
// プレイヤー変身開始状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateBeginning::CPlayerStateBeginning()
{
	m_nCntMetamorphose = 0;	// 変身時間カウント
}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateBeginning::~CPlayerStateBeginning()
{

}

//============================================================================
// 開始
//============================================================================
void CPlayerStateBeginning::Init()
{
	// 基底クラスの初期設定
	CPlayerState::Init();
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateBeginning::Update()
{
	if (m_nCntMetamorphose < BEGIN_CNT_MAX)
	{
		// 変身時間をカウントアップ
		m_nCntMetamorphose++;

		// 変身期間中は強制上昇
		D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
		posTarget.y += 1.0f;
		m_pPlayer->SetPosTarget(posTarget);

		// Y軸を高速回転し、Z軸回転を初期化
		D3DXVECTOR3 rot = m_pPlayer->GetRot();
		rot.y = posTarget.y * 0.25f;
		rot.z = 0.0f;
		m_pPlayer->SetRot(rot);
	}
	else
	{
		// 状態変更
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::FLYING);
	}
}

//============================================================================
// 終了
//============================================================================
void CPlayerStateBeginning::Exit()
{
	// 加速度を初期化
	m_pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });

	// 飛行方向を初期化
	m_pPlayer->SetAngleFlying(0.0f);

	// Z軸回転目標を初期化
	D3DXVECTOR3 rotTarget = m_pPlayer->GetRotTarget();
	rotTarget.z = 0.0f;
	m_pPlayer->SetRotTarget(rotTarget);

	// Y軸回転を初期化
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.y = 0.0f;
	m_pPlayer->SetRot(rot);

	// 見た目を変更
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_002));
}



//============================================================================
// 
// プレイヤー飛行状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateFlying::CPlayerStateFlying()
{

}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateFlying::~CPlayerStateFlying()
{

}

//============================================================================
// 開始
//============================================================================
void CPlayerStateFlying::Init()
{
	// 基底クラスの初期設定
	CPlayerState::Init();
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateFlying::Update()
{
	// 飛行
	if (!Flying())
	{
		return;
	}

	// 回転
	Rotation();

	// 制動調整
	Braking();

	// 加速度を位置に加算
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);

	// 位置調整
	if (m_pPlayer->AdjustPos())
	{
		// 何かに衝突で変身停止へ
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::STOPPING);
	}
}

//============================================================================
// 終了
//============================================================================
void CPlayerStateFlying::Exit()
{
	// 加速度を初期化
	m_pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });

	//// Z軸回転を初期化
	//D3DXVECTOR3 rot = m_pPlayer->GetRot();
	//rot.z = 0.0f;
	//m_pPlayer->SetRot(rot);

	// 見た目を変更
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_003));

	// 爆発を生成
	CExplosion3D::Create(
		m_pPlayer->GetPos(),		// 位置
		{ 30.0f, 0.0f, 30.0f });	// サイズ
}

//============================================================================
// 飛行
//============================================================================
bool CPlayerStateFlying::Flying()
{
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

	if (bMove)
	{
		// 目標向きを設定
		D3DXVECTOR3 rotTarget = { 0.0f, 0.0f, 0.0f };
		rotTarget.z = atan2f(-X, Y);
		m_pPlayer->SetRotTarget(rotTarget);

		// 飛行方向を設定
		m_pPlayer->SetAngleFlying(atan2f(X, Y));
	}

	// 飛行方向に突進
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();
	velocity.x += sinf(m_pPlayer->GetAngleFlying()) * 0.1f;
	velocity.y += cosf(m_pPlayer->GetAngleFlying()) * 0.1f;
	m_pPlayer->SetVelocity(velocity);

	return true;
}

//============================================================================
// 回転
//============================================================================
void CPlayerStateFlying::Rotation()
{
	// 向き情報取得
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	D3DXVECTOR3 rotTarget = m_pPlayer->GetRotTarget();

	// ブレーキ力
	float fStopEnergy = 0.1f;

	// 回転反映と回転量の減衰
	if (rotTarget.z - rot.z > D3DX_PI)
	{
		rot.z += ((rotTarget.z - rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (rotTarget.z - rot.z < -D3DX_PI)
	{
		rot.z += ((rotTarget.z - rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.z += ((rotTarget.z - rot.z) * fStopEnergy);
	}

	// 向き情報設定
	m_pPlayer->SetRot(rot);
}

//============================================================================
// 制動調整
//============================================================================
void CPlayerStateFlying::Braking()
{
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();

	// 加速度上限に到達で速度固定
	if (velocity.x > MAX_FLY_VELOCITY)
	{
		velocity.x = MAX_FLY_VELOCITY;
	}
	else if (velocity.x < -MAX_FLY_VELOCITY)
	{
		velocity.x = -MAX_FLY_VELOCITY;
	}

	if (velocity.y > MAX_FLY_VELOCITY)
	{
		velocity.y = MAX_FLY_VELOCITY;
	}
	else if (velocity.y < -MAX_FLY_VELOCITY)
	{
		velocity.y = -MAX_FLY_VELOCITY;
	}

	m_pPlayer->SetVelocity(velocity);
}



//============================================================================
// 
// プレイヤー変身停止状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateStopping::CPlayerStateStopping()
{
	m_nCntStopMetamorphose = 0;	// 変身時間カウント
}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateStopping::~CPlayerStateStopping()
{

}

//============================================================================
// 開始
//============================================================================
void CPlayerStateStopping::Init()
{
	// 基底クラスの初期設定
	CPlayerState::Init();
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateStopping::Update()
{
	if (m_nCntStopMetamorphose < STOP_CNT_MAX)
	{
		// 変身停止期間をカウントアップ
		m_nCntStopMetamorphose++;

		// 回転
		Rolling();

		// 反動
		Recoil();

		// 加速度を位置に加算
		D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
		posTarget += m_pPlayer->GetVelocity();
		m_pPlayer->SetPosTarget(posTarget);

		// 位置調整
		m_pPlayer->AdjustPos();
	}
	else
	{
		// 状態変更
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::DEFAULT);
	}
}

//============================================================================
// 終了
//============================================================================
void CPlayerStateStopping::Exit()
{
	// X, Z軸回転を初期化
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.x = 0.0f;
	rot.z = 0.0f;
	m_pPlayer->SetRot(rot);

	// 見た目を変更
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_000));
}

//============================================================================
// 回転
//============================================================================
void CPlayerStateStopping::Rolling()
{
	// 向き情報取得
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	D3DXVECTOR3 rotTarget = m_pPlayer->GetRotTarget();
	m_pPlayer->SetRotTarget(rotTarget);

	// ブレーキ力
	float fStopEnergy = 0.1f;

	// 回転反映と回転量の減衰
	if (rotTarget.x - rot.x > D3DX_PI)
	{
		rot.x += ((rotTarget.x - rot.x) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (rotTarget.x - rot.x < -D3DX_PI)
	{
		rot.x += ((rotTarget.x - rot.x) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.x += ((rotTarget.x - rot.x) * fStopEnergy);
	}

	// 向き情報設定
	m_pPlayer->SetRot(rot);
}

//============================================================================
// 反動
//============================================================================
void CPlayerStateStopping::Recoil()
{
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();

	// 飛行方向に突進
	velocity.x += -sinf(m_pPlayer->GetAngleFlying()) * 0.04f;
	velocity.y += -cosf(m_pPlayer->GetAngleFlying()) * 0.04f;

	m_pPlayer->SetVelocity(velocity);
}



//============================================================================
// 
// プレイヤー状態管理クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateManager::CPlayerStateManager() : m_pPlayer(nullptr), m_pState(nullptr)
{

}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateManager::~CPlayerStateManager()
{

}

//============================================================================
// 初期設定
//============================================================================
void CPlayerStateManager::Init()
{
	// 初期状態を設定しておく
	ChangeState(CPlayerState::STATE::DEFAULT);
}

//============================================================================
// 終了処理
//============================================================================
void CPlayerStateManager::Uninit()
{
	if (m_pState != nullptr)
	{
		// メモリを解放
		delete m_pState;

		// ポインタを初期化
		m_pState = nullptr;
	}
}

//============================================================================
// プレイヤー情報の取得
//============================================================================
CPlayer* CPlayerStateManager::GetPlayerInstance()
{
	return m_pPlayer;
}

//============================================================================
// プレイヤー情報の設定
//============================================================================
void CPlayerStateManager::SetPlayerInstance(CPlayer* player)
{
	m_pPlayer = player;
}

//============================================================================
// 状態を変更
//============================================================================
void CPlayerStateManager::ChangeState(CPlayerState::STATE state)
{
	if (m_pState != nullptr)
	{
		// 終了時限定の処理
		m_pState->Exit();

		// メモリを解放
		delete m_pState;

		// ポインタを初期化
		m_pState = nullptr;
	}

	// 次の状態を生成
	Create(state);

	m_pState->SetPlayerInstance(m_pPlayer);

	// 状態の初期設定
	m_pState->Init();
}

//============================================================================
// 状態を取得
//============================================================================
CPlayerState* CPlayerStateManager::GetState()
{
	return m_pState;
}

//============================================================================
// 新たな状態を生成
//============================================================================
void CPlayerStateManager::Create(CPlayerState::STATE state)
{
	switch (state)
	{
	case CPlayerState::STATE::DEFAULT:
		m_pState = DBG_NEW CPlayerStateDefault;
		break;

	case CPlayerState::STATE::BEGINNING:
		m_pState = DBG_NEW CPlayerStateBeginning;
		break;

	case CPlayerState::STATE::FLYING:
		m_pState = DBG_NEW CPlayerStateFlying;
		break;

	case CPlayerState::STATE::STOPPING:
		m_pState = DBG_NEW CPlayerStateStopping;
		break;

	default:
		assert(false);
		break;
	}
}