//============================================================================
// 
// 便利関数群 [utility.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "utility.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
const float CUtility::GRAVITY_FORCE = -0.15f;	// 重力
CUtility* CUtility::m_pInstance = nullptr;		// 便利関数群

//============================================================================
// 初期設定
//============================================================================
HRESULT CUtility::Init()
{
	return S_OK;
}

//============================================================================
// 破棄
//============================================================================
void CUtility::Release()
{
	if (m_pInstance != nullptr)
	{
		// 終了処理
		m_pInstance->Uninit();

		// メモリ解放
		delete m_pInstance;	

		// ポインタを初期化
		m_pInstance = nullptr;
	}
}

//============================================================================
// 便利関数群を取得
//============================================================================
CUtility* CUtility::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// 生成
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// 重力落下
//============================================================================
void CUtility::Gravity(D3DXVECTOR3& vec)
{
	vec.y += GRAVITY_FORCE;
}

//============================================================================
// 球形の衝突判定
//============================================================================
bool CUtility::OnlySphere(const D3DXVECTOR3& posSelf, const float& fRadiusSelf, const D3DXVECTOR3& posTarget, const float& fRadiusTarget)
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
// 球と立方体の当たり判定
//============================================================================
bool CUtility::SphereAndCube(const D3DXVECTOR3& posSph, const float& fRadius, const D3DXVECTOR3& posCube, const D3DXVECTOR3& size)
{
	// 全ての軸方向からお互いにめり込んでいるとき衝突
	if (posSph.x + fRadius > posCube.x - size.x &&
		posSph.x - fRadius < posCube.x + size.x &&
		posSph.y + fRadius > posCube.y - size.y &&
		posSph.y - fRadius < posCube.y + size.y &&
		posSph.z + fRadius > posCube.z - size.z &&
		posSph.z - fRadius < posCube.z + size.z)
	{
		return 1;
	}

	return 0;
}

//============================================================================
// 立方形の衝突判定
//============================================================================
bool CUtility::OnlyCube(const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget)
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
bool CUtility::CubeResponse(D3DXVECTOR3& posDest, D3DXVECTOR3& velocity, const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget)
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
// コンストラクタ
//============================================================================
CUtility::CUtility()
{

}

//============================================================================
// デストラクタ
//============================================================================
CUtility::~CUtility()
{

}

//============================================================================
// 生成
//============================================================================
void CUtility::Create()
{
	if (m_pInstance != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// インスタンスを生成
	m_pInstance = DBG_NEW CUtility{};
}

//============================================================================
// 終了処理
//============================================================================
void CUtility::Uninit()
{

}