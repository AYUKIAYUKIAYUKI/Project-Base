//============================================================================
// 
// テクスチャ管理、ヘッダファイル [texture.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _TEXTURE_H_
#define _TEXTURE_H_	// 二重インクルード防止

//****************************************************
// テクスチャクラス
//****************************************************
class CTexture
{
public:

	//****************************************************
	// テクスチャ識別
	//****************************************************
	enum TEX_TYPE
	{
		BG_000 = 0,		// 背景000
		BG_001,			// 背景001
		NUMBER_000,		// 数字000
		PLAYER_000,		// プレイヤー000
		BULLET_000,		// 弾000
		EFFECT_000,		// エフェクト000
		EXPLOSION_000,	// 爆発000
		ENEMY_000,		// 敵000
		MAX,
	};

	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

	HRESULT Load();	// テクスチャ読込
	void Unload();	// テクスチャ破棄

	LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE type);	// テクスチャを取得

private:

	static LPDIRECT3DTEXTURE9 m_apTexTemp[TEX_TYPE::MAX];	// テクスチャ管理
};

#endif // _ENEMY_H_