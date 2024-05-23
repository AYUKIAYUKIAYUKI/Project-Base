//============================================================================
// 
// ���͏����Ǘ� [input.cpp]
// Author : ���c����
// 
//============================================================================

// �C���N���[�h�t�@�C��
#include "input.h"

// �ÓI�����o�̏�����
LPDIRECTINPUT8 CInput::m_Input = nullptr;	// // DirectInput�I�u�W�F�N�g

//****************************************************************************
// �R���X�g���N�^
//****************************************************************************
CInput::CInput()
{

}

//****************************************************************************
// �f�X�g���N�^
//****************************************************************************
CInput::~CInput()
{

}

//****************************************************************************
// �����ݒ�
//****************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_Input == nullptr)
	{
		// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_Input, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//****************************************************************************
// �I������
//****************************************************************************
void CInput::Uninit()
{
	// ���̓f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_Input != nullptr)
	{
		m_Input->Release();
		m_Input = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//****************************************************************************
// �R���X�g���N�^
//****************************************************************************
CInputKeyboard::CInputKeyboard()
{

}

//****************************************************************************
// �f�X�g���N�^
//****************************************************************************
CInputKeyboard::~CInputKeyboard()
{

}

//****************************************************************************
// �����ݒ�
//****************************************************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_Input == nullptr)
	{
		// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(CInput::Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (m_pDevice == nullptr)
	{
		if (FAILED(m_Input->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�F�t�H�A�O���E���h
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//****************************************************************************
// �I������
//****************************************************************************
void CInputKeyboard::Uninit()
{
	// ���N���X�̏I������
	CInput::Uninit();
}

//****************************************************************************
// �X�V����
//****************************************************************************
void CInputKeyboard::Update()
{
	BYTE state_keyboard[MAX_KEY] = {};	// �L�[���͏��

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(state_keyboard), &state_keyboard[0])))
	{
		for (int i = 0; i < MAX_KEY; i++)
		{
			// �L�[�{�[�h�̃v���X����ۑ�
			m_aKeyState[i] = state_keyboard[i];

			// �L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyStateTrigger[i] = (m_aKeyState[i] ^ state_keyboard[i]) & state_keyboard[i];
		}
	}
	else
	{
		// �L�[�{�[�h�̃A�N�Z�X�����l��
		m_pDevice->Acquire();
	}
}

//****************************************************************************
// �v���X���擾
//****************************************************************************
bool CInputKeyboard::GetPress(int nKey)
{
	return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//****************************************************************************
// �g���K�[���擾
//****************************************************************************
bool CInputKeyboard::GetTrigger(int nKey)
{
	return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}