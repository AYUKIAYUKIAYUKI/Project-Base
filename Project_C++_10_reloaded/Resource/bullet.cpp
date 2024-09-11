//============================================================================
// 
// 弾 [bullet.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "bullet.h"
#include "utility.h"
#include "sound.h"

// オブジェクト用
#include "player.h"
#include "player_state.h"
#include "block.h"
#include "block_destructible.h"
#include "block_spikes.h"
#include "smoke.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CBullet::CBullet() :
	CObject_X{ static_cast<int>(LAYER::BACK) },	// 描画優先度を指定
	m_posTarget{ 0.0f, 0.0f, 0.0f },			// 目標座標
	m_velocity{ 0.0f, 0.0f, 0.0f },				// 加速度
	m_nDuration{ 0 }							// 寿命
{

}

//============================================================================
// 寿命設定コンストラクタ
//============================================================================
CBullet::CBullet(int nDuration) :
	CObject_X{ static_cast<int>(LAYER::BACK) },	// 描画優先度を指定
	m_posTarget{ 0.0f, 0.0f, 0.0f },			// 目標座標
	m_velocity{ 0.0f, 0.0f, 0.0f },				// 加速度
	m_nDuration{ nDuration }					// 寿命
{

}

//============================================================================
// デストラクタ
//============================================================================
CBullet::~CBullet()
{
	for (int i = 0; i < 3; i++)
	{
		// ランダムな加速度を生成
		D3DXVECTOR3 velocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };

		// 煙を生成
		CSmoke::Create(
			GetPos(),				// 座標
			velocity * 0.0025f);	// 加速度
	}
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CBullet::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBullet::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBullet::Update()
{
	// 寿命カウントダウン
	m_nDuration--;

	if (m_nDuration <= 0)
	{
		// 破棄予約
		SetRelease();
	}

	// 回転
	D3DXVECTOR3 rotTaget = GetRot();
	rotTaget.x += CUtility::GetInstance()->GetRandomValue<float>() * 0.01f;
	rotTaget.y += CUtility::GetInstance()->GetRandomValue<float>() * 0.01f;
	rotTaget.z += CUtility::GetInstance()->GetRandomValue<float>() * 0.01f;
	SetRot(rotTaget);

	// 現在の座標を取得し、変更を加えていく
	m_posTarget = GetPos();

	// 移動
	Translate();

	// 当たり判定
	if (Collision())
	{
		// 破棄予約
		SetRelease();
	}

	// 座標を反映
	SetPos(m_posTarget);

	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CBullet::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 生成
//============================================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// インスタンスを生成
	CBullet* pBullet = DBG_NEW CBullet{ 60 };

	if (pBullet == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pBullet->SetType(TYPE::BULLET);

	// 基底クラスの初期設定
	pBullet->Init();

	// 位置の設定
	pBullet->SetPos(pos);

	// サイズの設定
	pBullet->SetSize(size);

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::BULLET_CORE);

	// モデルを設定
	pBullet->BindModel(model);

	// プレイヤーを取得
	CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(CObject::FindObject(TYPE::PLAYER));

	// プレイヤーへのベクトル正規化し、加速度に設定
	D3DXVECTOR3 pV{ (pPlayer->GetPos() - pos) };
	D3DXVec3Normalize(&pBullet->m_velocity, &pV);

	// 描画前に座標を反映
	pBullet->Update();

	return pBullet;
}

//============================================================================
// 移動
//============================================================================
void CBullet::Translate()
{
	//// 座標を取得
	//D3DXVECTOR3 posTarget = GetPos();

	//// 目標座標に加速度を加算
	//posTarget += m_velocity;

	//// 目標座標を反映
	//SetPos(posTarget);

	m_posTarget += m_velocity * 2.0f;
}

//============================================================================
// 当たり判定
//============================================================================
bool CBullet::Collision()
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
			// 可壊ブロックを破棄
			pDestructible->SetRelease();

			// 衝突判定を出す
			bDetected = 1;

			// 破壊音
			CSound::GetInstance()->Play(CSound::LABEL::BREAK);
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
			// 衝突判定を出す
			bDetected = 1;
		}
	}

	// プレイヤーを取得
	CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(CObject::FindObject(CObject::TYPE::PLAYER));

	// プレイヤーと衝突する場合
	if (CUtility::GetInstance()->OnlyCube(pPlayer->GetPos(), pPlayer->GetSize(), m_posTarget, GetSize()))
	{
		// ゴール状態で無ければ
		if (typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerStateGoal))
		{
			// プレイヤーをミス状態へ移行
			pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::MISS);
		
			// 死亡音
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}

		// 衝突判定を出す
		bDetected = 1;
	}

	return bDetected;
}