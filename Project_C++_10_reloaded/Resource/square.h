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
#include "number.h"

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
	static void LineUpAll(int nSelect);			// マス目を並べる (不必要)
	static CSquare* Create(D3DXVECTOR3 pos);	// 生成

private:

	static const int MAX_DIGIT = 2;	// 最大桁数

	void Appear();		// 出現
	void Disappear();	// 消滅

	bool m_bAppear;					// 出現フラグ
	bool m_bDisappear;				// 消滅フラグ
	D3DXVECTOR3 m_posTarget;		// 目標座標
	CNumber* m_apNumber[MAX_DIGIT];	// 数字
};

#endif // _SQUARE_H_