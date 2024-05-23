//============================================================================
// 
// �|���S���̕`�� 5_16 [main.cpp]
// Author : ���c����
// 
//============================================================================

// �C���N���[�h�t�@�C��
#include "main.h"
#include "manager.h"

// �}�N����`
#define CLASS_NAME	"WindowClass"			// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME	"�E�C���h�E�e���v��"	// �E�C���h�E�̖��O

// �O���[�o���ϐ�
CManager* g_pManager = nullptr;	// �}�l�[�W���[�Ǘ�

// �v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��

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

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, SW_NORMAL);	// �E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);				// �N���C�A���g�̈���X�V

	// �}�l�[�W���[�̐���
	g_pManager = new CManager;

	if (g_pManager == nullptr)
	{ // �������s
		return -1;
	}

	if (FAILED(g_pManager->Init(hInstance, hWnd, TRUE)))
	{ // ���������������s�����ꍇ
		return -1;
	}

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
			g_pManager->Update();

			// �`�揈��
			g_pManager->Draw();
		}
	}

	// �}�l�[�W���[�̔j��
	if (g_pManager != nullptr)
	{
		g_pManager->Uninit();	// �I������
		delete g_pManager;		// �����������
		g_pManager = nullptr;	// �|�C���^��������
	}

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