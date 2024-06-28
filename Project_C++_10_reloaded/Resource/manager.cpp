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
#include "physics.h"

//****************************************************
// �ÓI�����o�̏�����
//****************************************************
CRenderer* CManager::m_pRenderer = nullptr;			// �����_���[�Ǘ�
CCamera* CManager::m_pCamera = nullptr;				// �J�����Ǘ�
CLight* CManager::m_pLight = nullptr;				// ���C�g�Ǘ�
CInputKeyboard* CManager::m_pKeyboard = nullptr;	// �L�[�{�[�h�Ǘ�
CInputPad* CManager::m_pPad = nullptr;				// �p�b�h�Ǘ�
CSound* CManager::m_pSound = nullptr;				// �T�E���h�Ǘ�
CScene* CManager::m_pScene = nullptr;				// �V�[���Ǘ�
CFade* CManager::m_pFade = nullptr;					// �t�F�[�h�Ǘ�

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
	m_pScene = nullptr;
	m_pFade = nullptr;
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
	m_pRenderer = DBG_NEW CRenderer;

	if (m_pRenderer == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �����_���[�̏�����
	m_pRenderer->Init(hWnd, bWindow);

	// �J�����̐���
	m_pCamera = DBG_NEW CCamera;

	if (m_pCamera == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �J�����̏�����
	m_pCamera->Init();

	// ���C�g�̐���
	m_pLight = DBG_NEW CLight;

	if (m_pLight == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// ���C�g�̏�����
	m_pLight->Init();

	// �L�[�{�[�h�̐���
	m_pKeyboard = DBG_NEW CInputKeyboard;

	if (m_pKeyboard == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �L�[�{�[�h�̏�����
	m_pKeyboard->Init(hInstance, hWnd);

	// �p�b�h�̐���
	m_pPad = DBG_NEW CInputPad;

	if (m_pPad == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �L�[�{�[�h�̏�����
	m_pPad->Init();

	// �T�E���h�̐���
	m_pSound = DBG_NEW CSound;

	if (m_pSound == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �T�E���h�̏�����
	m_pSound->Init(hWnd);

	// �t�F�[�h�̐���
	m_pFade = DBG_NEW CFade;

	if (m_pFade == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �t�F�[�h�̏����ݒ�
	m_pFade->Init();

	// �ŏ��̃V�[���ݒ�
	SetScene(CScene::MODE::TITLE);

	// �������Z�C���X�^���X�̐���
	if (FAILED(CPhysics::Create()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CManager::Uninit()
{
	// �������Z�C���X�^���X�̔j��
	CPhysics::Release();

	// �t�F�[�h�̔j��
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();	// �I������
		delete m_pFade;		// �����������
		m_pFade = nullptr;	// �|�C���^��������
	}

	// �V�[���̔j��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();	// �I������
		delete m_pScene;	// �����������
		m_pScene = nullptr;	// �|�C���^��������
	}

	// �T�E���h�̔j��
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();	// �I������
		delete m_pSound;	// �����������
		m_pSound = nullptr;	// �|�C���^��������
	}

	// �p�b�h�̔j��
	if (m_pPad != nullptr)
	{
		m_pPad->Uninit();	// �I������
		delete m_pPad;		// �����������
		m_pPad = nullptr;	// �|�C���^��������
	}

	// �L�[�{�[�h�̔j��
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();	// �I������
		delete m_pKeyboard;		// �����������
		m_pKeyboard = nullptr;	// �|�C���^��������
	}

	// ���C�g�̔j��
	if (m_pLight != nullptr)
	{
		delete m_pLight;		// �����������
		m_pLight = nullptr;		// �|�C���^��������
	}

	// �J�����̔j��
	if (m_pCamera != nullptr)
	{
		delete m_pCamera;		// �����������
		m_pCamera = nullptr;	// �|�C���^��������
	}

	// �����_���[�̔j��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();	// �I������
		delete m_pRenderer;		// �����������
		m_pRenderer = nullptr;	// �|�C���^��������
	}
}

//============================================================================
// �X�V����
//============================================================================
void CManager::Update()
{
	// �t�F�[�h�̍X�V
	m_pFade->Update();

	// �����_���[�̍X�V
	m_pRenderer->Update();

	// �V�[���̍X�V
	m_pScene->Update();

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

//============================================================================
// �V�[���擾
//============================================================================
CScene* CManager::GetScene()
{
	return m_pScene;
}

//============================================================================
// �t�F�[�h�擾
//============================================================================
CFade* CManager::GetFade()
{
	return m_pFade;
}

//============================================================================
// �V�[���ݒ�
//============================================================================
void CManager::SetScene(CScene::MODE mode)
{
	// ���݂̃V�[����j��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	// �V���ȃV�[����ݒ�
	m_pScene = CScene::Create(mode);
}