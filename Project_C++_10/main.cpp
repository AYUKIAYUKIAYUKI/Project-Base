//============================================================================
// 
// �|���S���̕`�� 5_16 [main.cpp]
// Author : ���c����
// 
//============================================================================

// �C���N���[�h�t�@�C��
#include "main.h"

// �}�N����`
#define CLASS_NAME	"WindowClass"			// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME	"�E�C���h�E�e���v��"	// �E�C���h�E�̖��O

// �|���S���N���X
CPolygon* CPolygon::m_pPolygon = NULL;	// �|���S�����i�[

// �O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;					// Direct3D�I�u�W�F�N�g�̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		// Direct3D�f�o�C�X�̃|�C���^

// �v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��
HRESULT InitProcess(HINSTANCE hInstance, HWND hWnd, BOOL bWindiw);	// �����ݒ�
void UninitProcess();	// �I������
void UpdateProcess();	// �X�V����
void DrawProcess();		// �`�揈��

//****************************************************************************
// ���C���֐�
//****************************************************************************
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						// �E�C���h�E�̃X�^�C��
		WindowProc,						// �E�C���h�E�v���V�[�W��
		0,								// ������0�ɂ���
		0,								// ������0�ɂ���
		hInstance,						// �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),	// �^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),		// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW),			// �N���C�A���g�̈�̔w�i�F
		NULL,							// ���j���[�o�[
		CLASS_NAME,						// �E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	// �t�@�C���̃A�C�R��
	};

	HWND hWnd;	// �E�C���h�E�n���h��(���ʎq)
	MSG msg;	// ���b�Z�[�W���i�[����ϐ�

	// ��ʃT�C�Y�̐ݒ�p
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// �E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,	// �g���E�C���h�E�̃X�^�C��
		CLASS_NAME,				// �E�C���h�E�N���X�̖��O
		WINDOW_NAME,			// �E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	// �E�C���h�E�̃X�^�C��
		125,					// �E�C���h�E�̍����X���W
		50,						// �E�C���h�E�̍����Y���W
		SCREEN_WIDTH,			// �E�C���h�E�̕�
		SCREEN_HEIGHT,			// �E�C���h�E�̍���
		NULL,					// �e�E�C���h�E�̃n���h��
		NULL,					// ���j���[�o�[�܂��͎q�E�C���h�EID
		hInstance,				// �C���X�^���X�n���h��
		NULL);					// �E�C���h�E�쐬�f�[�^

	if (FAILED(InitProcess(hInstance, hWnd, TRUE)))
	{ // ���������������s�����ꍇ
		return -1;
	}

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, SW_NORMAL);	// �E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);				// �N���C�A���g�̈���X�V

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			// Windows�̏���
			if (msg.message == WM_QUIT)
			{
				// WM_QUIT�̃��b�Z�[�W���󂯎��ƁA���b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);	// ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	// �E�C���h�E�v���V�[�W���փ��b�Z�[�W��n�o
			}
		}
		else
		{
			// �X�V����
			UpdateProcess();

			// �`�揈��
			DrawProcess();
		}
	}

	// �I������
	UninitProcess();

	// �E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//****************************************************************************
// �E�C���h�E�v���V�[�W���֐�
//****************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �Ԃ�l�i�[��
	int nID;

	switch (uMsg)
	{
		// �E�C���h�E�j���̃��b�Z�[�W�𑗂�
	case WM_DESTROY:

		PostQuitMessage(0);

		break;

		// �~�}�[�N�������Ă��郁�b�Z�[�W�𑗂�
	case WM_CLOSE:

		// ���b�Z�[�W�{�b�N�X��\��
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	// �uWM_DESTROY�Ƃ������b�Z�[�W�𑗂�v
		}
		else
		{
			return 0;
		}

		break;

		// �L�[��������Ă��郁�b�Z�[�W�𑗂�
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:

			// ���b�Z�[�W�{�b�N�X��\��
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	// �uWM_DESTROY�Ƃ������b�Z�[�W�𑗂�v
			}

			break;
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// ����̏�����Ԃ�
}

//****************************************************************************
// �����ݒ�
//****************************************************************************
HRESULT InitProcess(HINSTANCE hInstance, HWND hWnd, BOOL bWindiw)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{ // �����Ɏ��s�����ꍇ
		return E_FAIL;
	}

	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{ // ���݂̃f�B�X�v���C���[�h���擾
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));	// �p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[���T�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[���T�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindiw;									// �E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// Direct3D�f�o�C�X�̐����s���@
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		// Direct3D�f�o�C�X�̐����s���A
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// Direct3D�f�o�C�X�̐����s���B
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

	// �����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// �|���S�������ݒ�
	CPolygon* pPolygon = CPolygon::GetInstance();
	pPolygon->Init();

	return S_OK;
}

//****************************************************************************
// �I������
//****************************************************************************
void UninitProcess()
{
	// �|���S���I������
	CPolygon* pPolygon = CPolygon::GetInstance();
	pPolygon->Uninit();

	// Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//****************************************************************************
// �X�V�ݒ�
//****************************************************************************
void UpdateProcess()
{
	// �|���S���X�V����
	CPolygon* pPolygon = CPolygon::GetInstance();
	pPolygon->Update();
}

//****************************************************************************
// �`��ݒ�
//****************************************************************************
void DrawProcess()
{
	// ��ʃN���A
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// �|���S���`�揈��
		CPolygon* pPolygon = CPolygon::GetInstance();
		pPolygon->Draw();

		// �`��I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//****************************************************************************
// �R���X�g���N�^
//****************************************************************************
CPolygon::CPolygon()
{

}

//****************************************************************************
// �f�X�g���N�^
//****************************************************************************
CPolygon::~CPolygon()
{

}

//****************************************************************************
// �����ݒ�
//****************************************************************************
void CPolygon::Init()
{
	m_pVtxBuff = NULL;

	// ���_�o�b�t�@�̐���
	g_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�̐ݒ�
	pVtx[0].pos = { 400.0f, 100.0f, 0.0f };
	pVtx[1].pos = { 920.0f, 100.0f, 0.0f };
	pVtx[2].pos = { 400.0f, 620.0f, 0.0f };
	pVtx[3].pos = { 920.0f, 620.0f, 0.0f };

	// ���Z���̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �F�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//****************************************************************************
// �I������
//****************************************************************************
void CPolygon::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pPolygon != NULL)
	{ // ���������Ă�����
		delete m_pPolygon;	// �����������
		m_pPolygon = NULL;	// �ϐ���������
	}
}

//****************************************************************************
// �X�V�ݒ�
//****************************************************************************
void CPolygon::Update()
{

}

//****************************************************************************
// �`��ݒ�
//****************************************************************************
void CPolygon::Draw()
{
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	g_pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,												// ���_���̐擪�A�h���X
		2);												// �v���~�e�B�u��
}

//****************************************************************************
// ���擾
//****************************************************************************
CPolygon* CPolygon::GetInstance()
{
	if (m_pPolygon == NULL)
	{ // ��񂪂Ȃ���ΐV�K����
		m_pPolygon = new CPolygon;
	}

	return m_pPolygon;
}