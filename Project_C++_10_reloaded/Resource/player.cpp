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
#include "utility.h"
#include "sound.h"

// フェーズ情報用
#include "game_manager.h"

// デバッグ表示用
#include "renderer.h"

// オブジェクト情報用 
#include "achievement.h"
#include "block.h"
#include "block_destructible.h"
#include "block_spikes.h"
#include "enemy.h"
#include "fakescreen.h"
#include "goal.h"
#include "start.h"

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },	// 描画優先度を指定
	m_pStateManager{ nullptr },						// 状態マネージャーの初期化
	m_velocity{ 0.0f, 0.0f, 0.0f },					// 加速度の初期化
	m_velocityTarget{ 0.0f, 0.0f, 0.0f },			// 目標加速度の初期化
	m_posTarget{ 0.0f, 0.0f, 0.0f },				// 目標位置の初期化
	m_rotTarget{ 0.0f, 0.0f, 0.0f },				// 目標向きの初期化
	m_fAngleFlying{ 0.0f }							// 飛行向きの初期化
{
	
}

//============================================================================
// デストラクタ
//============================================================================
CPlayer::~CPlayer()
{
	m_pStateManager = nullptr;					// 状態マネージャーの初期化
	m_velocity = { 0.0f, 0.0f, 0.0f };			// 加速度の初期化
	m_velocityTarget = { 0.0f, 0.0f, 0.0f };	// 目標加速度の初期化
	m_posTarget = { 0.0f, 0.0f, 0.0f };			// 目標位置の初期化
	m_rotTarget = { 0.0f, 0.0f, 0.0f };			// 目標向きの初期化
	m_fAngleFlying = 0.0f;						// 飛行向きの初期化
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

		// 状態の変更を確認する (メモリ解放を含む処理のため、更新の後に別途行う)
		m_pStateManager->CheckStateChange();
	}

	// 目標座標を反映
	SetPos(m_posTarget);

#ifdef _DEBUG
	// 座標をデバッグ表示
	CRenderer::GetInstance()->SetDebugString("【プレイヤー座標】");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());

	CRenderer::GetInstance()->SetDebugString("現在の加速度X : " + std::to_string(m_velocity.x));
	CRenderer::GetInstance()->SetDebugString("現在の加速度Y : " + std::to_string(m_velocity.y));
#endif	// _DEBUG

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
// 当たり判定
//============================================================================
bool CPlayer::Collision()
{
	// 衝突検出
	bool bDetected = 0;

	// ブロックタグを取得
	CObject** pObject = CObject::FindAllObject(CObject::TYPE::BLOCK);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// ブロックタグの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ブロッククラスへダウンキャスト
		CBlock* pBlock = CUtility::GetInstance()->DownCast<CBlock, CObject>(pObject[nCntObj]);

		// ブロックと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pBlock->GetPos(), pBlock->GetSize(), m_posTarget, GetSize()))
		{
			// 押し出し処理
			CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pBlock->GetPos(), pBlock->GetSize());

			// 衝突判定を出す
			bDetected = 1;
		}
	}

	// 可壊タグを取得
	pObject = CObject::FindAllObject(CObject::TYPE::DESTRUCTIBLE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// 可壊タグの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// 可壊ブロックへダウンキャスト
		CBlockDestructible* pDestructible = CUtility::GetInstance()->DownCast<CBlockDestructible, CObject>(pObject[nCntObj]);

		// 可壊ブロックと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pDestructible->GetPos(), pDestructible->GetSize(), m_posTarget, GetSize()))
		{
			// 押し出し処理
			CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pDestructible->GetPos(), pDestructible->GetSize());

			// 飛行状態の場合のみ
			if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying))
			{
				// 可壊ブロックを破棄
				pDestructible->SetRelease();

				// 破壊音
				CSound::GetInstance()->Play(CSound::LABEL::BREAK);
			}

			// 衝突判定を出す
			bDetected = 1;
		}
	}

	// とげタグを取得
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// とげタグの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// とげブロックへダウンキャスト
		CBlockSpikes* pBlockSpikes = CUtility::GetInstance()->DownCast<CBlockSpikes, CObject>(pObject[nCntObj]);

		// とげブロックと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pBlockSpikes->GetPos(), pBlockSpikes->GetSize(), m_posTarget, GetSize()))
		{
			// ミス状態に移行
			m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);

			// 衝突判定を出す
			bDetected = 1;

			// 死亡音
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}
	
	// エネミータグを取得
	pObject = CObject::FindAllObject(CObject::TYPE::ENEMY);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// エネミータグの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// エネミーへダウンキャスト
		CEnemy* pEnemy = CUtility::GetInstance()->DownCast<CEnemy, CObject>(pObject[nCntObj]);

		// エネミーと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pEnemy->GetPos(), pEnemy->GetSize(), m_posTarget, GetSize()))
		{
			if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying))
			{ // 飛行状態の場合

				// 押し出し処理
				CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pEnemy->GetPos(), pEnemy->GetSize());

				// エネミーを破棄
				pEnemy->SetRelease();
			}
			else
			{
				// ミス状態に移行
				m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);
			}

			// 衝突判定を出す
			bDetected = 1;

			// 死亡音
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}

	// ゴールオブジェクトを取得
	CGoal* pGoal = CUtility::GetInstance()->DownCast<CGoal, CObject>(CObject::FindObject(CObject::TYPE::GOAL));

	// ゴールと衝突する場合
	if (CUtility::GetInstance()->SphereAndCube(pGoal->GetPos(), pGoal->GetSize().x, m_posTarget, GetSize()))
	{
		// ゴール状態に移行
		m_pStateManager->SetPendingState(CPlayerState::STATE::GOAL);

		// ウェーブを強制終了
		CFakeScreen::GetInstance()->StopWave();

		// レベル終了フェーズへ移行
		CFakeScreen::GetInstance()->SetWave(CGameManager::PHASE::FINISH);

		// ゴール音
		CSound::GetInstance()->Play(CSound::LABEL::GOAL);
	}

	// アチーブオブジェクトを取得
	if (CObject::FindObject(CObject::TYPE::ACHIEVE))
	{
		CAchieve* pAchieve = CUtility::GetInstance()->DownCast<CAchieve, CObject>(CObject::FindObject(CObject::TYPE::ACHIEVE));

		// アチーブと衝突する場合
		if (CUtility::GetInstance()->SphereAndCube(pAchieve->GetPos(), pAchieve->GetSize().x, m_posTarget, GetSize()))
		{
			// 破棄予約
			pAchieve->SetRelease();

			// 取得音
			CSound::GetInstance()->Play(CSound::LABEL::GET);
		}
	}

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
// 目標加速度を取得
//============================================================================
D3DXVECTOR3 CPlayer::GetVelocityTarget()
{
	return m_velocityTarget;
}

//============================================================================
// 目標加速度を設定
//============================================================================
void CPlayer::SetVelocityTarget(D3DXVECTOR3 velocityTarget)
{
	m_velocityTarget = velocityTarget;
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