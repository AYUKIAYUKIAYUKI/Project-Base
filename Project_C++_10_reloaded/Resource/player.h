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

	CPlayer();				// コンストラクタ
	~CPlayer() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CPlayer* Create(D3DXVECTOR3 pos);	// 生成

private:

	static const float MAX_VELOCITY;	// 加速度上限
	static const float JUMP_FORCE;		// ジャンプ力
	static const float BRAKING_FORCE;	// 制動力

	void Walking();			// 歩行
	void Rotation();		// 回転
	void Braking();			// 制動調整

	void Flying();			// 飛行
	void Rolling();			// 旋回
	void AirResistance();	// 空気抵抗

	void AdjustPos();		// 位置を調整
	bool Collision();		// 当たり判定

	void FinishTransform();	// 変身解除
	void Recoil();			// 反動

	CPlayerStateManager* m_pStateManager;	// 状態管理

	bool m_bMetamorphose;		// 変身判定
	int m_nCntMetamorphose;		// 変身期間
	D3DXVECTOR3 m_velocity;		// 加速度
	float m_fAngleFlying;		// 飛行方向
	D3DXVECTOR3 m_posTarget;	// 目標位置
	D3DXVECTOR3 m_rotTarget;	// 目標向き

	int m_nTestExplosionCnt;	// これはテスト用です
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
		FLYING,			// 飛行
		MAX,
	};

	CPlayerState();				// コンストラクタ
	virtual ~CPlayerState();	// デストラクタ

	virtual void Enter() = 0;	// 開始
	virtual void Update() = 0;	// 更新
	virtual void Exit() = 0;	// 終了

private:

	virtual void Control() = 0;		// 操作
	virtual void Rotation() = 0;	// 回転
	virtual void Braking() = 0;		// 制動調整
};

//****************************************************
// プレイヤー通常状態クラス
//****************************************************
class CPlayerStateDefault : public CPlayerState
{
public:

	CPlayerStateDefault();				// コンストラクタ
	~CPlayerStateDefault() override;	// デストラクタ

	void Enter() override;	// 開始
	void Update() override;	// 更新
	void Exit() override;	// 終了

private:

	void Control() override;	// 操作
	void Rotation() override;	// 回転
	void Braking() override;	// 制動調整
};

//****************************************************
// プレイヤー飛行状態クラス
//****************************************************
class CPlayerStateFlying : public CPlayerState
{
public:

	CPlayerStateFlying();			// コンストラクタ
	~CPlayerStateFlying() override;	// デストラクタ

	void Enter() override;	// 開始
	void Update() override;	// 更新
	void Exit() override;	// 終了

private:

	void Control() override;	// 操作
	void Rotation() override;	// 回転
	void Braking() override;	// 制動調整
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

	void ChangeState(CPlayerState::STATE state);	// 状態を変更

	CPlayerState* GetState();	// 状態を取得

private:
	
	CPlayerState* Create(CPlayerState::STATE state);	// 新たな状態を生成

	CPlayerState* m_pState;	// 状態を保持
};

#endif // _PALYER_H_