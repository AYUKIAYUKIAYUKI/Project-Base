//============================================================================
// 
// 2Dオブジェクト管理、ヘッダファイル [object2D.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_	// 二重インクルード防止

// インクルードファイル
#include "object.h"

// 2Dオブジェクト管理クラス
class CObject2D : public CObject
{
public:
	CObject2D();				// コンストラクタ
	~CObject2D();				// デストラクタ
	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理
	static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTex;			// テクスチャのポインタ
	int m_nCntTexChange;				// テクスチャ変更管理
	int m_nCntTexPattern;				// テクスチャパターン管理
	D3DXVECTOR3 m_pos;					// 中心座標
	D3DXVECTOR3 m_rot;					// 回転量
	float m_fAngle;						// 角度
	D3DXVECTOR3 m_size;					// 大きさ
	float m_fLength;					// 対角線
};

#endif // _OBJECT2D_H_