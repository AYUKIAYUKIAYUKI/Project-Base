//============================================================================
// 
// ステージメーカー [stagemaker.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "stagemaker.h"
#include "manager.h"

#include "block.h"
#include "block_destructible.h"
#include "dummy.h"
#include "start.h"
#include "goal.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CStageMaker* CStageMaker::m_pInstance = nullptr;	// ステージメーカーのポインタ

//============================================================================
// 生成
//============================================================================
void CStageMaker::Create()
{
	if (m_pInstance != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// インスタンスを生成
	m_pInstance = DBG_NEW CStageMaker{};
}

//============================================================================
// 初期設定
//============================================================================
void CStageMaker::Init()
{

}

//============================================================================
// 解放
//============================================================================
void CStageMaker::Release()
{
	if (m_pInstance != nullptr)
	{
		// 終了処理
		m_pInstance->Uninit();

		// メモリを解放
		delete m_pInstance;

		// ポインタを初期化
		m_pInstance = nullptr;
	}
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
}

//============================================================================
// ステージ読み込み
//============================================================================
void CStageMaker::Import(std::string path)
{
	// ステージ保存情報を展開
	std::ifstream Import(path);

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
		std::string str_pos[3];

		for (int i = 0; i < 3; i++)
		{
			// 数値部分のみ抽出する
			str_pos[i] = str.substr(str.find(":") + 1, str.find(",") - (str.find(":") + 1));

			// 不必要になった部分を削除する
			str.erase(0, str.find(",") + 1);
		}

		// 抽出した数値を座標に変換
		pos.x = std::stof(str_pos[0]);
		pos.y = std::stof(str_pos[1]);
		pos.z = std::stof(str_pos[2]);

		// 種類を識別する文字格納先
		std::string str_type;

		// 種類を抽出する
		str_type = str.substr(str.find(":") + 1, str.find(",") - (str.find(":") + 1));

		// 種類に応じて生成する
		if (str_type == "block")
		{ // ブロック
			CBlock::Create(pos);
		}
		else if (str_type == "destructible")
		{ // 可壊ブロック
			CBlockDestructible::Create(pos);
		}
		else if (str_type == "start")
		{ // スタート
			CStart::Create(pos);
		}
		else if (str_type == "goal")
		{ // ゴール
			CGoal::Create(pos);
		}
		else
		{ // 不明
			assert(false);
			//CBlock::Create(pos);
		}
	}

	Import.close();	// ファイルを閉じる
}

//============================================================================
// 配置物の種類を参照
//============================================================================
int& CStageMaker::GetPatternRef()
{
	return m_nPattern;
}

//============================================================================
// 取得
//============================================================================
CStageMaker* CStageMaker::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// 生成
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// コンストラクタ
//============================================================================
CStageMaker::CStageMaker() : m_nPattern{ 0 }	// 配置物の種類識別
{

}

//============================================================================
// デストラクタ
//============================================================================
CStageMaker::~CStageMaker()
{

}

//============================================================================
// 操作
//============================================================================
void CStageMaker::Control()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_F2))
	{
		// スタートタイプのオブジェクトを取得
		CObject* pStart = CObject::FindObject(CObject::TYPE::START);

		// ゴールタイプのオブジェクトを取得
		CObject* pGoal = CObject::FindObject(CObject::TYPE::GOAL);

		if (pStart == nullptr || pGoal == nullptr)
		{ // スタート・ゴールタイプのオブジェクトの発見に失敗
			CManager::GetRenderer()->SetTimeString("【スタート・ゴールの配置情報が異常です！】", 180);
		}
		else
		{
			// ステージ書き出し
			Export();
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_Q))
	{
		m_nPattern > 0 ? m_nPattern-- : m_nPattern = 3;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_E))
	{
		m_nPattern < 3 ? m_nPattern++ : m_nPattern = 0;
	}

	CManager::GetRenderer()->SetDebugString("現在の配置物の種類:" + std::to_string(m_nPattern));

	if (CManager::GetKeyboard()->GetTrigger(DIK_F3))
	{
		// ステージ読み込み
		Import("Data\\TXT\\stage.txt");
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		// 設置
		Register();
	}
}

//============================================================================
// 設置
//============================================================================
void CStageMaker::Register()
{
	// ダミーを取得
	CDummy* pDummy = CDummy::DownCast(CObject::FindObject(CObject::TYPE::DUMMY));

	// ダミーの位置にオブジェクト生成
	switch (m_nPattern)
	{
	case 0:
		CBlock::Create(pDummy->GetPos());
		break;

	case 1:
		CBlockDestructible::Create(pDummy->GetPos());
		break;

	case 2:

		// スタートタイプのオブジェクトを検索
		if (!CObject::FindObject(CObject::TYPE::START))
		{
			CStart::Create(pDummy->GetPos());
		}
		else
		{
			CManager::GetRenderer()->SetTimeString("【スタートはすでに配置されています】", 60);
		}

		break;

	case 3:

		// スタートタイプのオブジェクトを検索
		if (!CObject::FindObject(CObject::TYPE::GOAL))
		{
			CGoal::Create(pDummy->GetPos());
		}
		else
		{
			CManager::GetRenderer()->SetTimeString("【ゴールはすでに配置されています】", 60);
		}

		break;

	default:
		assert(false);
		break;
	}
}

//============================================================================
// ステージ書き出し
//============================================================================
void CStageMaker::Export()
{
	// ステージ配置情報を書き出し展開
	std::ofstream Export("Data\\TXT\\stage.txt");

	// スタートオブジェクトを取得
	CStart* pStart = CStart::DownCast(CObject::FindObject(CObject::TYPE::START));

	// 情報を書き出す
	Output(Export, pStart->GetPos(), "start");

	// ゴールオブジェクトを取得
	CGoal* pGoal = CGoal::DownCast(CObject::FindObject(CObject::TYPE::GOAL));

	// 情報を書き出す
	Output(Export, pGoal->GetPos(), "goal");

	// ブロックタイプのオブジェクトをすべて取得
	CObject** pObject = CObject::FindAllObject(CObject::TYPE::BLOCK);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ブロッククラスへダウンキャスト
		CBlock* pBlock = CBlock::DownCast(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pBlock->GetPos(), "block");
	}

	// 可壊ブロックタイプのオブジェクトをすべて取得
	pObject = CObject::FindAllObject(CObject::TYPE::DESTRUCTIBLE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// 可壊ブロッククラスへダウンキャスト
		CBlockDestructible* pDestructible = CBlockDestructible::DownCast(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pDestructible->GetPos(), "destructible");
	}

	Export.close();	// ファイルを閉じる

	// デバッグ表示の期間を設定
	CManager::GetRenderer()->SetTimeString("【ステージを書き出しました】", 180);
}

//============================================================================
// 情報書き出し
//============================================================================
void CStageMaker::Output(std::ofstream& file, D3DXVECTOR3 pos, std::string str)
{
	// 座標を書き出す
	file << std::fixed << std::setprecision(1) << "X:" << pos.x << ",";
	file << std::fixed << std::setprecision(1) << "Y:" << pos.y << ",";
	file << std::fixed << std::setprecision(1) << "Z:" << pos.z << ",";

	// 種類を書き出す
	file << "type:" << str << "," << std::endl;
}