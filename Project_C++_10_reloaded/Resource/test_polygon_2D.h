//============================================================================
// 
// テスト用ポリゴン、ヘッダファイル [test_polygon_2D.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _TEST_POLYGON_2D_H_
#define _TEST_POLYGON_2D_H_	// 二重インクルード防止

//****************************************************
// テスト用ポリゴンクラス
//****************************************************
class CTestPolygon2D
{
public:

	CTestPolygon2D();	// コンストラクタ
	~CTestPolygon2D();	// デストラクタ

	HRESULT Init();	// 初期設定
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画処理
	void Create();	// 生成
	void Release();	// 解放

	static CTestPolygon2D* GetInstance();	// 取得

private:

	static CTestPolygon2D* m_pInstance;	// 自クラス情報

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTex;			// テクスチャ情報のポインタ
	LPDIRECT3DSURFACE9 m_pSurface;		// サーフェイス情報のポインタ
};

#endif // _TEST_POLYGON_2D_H_