//============================================================================
// 
// スコア [score.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "score.h"

// インプット取得用
#include "manager.h"

//****************************************************
// 静的メンバの初期化
//****************************************************
CNumber* CScore::m_apNumber[MAX_DIGIT];	// 数字管理

//============================================================================
// コンストラクタ
//============================================================================
CScore::CScore() : CObject(static_cast<int>(LAYER::UI))
{
	m_nScore = 0;		// 現在のスコア
	m_nScore_old = 0;	// 過去のスコア
	m_pos = {};			// 数列の先頭位置
	m_fSpan = 0.0f;		// 数列の配置間隔
}

//============================================================================
// デストラクタ
//============================================================================
CScore::~CScore()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CScore::Init()
{
	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CScore::Uninit()
{

}

//============================================================================
// 更新処理
//============================================================================
void CScore::Update()
{
	// デバッグ用
	if (CManager::GetKeyboard()->GetTrigger(DIK_P))
	{
		m_nScore += 123;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_O))
	{
		m_nScore -= 123;
	}

	// 変動制限
	Adjust();
	
	// スコアに変動があればパーティクルを飛ばす
	if (m_nScore_old != m_nScore)
	{
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			D3DXVECTOR3 pos = {
				m_pos.x + (m_fSpan * ((MAX_DIGIT - 1) - nCntNum)),
				m_pos.y,
				0.0f,
			};

			//// パーティクルを生成
			//for (int i = 0; i < 20; i++)
			//{
			//	CParticle::Create(
			//		pos,					// 位置
			//		{ 15.0f, 15.0f, 0.0f },	// サイズ
			//		atan2f((float)(rand() % 314), (float)(rand() % 314)) * (rand() % 314));	// 飛ぶ角度
			//}
		}
	}

	// アニメーション
	Animation();

	// スコアを保存
	m_nScore_old = m_nScore;
}

//============================================================================
// 描画処理
//============================================================================
void CScore::Draw()
{

}

//============================================================================
// 現在のスコア取得
//============================================================================
int CScore::GetScore()
{
	return m_nScore;
}

//============================================================================
// 現在のスコア設定
//============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//============================================================================
// 生成
//============================================================================
CScore* CScore::Create(D3DXVECTOR3 pos, float fSpan)
{
	// インスタンスを生成
	CScore* pScore = DBG_NEW CScore;

	if (pScore == nullptr)
	{ // 生成失敗
		assert(false);
	}

	pScore->SetType(TYPE::SCORE);	// タイプを設定

	pScore->Init();				// 初期設定
	pScore->m_pos = pos;		// 数列の先頭位置
	pScore->m_fSpan = fSpan;	// 数列の配置間隔

	// 必要な数分数字を用意する
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		m_apNumber[nCntNum] = CNumber::Create(
			{ pScore->m_pos.x + (pScore->m_fSpan * ((MAX_DIGIT - 1) - nCntNum)),	// X座標位置
			pScore->m_pos.y, 0.0f },												// Y座標位置
			{ 25.0f, 20.0f, 0.0f });												// サイズ
	}

	return pScore;
}

//============================================================================
// 変動制限
//============================================================================
void CScore::Adjust()
{
	if (m_nScore > MAX_SCORE)
	{
		m_nScore = MAX_SCORE;
	}
	else if (m_nScore < 0)
	{
		m_nScore = 0;
	}
}

//============================================================================
// アニメーション
//============================================================================
void CScore::Animation()
{
	// スコアのコピーを作成
	int nScoreCopy = m_nScore;

	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 数字を設定
		m_apNumber[nCntNum]->SetNumber(nScoreCopy % 10);

		// 桁を減らす
		nScoreCopy /= 10;
	}
}