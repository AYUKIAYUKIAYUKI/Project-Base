//============================================================================
// 
// プレイヤー状態管理 [player_state.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "player_state.h"

#include "manager.h"
#include "physics.h"
#include "explosion3D.h"
#include "start.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
const float CPlayerStateDefault::MAX_WALK_VELOCITY = 0.75f;	// 歩行時の最大加速度
const float CPlayerStateDefault::BRAKING_WALK_SPEED = 0.8f;	// 歩行時の制動力
const int CPlayerStateBeginning::BEGIN_CNT_MAX = 20;		// 変身必要時間
const float CPlayerStateBeginning::BEGIN_FLOATING = 1.25f;	// 変身時上昇量
const float CPlayerStateBeginning::BEGIN_SPINNING = 0.5f;	// 変身時回転量
const float CPlayerStateFlying::MAX_FLY_VELOCITY = 2.0f;	// 飛行時の最大加速度
const float CPlayerStateFlying::FLY_SPEED = 0.25f;			// 飛行速度
const int CPlayerStateStopping::STOP_CNT_MAX = 20;			// 変身停止必要時間
const float CPlayerStateStopping::RECOIL_SPEED = 1.0f;		// 反動移動速度
const float CPlayerStateMistook::MAX_WARP_SPEED = 15.0f;	// 強制移動速度の上限

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
// 変更開始
//============================================================================
void CPlayerStateDefault::Enter()
{
	// 見た目を変更
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_000));
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

	// おかしなところに行くと一旦殺す
	if (posTarget.y < -300.0f)
	{
		// 失敗状態に変更
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::MISS);
	}
}

//============================================================================
// 変更終了
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
		// Y方向への加速度が無ければ変身
		if (m_pPlayer->GetVelocity().y == 0.0f)
		{
			// 見た目を変更する
			m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::BEGINNING);

			// 以降の更新処理を行わない
			return false;
		}
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
	velocity.x = velocity.x * BRAKING_WALK_SPEED;

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
// 変更開始
//============================================================================
void CPlayerStateBeginning::Enter()
{
	// 見た目を変更
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_001));

	// 爆発を生成
	CExplosion3D::Create(
		m_pPlayer->GetPos(),		// 位置
		{ 30.0f, 0.0f, 30.0f });	// サイズ
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
		posTarget.y += BEGIN_FLOATING;
		m_pPlayer->SetPosTarget(posTarget);

		// Y軸を高速回転し、Z軸回転を初期化
		D3DXVECTOR3 rot = m_pPlayer->GetRot();
		rot.y = posTarget.y * BEGIN_SPINNING;
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
// 変更終了
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
// 変更開始
//============================================================================
void CPlayerStateFlying::Enter()
{
	// 見た目を変更
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_002));
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
// 変更終了
//============================================================================
void CPlayerStateFlying::Exit()
{
	// 加速度を初期化
	m_pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });
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
	velocity.x += sinf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	velocity.y += cosf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
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
// 変更開始
//============================================================================
void CPlayerStateStopping::Enter()
{
	// 見た目を変更
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_003));

	// 爆発を生成
	CExplosion3D::Create(
		m_pPlayer->GetPos(),		// 位置
		{ 30.0f, 0.0f, 30.0f });	// サイズ

	// 反動
	Recoil();
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

		// 重力加速
		D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();
		CPhysics::GetInstance()->Gravity(velocity);
		m_pPlayer->SetVelocity(velocity);

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
// 変更終了
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
	velocity.x += -sinf(m_pPlayer->GetAngleFlying()) * RECOIL_SPEED;
	velocity.y += -cosf(m_pPlayer->GetAngleFlying()) * RECOIL_SPEED;

	m_pPlayer->SetVelocity(velocity);
}



//============================================================================
// 
// プレイヤー失敗状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateMistook::CPlayerStateMistook()
{
	m_posStartObject = { 0.0f, 0.0f, 0.0f };
}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateMistook::~CPlayerStateMistook()
{

}

//============================================================================
// 変更開始
//============================================================================
void CPlayerStateMistook::Enter()
{
	// 回転を初期化
	m_pPlayer->SetRot({ 0.0f, 0.0f, 0.0f });

	// 見た目を変更
	m_pPlayer->BindModel(CManager::GetRenderer()->GetModelInstane()->GetModel(CModel_X::MODEL_TYPE::PLAYER_004));

	// スタートオブジェクトの位置情報を取得
	FindStartObject();
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateMistook::Update()
{
	// リスポーン
	Respawn();
}

//============================================================================
// 変更終了
//============================================================================
void CPlayerStateMistook::Exit()
{

}

//============================================================================
// スタートオブジェクトの位置を検索
//============================================================================
void CPlayerStateMistook::FindStartObject()
{
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(CObject::LAYER::MAX); nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// オブジェクト情報を取得
			CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{ // 情報がなければコンティニュー
				continue;
			}

			if (pObject->GetType() == CObject::TYPE::START)
			{ // スタートオブジェクトなら

				// スタートクラスへダウンキャスト
				CStart* pStart = dynamic_cast<CStart*>(pObject);

				if (pStart == nullptr)
				{ // ダウンキャスト失敗
					assert(false);
				}

				// スタートオブジェクトの位置を取得
				m_posStartObject = pStart->GetPos();

				// 終了
				return;
			}
		}
	}

	// 発見できなければエラー
	assert(false);
}

//============================================================================
// リスポーン
//============================================================================
void CPlayerStateMistook::Respawn()
{
	// 目標位置取得
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();

	// プレイヤーの位置がスタートオブジェクトの位置と異なれば
	if (posTarget != m_posStartObject)
	{
		// プレイヤー位置とスタート位置の差を割り出す
		D3DXVECTOR3 distance = m_posStartObject - posTarget;

		// 差が一定以上あれば制限を付ける
		if (distance.x > MAX_WARP_SPEED)
		{
			distance.x = MAX_WARP_SPEED;
		}
		else if (distance.x < -MAX_WARP_SPEED)
		{
			distance.x = -MAX_WARP_SPEED;
		}

		if (distance.y > MAX_WARP_SPEED)
		{
			distance.y = MAX_WARP_SPEED;
		}
		else if (distance.y < -MAX_WARP_SPEED)
		{
			distance.y = -MAX_WARP_SPEED;
		}

		// 差を縮めて位置を補正していく
		posTarget += distance;

		// 目標位置を設定する
		m_pPlayer->SetPosTarget(posTarget);
	}
	else
	{
		// 通常状態に変更
		m_pPlayer->GetStateManager()->ChangeState(CPlayerState::STATE::DEFAULT);
	}
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
	ChangeState(CPlayerState::STATE::MISS);
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
		// 変更終了時の処理
		m_pState->Exit();

		// メモリを解放
		delete m_pState;

		// ポインタを初期化
		m_pState = nullptr;
	}

	// 次の状態を生成
	Create(state);

	m_pState->SetPlayerInstance(m_pPlayer);

	// 初回変更時の処理
	m_pState->Enter();
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

	case CPlayerState::STATE::MISS:
		m_pState = DBG_NEW CPlayerStateMistook;
		break;

	default:
		assert(false);
		break;
	}
}