//============================================================================
// 
// ゲーム、ヘッダファイル [game.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _GAME_H_
#define _GAME_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "scene.h"

//****************************************************
// ゲームクラス
//****************************************************
class CGame : public CScene
{
public:

	CGame();			// コンストラクタ
	~CGame() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理
};

#endif // _GAME_H_