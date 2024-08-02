//============================================================================
// 
// 煙エフェクト、ヘッダファイル [smoke.h]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "Object_X.h"

//****************************************************
// 煙エフェクトクラス
//****************************************************
class CSmoke : public CObject_X
{
public:

	CSmoke();	// コンストラクタ
	~CSmoke();	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3& GetVelocity();				// 加速度を取得
	void SetVelocity(D3DXVECTOR3 velocity);	// 加速度を設定

	static CSmoke* Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity);	// 生成

private:

	D3DXVECTOR3 m_velocity;	// 加速度
};