//============================================================================
// 
// ポリゴンの描画 5_16 [main.cpp]
// Author : 福田歩希
// 
//============================================================================

// インクルードファイル
#include "main.h"

// マクロ定義
#define CLASS_NAME	"WindowClass"			// ウインドウクラスの名前
#define WINDOW_NAME	"ウインドウテンプレ"	// ウインドウの名前

// ポリゴンクラス
CPolygon* CPolygon::m_pPolygon = NULL;	// ポリゴン情報格納

// グローバル変数
LPDIRECT3D9 g_pD3D = NULL;					// Direct3Dオブジェクトのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		// Direct3Dデバイスのポインタ

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャ
HRESULT InitProcess(HINSTANCE hInstance, HWND hWnd, BOOL bWindiw);	// 初期設定
void UninitProcess();	// 終了処理
void UpdateProcess();	// 更新処理
void DrawProcess();		// 描画処理

//****************************************************************************
// メイン関数
//****************************************************************************
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				// WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						// ウインドウのスタイル
		WindowProc,						// ウインドウプロシージャ
		0,								// 何かを0にする
		0,								// 何かを0にする
		hInstance,						// インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),	// タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),		// マウスカーソル
		(HBRUSH)(COLOR_WINDOW),			// クライアント領域の背景色
		NULL,							// メニューバー
		CLASS_NAME,						// ウインドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)	// ファイルのアイコン
	};

	HWND hWnd;	// ウインドウハンドル(識別子)
	MSG msg;	// メッセージを格納する変数

	// 画面サイズの設定用
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// ウインドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウインドウを生成
	hWnd = CreateWindowEx(0,	// 拡張ウインドウのスタイル
		CLASS_NAME,				// ウインドウクラスの名前
		WINDOW_NAME,			// ウインドウの名前
		WS_OVERLAPPEDWINDOW,	// ウインドウのスタイル
		125,					// ウインドウの左上のX座標
		50,						// ウインドウの左上のY座標
		SCREEN_WIDTH,			// ウインドウの幅
		SCREEN_HEIGHT,			// ウインドウの高さ
		NULL,					// 親ウインドウのハンドル
		NULL,					// メニューバーまたは子ウインドウID
		hInstance,				// インスタンスハンドル
		NULL);					// ウインドウ作成データ

	if (FAILED(InitProcess(hInstance, hWnd, TRUE)))
	{ // 初期化処理が失敗した場合
		return -1;
	}

	// ウインドウの表示
	ShowWindow(hWnd, SW_NORMAL);	// ウインドウの表示状態を設定
	UpdateWindow(hWnd);				// クライアント領域を更新

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			// Windowsの処理
			if (msg.message == WM_QUIT)
			{
				// WM_QUITのメッセージを受け取ると、メッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);	// 仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);	// ウインドウプロシージャへメッセージを創出
			}
		}
		else
		{
			// 更新処理
			UpdateProcess();

			// 描画処理
			DrawProcess();
		}
	}

	// 終了処理
	UninitProcess();

	// ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//****************************************************************************
// ウインドウプロシージャ関数
//****************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 返り値格納先
	int nID;

	switch (uMsg)
	{
		// ウインドウ破棄のメッセージを送る
	case WM_DESTROY:

		PostQuitMessage(0);

		break;

		// ×マークを押しているメッセージを送る
	case WM_CLOSE:

		// メッセージボックスを表示
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	// 「WM_DESTROYというメッセージを送る」
		}
		else
		{
			return 0;
		}

		break;

		// キーが押されているメッセージを送る
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:

			// メッセージボックスを表示
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	// 「WM_DESTROYというメッセージを送る」
			}

			break;
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// 既定の処理を返す
}

//****************************************************************************
// 初期設定
//****************************************************************************
HRESULT InitProcess(HINSTANCE hInstance, HWND hWnd, BOOL bWindiw)
{
	D3DDISPLAYMODE d3ddm;			// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	// プレゼンテーションパラメータ

	// Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{ // 生成に失敗した場合
		return E_FAIL;
	}

	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{ // 現在のディスプレイモードを取得
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));	// パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲームサイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲームサイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// バックバッファの形式
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindiw;									// ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// Direct3Dデバイスの生成行程①
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		// Direct3Dデバイスの生成行程②
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// Direct3Dデバイスの生成行程③
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ポリゴン初期設定
	CPolygon* pPolygon = CPolygon::GetInstance();
	pPolygon->Init();

	return S_OK;
}

//****************************************************************************
// 終了処理
//****************************************************************************
void UninitProcess()
{
	// ポリゴン終了処理
	CPolygon* pPolygon = CPolygon::GetInstance();
	pPolygon->Uninit();

	// Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//****************************************************************************
// 更新設定
//****************************************************************************
void UpdateProcess()
{
	// ポリゴン更新処理
	CPolygon* pPolygon = CPolygon::GetInstance();
	pPolygon->Update();
}

//****************************************************************************
// 描画設定
//****************************************************************************
void DrawProcess()
{
	// 画面クリア
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// ポリゴン描画処理
		CPolygon* pPolygon = CPolygon::GetInstance();
		pPolygon->Draw();

		// 描画終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//****************************************************************************
// コンストラクタ
//****************************************************************************
CPolygon::CPolygon()
{

}

//****************************************************************************
// デストラクタ
//****************************************************************************
CPolygon::~CPolygon()
{

}

//****************************************************************************
// 初期設定
//****************************************************************************
void CPolygon::Init()
{
	m_pVtxBuff = NULL;

	// 頂点バッファの生成
	g_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置の設定
	pVtx[0].pos = { 400.0f, 100.0f, 0.0f };
	pVtx[1].pos = { 920.0f, 100.0f, 0.0f };
	pVtx[2].pos = { 400.0f, 620.0f, 0.0f };
	pVtx[3].pos = { 920.0f, 620.0f, 0.0f };

	// 除算数の設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 色の設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//****************************************************************************
// 終了処理
//****************************************************************************
void CPolygon::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pPolygon != NULL)
	{ // 情報をもっていたら
		delete m_pPolygon;	// メモリを解放
		m_pPolygon = NULL;	// 変数を初期化
	}
}

//****************************************************************************
// 更新設定
//****************************************************************************
void CPolygon::Update()
{

}

//****************************************************************************
// 描画設定
//****************************************************************************
void CPolygon::Draw()
{
	// 頂点バッファをデータストリームに設定
	g_pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,												// 頂点情報の先頭アドレス
		2);												// プリミティブ数
}

//****************************************************************************
// 情報取得
//****************************************************************************
CPolygon* CPolygon::GetInstance()
{
	if (m_pPolygon == NULL)
	{ // 情報がなければ新規生成
		m_pPolygon = new CPolygon;
	}

	return m_pPolygon;
}