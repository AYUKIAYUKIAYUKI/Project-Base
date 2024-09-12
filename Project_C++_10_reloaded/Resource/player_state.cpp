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
const float CPlayerStateFlying::FLY_SPEED = 3.0f;			// 飛行速度
const float CPlayerStateCharging::MAX_SPAN = 0.25f;			// 幅
const int CPlayerStateStopping::STOP_CNT_MAX = 15;			// 変身停止必要時間
const float CPlayerStateStopping::RECOIL_SPEED = 3.0f;		// 反動移動速度
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
	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_000);

	// モデルの設定
	m_pPlayer->BindModel(model);

	// サイズを設定
	m_pPlayer->SetSize(model->size);
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
	CUtility::GetInstance()->Gravity(velocity);
	m_pPlayer->SetVelocity(velocity);

	// 制動調整
	Braking();

	// 加速度分、目標座標を変動
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);

	// 当たり判定
	m_pPlayer->Collision();

	// おかしなところに行くと一旦殺す
	if (m_pPlayer->GetPosTarget().y < -300.0f)
	{
		// 失敗状態に変更
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::MISS);
	}
}

//============================================================================
// 変更終了
//============================================================================
void CPlayerStateDefault::Exit()
{
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

	// パッド取得
	CInputPad* pPad = CManager::GetPad();

	// 移動方向用
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

	// X軸
	if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::LEFT))
	{
		X = -1.0f;
	}
	else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::RIGHT))
	{
		X = 1.0f;
	}

	// スティック
	X = pPad->GetJoyStickL().X;

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
	if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::A) || pPad->GetTrigger(CInputPad::JOYKEY::B) ||
		pPad->GetTrigger(CInputPad::JOYKEY::X) || pPad->GetTrigger(CInputPad::JOYKEY::Y))
	{
		// Y方向への加速度が無ければ変身
		if (m_pPlayer->GetVelocity().y == 0.0f)
		{
			// 飛行状態へ
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
	m_nCntMetamorphose = 0;	// 変身時間カウントを初期化
}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateBeginning::~CPlayerStateBeginning()
{
	m_nCntMetamorphose = 0;	// 変身時間カウントを初期化
}

//============================================================================
// 変更開始
//============================================================================
void CPlayerStateBeginning::Enter()
{
	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_001);

	// モデルの設定
	m_pPlayer->BindModel(model);

	// サイズを設定
	m_pPlayer->SetSize(model->size);

	for (int i = 0; i < 10; i++)
	{
		// ランダムな加速度を生成
		D3DXVECTOR3 velocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

		// 煙を生成
		CSmoke::Create(
			m_pPlayer->GetPos(),	// 座標
			velocity * 0.0075f);	// 加速度
	}

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
		D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
		posTarget.y += BEGIN_FLOATING;
		m_pPlayer->SetPosTarget(posTarget);

		// Y軸を高速回転し、Z軸回転を初期化
		D3DXVECTOR3 rot = m_pPlayer->GetRot();
		rot.y = posTarget.y * BEGIN_SPINNING;
		rot.z = 0.0f;
		m_pPlayer->SetRot(rot);

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
	m_pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });

	// 目標加速度を初期化
	m_pPlayer->SetVelocityTarget({ 0.0f, 0.0f, 0.0f });

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
	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_002);

	// モデルの設定
	m_pPlayer->BindModel(model);

	// サイズを設定
	m_pPlayer->SetSize(model->size);
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
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);
	
	// この時点での加速度を保持
	D3DXVECTOR3 oldVelocity{ m_pPlayer->GetVelocity() };

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

		// 当たり判定により消失した加速度を戻す
		m_pPlayer->SetVelocity(oldVelocity);

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
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// パッド取得
	CInputPad* pPad = CManager::GetPad();

	// 移動方向用
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

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

	// スティック
	X = pPad->GetJoyStickL().X;
	Y = pPad->GetJoyStickL().Y;

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

	// 目標加速度を設定
	D3DXVECTOR3 velocityTarget{ 0.0f, 0.0f, 0.0f };
	velocityTarget.x = sinf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	velocityTarget.y = cosf(m_pPlayer->GetAngleFlying()) * FLY_SPEED;
	m_pPlayer->SetVelocityTarget(velocityTarget);

#ifdef _DEBUG
	// 目標加速度をデバッグ表示
	CRenderer::GetInstance()->SetDebugString("【　目標加速度　】");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(3) << "X:" << m_pPlayer->GetVelocityTarget().x << "\nY:" << m_pPlayer->GetVelocityTarget().y;
	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());
#endif // _DEBUG

	// 現在の加速度を取得
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();

#ifdef _DEBUG
	// 現在の加速度をデバッグ表示
	CRenderer::GetInstance()->SetDebugString("【　現在の加速度　】");
	std::ostringstream oss1;
	oss1 << std::fixed << std::setprecision(3) << "X:" << velocity.x << "\nY:" << velocity.y;
	CRenderer::GetInstance()->SetDebugString(oss1.str().c_str());
#endif // _DEBUG

	// 現在の加速度を補正
	velocity += (m_pPlayer->GetVelocityTarget() - velocity) * 0.1f;

	// 変更した加速度を反映
	m_pPlayer->SetVelocity(velocity);

	if (rand() % 3 == 0)
	{
		// 波紋を生成
		CRipple::Create(
			m_pPlayer->GetPos() + (-velocity * 5.0f),	// 座標
			-velocity);									// 加速度 (飛行方向の逆)

		// 星を生成
		CStar::Create(
			m_pPlayer->GetPos() + (-velocity * 5.0f),	// 座標
			-velocity);									// 加速度 (飛行方向の逆)

		// きらきら音
		//CSound::GetInstance()->Play(CSound::LABEL::TWINKLING);
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
// プレイヤー溜め状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateCharging::CPlayerStateCharging() :
	m_rotHold{ 0.0f, 0.0f, 0.0f },
	m_fCoeff{ 0.0f },
	m_pArrow{ nullptr }
{
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
}

//============================================================================
// 変更開始
//============================================================================
void CPlayerStateCharging::Enter()
{
	// 増加量を設定
	m_fCoeff = 0.015f;

	// 出現設定
	m_pArrow->SetAppear();

	// 初期座標を設定
	m_pArrow->SetPos(m_pPlayer->GetPos());
	
	// 飛行方向に合わせた向きを生成
	D3DXVECTOR3 newRot{ 0.0f, 0.0f, m_pPlayer->GetRot().z * 0.5f };

	// 向きを設定
	m_pArrow->SetRot(newRot);

	// この向きを保持
	m_rotHold = newRot;

	// 目標サイズを設定
	m_pArrow->SetSizeTarget({ 20.0f, 20.0f, 0.0f });

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_004);

	// モデルの設定
	m_pPlayer->BindModel(model);

	// サイズを設定
	m_pPlayer->SetSize(model->size);
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateCharging::Update()
{ 
	// パッド取得
	CInputPad* pPad = CManager::GetPad();

	// 震える
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.x = CUtility::GetInstance()->GetRandomValue<float>() * 0.0005f;
	rot.y = CUtility::GetInstance()->GetRandomValue<float>() * 0.0005f;
	m_pPlayer->SetRot(rot);

	// 加速度減衰
	D3DXVECTOR3 newVelocity{ m_pPlayer->GetVelocity() };
	newVelocity = CUtility::GetInstance()->AdjustToTarget(newVelocity, D3DXVECTOR3{ 0.0f, 0.0f, 0.0f }, 0.2f);
	m_pPlayer->SetVelocity(newVelocity);

	// 加速度分、目標座標を変動
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);

	// エフェクト生成
	if (rand() % 5 == 0)
	{
		// ランダムなベクトル
		D3DXVECTOR3 random{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

		// 星を生成
		CStar::Create(
			m_pPlayer->GetPos() + random * 2.0f,	// 座標
			random);								// 加速度 (ランダム)
	}

	// この時点での加速度を保持
	D3DXVECTOR3 oldVelocity{ m_pPlayer->GetVelocity() };

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

		// 当たり判定により消失した加速度を戻す
		m_pPlayer->SetVelocity(oldVelocity);

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
	// XY軸回転を初期化
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.x = 0.0f;
	rot.y = 0.0f;
	m_pPlayer->SetRot(rot);

	// 矢印の向いている方向を飛行角度に設定
	m_pPlayer->SetAngleFlying(-m_pArrow->GetRot().z * 2.0f);
}

//============================================================================
// 矢印の更新を行う
//============================================================================
void CPlayerStateCharging::UpdateArrow()
{
	// キーボード取得
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// パッド取得
	CInputPad* pPad = CManager::GetPad();

	// 新たな向きを作成
	D3DXVECTOR3 newRot{ 0.0f, 0.0f, 0.0f };

	// 移動方向用
	bool bMove = 0;
	float X = 0.0f;
	float Y = 0.0f;

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

	// スティック
	X = pPad->GetJoyStickL().X;
	Y = pPad->GetJoyStickL().Y;

	// 何か入力していれば移動判定を出す
	if (X != 0.0f || Y != 0.0f)
	{
		bMove = true;
	}

	// 移動判定が出ていれば
	if (bMove)
	{
		// 方向を選択する
		newRot.z = atan2f(X, Y);
	}

	// 向きを反映
	m_pArrow->SetRot(-newRot * 0.5f);

	// 新たな座標を作成
	D3DXVECTOR3 newPos{ 0.0f, 0.0f, 0.0f };

	// プレイヤー座標を取得
	newPos = m_pPlayer->GetPos();

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
	newPos += {
		sinf(newRot.z) * 10.0f,
		cosf(newRot.z) * 10.0f,
		0.0f
	};

	// ずらされた座標を基点に弧を描くように移動
	newPos += {
		sinf(newRot.z) * 20.0f,
		cosf(newRot.z) * 20.0f,
		0.0f
	};
#endif

	// 座標を反映
	m_pArrow->SetPos(newPos);
}



//============================================================================
// 
// プレイヤー突撃状態クラス
// 
//============================================================================

//============================================================================
// コンストラクタ
//============================================================================
CPlayerStateRushing::CPlayerStateRushing()
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
	D3DXVECTOR3 newRotTarget{ 0.0f, 0.0f, -m_pPlayer->GetAngleFlying() };
	m_pPlayer->SetRotTarget(newRotTarget);

	// 飛行角度から新たな加速度を作成
	D3DXVECTOR3 newVelocity{ 
		sinf(m_pPlayer->GetAngleFlying()),
		cosf(m_pPlayer->GetAngleFlying()),
		0.0f
	};

	// 加速度を設定
	m_pPlayer->SetVelocity(newVelocity * 5.0f);

#ifdef _DEBUG
	// 新たな加速度を表示
	CRenderer::GetInstance()->SetTimeString("【設定されている飛行角度】" + std::to_string(m_pPlayer->GetAngleFlying()), 600);
	CRenderer::GetInstance()->SetTimeString("【飛行方向から設定した新たな加速度】" + std::to_string(newVelocity.x) + " : " + std::to_string(newVelocity.y), 600);
#endif

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_005);

	// モデルの設定
	m_pPlayer->BindModel(model);

	// サイズを設定
	m_pPlayer->SetSize(model->size);
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateRushing::Update()
{
	// 回転
	Rotation();

	// 加速度分、目標座標を変動
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);

	// エフェクト生成
	if (rand() % 2 == 0)
	{
		// ランダムなベクトル
		D3DXVECTOR3 random{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

		// 煙を生成
		CSmoke::Create(
			m_pPlayer->GetPos() - (m_pPlayer->GetVelocity() * 5.0f) + random,	// 座標
			m_pPlayer->GetVelocity());											// 加速度 (飛行方向)

		// 星を生成
		CStar::Create(
			m_pPlayer->GetPos() - m_pPlayer->GetVelocity() + random * 5.0f,	// 座標
			-m_pPlayer->GetVelocity());										// 加速度 (飛行方向の逆)
		
		// 波紋を生成
		CRipple::Create(
			m_pPlayer->GetPos() - m_pPlayer->GetVelocity() + random * 5.0f,	// 座標
			-m_pPlayer->GetVelocity());										// 加速度 (飛行方向の逆)

		// きらきら音
		//CSound::GetInstance()->Play(CSound::LABEL::TWINKLING);
	}

	// この時点での加速度を保持
	D3DXVECTOR3 oldVelocity{ m_pPlayer->GetVelocity() };

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

		// 当たり判定により消失した加速度を戻す
		m_pPlayer->SetVelocity(oldVelocity);

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

}

//============================================================================
// 回転
//============================================================================
void CPlayerStateRushing::Rotation()
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

	// 震える
	rot.x = CUtility::GetInstance()->GetRandomValue<float>() * 0.0005f;
	rot.y = CUtility::GetInstance()->GetRandomValue<float>() * 0.0005f;
	
	// 向き情報設定
	m_pPlayer->SetRot(rot);
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
	m_nCntStopMetamorphose = 0;	// 変身時間カウントを初期化
}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateStopping::~CPlayerStateStopping()
{
	m_nCntStopMetamorphose = 0;	// 変身時間カウントを初期化
}

//============================================================================
// 変更開始
//============================================================================
void CPlayerStateStopping::Enter()
{
	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_003);

	// モデルの設定
	m_pPlayer->BindModel(model);

	// サイズを設定
	m_pPlayer->SetSize(model->size);

	for (int i = 0; i < 10; i++)
	{
		// ランダムな加速度を生成
		D3DXVECTOR3 velocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

		// 煙を生成
		CSmoke::Create(
			m_pPlayer->GetPos(),	// 座標
			velocity * 0.0075f);	// 加速度
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
		Rolling();

		// 重力加速
		D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();
		CUtility::GetInstance()->Gravity(velocity);
		m_pPlayer->SetVelocity(velocity);

		// 加速度分、目標座標を変動
		D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
		posTarget += m_pPlayer->GetVelocity();
		m_pPlayer->SetPosTarget(posTarget);

		// 当たり判定
		m_pPlayer->Collision();
	}
	else
	{
		// 状態変更
		m_pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::DEFAULT);
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

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_000);

	// モデルの設定
	m_pPlayer->BindModel(model);

	// サイズを設定
	m_pPlayer->SetSize(model->size);
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
	// 衝突寸前の加速度を取得
	D3DXVECTOR3 newVelocity{ m_pPlayer->GetVelocity() };

#ifdef _DEBUG
	CRenderer::GetInstance()->SetTimeString("\n衝突時の加速度X : " + std::to_string(newVelocity.x), 120);
	CRenderer::GetInstance()->SetTimeString("衝突時の加速度Y : " + std::to_string(newVelocity.y), 120);
#endif	// _DEBUG

	// 寸前の向きの真逆の角度を算出
	float fNewFlyingAngle{ atan2f(newVelocity.x, newVelocity.y) };

	// 真逆の角度方向に加速度を設定
	newVelocity.x = -sinf(fNewFlyingAngle) * RECOIL_SPEED;
	newVelocity.y = -cosf(fNewFlyingAngle) * RECOIL_SPEED;

#ifdef _DEBUG
	CRenderer::GetInstance()->SetTimeString("衝突後の加速度X : " + std::to_string(newVelocity.x), 120);
	CRenderer::GetInstance()->SetTimeString("衝突後の加速度Y : " + std::to_string(newVelocity.y), 120);
#endif	// _DEBUG

	m_pPlayer->SetVelocity(newVelocity);
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
	m_posStartObject = { 0.0f, 0.0f, 0.0f };	// スタートオブジェクトの位置を初期化
}

//============================================================================
// デストラクタ
//============================================================================
CPlayerStateMistook::~CPlayerStateMistook()
{
	m_posStartObject = { 0.0f, 0.0f, 0.0f };	// スタートオブジェクトの位置を初期化
}

//============================================================================
// 変更開始
//============================================================================
void CPlayerStateMistook::Enter()
{
	// 回転を初期化
	m_pPlayer->SetRot({ 0.0f, 0.0f, 0.0f });

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_006);

	// モデルの設定
	m_pPlayer->BindModel(model);

	// サイズを設定
	m_pPlayer->SetSize(model->size);

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
}

//============================================================================
// スタートオブジェクトの位置を検索
//============================================================================
void CPlayerStateMistook::FindStartObject()
{
	CStart* pStart = CUtility::GetInstance()->DownCast<CStart, CObject>(CObject::FindObject(CObject::TYPE::START));

	if (pStart == nullptr)
	{ // 発見失敗
		assert(false);
	}

	// スタートオブジェクトの位置を取得
	m_posStartObject = pStart->GetPos();
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
	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PLAYER_007);

	// モデルの設定
	m_pPlayer->BindModel(model);

	// サイズを設定
	m_pPlayer->SetSize(model->size);
}

//============================================================================
// 更新
//============================================================================
void CPlayerStateGoal::Update()
{
	// 加速度を減らしていく
	D3DXVECTOR3 velocity = m_pPlayer->GetVelocity();
	velocity = velocity * 0.9f;
	m_pPlayer->SetVelocity(velocity);

	// 変身期間中は強制上昇
	D3DXVECTOR3 posTarget = m_pPlayer->GetPosTarget();
	posTarget.y += 1.0f;
	m_pPlayer->SetPosTarget(posTarget);

	// Y軸を高速回転し、Z軸回転を初期化
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	rot.y = posTarget.y * 0.1f;
	rot.z = 0.0f;
	m_pPlayer->SetRot(rot);

	// 加速度分、目標座標を変動
	posTarget = m_pPlayer->GetPosTarget();
	posTarget += m_pPlayer->GetVelocity();
	m_pPlayer->SetPosTarget(posTarget);
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
CPlayerStateManager::CPlayerStateManager() : m_pPlayer(nullptr), m_pState(nullptr)
{
	m_PendingState = CPlayerState::STATE::NONE;	// 変更予定の状態を初期化
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