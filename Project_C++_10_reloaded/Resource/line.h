//============================================================================
// 
// ライン、ヘッダファイル [line.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _LINE_H_
#define _LINE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// ラインクラス
//****************************************************
class CLine : public CObject_X
{
public:

	CLine();			// デフォルトコンストラクタ
	~CLine() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static void CreateGrid();	// グリッドライン生成
};

#endif // _LINE_H_