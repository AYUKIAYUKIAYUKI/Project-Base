//============================================================================
// 
// タイム、ヘッダファイル [timer.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _TIMER_H_
#define _TIMER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"
#include "number.h"
#include "game_manager.h"

//****************************************************
// タイムクラス
//****************************************************
class CTimer : public CObject_2D
{
public:

	CTimer();			// デフォルトコンストラクタ
	~CTimer() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CTimer* Create();						// 生成
	static void SwitchControlByPahse(int nSelect);	// フェーズによる動作切替
	static void ExportTimer(int nTimer);			// タイムの書き出し

private:

	static const int MAX_DIGIT = 4;	// 最大桁数

	int ImportTimer(int nSelect);	// タイムの読み込み
	void Appear();					// 出現
	void Disappear();				// 消滅

	bool m_bAppear;					// 出現フラグ
	bool m_bDisappear;				// 消滅フラグ
	int m_nCntFrame;				// フレームカウント
	int m_nTimer;					// タイム情報
	D3DXVECTOR3 m_posTarget;		// 目標座標
	CNumber* m_apNumber[MAX_DIGIT];	// 数字情報
};

#endif	// _TIMER_H_