//============================================================================
// 
// マス目、ヘッダファイル [square.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _SQUARE_H_
#define _SQUARE_H_// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"

//****************************************************
// マス目クラス
//****************************************************
class CSquare : public CObject_2D
{
public:

	CSquare();				// デフォルトコンストラクタ
	~CSquare() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static void ControlAll(int nSelect);		// マス目を動作
	static void LineUpAll(int nSelect);			// マス目を並べる 
	static CSquare* Create(D3DXVECTOR3 pos);	// 生成
};

#endif // _SQUARE_H_