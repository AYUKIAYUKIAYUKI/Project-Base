//============================================================================
// 
// ブロック、ヘッダファイル [block.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _BLOCK_H_
#define _BLOCK_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// ブロッククラス
//****************************************************
class CBlock : public CObject_X
{
public:

	CBlock();			// デフォルトコンストラクタ
	~CBlock() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CBlock* Create(D3DXVECTOR3 pos);	// 生成
};

#endif // _BLOCK_H_