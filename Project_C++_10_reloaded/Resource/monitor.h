//============================================================================
// 
// モニター、ヘッダファイル [monitor.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _MONITOR_H_
#define _MONITOR_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// モニタークラス
//****************************************************
class CMonitor : public CObject_X
{
public:

	CMonitor();				// デフォルトコンストラクタ
	~CMonitor() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CMonitor* Create(D3DXVECTOR3 pos);	// 生成
};

#endif // _MONITOR_H_