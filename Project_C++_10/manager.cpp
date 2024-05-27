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

// ��
#include "bg.h"
#include "player.h"
#include "enemy.h"
#include "number.h"

//****************************************************
// �ÓI�����o�̏�����
//****************************************************
CRenderer* CManager::m_pRenderer = nullptr;			// �����_���[�Ǘ�
CTexture* CManager::m_pTexture = nullptr;			// �e�N�X�`���Ǘ�
CInputKeyboard* CManager::m_pKeyboard = nullptr;	// �L�[�{�[�h�Ǘ�
CInputPad* CManager::m_pPad = nullptr;				// �p�b�h�Ǘ�
CSound* CManager::m_pSound = nullptr;				// �T�E���h�Ǘ�

//============================================================================
// �R���X�g���N�^
//============================================================================
CManager::CManager()
{
	m_pRenderer = nullptr;
	m_pTexture = nullptr;
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

	// �e�N�X�`���̐���
	m_pTexture = new CTexture;

	if (m_pTexture == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �e�N�X�`���̃��[�h
	m_pTexture->Load();

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

	// �w�i�̐���
	CBg::Create();

	// �v���C���[�̐���
	CPlayer::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// ���S�ʒu
		{ 25.0f, 50.0f, 0.0f });								// �T�C�Y

	// �G�l�~�[�̐���
	CEnemy::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// ���S�ʒu
		{ 50.0f, 50.0f, 0.0f });								// �T�C�Y

	// �����̐���
	CNumber::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// ���S�ʒu
		{ 25.0f, 20.0f, 0.0f });								// �T�C�Y


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

	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();	// �j������
		delete m_pTexture;		// �����������
		m_pTexture = nullptr;	// �|�C���^��������
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
// �e�N�X�`�����擾
//============================================================================
CTexture* CManager::GetTexture()
{
	return m_pTexture;
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