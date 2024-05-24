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
#include "object2D.h"

//****************************************************
// プレイヤークラス
//****************************************************
class CPlayer : public CObject2D
{
public:

	CPlayer();					// コンストラクタ
	~CPlayer();					// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CPlayer* Create(D3DXVECTOR3 pos_arg, D3DXVECTOR3 size_arg);	// 生成

private:

	void Scaling();		// 拡縮
	void Rotation();	// 回転
	void Translation();	// 移動
	void Animation();	// アニメーション

	int m_nCntTexChange;	// テクスチャ変更管理
	int m_nCntTexPattern;	// テクスチャパターン管理
	D3DXVECTOR3 m_rot_tgt;	// 目標向き
};

#endif // _PALYER_H_