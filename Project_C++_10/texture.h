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
		BG_000 = 0,		// 背景
		PLAYER_000,		// プレイヤー
		BULLET_000,		// 弾
		EXPLOSION_000,	// 爆発
		ENEMY_000,		// 敵
		MAX,
	};

	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

	HRESULT Load();	// テクスチャ読込
	void Unload();	// テクスチャ破棄

	LPDIRECT3DTEXTURE9 GetTex(TEX_TYPE type);	// テクスチャを取得

private:

	static const int MAX_TEX = 64;	// 最大テクスチャ数

	// ↓これは削除しろ->あとテクスチャマネージャーは順序的にレンダラーのメンバの方が楽そう
	const char* m_aFilename[TEX_TYPE::MAX] = {
		"data\\TEXTURE\\KOME.png",
		"data\\TEXTURE\\runningman000.png",
		"data\\TEXTURE\\bullet000.png",
		"data\\TEXTURE\\explosion000.png",
		"data\\TEXTURE\\AL-1S.png",
	};

	static LPDIRECT3DTEXTURE9 m_apTexTemp[MAX_TEX];	// テクスチャ管理
};

#endif // _ENEMY_H_