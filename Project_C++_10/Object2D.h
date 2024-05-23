//============================================================================
// 
// 2Dオブジェクト管理、ヘッダファイル [object2D.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object.h"

//****************************************************
// 2Dオブジェクトクラス
//****************************************************
class CObject2D : public CObject
{
public:
	CObject2D();							// コンストラクタ
	~CObject2D();							// デストラクタ
	HRESULT Init() override;				// 初期設定
	void Uninit() override;					// 終了処理
	void Update() override;					// 更新処理
	void Draw() override;					// 描画処理
	static CObject2D* Create();				// 生成
	void BindTex(LPDIRECT3DTEXTURE9 pTex);	// テクスチャ割当

	// 頂点バッファのポインタを取得する
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() { 
		return m_pVtxBuff;
	}

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTex;			// テクスチャのポインタ
};

#endif // _OBJECT2D_H_