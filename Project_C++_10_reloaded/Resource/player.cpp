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
#include "player_state.h"
#include "manager.h"
#include "game_manager.h"
#include "physics.h"
#include "fakescreen.h"

#include "block.h"
#include "block_destructible.h"
#include "explosion.h"
#include "goal.h"
#include "start.h"

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer() : CObject_X(static_cast<int>(LAYER::FRONT_MIDDLE))
{
	m_pStateManager = nullptr;				// 状態マネージャーの初期化
	m_velocity = { 0.0f, 0.0f, 0.0f };		// 加速度の初期化
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// 目標位置の初期化
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// 目標向きの初期化
	m_fAngleFlying = 0.0f;					// 飛行向きの初期化
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

	if (m_pStateManager == nullptr)
	{
		// 状態マネージャーの生成
		m_pStateManager = DBG_NEW CPlayerStateManager;

		// 初期設定
		m_pStateManager->Init(this);
	}

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CPlayer::Uninit()
{
	// 状態マネージャーの破棄
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
	// 現在座標をコピーし、以降このコピーを目標座標として変更を加えていく
	m_posTarget = CObject_X::GetPos();

	// 状態オブジェクトが生成されていれば
	if (m_pStateManager->GetState() != nullptr)
	{
		// 状態の更新
		m_pStateManager->GetState()->Update();

		// 状態の変更を確認する (メモリ解放を含む処理は更新の後にフラグを参照して行う)
		m_pStateManager->CheckStateChange();
	}

	// 目標座標を反映
	SetPos(m_posTarget);

	// 座標をデバッグ表示
	CManager::GetRenderer()->SetDebugString("【プレイヤー座標】");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	CManager::GetRenderer()->SetDebugString(oss.str().c_str());

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
// 座標変更を反映
//============================================================================
bool CPlayer::ApplyPos()
{
	// 衝突検出用
	bool bDetected = false;

	// 加速度分座標を変動
	m_posTarget += m_velocity;

	// 当たり判定
	bDetected = Collision();

	// 座標を設定
	SetPos(m_posTarget);

	// 衝突検出を返す
	return bDetected;
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

	// タイプを設定
	pPlayer->SetType(TYPE::PLAYER);

	// 基底クラスの初期設定
	pPlayer->Init();

	// 位置の設定
	pPlayer->SetPos(pos);

	return pPlayer;
}

//============================================================================
// ダウンキャスト
//============================================================================
CPlayer* CPlayer::DownCast(CObject* pObject)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);

	if (pPlayer == nullptr)
	{ // ダウンキャスト失敗
		assert(false);
	}

	return pPlayer;
}

//============================================================================
// 当たり判定
//============================================================================
bool CPlayer::Collision()
{
	// 衝突検出
	bool bDetected = 0;

	// オブジェクトを取得
	CObject** pObject = CObject::FindAllObject(CObject::TYPE::BLOCK);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ブロッククラスへダウンキャスト
		CBlock* pBlock = CBlock::DownCast(pObject[nCntObj]);

		// ブロックと衝突する場合
		if (CPhysics::GetInstance()->OnlyCube(pBlock->GetPos(), pBlock->GetSize(), m_posTarget, GetSize()))
		{
			// 押し出し処理
			CPhysics::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), GetSize(), pBlock->GetPos(), pBlock->GetSize());

			// 衝突判定を出す
			bDetected = 1;
		}
	}

	// オブジェクトを取得
	pObject = CObject::FindAllObject(CObject::TYPE::DESTRUCTIBLE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// 可壊ブロックへダウンキャスト
		CBlockDestructible* pDestructible = CBlockDestructible::DownCast(pObject[nCntObj]);

		// 可壊ブロックと衝突する場合
		if (CPhysics::GetInstance()->OnlyCube(pDestructible->GetPos(), pDestructible->GetSize(), m_posTarget, GetSize()))
		{
			// 押し出し処理
			CPhysics::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), GetSize(), pDestructible->GetPos(), pDestructible->GetSize());

			// 消す
			pDestructible->Release();

			// 衝突判定を出す
			bDetected = 1;
		}
	}

	// ゴールオブジェクトを取得
	CGoal* pGoal = CGoal::DownCast(CObject::FindObject(CObject::TYPE::GOAL));

	// ゴールと衝突する場合
	if (CPhysics::GetInstance()->SphereAndCube(pGoal->GetPos(), pGoal->GetSize().x, m_posTarget, GetSize()))
	{			
		// ゴール状態に移行する合図を設定
		m_pStateManager->SetPendingState(CPlayerState::STATE::GOAL);

		// レベル終了フェーズへ移行
		CFakeScreen::GetInstance()->SetWave(CGameManager::PHASE::FINISH);
	}

	return bDetected;
}