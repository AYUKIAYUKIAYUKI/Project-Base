//============================================================================
// 
// ダミー、ヘッダファイル [dummy.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _DUMMY_H_
#define _DUMMY_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// ダミークラス
//****************************************************
class CDummy : public CObject_X
{
public:

	CDummy(int& nPattern);	// コンストラクタ
	~CDummy();				// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CDummy* Create(D3DXVECTOR3 pos, int& nPattern);	// 生成
	static CDummy* DownCast(CObject* pObject);				// ダウンキャスト

private:

	void Control();			// 操作
	void CheckPattern();	// ダミーの種類を確認

	int& m_nPatternRef;	// 配置物の種類を参照
};

#endif // _DUMMY_H_