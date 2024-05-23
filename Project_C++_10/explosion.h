//============================================================================
// 
// 爆発、ヘッダファイル [explosion.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object2D.h"

//****************************************************
// エクスプロージョンクラス
//****************************************************
class CExplosion : public CObject2D
{
public:
	CExplosion();				// コンストラクタ
	~CExplosion();				// デストラクタ
	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理
	static CExplosion* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成

private:
	void Animation();	// アニメーション

	int m_nCntTexChange;	// テクスチャ変更管理
	int m_nCntTexPattern;	// テクスチャパターン管理
	D3DXVECTOR3 m_pos;		// 中心座標
	D3DXVECTOR3 m_rot;		// 回転量
	float m_fAngle;			// 角度
	D3DXVECTOR3 m_size;		// 大きさ
	float m_fLength;		// 対角線
};

#endif // _PALYER_H_