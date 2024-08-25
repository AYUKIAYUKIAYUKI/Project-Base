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
#include "utility.h"

// キーボード取得用
#include "manager.h"

// デバッグ表示用
#include "renderer.h"

// オブジェクト配置用
#include "block.h"
#include "block_destructible.h"
#include "block_spikes.h"
#include "dummy.h"
#include "enemy.h"
#include "goal.h"
#include "line.h"
#include "start.h"

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

	// モデルパターン譲渡用
	int nPattern = 0;

	// 配置モードなら現在のモデル、編集モードならそれ以外を指定
	m_bModify ? nPattern = -1 : nPattern = m_nPattern;
	
	// モデルを設定
	m_pDummy->ChangeModel(nPattern);
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
		else if (str_type == "spikes")
		{ // とげブロック
			CBlockSpikes::Create(pos);
		}
		else if (str_type == "enemy")
		{ // エネミー
			CEnemy::Create(pos);
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
CStageMaker::CStageMaker() :
	m_nPattern{ 0 },	// 構造物の種類識別
	m_bModify{ false },	// 編集切り替え
	m_nID{ 0 },			// 編集する構造物を識別
	m_pDummy{ nullptr }	// 構造物のダミー情報
{
	// ステージデバッグモードのみ
	if (CManager::GetScene()->GetMode() == CScene::MODE::STAGE)
	{
		// 構造物のダミーを生成
		m_pDummy = CDummy::Create();

		// ダミー取得失敗
		if (!m_pDummy)
		{
			assert(false);
		}

		// グリッドラインを生成
		CLine::CreateGrid();
	}
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
			CRenderer::GetInstance()->SetTimeString("【スタート・ゴールの配置情報が異常です！】", 180);
		}
		else
		{
			// ステージ書き出し
			Export();
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_F3))
	{
		// ステージ読み込み (仮)
		Import("Data\\TXT\\stage01.txt");
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
	{
		// 編集切り替え
		m_bModify = !m_bModify;
	}

	if (!m_bModify)
	{
		CRenderer::GetInstance()->SetDebugString("現在のモード -> 配置");

		// ダミー操作
		m_pDummy->Control();

		// 操作反映
		m_pDummy->Update();

		if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
		{
			// 設置
			Register();
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD4))
		{
			m_nPattern > 0 ? m_nPattern-- : m_nPattern = 5;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD6))
		{
			m_nPattern < 5 ? m_nPattern++ : m_nPattern = 0;
		}

		CRenderer::GetInstance()->SetDebugString("現在の構造物の種類:" + std::to_string(m_nPattern));
	}
	else
	{
		CRenderer::GetInstance()->SetDebugString("現在のモード -> 編集");

		if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD4))
		{
			m_nID--;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD6))
		{
			m_nID++;
		}

		CRenderer::GetInstance()->SetDebugString("現在の構造物のID:" + std::to_string(m_nID));
	
		// 編集
		Modify();
	}
}

//============================================================================
// 設置
//============================================================================
void CStageMaker::Register()
{
	// ダミーの位置を取得
	D3DXVECTOR3 pos = m_pDummy->GetPos();

	// ダミーの位置にオブジェクト生成
	switch (m_nPattern)
	{
	case 0:
		CBlock::Create(pos);
		break;

	case 1:
		CBlockDestructible::Create(pos);
		break;

	case 2:
		CBlockSpikes::Create(pos);
		break;

	case 3:
		CEnemy::Create(pos);
		break;

	case 4:

		// スタートタイプのオブジェクトを検索
		if (!CObject::FindObject(CObject::TYPE::START))
		{
			CStart::Create(pos);
		}
		else
		{
			CRenderer::GetInstance()->SetTimeString("【スタートはすでに配置されています】", 60);
		}

		break;

	case 5:

		// スタートタイプのオブジェクトを検索
		if (!CObject::FindObject(CObject::TYPE::GOAL))
		{
			CGoal::Create(pos);
		}
		else
		{
			CRenderer::GetInstance()->SetTimeString("【ゴールはすでに配置されています】", 60);
		}

		break;

	default:
		assert(false);
		break;
	}
}

//============================================================================
// 編集
//============================================================================
void CStageMaker::Modify()
{
	// オブジェクトリストの先頭を取得
	CObject* pObj = CObject::GetObject(static_cast<int>(CObject::LAYER::FRONT_MIDDLE));

	// 編集するIDまでオブジェクトを検索する
	for (int i = 0; i < m_nID; i++)
	{
		// オブジェクトが見つからなければ終了
		if (!pObj)
		{
			return;
		}

		// 次のオブジェクトのポインタをコピー
		CObject* pNext = pObj->GetNext();

		// 次のオブジェクトを代入
		pObj = pNext;
	}

	// オブジェクトが見つからなければ終了
	if (pObj == nullptr)
	{
		return;
	}

	// オブジェクトをXオブジェクトにダウンキャスト
	CObject_X* pX = CUtility::GetInstance()->DownCast<CObject_X, CObject>(pObj);

	// ダミーの座標をオブジェクトの座標に同期
	m_pDummy->SetPos(pX->GetPos());

	// ダミー操作
	m_pDummy->Control();

	// 操作反映
	m_pDummy->Update();

	// 座標を反映
	pX->SetPos(m_pDummy->GetPos());
	pX->Update();
}

//============================================================================
// ステージ書き出し
//============================================================================
void CStageMaker::Export()
{
	// ステージ配置情報を書き出し展開
	std::ofstream Export("Data\\TXT\\stage.txt");

	// スタートオブジェクトを取得
	CStart* pStart = CUtility::GetInstance()->DownCast<CStart, CObject>(CObject::FindObject(CObject::TYPE::START));

	// 情報を書き出す
	Output(Export, pStart->GetPos(), "start");

	// ゴールオブジェクトを取得
	CGoal* pGoal = CUtility::GetInstance()->DownCast<CGoal, CObject>(CObject::FindObject(CObject::TYPE::GOAL));

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
		CBlock* pBlock = CUtility::GetInstance()->DownCast<CBlock, CObject>(pObject[nCntObj]);

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
		CBlockDestructible* pDestructible = CUtility::GetInstance()->DownCast<CBlockDestructible, CObject>(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pDestructible->GetPos(), "destructible");
	}

	// とげブロックタイプのオブジェクトをすべて取得
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// とげブロッククラスへダウンキャスト
		CBlockSpikes* pDestructible = CUtility::GetInstance()->DownCast<CBlockSpikes, CObject>(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pDestructible->GetPos(), "spikes");
	}

	// エネミータイプのオブジェクトをすべて取得
	pObject = CObject::FindAllObject(CObject::TYPE::ENEMY);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// エネミーブロッククラスへダウンキャスト
		CEnemy* pEnemy = CUtility::GetInstance()->DownCast<CEnemy, CObject>(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pEnemy->GetPos(), "enemy");
	}

	Export.close();	// ファイルを閉じる

	// デバッグ表示の期間を設定
	CRenderer::GetInstance()->SetTimeString("【ステージを書き出しました】", 180);
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