//============================================================================
// 
// Xモデルマネージャー、ヘッダファイル [model_X_manager.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _MODEL_X_MANAGER_H_
#define _MODEL_X_MANAGER_H_	// 二重インクルード防止

//****************************************************
// Xモデルマネージャークラス
//****************************************************
class CModel_X_Manager final
{
public:

	//****************************************************
	// モデル識別
	//****************************************************
	enum class TYPE
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

	HRESULT Load();	// モデル読込
	void Release();	// 解放

	MODEL* GetModel(TYPE type);	// モデルを取得

	static CModel_X_Manager* GetInstance();	// Xモデルマネージャーを取得

private:

	CModel_X_Manager();		// コンストラクタ
	~CModel_X_Manager();	// デストラクタ

	void Create();									// 生成
	D3DXVECTOR3 ImportSize(std::string filename);	// サイズ読み込み
	void Unload();									// モデル破棄

	MODEL m_apModelTemp[static_cast<int>(TYPE::MAX)];	// Xモデル情報

	static CModel_X_Manager* m_pInstnce;	// Xモデルマネージャー
};

#endif // _MODEL_X_MANAGER_H_