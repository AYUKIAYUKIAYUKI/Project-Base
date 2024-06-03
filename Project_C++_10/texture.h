//============================================================================
// 
// テクスチャ管理、ヘッダファイル [texture.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _TEXTURE_H_
#define _TEXTURE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "vector"

//****************************************************
// テクスチャクラス
//****************************************************
class CTexture
{
public:

	//****************************************************
	// テクスチャ識別
	//****************************************************
	enum class TEX_TYPE
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

	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

	HRESULT Load();	// テクスチャ読込
	void Unload();	// テクスチャ破棄

	LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE type);	// テクスチャを取得

private:

	static LPDIRECT3DTEXTURE9 m_apTexTemp[static_cast<int>(TEX_TYPE::MAX)];	// テクスチャ管理
};

#endif // _ENEMY_H_