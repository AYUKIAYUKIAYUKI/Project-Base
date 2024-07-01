//============================================================================
// 
// ステージ作成 [stagemaker.cpp]
// Author : 福田歩希
// 
//============================================================================

#ifndef _SATEGEMAKER_H_
#define _SATEGEMAKER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************}
#include "block.h"

//****************************************************
// ステージ作成クラス
//****************************************************
class CStageMaker
{
public:

	CStageMaker();	// コンストラクタ
	~CStageMaker();	// デストラクタ

	HRESULT Init();	// 初期設定
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Import();	// ステージ読み込み

	D3DXVECTOR3 GetPos();	// 位置を取得

	static HRESULT Create();			// 生成
	static void Release();				// 破棄
	static CStageMaker* GetInstance();	// ステージ作成クラス取得

private:

	void Control();	// 操作
	void Export();	// ステージ書き出し

	static CStageMaker* m_pStageMaker;	// 自身のインスタンス
};

#endif // _SATEGEMAKER_H_