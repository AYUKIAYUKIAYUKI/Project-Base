//============================================================================
// 
// エネミー、ヘッダファイル [enemy.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object2D.h"

//****************************************************
// エネミークラス
//****************************************************
class CEnemy : public CObject2D
{
public:

	CEnemy();				// コンストラクタ
	~CEnemy() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成

private:

	void Rotation();	// 回転
	void Translation();	// 移動

	D3DXVECTOR3 m_rot_tgt;	// 目標向き
};

#endif // _ENEMY_H_