//============================================================================
// 
// プレイヤー、ヘッダファイル [player.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// 前方宣言
//****************************************************
class CPlayerStateManager;	// プレイヤー状態管理クラス

//****************************************************
// プレイヤークラス
//****************************************************
class CPlayer : public CObject_X
{
public:

	static const float MAX_VELOCITY;	// 加速度上限
	static const float JUMP_FORCE;		// ジャンプ力
	static const float BRAKING_FORCE;	// 制動力

	CPlayer();				// コンストラクタ
	~CPlayer() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3 GetVelocity();				// 加速度を取得
	void SetVelocity(D3DXVECTOR3 velocity);	// 加速度を設定

	float GetAngleFlying();						// 飛行方向を取得
	void SetAngleFlying(float fAngleFlying);	// 飛行方向を設定

	D3DXVECTOR3 GetPosTarget();					// 目標位置を取得
	void SetPosTarget(D3DXVECTOR3 posTarget);	// 目標位置を設定

	D3DXVECTOR3 GetRotTarget();					// 目標向きを取得
	void SetRotTarget(D3DXVECTOR3 rotTarget);	// 目標向きを設定

	CPlayerStateManager* GetStateManager();	// 状態管理取得

	static CPlayer* Create(D3DXVECTOR3 pos);	// 生成

	bool AdjustPos();	// 位置を調整

private:

	bool Collision();	// 当たり判定

	CPlayerStateManager* m_pStateManager;	// 状態管理

	D3DXVECTOR3 m_velocity;		// 加速度
	float m_fAngleFlying;		// 飛行方向
	D3DXVECTOR3 m_posTarget;	// 目標位置
	D3DXVECTOR3 m_rotTarget;	// 目標向き
};

//****************************************************
// プレイヤー状態クラス
//****************************************************
class CPlayerState
{
public:

	//****************************************************
	// 状態を識別
	//****************************************************
	enum class STATE
	{
		DEFAULT = 0,	// 通常
		BEGINNING,		// 変身開始
		FLYING,			// 飛行
		STOPPING,		// 変身停止
		MAX,
	};

	CPlayerState();				// コンストラクタ
	virtual ~CPlayerState();	// デストラクタ

	virtual void Init();		// 初期設定
	virtual void Update();		// 更新
	virtual void Exit() = 0;	// 終了

	void SetPlayerInstance(CPlayer* player);	// プレイヤー情報の設定

protected:

	CPlayer* m_pPlayer;	// プレイヤーインスタンスへのポインタ
};

//****************************************************
// プレイヤー通常状態クラス
//****************************************************
class CPlayerStateDefault : public CPlayerState
{
public:

	CPlayerStateDefault();				// コンストラクタ
	~CPlayerStateDefault() override;	// デストラクタ

	void Init() override;	// 初期設定
	void Update() override;	// 更新
	void Exit() override;	// 終了

private:

	bool Walk();		// 操作
	void Rotation();	// 回転
	void Braking();		// 制動調整
};

//****************************************************
// プレイヤー変身開始クラス
//****************************************************
class CPlayerStateBeginning : public CPlayerState
{
public:

	CPlayerStateBeginning();			// コンストラクタ
	~CPlayerStateBeginning() override;	// デストラクタ

	void Init() override;	// 初期設定
	void Update() override;	// 更新
	void Exit() override;	// 終了

private:

	static const int END_CNT = 45;	// 変身必要時間

	int m_nCntMetamorphose;	// 変身時間カウント
};

//****************************************************
// プレイヤー飛行状態クラス
//****************************************************
class CPlayerStateFlying : public CPlayerState
{
public:

	CPlayerStateFlying();			// コンストラクタ
	~CPlayerStateFlying() override;	// デストラクタ

	void Init() override;	// 開始
	void Update() override;	// 更新
	void Exit() override;	// 終了

private:

	bool Flying();		// 操作
	void Rotation();	// 回転
	void Braking();		// 制動調整
	void Finish();		// 変身解除
	void Recoil();		// 反動
};

//****************************************************
// プレイヤー変身停止クラス
//****************************************************
class CPlayerStateStopping : public CPlayerState
{
public:

	CPlayerStateStopping();			// コンストラクタ
	~CPlayerStateStopping() override;	// デストラクタ

	void Init() override;	// 初期設定
	void Update() override;	// 更新
	void Exit() override;	// 終了

private:

	static const int END_CNT = 45;	// 変身停止必要時間

	int m_nCntStopMetamorphose;	// 変身時間カウント
};

//****************************************************
// プレイヤー状態管理クラス
//****************************************************
class CPlayerStateManager
{
public:

	CPlayerStateManager();	// コンストラクタ
	~CPlayerStateManager();	// デストラクタ

	void Init();	// 初期設定
	void Uninit();	// 終了処理

	CPlayer* GetPlayerInstance();				// プレイヤーインスタンスの取得
	void SetPlayerInstance(CPlayer* player);	// プレイヤーインスタンスの設定

	void ChangeState(CPlayerState::STATE state);	// 状態を変更

	CPlayerState* GetState();	// 状態を取得

private:
	
	void Create(CPlayerState::STATE state);	// 新たな状態を生成

	CPlayer* m_pPlayer;		// プレイヤーインスタンスへのポインタ
	CPlayerState* m_pState;	// 状態を保持
};

#endif // _PALYER_H_