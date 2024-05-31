//============================================================================
// 
// ブロック [block.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "block.h"
#include "manager.h"
#include "particle.h"

//============================================================================
// コンストラクタ
//============================================================================
CBlock::CBlock() : CObject2D(BACK_MIDDLE)
{

}

//============================================================================
// デストラクタ
//============================================================================
CBlock::~CBlock()
{
	// パーティクルを生成
	for (int i = 0; i < 10; i++)
	{
		CParticle::Create(
			CObject2D::GetPos(),	// 中心位置
			{ 20.0f, 20.0f, 0.0f },	// サイズ
			atan2f((float)(rand() % 314), (float)(rand() % 314)) * (rand() % 314));	// 飛ぶ角度
	}
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CBlock::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBlock::Uninit()
{
	// 基底クラスの終了処理
	CObject2D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBlock::Update()
{
	// 基底クラスの更新
	CObject2D::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CBlock::Draw()
{
	// 基底クラスの描画処理
	CObject2D::Draw();
}

//============================================================================
// 生成
//============================================================================
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// プレイヤーを生成
	CBlock* pBlock = new CBlock;

	// 生成出来ていたら初期設定
	if (pBlock != nullptr)
	{
		pBlock->SetType(TYPE::BLOCK);	// タイプを設定

		pBlock->Init();			// 基底クラスの初期設定
		pBlock->SetPos(pos);	// 中心位置の設定
		pBlock->SetSize(size);	// サイズの設定
	}

	// テクスチャを取得
	LPDIRECT3DTEXTURE9 pTex = CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::BLOCK_000);

	if (pTex == nullptr)
	{ // 取得失敗
		assert(false);
	}

	// テクスチャを設定
	pBlock->BindTex(pTex);

	return pBlock;
}