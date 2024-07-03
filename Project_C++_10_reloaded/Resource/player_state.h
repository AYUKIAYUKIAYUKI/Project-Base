//============================================================================
// 
// プレイヤー状態管理、ヘッダファイル [player_state.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "player.h"

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
		DEFAULT = 0,	// 通常状態
		BEGINNING,		// 変身開始
		FLYING,			// 飛行状態
		STOPPING,		// 変身停止
		MISS,			// 失敗状態
		MAX,
	};

	CPlayerState();				// コンストラクタ
	virtual ~CPlayerState();	// デストラクタ

	virtual void Enter() = 0;	// 変更開始
	virtual void Update();		// 更新
	virtual void Exit() = 0;	// 変更終了

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

	void Enter() override;	// 変更開始
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	static const float MAX_WALK_VELOCITY;	// 歩行時の最大加速度
	static const float BRAKING_WALK_SPEED;	// 歩行時の制動力

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

	void Enter() override;	// 変更開始
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	static const int BEGIN_CNT_MAX;	// 変身必要時間

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

	void Enter() override;	// 変更開始
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	static const float MAX_FLY_VELOCITY;	// 飛行時の最大加速度

	bool Flying();		// 操作
	void Rotation();	// 回転
	void Braking();		// 制動調整
};

//****************************************************
// プレイヤー変身停止クラス
//****************************************************
class CPlayerStateStopping : public CPlayerState
{
public:

	CPlayerStateStopping();				// コンストラクタ
	~CPlayerStateStopping() override;	// デストラクタ

	void Enter() override;	// 変更開始
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	void Rolling();	// 回転
	void Recoil();	// 反動

	static const int STOP_CNT_MAX;	// 変身停止必要時間

	int m_nCntStopMetamorphose;	// 変身時間カウント
};

//****************************************************
// プレイヤー失敗状態クラス
//****************************************************
class CPlayerStateMistook : public CPlayerState
{
public:

	CPlayerStateMistook();				// コンストラクタ
	~CPlayerStateMistook() override;	// デストラクタ

	void Enter() override;	// 初回変更
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	static const float MAX_WARP_SPEED;	// 強制移動速度の上限

	void FindStartObject();	// スタートオブジェクトの位置を検索
	void Respawn();			// リスポーン

	D3DXVECTOR3 m_posStartObject;	// スタートオブジェクトの位置
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

#endif // _PLAYER_STATE_H_