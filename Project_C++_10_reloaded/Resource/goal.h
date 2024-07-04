//============================================================================
// 
// ゴール、ヘッダファイル [goal.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _GOAL_H_
#define _GOAL_H_// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// ゴールクラス
//****************************************************
class CGoal : public CObject_X
{
public:

	CGoal();			// コンストラクタ
	~CGoal() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CGoal* Create(D3DXVECTOR3 pos);		// 生成
	static CGoal* DownCast(CObject* pObject);	// ダウンキャスト
};

#endif // _GOAL_H_