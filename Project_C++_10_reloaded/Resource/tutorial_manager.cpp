//============================================================================
// 
// チュートリアルマネージャー [tutorial_manager.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "tutorial_manager.h"
#include "utility.h"

// デバッグ表示用
#include "renderer.h"

// プレイヤー取得用
#include "player.h"
#include "player_state.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CTutorial_Manager* CTutorial_Manager::m_pInstance = nullptr;	// 自クラスのポインタ

//============================================================================
// 更新
//============================================================================
void CTutorial_Manager::UpdateTutorial()
{
	if (!m_pInstance)
	{
		// 生成
		CTutorial_Manager::CreateInstance();
	}

	// プレイヤーの座標を確認
	m_pInstance->CheckPlayerPos();
}

//============================================================================
// 削除
//============================================================================
void CTutorial_Manager::DeleteInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CTutorial_Manager::CTutorial_Manager() :
	m_pText{ nullptr }
{

}

//============================================================================
// デストラクタ
//============================================================================
CTutorial_Manager::~CTutorial_Manager()
{
	// 省略
	if (m_pText)
	{
		m_pText->SetDisappear(true);
		m_pText->SetPosTarget(D3DXVECTOR3{ 0.0f, SCREEN_HEIGHT + 100.0f, 0.0f });
		m_pText->SetSizeTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
		m_pText = nullptr;
	}
}

//============================================================================
// 生成
//============================================================================
void CTutorial_Manager::CreateInstance()
{
	if (m_pInstance != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// チュートリアルマネージャーを生成
	m_pInstance = DBG_NEW CTutorial_Manager{};
}

//============================================================================
// テキストの生成
//============================================================================
void CTutorial_Manager::CreateText()
{
	if (!m_pText)
	{
		// テキストの生成
		m_pText = CText::Create(CTexture_Manager::TYPE::TEXT00);

		// 出現設定
		m_pText->SetAppear(true);

		// 目標座標を設定
		m_pText->SetPosTarget(D3DXVECTOR3{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f });

		// 目標サイズを設定
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f, 50.0f, 0.0f });
	}
}

//============================================================================
// テキストの削除
//============================================================================
void CTutorial_Manager::DeleteText()
{
	// 省略
	if (m_pText)
	{
		m_pText->SetDisappear(true);
		m_pText->SetPosTarget(D3DXVECTOR3{ 0.0f, SCREEN_HEIGHT + 100.0f, 0.0f });
		m_pText->SetSizeTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
		m_pText = nullptr;
	}
}

//============================================================================
// プレイヤーの座標を確認
//============================================================================
void CTutorial_Manager::CheckPlayerPos()
{
	// プレイヤータグを取得
	CObject* pObj{ CObject::FindObject(CObject::TYPE::PLAYER) };

	// 取得失敗
	if (!pObj)
	{
		return;
	}

	// プレイヤークラスにダウンキャスト
	CPlayer* pPlayer{ CUtility::GetInstance()->DownCast<CPlayer, CObject>(pObj) };

	// 状態に応じてテキスト操作
	if (typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateGoal))
	{
		// テキストを削除
		DeleteText();

		// 以降テキストをいじらない
		return;
	}
	else
	{
		// テキストを生成
		CreateText();
	}

	// テキストの目標座標を設定
	m_pText->SetPosTarget(D3DXVECTOR3{ SCREEN_WIDTH * 0.5f, (SCREEN_HEIGHT * 0.8f) + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });

	// プレイヤーの座標をコピー
	D3DXVECTOR3 Pos{ pPlayer->GetPos() };
}