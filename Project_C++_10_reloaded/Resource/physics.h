//============================================================================
// 
// 物理演算、ヘッダファイル [physics.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _PHISICS_H_
#define _PHISICS_H_	// 二重インクルード防止

//****************************************************
// 物理演算クラス
//****************************************************
class CPhysics
{
public:

	void Gravity(D3DXVECTOR3& vec);	// 重力落下

	bool Sphere(const D3DXVECTOR3& posSelf, const float& fRadiusSelf, const D3DXVECTOR3& posTarget, const float& fRadiusTarget);	// 球体の衝突判定
	bool Cube(const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget);	// 立方体の衝突判定
	bool CubeResponse(D3DXVECTOR3& posDest, D3DXVECTOR3& velocity, const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget);	// 押し出し処理

	static HRESULT Create();		// 生成
	static void Release();			// 破棄
	static CPhysics* GetInstance();	// インスタンスを取得

private:

	static const float GRAVITY_FORCE;	// 重力

	CPhysics();		// コンストラクタ
	~CPhysics();	// デストラクタ

	static CPhysics* m_pInstance;	// インスタンス情報
};

#endif // _PHISICS_H_