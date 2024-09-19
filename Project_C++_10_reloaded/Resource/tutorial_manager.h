//============================================================================
// 
// チュートリアル、ヘッダファイル [tutorial_manager.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _TUTORIAL_MANAGER_H_
#define _TUTORIAL_MANAGER_H	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "text.h"

//****************************************************
// チュートリアルマネージャークラス
//****************************************************
class CTutorial_Manager
{
public:

	static void UpdateTutorial();	// チュートリアルの更新
	static void DeleteInstance();	// 削除

private:

	CTutorial_Manager();	// デフォルトコンストラクタ
	~CTutorial_Manager();	// デストラクタ

	void CreateText();		// テキストの生成
	void DeleteText();		// テキストの削除
	void CheckPlayerPos();	// プレイヤーの座標を確認
	
	static void CreateInstance();	// 生成

	CText* m_pText;	// テキストのポインタ

	static CTutorial_Manager* m_pInstance;	// 自クラスのポインタ
};

#endif	// _TUTORIAL_MANAGER_H