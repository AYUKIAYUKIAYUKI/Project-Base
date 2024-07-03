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
#include "physics.h"
#include "block.h"
#include "explosion.h"
#include "explosion3D.h"
#include "goal.h"
#include "particle.h"
#include "start.h"

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

		// プレイヤーのインスタンス情報を状態管理クラスに渡す
		m_pStateManager->SetPlayerInstance(this);

		// 初期化
		m_pStateManager->Init();

		// プレイヤーのインスタンス情報を状態クラスに渡す
		m_pStateManager->GetState()->SetPlayerInstance(this);
	}

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

	// 位置を反映
	SetPos(m_posTarget);

	// 位置をデバッグ表示
	CManager::GetRenderer()->SetDebugString("【プレイヤー位置】");
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
				if (CPhysics::GetInstance()->OnlyCube(m_posTarget, GetSize(), pBlock->GetPos(), BlockSize))
				{
					// 押し出し処理
					CPhysics::GetInstance()->CubeResponse(m_posTarget, m_velocity, GetPos(), GetSize(), pBlock->GetPos(), BlockSize);

					// 衝突判定を出す
					bDetected = 1;
				}
			}
			else if (pObject->GetType() == CObject::TYPE::GOAL)
			{ // ゴールタイプなら

				// オブジェクトクラスをゴールクラスへダウンキャスト
				CGoal* pGoal = dynamic_cast<CGoal*>(pObject);

				// ゴールと衝突する場合
				if (CPhysics::GetInstance()->SphereAndCube(pGoal->GetPos(), 10.0f, m_posTarget, GetSize()))
				{
					// とりあえずゲームを終了させる
					CManager::GetFade()->SetFade(CScene::MODE::RESULT);
				}
			}
		}
	}

	return bDetected;
}