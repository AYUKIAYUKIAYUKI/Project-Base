//============================================================================
// 
// スコア、ヘッダファイル [score.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _SCORE_H_
#define _SCORE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object2D.h"

//****************************************************
// スコアクラス
//****************************************************
class CScore : public CObject2D
{
public:

	CScore();			// コンストラクタ
	~CScore() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CScore* Create();	// 生成

private:

	void Translate();	// 移動
	void Progress();	// 期間経過
};

#endif // _SCORE_H_