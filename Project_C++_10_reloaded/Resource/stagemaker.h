//============================================================================
// 
// ステージメーカー [stagemaker.cpp]
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
// ステージメーカークラス
//****************************************************
class CStageMaker
{
public:

	CStageMaker();	// コンストラクタ
	~CStageMaker();	// デストラクタ

	void Init();	// 初期設定
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Create();	// 生成
	void Release();	// 解放
	void Import(std::string path);	// ステージ読み込み

	static CStageMaker* GetInstance();	// 取得

private:

	void Control();	// 操作
	void Regist();	// 設置
	void Export();	// ステージ書き出し
	void Output(std::ofstream& file, D3DXVECTOR3 pos, std::string str);	// 情報書き出し

	static CStageMaker* m_pStageMaker;	// 自クラス情報
};

#endif // _SATEGEMAKER_H_