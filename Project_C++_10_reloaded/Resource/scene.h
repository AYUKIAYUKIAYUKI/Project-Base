//============================================================================
// 
// シーン管理、ヘッダファイル [scene.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _SCENE_H_
#define _SCENE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "fade.h"

//****************************************************
// シーン管理クラス
//****************************************************
class CScene
{
public:

	//****************************************************
	// シーンの種類
	//****************************************************
	enum class MODE
	{
		TITLE = 0,
		GAME,
		RESULT,
		MAX,
	};

	CScene();			// コンストラクタ
	virtual ~CScene();	// デストラクタ

	virtual HRESULT Init();	// 初期設定
	virtual void Uninit();	// 終了処理
	virtual void Update();	// 更新処理
	virtual void Draw();	// 描画処理

	static CScene* Create(MODE mode);	// 生成

private:

	CFade* m_pFade;	// フェード情報

	MODE m_mode;	// 現在のモード
};

#endif // _SCENE_H_