//============================================================================
// 
// ステージ作成 [stagemaker.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "stagemaker.h"
#include "manager.h"

#include "block.h"
#include "dummy.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CStageMaker* CStageMaker::m_pStageMaker = nullptr;	// 自身のインスタンス

//============================================================================
// コンストラクタ
//============================================================================
CStageMaker::CStageMaker()
{
	m_pStageMaker = nullptr;	// 自身のインスタンス

	m_nCntMessage = 0;	// メッセージ表示期間
}

//============================================================================
// デストラクタ
//============================================================================
CStageMaker::~CStageMaker()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CStageMaker::Init()
{
	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CStageMaker::Uninit()
{

}

//============================================================================
// 更新処理
//============================================================================
void CStageMaker::Update()
{
	// 操作
	Control();

	// デバッグ表示 (ステージ書き出し)
	if (m_nCntMessage > 0)
	{
		m_nCntMessage--;

		// デバッグ表示
		CManager::GetRenderer()->SetDebugString("【ステージを書き出しました】");
	}
}

//============================================================================
// ステージ読み込み
//============================================================================
void CStageMaker::Import()
{
	// ステージ保存情報を展開
	std::ifstream Import("Data\\TXT\\stage.txt");

	if (!Import)
	{ // 展開に失敗
		assert(false);
	}

	// 文章格納先
	std::string str;

	// テキストを読み取る
	while (std::getline(Import, str))
	{
		// 座標格納先
		D3DXVECTOR3 pos = {};

		// 数値となる文字格納先
		std::string strf[3];

		// 数値を抽出する
		strf[0] = str.substr(str.find("X") + 2, str.find(","));
		strf[1] = str.substr(str.find("Y") + 2, str.find(","));
		strf[2] = str.substr(str.find("Z") + 2, str.find(","));

		// 抽出した数値を座標に変換
		pos.x = std::stof(strf[0]);
		pos.y = std::stof(strf[1]);
		pos.z = std::stof(strf[2]);

		// ブロックを生成
		CBlock::Create(pos);
	}

	Import.close();	// ファイルを閉じる
}

//============================================================================
// 生成
//============================================================================
HRESULT CStageMaker::Create()
{
	if (m_pStageMaker == nullptr)
	{
		// インスタンスを生成
		m_pStageMaker = DBG_NEW CStageMaker();
	}

	if (m_pStageMaker == nullptr)
	{
		// 生成失敗
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// 破棄
//============================================================================
void CStageMaker::Release()
{
	if (m_pStageMaker != nullptr)
	{
		// メモリを解放
		delete m_pStageMaker;

		// ポインタを初期化
		m_pStageMaker = nullptr;
	}
}

//============================================================================
// ステージ作成クラス取得
//============================================================================
CStageMaker* CStageMaker::GetInstance()
{
	return m_pStageMaker;
}

//============================================================================
// 操作
//============================================================================
void CStageMaker::Control()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_F2))
	{
		// ステージ書き出し
		Export();
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_F3))
	{
		// ステージ読み込み
		Import();
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		// 設置
		Regist();
	}
}

//============================================================================
// 設置
//============================================================================
void CStageMaker::Regist()
{
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(CObject::LAYER::MAX); nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// オブジェクト情報を取得
			CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{ // 情報がなければコンティニュー
				continue;
			}

			if (pObject->GetType() == CObject::TYPE::DUMMY)
			{ // ダミータイプなら

				// オブジェクトクラスをダミークラスへダウンキャスト
				CDummy* pDummy = dynamic_cast<CDummy*>(pObject);

				if (pDummy == nullptr)
				{ // ダウンキャスト失敗
					assert(false);
				}

				// ダミーの位置にブロックを生成
				CBlock::Create(pDummy->GetPos());
			}
		}
	}
}

//============================================================================
// ステージ書き出し
//============================================================================
void CStageMaker::Export()
{
	// ステージ配置情報を書き出し展開
	std::ofstream Export("Data\\TXT\\stage.txt");

	for (int nCntPriority = 0; nCntPriority < static_cast<int>(CObject::LAYER::MAX); nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// オブジェクト情報を取得
			CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{ // 情報がなければコンティニュー
				continue;
			}

			if (pObject->GetType() == CObject::TYPE::BLOCK)
			{ // ブロックタイプなら

				// オブジェクトクラスをブロッククラスへダウンキャスト
				CBlock* pBlock = dynamic_cast<CBlock*>(pObject);

				if (pBlock == nullptr)
				{ // ダウンキャスト失敗
					assert(false);
				}

				// 座標を書き出す
				Export << std::fixed << std::setprecision(1) << "X:" << pBlock->GetPos().x << "," << "Y:" << pBlock->GetPos().y << "," << "Z:" << pBlock->GetPos().z << "," << std::endl;

				// デバッグ表示の期間を設定
				m_nCntMessage = 180;
			}
		}
	}

	Export.close();	// ファイルを閉じる
}