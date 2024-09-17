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
#include "utility.h"
#include "sound.h"

// インプット取得用
#include "manager.h"

// デバッグ表示用
#include "renderer.h"

// オブジェクト情報用
#include "arrow.h"
#include "ring.h"
#include "object_2D.h"
#include "ripple.h"
#include "smoke.h"
#include "star.h"
#include "start.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
const float CPlayerStateDefault::MAX_WALK_VELOCITY = 1.5f;	// 歩行時の最大加速度
const float CPlayerStateDefault::BRAKING_WALK_SPEED = 0.8f;	// 歩行時の制動力
const int CPlayerStateBeginning::BEGIN_CNT_MAX = 20;		// 変身必要時間
const float CPlayerStateBeginning::BEGIN_FLOATING = 1.25f;	// 変身時上昇量
const float CPlayerStateBeginning::BEGIN_SPINNING = 0.5f;	// 変身時回転量
const float CPlayerStateFlying::MAX_FLY_VELOCITY =	10.0f;	// 飛行時の最大加速度 (飛行速度以上推奨)
const float CPlayerStateFlying::FLY_SPEED = 3.5f;			// 飛行速度
const int CPlayerStateCharging::MAX_LIMITCHARGE = 120;		// 最大チャージ猶予
const int CPlayerStateStopping::STOP_CNT_MAX = 25;			// 変身停止必要時間
const float CPlayerStateStopping::RECOIL_SPEED = 4.0f;		// 反動移動速度
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
	m_pPlayer = nullptr;	// プレイヤーのポインタを初期化
}

//============================================================================
// プレイヤーを登録
//============================================================================
void CPlayerState::RegisterPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}



//============================================================================
// 
// プレイヤー通常状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateDefault::CPlayerStateDefault() : 
	m_OldRotTarget{ 0.0f, 0.0f, 0.0f }
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
	// X・Y軸の向きをリセット
	m_pPlayer->SetRot(D3DXVECTOR3{ 0.0f, 0.0f, m_pPlayer->GetRot().z });

	// 目標向きをリセット
	m_pPlayer->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });

	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_000) };

	// モデルの設定
	m_pPlayer->BindModel(Model);

	// サイズを設定
	m_pPlayer->SetSize(Model->size);
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateDefault::Update()
{
	// 操作
	if (!Control())
	{
		// 変更開始状態になっていたら終了
		return;
	}

	// 回転
	Rotation();

	// 重力加速
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };
	CUtility::GetInstance()->Gravity(NewVelocity);
	m_pPlayer->SetVelocity(NewVelocity);

	// 加速度を減衰
	NewVelocity.x = CUtility::GetInstance()->AdjustToTarget(NewVelocity.x, 0.0f, 0.1f);
	m_pPlayer->SetVelocity(NewVelocity);

	// 制動調整
	Braking();

	// 加速度分、目標座標を変動
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
	NewPosTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(NewPosTarget);

	// 目標サイズへ拡大
	m_pPlayer->SetScale(CUtility::GetInstance()->AdjustToTarget(m_pPlayer->GetScale(), 1.0f, 0.1f));

	// 当たり判定
	m_pPlayer->Collision();

	// 一定以上落下すると
	if (m_pPlayer->GetPosTarget().y < -300.0f)
	{
		// 死亡状態に変更
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::MISS);
	}
}

//============================================================================
// 変更終了
//============================================================================
void CPlayerStateDefault::Exit()
{

}

//============================================================================
// 移動
//============================================================================
bool CPlayerStateDefault::Control()
{
	// キーボード取得
	CInputKeyboard* pKeyboard{ CManager::GetKeyboard() };

	// パッド取得
	CInputPad* pPad{ CManager::GetPad() };

	// 移動方向用
	bool bMove{ false };
	float X{ 0.0f };

	// スティックのX軸の傾きを取得
	X = pPad->GetJoyStickL().X;

	// X軸
	if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::LEFT))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::RIGHT))
	{
		X = 1.0f;
	}

	// 何か入力していれば移動判定を出す
	if (X != 0.0f)
	{
		bMove = true;
	}

	if (bMove)
	{
		// 入力方向に加速度を設定
		D3DXVECTOR3 NewVeloctiy{ m_pPlayer->GetVelocity() };
		NewVeloctiy.x += sinf(atan2f(X, 0.0f)) * 0.25f;
		m_pPlayer->SetVelocity(NewVeloctiy);

		// 入力方向にモデルの目標向きを設定
		D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };
		NewRotTarget.y = atan2f(X, 0.0f);
		m_pPlayer->SetRotTarget(NewRotTarget);
	}

	// 変身
	if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::A) || pPad->GetTrigger(CInputPad::JOYKEY::B) ||
		pPad->GetTrigger(CInputPad::JOYKEY::X) || pPad->GetTrigger(CInputPad::JOYKEY::Y))
	{
		// Y方向への加速度が無ければ変身
		if (m_pPlayer->GetVelocity().y == 0.0f)
		{
			// 変身開始状態へ変更
			m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::BEGINNING);

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
	// 新しい向き情報を作成
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };

	// 目標向きを綺麗に追いかけるように、Y軸の向きを補正
	if (NewRotTarget.y > 0.0f && m_OldRotTarget.y < 0.0f)
	{
		NewRot.y += D3DX_PI * 2.0f;
	}
	else if (NewRotTarget.y < 0.0f && m_OldRotTarget.y > 0.0f)
	{
		NewRot.y += D3DX_PI * -2.0f;
	}

	// 目標向きへ補正
	NewRot = CUtility::GetInstance()->AdjustToTarget(NewRot, NewRotTarget, 0.1f);

	// 新しい向き情報を反映
	m_pPlayer->SetRot(NewRot);

	// 目標向きを記録
	m_OldRotTarget = NewRotTarget;
}

//============================================================================
// 制動調整
//============================================================================
void CPlayerStateDefault::Braking()
{
	// 新しい加速度を作成
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };

	// 加速度上限に到達で速度固定
	if (NewVelocity.x > MAX_WALK_VELOCITY)
	{
		NewVelocity.x = MAX_WALK_VELOCITY;
	}
	else if (NewVelocity.x < -MAX_WALK_VELOCITY)
	{
		NewVelocity.x = -MAX_WALK_VELOCITY;
	}

	// 新しい加速度を反映
	m_pPlayer->SetVelocity(NewVelocity);
}

//============================================================================
// 反動
//============================================================================
void CPlayerStateDefault::Recoil()
{

}



//============================================================================
// 
// プレイヤー変身開始状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateBeginning::CPlayerStateBeginning() :
	m_nCntMetamorphose{ 0 }
{

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
	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_001) };

	// モデルの設定
	m_pPlayer->BindModel(Model);

	// サイズを設定
	m_pPlayer->SetSize(Model->size);

	// 爆発音
	CSound::GetInstance()->Play(CSound::LABEL::EXPLOSION);

	// 変身音
	CSound::GetInstance()->Play(CSound::LABEL::METAMORPHOSE);
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
		D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
		NewPosTarget.y += BEGIN_FLOATING;
		m_pPlayer->SetPosTarget(NewPosTarget);

		// Y軸向きを高速回転し、Z軸向きはリセット
		D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
		NewRot.y = NewPosTarget.y * BEGIN_SPINNING;
		NewRot.z = 0.0f;
		m_pPlayer->SetRot(NewRot);

		// 当たり判定
		if (m_pPlayer->Collision())
		{
			// この時、判定により死亡状態に移行するなら強制終了
			if (m_pPlayer->GetStateManager()->GetPendingState() == CPlayerState::STATE::MISS)
			{
				return;
			}

			// 何かに衝突で通常状態へ
			m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::DEFAULT);

			// 衝突音
			CSound::GetInstance()->Play(CSound::LABEL::STOP);

			// 死亡音
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}
	else
	{
		// 状態変更
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::FLYING);
	}
}

//============================================================================
// 変更終了
//============================================================================
void CPlayerStateBeginning::Exit()
{
	// 加速度を初期化
	m_pPlayer->SetVelocity(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });

	// 目標加速度を初期化
	m_pPlayer->SetVelocityTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });

	// 飛行方向を初期化
	m_pPlayer->SetAngleFlying(0.0f);

	// Y軸の向きをリセット
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	NewRot.y = 0.0f;
	m_pPlayer->SetRot(NewRot);

	// Z軸の目標向きをリセット
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };
	NewRotTarget.z = 0.0f;
	m_pPlayer->SetRotTarget(NewRotTarget);
}



//============================================================================
// 
// プレイヤー飛行状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateFlying::CPlayerStateFlying() :
	m_OldRotTarget{ 0.0f, 0.0f, 0.0f }
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
	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_002) };

	// モデルの設定
	m_pPlayer->BindModel(Model);

	// サイズを設定
	m_pPlayer->SetSize(Model->size);

	// エフェクト生成
	for (int i = 0; i < 10; i++)
	{
		// ランダムな加速度を作成
		D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

		// 煙を生成
		CSmoke::Create(
			m_pPlayer->GetPos(),		// 座標
			RandomVelocity * 0.0075f);	// 加速度
	}
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateFlying::Update()
{
	// 飛行
	if (!Control())
	{
		return;
	}

	// 回転
	Rotation();

	// 制動調整
	Braking();

	// 加速度分、目標座標を変動
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
	NewPosTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(NewPosTarget);
	
	// この時点での加速度を保持
	D3DXVECTOR3 OldVelocity{ m_pPlayer->GetVelocity() };

	// 当たり判定
	if (m_pPlayer->Collision())
	{
		// この時、判定により死亡状態に移行するなら強制終了
		if (m_pPlayer->GetStateManager()->GetPendingState() == CPlayerState::STATE::MISS)
		{
			return;
		}

		// 何かに衝突で変身停止へ
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::STOPPING);

		// 横方向に衝突しているなら
		if (m_pPlayer->GetVelocity().x == 0.0f)
		{
			// 横方向の反射ベクトルを代入しておく
			OldVelocity.x *= -1.0f;
		}

		// 縦方向に衝突しているなら
		if (m_pPlayer->GetVelocity().y == 0.0f)
		{
			// 縦方向の反射ベクトルを代入しておく
			OldVelocity.y *= -1.0f;
		}
		
		m_pPlayer->SetVelocity(OldVelocity);

		// 衝突音
		CSound::GetInstance()->Play(CSound::LABEL::STOP);

		// バウンド音
		CSound::GetInstance()->Play(CSound::LABEL::BOUND);
	}
}

//============================================================================
// 変更終了
//============================================================================
void CPlayerStateFlying::Exit()
{

}

//============================================================================
// 操縦
//============================================================================
bool CPlayerStateFlying::Control()
{
	// キーボード取得
	CInputKeyboard* pKeyboard{ CManager::GetKeyboard() };

	// パッド取得
	CInputPad* pPad{ CManager::GetPad() };

	// 移動方向用
	bool bMove{ false };
	float X{ 0.0f }, Y{ 0.0f };

	// スティックの傾きを取得
	X = pPad->GetJoyStickL().X;
	Y = pPad->GetJoyStickL().Y;

	// X軸
	if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::LEFT))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::RIGHT))
	{
		X = 1.0f;
	}

	// Y軸
	if (pKeyboard->GetPress(DIK_W) || pPad->GetPress(CInputPad::JOYKEY::UP))
	{
		Y = 1.0f;
	}
	else if (pKeyboard->GetPress(DIK_S) || pPad->GetPress(CInputPad::JOYKEY::DOWN))
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
		// 飛行方向を設定
		m_pPlayer->SetAngleFlying(atan2f(X, Y));
	
		// モデルの目標向きを設定
		D3DXVECTOR3 NewRotTarget{ 0.0f, 0.0f, 0.0f };
		NewRotTarget.z = atan2f(-X, Y);
		m_pPlayer->SetRotTarget(NewRotTarget);
	}

	// 目標加速度を設定
	D3DXVECTOR3 NewVelocityTarget{ 0.0f, 0.0f, 0.0f };
	NewVelocityTarget.x = sinf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	NewVelocityTarget.y = cosf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	m_pPlayer->SetVelocityTarget(NewVelocityTarget);

//#ifdef _DEBUG
//	// 目標加速度をデバッグ表示
//	CRenderer::GetInstance()->SetDebugString("【　目標加速度　】");
//	std::ostringstream oss;
//	oss << std::fixed << std::setprecision(3) << "X:" << m_pPlayer->GetVelocityTarget().x << "\nY:" << m_pPlayer->GetVelocityTarget().y;
//	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());
//#endif // _DEBUG

	// 現在の加速度を取得
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };

//#ifdef _DEBUG
//	// 現在の加速度をデバッグ表示
//	CRenderer::GetInstance()->SetDebugString("【　現在の加速度　】");
//	std::ostringstream oss1;
//	oss1 << std::fixed << std::setprecision(3) << "X:" << NewVelocity.x << "\nY:" << NewVelocity.y;
//	CRenderer::GetInstance()->SetDebugString(oss1.str().c_str());
//#endif // _DEBUG

	// 現在の加速度を補正
	NewVelocity += (m_pPlayer->GetVelocityTarget() - NewVelocity) * 0.1f;

	// 変更した加速度を反映
	m_pPlayer->SetVelocity(NewVelocity);

	// エフェクト生成
	if (rand() % 3 == 0)
	{
		// 波紋を生成
		CRipple::Create(
			m_pPlayer->GetPos() + (-NewVelocity * 5.0f),	// 座標
			-NewVelocity);									// 加速度 (飛行方向の逆)

		// 星を生成
		CStar::Create(
			m_pPlayer->GetPos() + (-NewVelocity * 5.0f),	// 座標
			-NewVelocity);									// 加速度 (飛行方向の逆)
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::A) || pPad->GetTrigger(CInputPad::JOYKEY::B) ||
		pPad->GetTrigger(CInputPad::JOYKEY::X) || pPad->GetTrigger(CInputPad::JOYKEY::Y))
	{
		// 溜め状態に移行
		m_pPlayer->GetStateManager()->SetPendingState(STATE::CHARGING);
	}

	return true;
}

//============================================================================
// 回転
//============================================================================
void CPlayerStateFlying::Rotation()
{
	// 新しい向き情報を作成
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };

	// 目標向きを綺麗に追いかけるように、Z軸の向きを補正
	if (NewRotTarget.z > 0.0f && m_OldRotTarget.z < 0.0f)
	{
		NewRot.z += D3DX_PI * 2.0f;
	}
	else if (NewRotTarget.z < 0.0f && m_OldRotTarget.z > 0.0f)
	{
		NewRot.z += D3DX_PI * -2.0f;
	}

	// 目標向きへ補正
	NewRot = CUtility::GetInstance()->AdjustToTarget(NewRot, NewRotTarget, 0.1f);

	// 新しい向き情報を反映
	m_pPlayer->SetRot(NewRot);

	// 目標向きを記録
	m_OldRotTarget = NewRotTarget;
}

//============================================================================
// 制動調整
//============================================================================
void CPlayerStateFlying::Braking()
{
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };

	// 加速度上限に到達で速度固定
	if (NewVelocity.x > MAX_FLY_VELOCITY)
	{
		NewVelocity.x = MAX_FLY_VELOCITY;
	}
	else if (NewVelocity.x < -MAX_FLY_VELOCITY)
	{
		NewVelocity.x = -MAX_FLY_VELOCITY;
	}

	if (NewVelocity.y > MAX_FLY_VELOCITY)
	{
		NewVelocity.y = MAX_FLY_VELOCITY;
	}
	else if (NewVelocity.y < -MAX_FLY_VELOCITY)
	{
		NewVelocity.y = -MAX_FLY_VELOCITY;
	}

	m_pPlayer->SetVelocity(NewVelocity);
}



//============================================================================
// 
// プレイヤー溜め状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateCharging::CPlayerStateCharging() :
	m_OldRotTarget{ 0.0f, 0.0f, 0.0f },
	m_rotHold{ 0.0f, 0.0f, 0.0f },
	m_nLimitCharge{ 0 },
	m_pArrow{ nullptr },
	m_fArrowSize{ 0.0f },
	m_pRing{ nullptr },
	m_fRingSize{ 0.0f }
{
	// リングの生成 (先行)
	m_pRing = CRing::Create();

	// 矢印の生成
	m_pArrow = CArrow::Create();
}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateCharging::~CPlayerStateCharging()
{
	// 矢印の破棄
	if (m_pArrow)
	{
		// 消滅予約
		m_pArrow->SetDisappear();
	
		// ポインタを初期化
		m_pArrow = nullptr;
	}

	// リングの破棄
	if (m_pRing)
	{
		// 消滅予約
		m_pRing->SetDisappear();

		// ポインタを初期化
		m_pRing = nullptr;
	}
}

//============================================================================
// 変更開始
//============================================================================
void CPlayerStateCharging::Enter()
{
	// 出現設定
	m_pArrow->SetAppear();
	m_pRing->SetAppear();

	// UI初期座標を設定
	m_pArrow->SetPos(m_pPlayer->GetPos());
	m_pRing->SetPos(m_pPlayer->GetPos());

	// 矢印用のホールド向きに、モデルの向ている方向を設定
	D3DXVECTOR3 NewRot{ 0.0f, 0.0f, -m_pPlayer->GetRot().z };
	m_rotHold = NewRot;

	// UI初期サイズを設定
	m_fArrowSize = 30.0f;
	m_pArrow->SetSize({ m_fArrowSize, m_fArrowSize, 0.0f });
	m_fRingSize = 27.5f;
	m_pRing->SetSize({ m_fRingSize, m_fRingSize, 0.0f });
	m_pRing->SetSizeTarget({ m_fRingSize, m_fRingSize, 0.0f });

	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_004) };

	// モデルの設定
	m_pPlayer->BindModel(Model);

	// サイズを設定
	m_pPlayer->SetSize(Model->size);

	// チャージ音
	CSound::GetInstance()->Play(CSound::LABEL::CHARGE);
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateCharging::Update()
{ 
	// チャージが終わると強制終了
	if (m_nLimitCharge > MAX_LIMITCHARGE)
	{
		// 通常状態へ
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::DEFAULT);

		return;
	}

	// チャージ猶予カウント
	m_nLimitCharge++;

	// パッド取得
	CInputPad* pPad{ CManager::GetPad() };

	// 回転
	Rotation();

	// 加速度減衰
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };
	NewVelocity = CUtility::GetInstance()->AdjustToTarget(NewVelocity, D3DXVECTOR3{ 0.0f, 0.0f, 0.0f }, 0.2f);
	m_pPlayer->SetVelocity(NewVelocity);

	// 加速度分、目標座標を変動
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
	NewPosTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(NewPosTarget);

	// エフェクト生成
	if (rand() % 5 == 0)
	{
		// ランダムな加速度を作成
		D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

		// 星を生成
		CStar::Create(
			m_pPlayer->GetPos() + RandomVelocity * 2.0f,	// 座標
			RandomVelocity);								// 加速度 (ランダム)
	}

	// この時点での加速度を保持
	D3DXVECTOR3 OldVelocity{ m_pPlayer->GetVelocity() };

	// 当たり判定
	if (m_pPlayer->Collision())
	{
		// この時、判定により死亡状態に移行するなら強制終了
		if (m_pPlayer->GetStateManager()->GetPendingState() == CPlayerState::STATE::MISS)
		{
			return;
		}

		// 何かに衝突で変身停止へ
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::STOPPING);

		// 横方向に衝突しているなら
		if (m_pPlayer->GetVelocity().x == 0.0f)
		{
			// 横方向の反射ベクトルを代入しておく
			OldVelocity.x *= -1.0f;
		}

		// 縦方向に衝突しているなら
		if (m_pPlayer->GetVelocity().y == 0.0f)
		{
			// 縦方向の反射ベクトルを代入しておく
			OldVelocity.y *= -1.0f;
		}

		m_pPlayer->SetVelocity(OldVelocity);

		// 衝突音
		CSound::GetInstance()->Play(CSound::LABEL::STOP);

		// バウンド音
		CSound::GetInstance()->Play(CSound::LABEL::BOUND);
	}

	// 矢印の更新を行う
	UpdateArrow();

	// 突進状態へ
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::A) || pPad->GetTrigger(CInputPad::JOYKEY::B) ||
		pPad->GetTrigger(CInputPad::JOYKEY::X) || pPad->GetTrigger(CInputPad::JOYKEY::Y))
	{
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::RUSHING);
	}
}

//============================================================================
// 変更終了
//============================================================================
void CPlayerStateCharging::Exit()
{
	// X・Y軸回転をリセット
	D3DXVECTOR3 NweRot{ m_pPlayer->GetRot() };
	NweRot.x = 0.0f;
	NweRot.y = 0.0f;
	m_pPlayer->SetRot(NweRot);

	// 矢印の向いている方向を飛行角度に設定
	m_pPlayer->SetAngleFlying(-m_pArrow->GetRot().z * 2.0f);
}

//============================================================================
// 回転
//============================================================================
void CPlayerStateCharging::Rotation()
{
	// 向き情報を取得
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };

#ifdef _DEBUG
	CRenderer::GetInstance()->SetDebugString("【現在の向き :" + std::to_string(NewRot.z) + "】");
	CRenderer::GetInstance()->SetDebugString("【目標の向き :" + std::to_string(NewRotTarget.z) + "】");
#endif // _DEBUG

	// 目標向きを綺麗に追いかけるように、Z軸の向きを補正
	if (NewRotTarget.z > 0.0f && m_OldRotTarget.z < 0.0f)
	{
		NewRot.z += D3DX_PI * 2.0f;
#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("なんなんなんなんなんなんなんなんなん", 60);
#endif // _DEBUG
	}
	else if (NewRotTarget.z < 0.0f && m_OldRotTarget.z > 0.0f)
	{
		NewRot.z += D3DX_PI * -2.0f;
#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("おんおんおんおんおんおんおんおんおん", 60);
#endif // _DEBUG
	}

	// 目標向きへ補正
	NewRot = CUtility::GetInstance()->AdjustToTarget(NewRot, NewRotTarget, 0.1f);

	// 震える
	NewRot.x = CUtility::GetInstance()->GetRandomValue<float>() * 0.00025f;
	NewRot.y = CUtility::GetInstance()->GetRandomValue<float>() * 0.00025f;

	// 向き情報設定
	m_pPlayer->SetRot(NewRot);

	// 目標向きを記録
	m_OldRotTarget = NewRotTarget;
}

//============================================================================
// 矢印の更新を行う
//============================================================================
void CPlayerStateCharging::UpdateArrow()
{
	// キーボード取得
	CInputKeyboard* pKeyboard{ CManager::GetKeyboard() };

	// パッド取得
	CInputPad* pPad{ CManager::GetPad() };

	// 新たな向きを作成
	D3DXVECTOR3 NewRot{ m_rotHold };

	// 移動方向用
	bool bMove{ false };
	float X{ 0.0f }, Y{ 0.0f };

	// スティックの傾きを取得
	X = pPad->GetJoyStickL().X;
	Y = pPad->GetJoyStickL().Y;

	// X軸
	if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::LEFT))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::RIGHT))
	{
		X = 1.0f;
	}

	// Y軸
	if (pKeyboard->GetPress(DIK_W) || pPad->GetPress(CInputPad::JOYKEY::UP))
	{
		Y = 1.0f;
	}
	else if (pKeyboard->GetPress(DIK_S) || pPad->GetPress(CInputPad::JOYKEY::DOWN))
	{
		Y = -1.0f;
	}

	// 何か入力していれば移動判定を出す
	if (X != 0.0f || Y != 0.0f)
	{
		bMove = true;
	}

	// 移動判定が出ていれば
	if (bMove)
	{
		// 新しい向きを設定
		NewRot.z = atan2f(X, Y);

		// この方向をモデルの目標向きに設定
		m_pPlayer->SetRotTarget(D3DXVECTOR3{  0.0f, 0.0f, -NewRot.z });
	}

	// 矢印に新しい向きを反映
	m_pArrow->SetRot(-NewRot * 0.5f);

	// ホールド向きに記録
	m_rotHold = NewRot;

	// 矢印の目標サイズを縮小
	D3DXVECTOR3 NewArrowSizeTarget{ m_pArrow->GetSizeTarget() };
	NewArrowSizeTarget.x = m_fArrowSize - ((m_fArrowSize / MAX_LIMITCHARGE) * (m_nLimitCharge));
	NewArrowSizeTarget.y = m_fArrowSize - ((m_fArrowSize / MAX_LIMITCHARGE) * (m_nLimitCharge));
	m_pArrow->SetSizeTarget(NewArrowSizeTarget);

	// リングの目標サイズを縮小
	D3DXVECTOR3 NewRingSizeTarget{ m_pRing->GetSizeTarget() };
	NewRingSizeTarget.x = m_fRingSize - ((m_fRingSize / MAX_LIMITCHARGE) * (m_nLimitCharge));
	NewRingSizeTarget.y = m_fRingSize - ((m_fRingSize / MAX_LIMITCHARGE) * (m_nLimitCharge));
	m_pRing->SetSizeTarget(NewRingSizeTarget);

	// 新たな座標を作成
	D3DXVECTOR3 NewPos{ 0.0f, 0.0f, 0.0f };

	// プレイヤー座標を取得
	NewPos = m_pPlayer->GetPos();

	// リングへ座標を反映
	m_pRing->SetPos(NewPos);

	// 座標を補正
#if 0
	// 移動方向から角度を抜き出す
	float fAngle{ atan2f(m_pPlayer->GetVelocity().x, m_pPlayer->GetVelocity().y) };

	// プレイヤーの座標を基点に、移動していた方向の延長線上に出現する
	newPos += {
		sinf(fAngle) * 20.0f,
		cosf(fAngle) * 20.0f,
		0.0f
	};
#elif 0
	// 移動方向から角度を抜き出す
	float fAngle{ atan2f(m_pPlayer->GetVelocity().x, m_pPlayer->GetVelocity().y) };

	// プレイヤーの座標を基点に、向きに合わせて円を描くように出現する
	newPos += {
		sinf(-newRot.z * 2.0f) * 20.0f,
		cosf(-newRot.z * 2.0f) * 20.0f,
		0.0f
	};
#elif 1
	// 移動方向の延長線上へずらす
	/* 振り向き時などプレイヤーの移動方向とモデルの向きがずれるため、今回は見た目の角度を基にする */
	//newPos += {
	//	sinf(newRot.z) * (10.0f - ((10.0f / 120) * (m_nLimitCharge))),
	//	cosf(newRot.z) * (10.0f - ((10.0f / 120) * (m_nLimitCharge))),
	//	0.0f
	//};

	//// ずらされた座標を基点に弧を描くように移動
	//newPos += {
	//	sinf(newRot.z) * (20.0f - ((20.0f / 120) * (m_nLimitCharge))),
	//	cosf(newRot.z) * (20.0f - ((20.0f / 120) * (m_nLimitCharge))),
	//	0.0f
	//};
#endif

	// 矢印へ座標を反映
	m_pArrow->SetPos(NewPos);
}



//============================================================================
// 
// プレイヤー突撃状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateRushing::CPlayerStateRushing() :
	m_OldRotTarget{ 0.0f, 0.0f, 0.0f }
{

}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateRushing::~CPlayerStateRushing()
{

}

//============================================================================
// 変更開始
//============================================================================
void CPlayerStateRushing::Enter()
{
	// 目標向きを設定
	D3DXVECTOR3 NewRotTarget{ 0.0f, 0.0f, -m_pPlayer->GetAngleFlying() };
	m_pPlayer->SetRotTarget(NewRotTarget);

	// 飛行角度から新たな加速度を作成
	D3DXVECTOR3 NewVelocity{ sinf(m_pPlayer->GetAngleFlying()),cosf(m_pPlayer->GetAngleFlying()), 0.0f };

	// 加速度を設定
	m_pPlayer->SetVelocity(NewVelocity * 5.0f);

#ifdef _DEBUG
	// 新たな加速度を表示
	CRenderer::GetInstance()->SetTimeString("【設定されている飛行角度】" + std::to_string(m_pPlayer->GetAngleFlying()), 600);
	CRenderer::GetInstance()->SetTimeString("【飛行方向から設定した新たな加速度】" + std::to_string(NewVelocity.x) + " : " + std::to_string(NewVelocity.y), 600);
#endif

	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_005) };

	// モデルの設定
	m_pPlayer->BindModel(Model);

	// サイズを設定
	m_pPlayer->SetSize(Model->size);

	// 突進音
	CSound::GetInstance()->Play(CSound::LABEL::RUSH);
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateRushing::Update()
{
	// 回転
	Rotation();

	// 加速度分、目標座標を変動
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
	NewPosTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(NewPosTarget);

	// エフェクト生成
	if (rand() % 2 == 0)
	{
		// ランダムな加速度を作成
		D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

		// 煙を生成
		CSmoke::Create(
			m_pPlayer->GetPos() - (m_pPlayer->GetVelocity() * 5.0f) + RandomVelocity,	// 座標
			m_pPlayer->GetVelocity());													// 加速度 (飛行方向)

		// 星を生成
		CStar::Create(
			m_pPlayer->GetPos() - m_pPlayer->GetVelocity() + RandomVelocity * 5.0f,	// 座標
			-m_pPlayer->GetVelocity());												// 加速度 (飛行方向の逆)
		
		// 波紋を生成
		CRipple::Create(
			m_pPlayer->GetPos() - m_pPlayer->GetVelocity() + RandomVelocity * 5.0f,	// 座標
			-m_pPlayer->GetVelocity());												// 加速度 (飛行方向の逆)
	}

	// この時点での加速度を保持
	D3DXVECTOR3 OldVelocity{ m_pPlayer->GetVelocity() };

	// 当たり判定
	if (m_pPlayer->Collision())
	{
		// この時、判定により死亡状態に移行するなら強制終了
		if (m_pPlayer->GetStateManager()->GetPendingState() == CPlayerState::STATE::MISS)
		{
			return;
		}

		// 何かに衝突で変身停止へ
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::STOPPING);

		// 横方向に衝突しているなら
		if (m_pPlayer->GetVelocity().x == 0.0f)
		{
			// 横方向の反射ベクトルを代入しておく
			OldVelocity.x *= -1.0f;
		}
		
		// 縦方向に衝突しているなら
		if (m_pPlayer->GetVelocity().y == 0.0f)
		{
			// 縦方向の反射ベクトルを代入しておく
			OldVelocity.y *= -1.0f;
		}

		m_pPlayer->SetVelocity(OldVelocity);

		// 衝突音
		CSound::GetInstance()->Play(CSound::LABEL::STOP);

		// バウンド音
		CSound::GetInstance()->Play(CSound::LABEL::BOUND);
	}

#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::STOPPING);
	}
#endif // _DEBUG
}

//============================================================================
// 変更終了
//============================================================================
void CPlayerStateRushing::Exit()
{
	// X・Y軸の向きを少し大げさに設定
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	NewRot.x = CUtility::GetInstance()->GetRandomValue<float>() * 0.003f;
	NewRot.y = CUtility::GetInstance()->GetRandomValue<float>() * 0.003f;
	m_pPlayer->SetRot(NewRot);
}

//============================================================================
// 回転
//============================================================================
void CPlayerStateRushing::Rotation()
{
	// 向き情報を取得
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };

	// 目標向きを綺麗に追いかけるように、Z軸の向きを補正
	if (NewRotTarget.z > 0.0f && m_OldRotTarget.z < 0.0f)
	{
		NewRot.z += D3DX_PI * 2.0f;
	}
	else if (NewRotTarget.z < 0.0f && m_OldRotTarget.z > 0.0f)
	{
		NewRot.z += D3DX_PI * -2.0f;
	}

	// 目標向きへ補正
	NewRot = CUtility::GetInstance()->AdjustToTarget(NewRot, NewRotTarget, 0.1f);

	// 震える
	NewRot.x = CUtility::GetInstance()->GetRandomValue<float>() * 0.001f;
	NewRot.y = CUtility::GetInstance()->GetRandomValue<float>() * 0.001f;

	// 向き情報設定
	m_pPlayer->SetRot(NewRot);

	// 目標向きを記録
	m_OldRotTarget = NewRotTarget;
}



//============================================================================
// 
// プレイヤー変身停止状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateStopping::CPlayerStateStopping() :
	m_OldRotTarget{ 0.0f, 0.0f, 0.0f },
	m_nCntStopMetamorphose{ 0 }
{

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
	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_003) };

	// モデルの設定
	m_pPlayer->BindModel(Model);

	// サイズを設定
	m_pPlayer->SetSize(Model->size);

	// エフェクトを生成
	for (int i = 0; i < 10; i++)
	{
		// ランダムな加速度を作成
		D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

		// 煙を生成
		CSmoke::Create(
			m_pPlayer->GetPos(),		// 座標
			RandomVelocity * 0.0075f);	// 加速度
	}

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
		Rotation();

		// 重力加速
		D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };
		CUtility::GetInstance()->Gravity(NewVelocity);
		m_pPlayer->SetVelocity(NewVelocity);

		// 加速度を減衰
		m_pPlayer->SetVelocity(CUtility::GetInstance()->AdjustToTarget(m_pPlayer->GetVelocity(), D3DXVECTOR3{ 0.0f, 0.0f, 0.0f }, 0.05f));

		// 加速度分、目標座標を変動
		D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
		NewPosTarget += m_pPlayer->GetVelocity();
		m_pPlayer->SetPosTarget(NewPosTarget);

		// この時点での加速度を保持
		D3DXVECTOR3 OldVelocity{ m_pPlayer->GetVelocity() };

		// 当たり判定
		if (m_pPlayer->Collision())
		{
			// ランダムな加速度を作成
			D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

			// 煙を生成
			CSmoke* pSmoke = CSmoke::Create(
				m_pPlayer->GetPos(),		// 座標
				RandomVelocity * 0.0075f);	// 加速度

			// 小さめに
			pSmoke->SetScale(0.5f);

			// 横方向に衝突しているなら
			if (m_pPlayer->GetVelocity().x == 0.0f)
			{
				// 横方向の反射ベクトルを代入しておく
				OldVelocity.x *= -1.0f;
			}

			// 縦方向に衝突しているなら
			if (m_pPlayer->GetVelocity().y == 0.0f)
			{
				// 縦方向の反射ベクトルを代入しておく
				OldVelocity.y *= -1.0f;

				OldVelocity.y *= 0.9f;
			}

			// 加速度を反映
			m_pPlayer->SetVelocity(OldVelocity);
		}
	}
	else
	{
		// 通常状態に変更
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::DEFAULT);
	}
}

//============================================================================
// 変更終了
//============================================================================
void CPlayerStateStopping::Exit()
{
	// 目標向きをリセット
	m_pPlayer->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });

	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_000) };

	// モデルの設定
	m_pPlayer->BindModel(Model);

	// サイズを設定
	m_pPlayer->SetSize(Model->size);
}

//============================================================================
// 回転
//============================================================================
void CPlayerStateStopping::Rotation()
{
	// 新しい向き情報を作成
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	D3DXVECTOR3 NewRotTarget{ m_pPlayer->GetRotTarget() };

	// 目標向きを綺麗に追いかけるように、Z軸の向きを補正
	if (NewRotTarget.z > 0.0f && m_OldRotTarget.z < 0.0f)
	{
		NewRot.z += D3DX_PI * 2.0f;
	}
	else if (NewRotTarget.y < 0.0f && m_OldRotTarget.z > 0.0f)
	{
		NewRot.z += D3DX_PI * -2.0f;
	}

	// 目標向きへ補正
	NewRot = CUtility::GetInstance()->AdjustToTarget(NewRot, NewRotTarget, 0.1f);

	// 新しい向き情報を反映
	m_pPlayer->SetRot(NewRot);

	// 目標向きを記録
	m_OldRotTarget = NewRotTarget;
}

//============================================================================
// 反動
//============================================================================
void CPlayerStateStopping::Recoil()
{
	// 衝突寸前の加速度を取得
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };

#ifdef _DEBUG
	CRenderer::GetInstance()->SetTimeString("\n衝突時の加速度X : " + std::to_string(NewVelocity.x), 120);
	CRenderer::GetInstance()->SetTimeString("衝突時の加速度Y : " + std::to_string(NewVelocity.y), 120);
#endif	// _DEBUG

	// 寸前の加速度の角度を算出
	float fNewFlyingAngle{ atan2f(NewVelocity.x, NewVelocity.y) };

	// 真逆の角度方向に加速度を設定
	NewVelocity.x = sinf(fNewFlyingAngle) * RECOIL_SPEED;
	NewVelocity.y = cosf(fNewFlyingAngle) * RECOIL_SPEED;

	//newVelocity.x = sinf(fNewFlyingAngle) * (fabsf(newVelocity.x) + fabsf(newVelocity.y));
	//newVelocity.y = cosf(fNewFlyingAngle) * (fabsf(newVelocity.x) + fabsf(newVelocity.y));

#ifdef _DEBUG
	CRenderer::GetInstance()->SetTimeString("衝突後の加速度X : " + std::to_string(NewVelocity.x), 120);
	CRenderer::GetInstance()->SetTimeString("衝突後の加速度Y : " + std::to_string(NewVelocity.y), 120);
#endif	// _DEBUG

	m_pPlayer->SetVelocity(NewVelocity);
}



//============================================================================
// 
// プレイヤー失敗状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateMistook::CPlayerStateMistook() :
	m_PosStartObject{ 0.0f, 0.0f, 0.0f }
{

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
	// 向きを初期化
	m_pPlayer->SetRot({ 0.0f, 0.0f, 0.0f });

	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_006) };

	// モデルの設定
	m_pPlayer->BindModel(Model);

	// サイズを設定
	m_pPlayer->SetSize(Model->size);

	// スタートオブジェクトの位置情報を取得
	FindStartObject();

	// ミス音
	CSound::GetInstance()->Play(CSound::LABEL::MISS);
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
	// 加速度を初期化
	m_pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });

	// 縮尺をリセット
	m_pPlayer->SetScale(0.0f);
}

//============================================================================
// スタートオブジェクトの位置を検索
//============================================================================
void CPlayerStateMistook::FindStartObject()
{
	// スタートオブジェクトを取得
	CStart* pStart{ CUtility::GetInstance()->DownCast<CStart, CObject>(CObject::FindObject(CObject::TYPE::START)) };

	if (pStart == nullptr)
	{ // 発見失敗
		assert(false);
	}

	// スタート座標をコピー
	m_PosStartObject = pStart->GetActualPos();
}

//============================================================================
// リスポーン
//============================================================================
void CPlayerStateMistook::Respawn()
{
	// 新しい目標座標を作成
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };

	// プレイヤーの座標がスタートの座標と異なれば
	if (NewPosTarget != m_PosStartObject)
	{
		// プレイヤー座標とスタート位置の差を割り出す
		D3DXVECTOR3 Distance{ m_PosStartObject - NewPosTarget };

		// 差が一定以上あれば制限を付ける
		if (Distance.x > MAX_WARP_SPEED)
		{
			Distance.x = MAX_WARP_SPEED;
		}
		else if (Distance.x < -MAX_WARP_SPEED)
		{
			Distance.x = -MAX_WARP_SPEED;
		}

		if (Distance.y > MAX_WARP_SPEED)
		{
			Distance.y = MAX_WARP_SPEED;
		}
		else if (Distance.y < -MAX_WARP_SPEED)
		{
			Distance.y = -MAX_WARP_SPEED;
		}

		// 差を縮めて座標を補正していく
		NewPosTarget += Distance;

		// 目標座標を設定する
		m_pPlayer->SetPosTarget(NewPosTarget);

		// 縮小させていく
		m_pPlayer->SetScale(CUtility::GetInstance()->AdjustToTarget(m_pPlayer->GetScale(), 0.0f, 0.1f));
	}
	else
	{
		// 通常状態に変更
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::DEFAULT);
	}
}



//============================================================================
// 
// プレイヤーゴール後クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateGoal::CPlayerStateGoal()
{

}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateGoal::~CPlayerStateGoal()
{

}

//============================================================================
// 変更開始
//============================================================================
void CPlayerStateGoal::Enter()
{
	// 真上方向に加速度を設定
	D3DXVECTOR3 NewVelocity{ m_pPlayer->GetVelocity() };
	NewVelocity.y += 10.0f;
	m_pPlayer->SetVelocity(NewVelocity);

	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_007) };

	// モデルの設定
	m_pPlayer->BindModel(Model);

	// サイズを設定
	m_pPlayer->SetSize(Model->size);
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateGoal::Update()
{
	// Y軸向きを高速回転し、Z軸向きをリセット
	D3DXVECTOR3 NewRot{ m_pPlayer->GetRot() };
	NewRot.y += 0.1f;
	NewRot.z = 0.0f;
	m_pPlayer->SetRot(NewRot);

	// 加速度を減衰
	m_pPlayer->SetVelocity(CUtility::GetInstance()->AdjustToTarget(m_pPlayer->GetVelocity(), D3DXVECTOR3{ 0.0f, 0.0f, 0.0f }, 0.05f));

	// 加速度分、目標座標を変動
	D3DXVECTOR3 NewPosTarget{ m_pPlayer->GetPosTarget() };
	NewPosTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(NewPosTarget);

	// 縮小させていく
	m_pPlayer->SetScale(CUtility::GetInstance()->AdjustToTarget(m_pPlayer->GetScale(), 0.0f, 0.035f));

}

//============================================================================
// 変更終了
//============================================================================
void CPlayerStateGoal::Exit()
{

}



//============================================================================
// 
// プレイヤー状態マネージャークラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateManager::CPlayerStateManager() :
	m_pPlayer{ nullptr },
	m_pState{ nullptr },
	m_PendingState{ CPlayerState::STATE::NONE }
{

}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateManager::~CPlayerStateManager()
{
	m_pPlayer = nullptr;						// プレイヤーのポインタを初期化
	m_pState = nullptr;							// 状態のポインタを初期化
	m_PendingState = CPlayerState::STATE::NONE;	// 変更予定の状態を初期化
}

//============================================================================
// 状態の変更を確認
//============================================================================
void CPlayerStateManager::CheckStateChange()
{
#ifdef _DEBUG
	if (m_pState)
	{
		// 型名のデバッグ表示
		CRenderer::GetInstance()->SetDebugString(typeid(*m_pState).name());
	}
#endif	// _DEBUG

	// 変更予定の状態が無ければリターン
	if (m_PendingState == CPlayerState::STATE::NONE)
	{
		return;
	}

	// 既に状態が生成されていれば破棄
	if (m_pState != nullptr)
	{
		// 変更終了時の処理
		m_pState->Exit();

		// メモリを解放
		delete m_pState;

		// 状態クラスのポインタを初期化
		m_pState = nullptr;
	}

	// 次の状態を生成
	Create(m_PendingState);

	// 変更予定の状態を初期化
	m_PendingState = CPlayerState::STATE::NONE;

	// 新しい状態にプレイヤーを登録
	m_pState->RegisterPlayer(m_pPlayer);

	// 変更時の処理
	m_pState->Enter();
}

//============================================================================
// 初期設定
//============================================================================
void CPlayerStateManager::Init(CPlayer* pPlayer)
{
	// 状態マネージャーにプレイヤーを登録
	RegisterPlayer(pPlayer);

	// 初期状態を予定しておく
	m_PendingState = CPlayerState::STATE::MISS;

	// 初期状態を反映する
	CheckStateChange();
}

//============================================================================
// プレイヤーを登録
//============================================================================
void CPlayerStateManager::RegisterPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

//============================================================================
// 終了処理
//============================================================================
void CPlayerStateManager::Uninit()
{
	// プレイヤーのポインタを初期化
	m_pPlayer = nullptr;

	// 状態を破棄
	if (m_pState != nullptr)
	{
		// メモリを解放
		delete m_pState;

		// ポインタを初期化
		m_pState = nullptr;
	}
}

//============================================================================
// プレイヤーを取得
//============================================================================
CPlayer* CPlayerStateManager::GetPlayer()
{
	return m_pPlayer;
}

//============================================================================
// 状態を取得
//============================================================================
CPlayerState* CPlayerStateManager::GetState()
{
	return m_pState;
}

//============================================================================
// 変更予定の状態を取得
//============================================================================
CPlayerState::STATE CPlayerStateManager::GetPendingState()
{
	return m_PendingState;
}

//============================================================================
// 変更予定の状態を設定
//============================================================================
void CPlayerStateManager::SetPendingState(CPlayerState::STATE state)
{
	m_PendingState = state;
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

	case CPlayerState::STATE::CHARGING:
		m_pState = DBG_NEW CPlayerStateCharging;
		break;

	case CPlayerState::STATE::RUSHING:
		m_pState = DBG_NEW CPlayerStateRushing;
		break;

	case CPlayerState::STATE::STOPPING:
		m_pState = DBG_NEW CPlayerStateStopping;
		break;

	case CPlayerState::STATE::MISS:
		m_pState = DBG_NEW CPlayerStateMistook;
		break;

	case CPlayerState::STATE::GOAL:
		m_pState = DBG_NEW CPlayerStateGoal;
		break;

	default:
		assert(false);
		break;
	}
}