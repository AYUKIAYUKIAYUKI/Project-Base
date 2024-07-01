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
	D3DXVECTOR3 m_posTarget;	// 目標位置
	D3DXVECTOR3 m_rotTarget;	// 目標向き
	float m_fAngleFlying;		// 飛行方向
};

#endif // _PALYER_H_