//============================================================================
// 
// テクスチャマネージャー、ヘッダファイル [texture_manager.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_	// 二重インクルード防止

//****************************************************
// テクスチャマネージャークラス
//****************************************************
class CTexture_Manager final
{
public:

	//****************************************************
	// テクスチャ識別
	//****************************************************
	enum class TYPE
	{
		BG_000 = 0,		// 背景000
		BG_001,			// 背景001
		ARROW,			// 矢印
		RING,			// リング
		SQUARE_00,		// マス目1
		LEAF_00,		// 葉っぱ00
		LEAF_01,		// 葉っぱ01
		LEAF_02,		// 葉っぱ02
		LEAF_03,		// 葉っぱ03
		LEAF_04,		// 葉っぱ04
		NUMBER_00,		// 数字00
		LASTTIME,		// ラストタイム
		BESTTIME,		// ベストタイム
		BACK,			// 戻るマーク
		CROWN,			// 王冠
		TEXT00,			// テキスト00
		TEXT01,			// テキスト01
		MAX,
	};

	HRESULT Load();	// テクスチャ読込
	void Release();	// 解放

	LPDIRECT3DTEXTURE9 GetTexture(TYPE type);	// テクスチャを取得

	static CTexture_Manager* GetInstance();	// テクスチャマネージャーを取得

private:

	CTexture_Manager();		// コンストラクタ
	~CTexture_Manager();	// デストラクタ

	void Create();	// 生成
	void Unload();	// テクスチャ破棄

	LPDIRECT3DTEXTURE9 m_apTexTemp[static_cast<int>(TYPE::MAX)];	// テクスチャ情報

	static CTexture_Manager* m_pInstance;	// テクスチャマネージャー
};

#endif // _TEXTURE_MANAGER_H_