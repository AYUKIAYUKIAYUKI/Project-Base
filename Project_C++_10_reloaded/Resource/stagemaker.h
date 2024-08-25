//============================================================================
// 
// ステージメーカー [stagemaker.cpp]
// Author : 福田歩希
// 
//============================================================================

#ifndef _SATEGEMAKER_H_
#define _SATEGEMAKER_H_	// 二重インクルード防止

//****************************************************
// 前方宣言
//****************************************************
class CDummy;

//****************************************************
// ステージメーカークラス
//****************************************************
class CStageMaker final
{
public:

	void Create();					// 生成
	void Init();					// 初期設定
	void Release();					// 解放
	void Uninit();					// 終了処理
	void Update();					// 更新処理
	void Import(std::string path);	// ステージ読み込み

	int& GetPatternRef();	// 配置物の種類を参照

	static CStageMaker* GetInstance();	// ステージメーカーを取得

private:

	CStageMaker();	// コンストラクタ
	~CStageMaker();	// デストラクタ

	void Control();		// 操作
	void Register();	// 設置
	void Modify();		// 編集
	void Export();		// ステージ書き出し
	void Output(std::ofstream& file, D3DXVECTOR3 pos, std::string str);	// 情報書き出し

	int m_nPattern;		// 構造物の種類を識別
	bool m_bModify;		// 編集切り替え
	int m_nID;			// 編集する構造物を識別
	CDummy* m_pDummy;	// 構造物のダミー情報

	static CStageMaker* m_pInstance;	// ステージメーカー
};

#endif // _SATEGEMAKER_H_