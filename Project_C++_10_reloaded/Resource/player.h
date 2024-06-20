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
// 先行宣言
//****************************************************
class CStatePlayer;	// プレイヤー状態クラス

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

	D3DXVECTOR3* GetVelocity();				// 加速度を取得
	void SetVelocity(D3DXVECTOR3 velocity);	// 加速度を設定

	float* GetAngleFlying();					// 飛行方向を取得
	void SetAngleFlying(float fAngleFlying);	// 飛行方向を設定

	D3DXVECTOR3* GetPosTarget();				// 目標位置を取得
	void SetPosTarget(D3DXVECTOR3 posTarget);	// 目標位置を設定

	D3DXVECTOR3* GetRotTarget();				// 目標向きを取得
	void SetRotTarget(D3DXVECTOR3 rotTarget);	// 目標向きを設定

	static CPlayer* Create(D3DXVECTOR3 pos);	// 生成

private:

	static const float MAX_VELOCITY;	// 加速度上限
	static const float JUMP_FORCE;		// ジャンプ力
	static const float BRAKING_FORCE;	// 制動力

	CPlayer* GetSelf();		// 自身のポインタを取得
	void AdjustPos();		// 位置を調整
	bool Collision();		// 当たり判定
	void FinishTransform();	// 変身解除

	CStatePlayer* m_state;		// 状態
	D3DXVECTOR3 m_velocity;		// 加速度
	float m_fAngleFlying;		// 飛行方向
	D3DXVECTOR3 m_posTarget;	// 目標位置
	D3DXVECTOR3 m_rotTarget;	// 目標向き

	int m_nTestExplosionCnt;	// これはテスト用です
};

//****************************************************
// プレイヤー状態クラス
//****************************************************
class CStatePlayer
{
public:

	virtual ~CStatePlayer();	// デストラクタ

	virtual void Update() = 0;	// 更新

	void SetInstance(CPlayer* player);	// プレイヤーのインスタンスを設定

protected:

	CStatePlayer();	// コンストラクタ
	CPlayer* m_player;			// プレイヤーのインスタンス

private:

	virtual void Control() = 0;		// 操作
	virtual void Rotation() = 0;	// 回転
	virtual void Braking() = 0;		// 制動調整

	bool m_bMetamorphose;		// 変身判定
	int m_nCntMetamorphose;		// 変身期間
};

//****************************************************
// プレイヤー通常状態クラス
//****************************************************
class CStateDefaultPlayer : public CStatePlayer
{
public:

	~CStateDefaultPlayer() override;	// デストラクタ

	void Update() override;	// 更新

private:

	void Control() override;	// 操作
	void Rotation() override;	// 回転
	void Braking() override;	// 制動調整
};

//****************************************************
// プレイヤー飛行状態クラス
//****************************************************
class CStateFlyingPlayer : public CStatePlayer
{
public:

	~CStateFlyingPlayer() override;	// デストラクタ

	void Update() override;	// 更新

private:

	void Control() override;	// 操作
	void Rotation() override;	// 回転
	void Braking() override;	// 制動調整
	void Recoil();				// 反動
};

#endif // _PALYER_H_