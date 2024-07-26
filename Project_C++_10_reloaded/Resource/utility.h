//============================================================================
// 
// 便利関数群、ヘッダファイル [utility.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _UTILITY_H_
#define _UTILITY_H_	// 二重インクルード防止

//****************************************************
// 便利関数群クラス
//****************************************************
class CUtility final
{
public:

	HRESULT Init();	// 初期設定
	void Release();	// 破棄

	static CUtility* GetInstance();	// 便利関数群を取得

	// 重力落下
	void Gravity(D3DXVECTOR3& vec);

	// 球体の衝突判定
	bool OnlySphere(const D3DXVECTOR3& posSelf, const float& fRadiusSelf, const D3DXVECTOR3& posTarget, const float& fRadiusTarget);

	// 球体と立方体の衝突判定
	bool SphereAndCube(const D3DXVECTOR3& posSph, const float& fRadius, const D3DXVECTOR3& posCube, const D3DXVECTOR3& size);

	// 立方体の衝突判定
	bool OnlyCube(const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget);

	// 押し出し処理
	bool CubeResponse(D3DXVECTOR3& posDest, D3DXVECTOR3& velocity, const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget);

private:

	static const float GRAVITY_FORCE;	// 重力

	CUtility();		// コンストラクタ
	~CUtility();	// デストラクタ

	void Create();	// 生成
	void Uninit();	// 終了処理

	static CUtility* m_pInstance;	// 便利関数群
};

#endif // _UTILITY_H_