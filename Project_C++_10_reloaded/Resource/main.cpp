//============================================================================
// 
// �^�C�g������Q�[�� [main.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "main.h"
#include "manager.h"

// �f�o�b�O�\���p
#include "renderer.h"

// ���������[�N���o�p
#include <crtdbg.h>
#include <stdlib.h>

//****************************************************
// �}�N����`
//****************************************************
#define CLASS_NAME	"WindowClass"			// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME	"�E�C���h�E�e���v��"	// �E�C���h�E�̖��O

// ���������[�N���o�p
#define _CRTDBG_MAP_ALLOC

//****************************************************
// �O���[�o���錾
//****************************************************
CManager* g_pManager = nullptr;	// �}�l�[�W���[�Ǘ�

//****************************************************
// �v���g�^�C�v�錾
//****************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��

//****************************************************************************
// ���C���֐�
//****************************************************************************
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// CRT���������[�N���o�p
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, SW_NORMAL);	// �E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);				// �N���C�A���g�̈���X�V

	// �}�l�[�W���[�̐���
	g_pManager = DBG_NEW CManager;

	if (g_pManager == nullptr)
	{ // �������s
		return -1;
	}

	if (FAILED(g_pManager->Init(hInstance, hWnd, TRUE)))
	{ // ���������������s�����ꍇ
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// FPS�v���p
	int nCountFPS = 0;						// ���݂�FPS
	DWORD dwCurrentTime = 0;				// ���ݎ����p
	DWORD dwFrameCount = 0;					// �Ō�ɏ�����������
	DWORD dwExecLastTime = timeGetTime();	// �t���[���J�E���g�i�[
	DWORD dwFPSLastTime = timeGetTime();	// �Ō��FPS���v�����������i�[

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
			// ���ݎ������擾
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				// FPS���v��
				nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				// FPS���v���������Ԃ�ۑ�
				dwFPSLastTime = dwCurrentTime;

				// �t���[���J�E���g���N���A
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				// ���ݎ�����ۑ�
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				g_pManager->Update();

#ifdef _DEBUG
				// FPS�\��
				CRenderer::GetInstance()->SetDebugString("FPS:" + std::to_string(nCountFPS));
#endif	// _DEBUG

				// �`�揈��
				g_pManager->Draw();

				// �t���[���J�E���g�����Z
				dwFrameCount++;
			}
		}
	}

	// ����\��߂�
	timeEndPeriod(1);

	// �}�l�[�W���[�̔j��
	if (g_pManager != nullptr)
	{
		g_pManager->Uninit();	// �I������
		delete g_pManager;		// �����������
		g_pManager = nullptr;	// �|�C���^��������
	}

	// �E�C���h�E�N���X�̓o�^������

	// CRT���������[�N�ӏ����o
	//_CrtSetBreakAlloc();

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