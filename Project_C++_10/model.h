//============================================================================
// 
// モデル管理、ヘッダファイル [model.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _MODEL_H_
#define _MODEL_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "main.h"

//****************************************************
// テクスチャクラス
//****************************************************
class CModel
{
public:

	//****************************************************
	// モデル識別
	//****************************************************
	enum class MODEL_TYPE
	{
		MODEL_000 = 0,	// テスト
		MAX,
	};

	CModel();	// コンストラクタ
	~CModel();	// デストラクタ

	HRESULT Load();	// モデル読込
	void Unload();	// モデル破棄

	MODEL* GetModel(MODEL_TYPE type);	// モデルを取得

private:

	bool LoadCheck();	// 読み込みテチェック

	static MODEL m_aModelTemp[static_cast<int>(MODEL_TYPE::MAX)];	// モデル管理
};

#endif // _MODEL_H_