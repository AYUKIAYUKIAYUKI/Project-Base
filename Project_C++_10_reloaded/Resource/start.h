//============================================================================
// 
// スタート、ヘッダファイル [start.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _START_H_
#define _START_H_// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// スタートクラス
//****************************************************
class CStart : CObject_X
{
public:

	CStart();			// コンストラクタ
	~CStart() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3* GetPos();	// 位置情報を取得

	static CStart* Create(D3DXVECTOR3 pos);	// 生成

private:

	D3DXVECTOR3 m_pos;	// 自身の位置を保持
};

#endif // _START_H_