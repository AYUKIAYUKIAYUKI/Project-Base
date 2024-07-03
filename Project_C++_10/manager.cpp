//============================================================================
// 
// �}�l�[�W���[ [manager.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "manager.h"

//****************************************************
// �ÓI�����o�̏�����
//****************************************************
CRenderer* CManager::m_pRenderer = nullptr;			// �����_���[�Ǘ�
CCamera* CManager::m_pCamera = nullptr;				// �J�����Ǘ�
CLight* CManager::m_pLight = nullptr;				// ���C�g�Ǘ�
CInputKeyboard* CManager::m_pKeyboard = nullptr;	// �L�[�{�[�h�Ǘ�
CInputPad* CManager::m_pPad = nullptr;				// �p�b�h�Ǘ�
CSound* CManager::m_pSound = nullptr;				// �T�E���h�Ǘ�

//============================================================================
// �R���X�g���N�^
//============================================================================
CManager::CManager()
{
	m_pRenderer = nullptr;
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_pKeyboard = nullptr;
	m_pPad = nullptr;
	m_pSound = nullptr;
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CManager::~CManager()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_���[�̐���
	m_pRenderer = new CRenderer;

	if (m_pRenderer == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �����_���[�̏�����
	m_pRenderer->Init(hWnd, bWindow);

	// �J�����̐���
	m_pCamera = new CCamera;

	if (m_pCamera == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �J�����̏�����
	m_pCamera->Init();

	// ���C�g�̐���
	m_pLight = new CLight;

	if (m_pLight == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// ���C�g�̏�����
	m_pLight->Init();

	// �L�[�{�[�h�̐���
	m_pKeyboard = new CInputKeyboard;

	if (m_pKeyboard == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �L�[�{�[�h�̏�����
	m_pKeyboard->Init(hInstance, hWnd);

	// �p�b�h�̐���
	m_pPad = new CInputPad;

	if (m_pPad == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �L�[�{�[�h�̏�����
	m_pPad->Init();

	// �T�E���h�̐���
	m_pSound = new CSound;

	if (m_pSound == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �T�E���h�̏�����
	m_pSound->Init(hWnd);

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CManager::Uninit()
{
	// �����_���[�̔j��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();	// �I������
		delete m_pRenderer;		// �����������
		m_pRenderer = nullptr;	// �|�C���^��������
	}

	// �J�����̔j��
	if (m_pCamera != nullptr)
	{
		delete m_pCamera;		// �����������
		m_pCamera = nullptr;	// �|�C���^��������
	}

	// ���C�g�̔j��
	if (m_pLight != nullptr)
	{
		delete m_pLight;		// �����������
		m_pLight = nullptr;		// �|�C���^��������
	}

	// �L�[�{�[�h�̔j��
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();	// �I������
		delete m_pKeyboard;		// �����������
		m_pKeyboard = nullptr;	// �|�C���^��������
	}

	// �p�b�h�̔j��
	if (m_pPad != nullptr)
	{
		m_pPad->Uninit();	// �I������
		delete m_pPad;		// �����������
		m_pPad = nullptr;	// �|�C���^��������
	}

	// �T�E���h�̔j��
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();	// �I������
		delete m_pSound;	// �����������
		m_pSound = nullptr;	// �|�C���^��������
	}
}

//============================================================================
// �X�V����
//============================================================================
void CManager::Update()
{
	// �����_���[�̍X�V
	m_pRenderer->Update();

	// �J�����̍X�V
	m_pCamera->Update();

	// ���C�g�̍X�V
	m_pLight->Update();

	// �L�[�{�[�h�̍X�V
	m_pKeyboard->Update();

	// �p�b�h�̍X�V
	m_pPad->Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CManager::Draw()
{
	// �����_���[�̕`��
	m_pRenderer->Draw();
}

//============================================================================
// �����_���[�擾
//============================================================================
CRenderer* CManager::GetRenderer()
{ 
	return m_pRenderer;
}

//============================================================================
// �J�����擾
//============================================================================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

//============================================================================
// ���C�g�擾
//============================================================================
CLight* CManager::GetLight()
{
	return m_pLight;
}

//============================================================================
// �L�[�{�[�h�擾
//============================================================================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//============================================================================
// �p�b�h�擾
//============================================================================
CInputPad* CManager::GetPad()
{
	return m_pPad;
}

//============================================================================
// �T�E���h�擾
//============================================================================
CSound* CManager::GetSound()
{
	return m_pSound;
}