//============================================================================
// 
// 物理演算 [physics.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "physics.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
const float CPhysics::GRAVITY_FORCE = -0.3f;	// 重力
CPhysics* CPhysics::m_pInstance = nullptr;		// インスタンス情報

//============================================================================
// 重力落下
//============================================================================
void CPhysics::Gravity(D3DXVECTOR3& vec)
{
	vec.y += GRAVITY_FORCE;
}

//============================================================================
// 球形の衝突判定
//============================================================================
bool CPhysics::Sphere(const D3DXVECTOR3& posSelf, const float& fRadiusSelf, const D3DXVECTOR3& posTarget, const float& fRadiusTarget)
{
	// 目標地点へのベクトルを算出
	D3DXVECTOR3 vec = posTarget - posSelf;

	// お互いの距離が、お互いの半径の和以下であれば衝突
	if (sqrtf(vec.x * vec.x + vec.y * vec.y) <= (fRadiusSelf + fRadiusTarget))
	{
		return 1;
	}

	return 0;
}

//============================================================================
// 立方形の衝突判定
//============================================================================
bool CPhysics::Cube(const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget)
{
	// 全ての軸方向からお互いにめり込んでいるとき衝突
	if (posSelf.x + sizeSelf.x > posTarget.x - sizeTarget.x &&
		posSelf.x - sizeSelf.x < posTarget.x + sizeTarget.x &&
		posSelf.y + sizeSelf.y > posTarget.y - sizeTarget.y &&
		posSelf.y - sizeSelf.y < posTarget.y + sizeTarget.y &&
		posSelf.z + sizeSelf.z > posTarget.z - sizeTarget.z &&
		posSelf.z - sizeSelf.z < posTarget.z + sizeTarget.z)
	{
		return 1;
	}

	return 0;
}

//============================================================================
// 押し出し処理
//============================================================================
bool CPhysics::CubeResponse(D3DXVECTOR3& posDest, D3DXVECTOR3& velocity, const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget)
{
	// 過去の位置がどちらかの軸方向に重なっていたかで処理分岐
	if (posSelf.x + sizeSelf.x > posTarget.x - sizeTarget.x &&
		posSelf.x - sizeSelf.x < posTarget.x + sizeTarget.x)
	{
		// Y軸方向の加速度をリセット
		velocity.y = 0.0f;

		if (posSelf.y < posTarget.y)
		{
			// 位置をこのブロックの上端に設定
			posDest.y = -sizeSelf.y + (posTarget.y - sizeTarget.y);
		}
		else if (posSelf.y > posTarget.y)
		{
			// 位置をこのブロックの下端に設定
			posDest.y = sizeSelf.y + (posTarget.y + sizeTarget.y);
		}

		return 1;
	}
	else if (posSelf.y + sizeSelf.y > posTarget.y - sizeTarget.y &&
		posSelf.y - sizeSelf.y < posTarget.y + sizeTarget.y)
	{
		// X軸方向の加速度をリセット
		velocity.x = 0.0f;

		if (posSelf.x < posTarget.x)
		{
			// 位置をこのブロックの左端に設定
			posDest.x = -sizeSelf.x + (posTarget.x - sizeTarget.x);
		}
		else if (posSelf.x > posTarget.x)
		{
			// 位置をこのブロックの右端に設定
			posDest.x = sizeSelf.x + (posTarget.x + sizeTarget.x);
		}

		return 1;
	}

	return 0;
}

//============================================================================
// 生成
//============================================================================
HRESULT CPhysics::Create()
{
	if (m_pInstance == nullptr)
	{
		// インスタンスを生成
		m_pInstance = DBG_NEW CPhysics();
	}

	if (m_pInstance == nullptr)
	{
		// 生成失敗
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// 破棄
//============================================================================
void CPhysics::Release()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;		// メモリ解放
		m_pInstance = nullptr;	// ポインタを初期化
	}
}

//============================================================================
// インスタンスを取得
//============================================================================
CPhysics* CPhysics::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// 取得失敗
		assert(false);
	}

	return m_pInstance;
}

//============================================================================
// コンストラクタ
//============================================================================
CPhysics::CPhysics()
{

}

//============================================================================
// デストラクタ
//============================================================================
CPhysics::~CPhysics()
{

}