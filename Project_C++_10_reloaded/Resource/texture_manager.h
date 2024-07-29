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
		BG_000 = 0,		// 背景0
		BG_001,			// 背景1
		BLOCK_000,		// ブロック0
		BULLET_000,		// 弾0
		EFFECT_000,		// エフェクト0
		ENEMY_000,		// 敵0
		EXPLOSION_000,	// 爆発0
		ITEM_000,		// アイテム0
		NUMBER_000,		// 数字0
		PLAYER_000,		// プレイヤー0
		PLAYER_001,		// プレイヤー1
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

#endif // _TEXTURE_H_