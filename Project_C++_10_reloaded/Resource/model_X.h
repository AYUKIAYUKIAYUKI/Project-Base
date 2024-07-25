//============================================================================
// 
// Xモデル管理、ヘッダファイル [model_X.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _MODEL_X_H_
#define _MODEL_X_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "main.h"

//****************************************************
// Xモデル管理クラス
//****************************************************
class CModel_X
{
public:

	//****************************************************
	// モデル識別
	//****************************************************
	enum class MODEL_TYPE
	{
		PLAYER_000 = 0,	// プレイヤー1
		PLAYER_001,		// プレイヤー2
		PLAYER_002,		// プレイヤー3
		PLAYER_003,		// プレイヤー4
		PLAYER_004,		// プレイヤー5
		PLAYER_005,		// プレイヤーゴール
		BLOCK_000,		// ブロック0
		DESTRUCTIBLE,	// 可壊ブロック
		START,			// スタート
		GOAL,			// ゴール
		LINE_X,			// X軸
		LINE_Y,			// Y軸
		MAX,
	};

	//****************************************************
	// モデル情報の構造体の定義
	//****************************************************
	struct MODEL
	{
		D3DXVECTOR3 size;			// サイズ
		LPD3DXMESH pMesh;			// メッシュ情報
		LPD3DXBUFFER pBuffMat;		// マテリアル情報
		DWORD dwNumMat;				// マテリアルの数
		LPDIRECT3DTEXTURE9* ppTex;	// テクスチャ情報
	};

	CModel_X();	// コンストラクタ
	~CModel_X();	// デストラクタ

	HRESULT Load();	// モデル読込
	void Unload();	// モデル破棄

	MODEL* GetModel(MODEL_TYPE type);	// モデルを取得

private:

	D3DXVECTOR3 ImportSize(std::string filename);	// サイズ読み込み

	static MODEL m_apModelTemp[static_cast<int>(MODEL_TYPE::MAX)];	// モデル管理
};

#endif // _MODEL_X_H_