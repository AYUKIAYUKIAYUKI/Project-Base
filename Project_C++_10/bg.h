//============================================================================
// 
// 背景、ヘッダファイル [bg.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _BG_H_
#define _BG_H_	// 二重インクルード防止

// インクルードファイル
#include "object.h"

// プレイヤークラス
class CBg : public CObject
{
public:
	CBg();						// コンストラクタ
	~CBg();						// デストラクタ
	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理
	static CBg* Create();		// 生成

private:
	void Translation();	// 移動

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTex;			// テクスチャのポインタ
	D3DXVECTOR3 m_pos;					// 中心座標
	D3DXVECTOR3 m_size;					// 大きさ
	float m_fLength;					// 対角線
};

#endif // _BG_H_