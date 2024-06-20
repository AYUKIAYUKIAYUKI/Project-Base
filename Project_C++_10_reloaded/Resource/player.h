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
// プレイヤークラス
//****************************************************
class CPlayer : public CObject_X
{
public:

	//****************************************************
	// プレイヤーの状態
	//****************************************************
	enum class STATE
	{
		NONE = 0,	// 無し
		DEFAULT,	// 通常
		CHANGING,	// 変身開始
		FLYING,		// 飛行
		RETURNING,	// 変身解除
		MAX,
	};

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

	STATE m_state;				// 状態
	bool m_bMetamorphose;		// 変身判定
	int m_nCntMetamorphose;		// 変身期間
	D3DXVECTOR3 m_velocity;		// 加速度
	float m_fAngleFlying;		// 飛行方向
	D3DXVECTOR3 m_posTarget;	// 目標位置
	D3DXVECTOR3 m_rotTarget;	// 目標向き

	int m_nTestExplosionCnt;	// これはテスト用です
};

#endif // _PALYER_H_