//============================================================================
// 
// カメラ [camera.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************s
// インクルードファイル
//****************************************************
#include "camera.h"
#include "main.h"

// インプット取得用
#include "manager.h"

// デバイス取得用
#include "renderer.h"

// 追従地点参照用
#include "game.h"
#include "player.h"
#include "dummy.h"
#include "stagemaker.h"

//============================================================================
// コンストラクタ
//============================================================================
CCamera::CCamera()
{
	m_pos = { 0.0f, 0.0f, 0.0f };			// 位置
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// 目標位置
	m_posV = { 0.0f, 0.0f, 0.0f };			// 視点位置
	m_posTargetV = { 0.0f, 0.0f, 0.0f };	// 目標視点位置
	m_posR = { 0.0f, 0.0f, 0.0f };			// 注視点位置
	m_posTargetR = { 0.0f, 0.0f, 0.0f };	// 目標注視点位置
	m_rot = { 0.0f, 0.0f, 0.0f };			// 向き
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// 目標向き
	m_fDistance = 300.0f;					// 視点 -> 注視点間の距離
	m_vecU = { 0.0f, 1.0f, 0.0f };			// 上方向ベクトル
	D3DXMatrixIdentity(&m_mtxProjection);	// プロジェクションマトリックス
	D3DXMatrixIdentity(&m_mtxView);			// ビューマトリックス
	m_fAdjust = 0.0f;						// 俯瞰度合
}

//============================================================================
// デストラクタ
//============================================================================
CCamera::~CCamera()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CCamera::Init()
{
	return S_OK;
}

//============================================================================
// 更新処理
//============================================================================
void CCamera::Update()
{
	// オブジェクト用ポインタ
	CObject* pObj;

	// プレイヤータイプのオブジェクトを取得
	pObj = CObject::FindObject(CObject::TYPE::PLAYER);

	if (pObj != nullptr)
	{ // プレイヤータイプの取得に成功

		// プレイヤークラスにダウンキャスト
		CPlayer* pPlayer = CPlayer::DownCast(pObj);

		// 位置を同期
		m_pos = pPlayer->GetPos();
		m_fAdjust = 50.0f;
	}
	else
	{ // プレイヤータイプの取得に失敗

		// ダミータイプのオブジェクトを取得
		pObj = CObject::FindObject(CObject::TYPE::DUMMY);

		if(pObj != nullptr)
		{ // ダミータイプの取得に成功

			// ダミークラスにダウンキャスト
			CDummy* pDummy = CDummy::DownCast(pObj);

			// 位置を同期
			m_pos = pDummy->GetPos();
			m_fAdjust = 0.0f;
		}
	}

	// 位置をデバッグ表示
	//CRenderer::GetInstance()->SetDebugString("【カメラ位置】");
	//std::ostringstream oss;
	//oss << std::fixed << std::setprecision(1) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	//CRenderer::GetInstance()->SetDebugString(oss.str().c_str());

	// カメラ操作
	Control();

	// 回転
	Rotation();

	// 移動
	//Translation();

	// ヨー角の範囲を制限
	RestrictYaw();

	// ピッチ角の範囲を制限
	RestrictPitch();

	// 視点位置を算出
	CalcPosV();

	// 注視点位置を算出
	CalcPosR();
}

//============================================================================
// カメラをセット
//============================================================================
void CCamera::SetCamera()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// 画面バッファクリア
	pDev->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// プロジェクション行列を計算
	CalcMtxProjection();
	
	// ビュー行列を計算
	CalcMtxView();
}

//============================================================================
// 位置を取得
//============================================================================
D3DXVECTOR3 CCamera::GetPos()
{
	return m_pos;
}

//============================================================================
// 位置を設定
//============================================================================
void CCamera::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================================================
// 目標位置を取得
//============================================================================
D3DXVECTOR3 CCamera::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// 目標位置を設定
//============================================================================
void CCamera::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// 向きを取得
//============================================================================
D3DXVECTOR3 CCamera::GetRot()
{
	return m_rot;
}

//============================================================================
// カメラ操作
//============================================================================
void CCamera::Control()
{
	// ズームイン / アウト
	if (CManager::GetKeyboard()->GetPress(DIK_AT) && m_fDistance > 10.0f)
	{
		m_fDistance -= 10.0f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_COLON))
	{
		m_fDistance += 10.0f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_BACKSLASH))
	{
		// 距離間リセット
		m_fDistance = 200.0f;
	}

	// 左右
	if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))
	{
		m_rotTarget.y += 0.02f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_LEFT))
	{
		m_rotTarget.y -= 0.02f;
	}

	// 上下
	if (CManager::GetKeyboard()->GetPress(DIK_UP))
	{
		m_rotTarget.x += 0.02f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_DOWN))
	{
		m_rotTarget.x -= 0.02f;
	}
}

//============================================================================
// 回転
//============================================================================
void CCamera::Rotation()
{
	// 回転量減衰
	m_rotTarget *= 0.8f;

	// 回転量反映
	m_rot += m_rotTarget * 0.5f;
}

//============================================================================
// 移動
//============================================================================
void CCamera::Translation()
{
	// 追従度合
	float fTracking = 0.25f;

	// 移動量反映
	// posTargetに値を設定していない場合は数値がおかしくなります
	m_pos += (m_posTarget - m_pos) * fTracking;
}

//============================================================================
// ヨー角の範囲を制限
//============================================================================
void CCamera::RestrictYaw()
{
	// 回転の制限
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}
}

//============================================================================
// ピッチ角の範囲を制限
//============================================================================
void CCamera::RestrictPitch()
{
	if (m_rot.x + m_rotTarget.x > D3DX_PI * 0.48f)
	{
		m_rot.x = D3DX_PI * 0.48f;
	}
	else if (m_rot.x + m_rotTarget.x < -D3DX_PI * 0.48f)
	{
		m_rot.x = -D3DX_PI * 0.48f;
	}
}

//============================================================================
// 視点位置を算出
//============================================================================
void CCamera::CalcPosV()
{
	// 視点は対象物の後方に
	m_posV =
	{
		m_pos.x - (sinf(m_rot.y) * cosf(m_rot.x) * (m_fDistance)),
		m_pos.y - (sinf(m_rot.x) * (m_fDistance)),
		m_pos.z - (cosf(m_rot.y) * cosf(m_rot.x) * (m_fDistance))
	};
}

//============================================================================
// 注視点位置を算出
//============================================================================
void CCamera::CalcPosR()
{
	// 注視点を対象物の前方に
	m_posR =
	{
		m_pos.x + (sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance),
		m_pos.y + (sinf(m_rot.x) * m_fDistance),
		m_pos.z + (cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance)
	};
}

//============================================================================
// プロジェクション行列計算
//============================================================================
void CCamera::CalcMtxProjection()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// プロジェクション行列の初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクション行列を生成
#if 1
	// 透視投影
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		5000.0f);

	static float eiieei = 0.0f;
	float f = 1.0f;
	if (CManager::GetKeyboard()->GetPress(DIK_T))
	{
		eiieei += -f;
	}
	else if(CManager::GetKeyboard()->GetPress(DIK_Y))
	{
		eiieei += f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_U))
	{
		eiieei = 0.0f;
	}
	std::string str = std::to_string(eiieei);
	CRenderer::GetInstance()->SetDebugString(str);
	m_mtxProjection._44 += eiieei;
	
#else
	// 平行投影
	D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_WIDTH * 0.25f,
		(float)SCREEN_HEIGHT * 0.25f,
		10.0f,
		5000.0f);
#endif

	// プロジェクション行列の設定
	pDev->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}

//============================================================================
// ビュー行列計算
//============================================================================
void CCamera::CalcMtxView()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// 視点位置の調整用
	D3DXVECTOR3 posV = m_posV;
	D3DXVECTOR3 posR = m_posR;

	// カメラを俯瞰気味に
	posV.y += m_fAdjust;

	// ビューマトリックスの生成
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,
		&posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDev->SetTransform(D3DTS_VIEW,
		&m_mtxView);
}