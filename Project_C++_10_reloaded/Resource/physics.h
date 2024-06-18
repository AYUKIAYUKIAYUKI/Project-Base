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

	void Gravity();				// 重力落下
	bool Collision_Sphere();	// 球体の衝突判定
	bool Collision_Cube();		// 立方体の衝突判定
	bool Collision_Response();	// 押し出し処理

	static HRESULT Create();	// 生成
	static void Release();		// 破棄
	static CPhysics* GetInstance();	// インスタンスを取得

private:

	CPhysics();		// コンストラクタ
	~CPhysics();	// デストラクタ

	static CPhysics* m_pInstance;	// インスタンス情報
};

#endif // _PHISICS_H_