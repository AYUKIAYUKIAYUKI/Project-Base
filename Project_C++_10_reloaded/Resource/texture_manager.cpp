//============================================================================
// 
// �e�N�X�`���}�l�[�W���[ [texture_manager.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "texture_manager.h"

// �f�o�C�X�擾�p
#include "renderer.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
CTexture_Manager* CTexture_Manager::m_pInstance = nullptr;	// �e�N�X�`���}�l�[�W���[

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CTexture_Manager::Load()
{
	// �e�N�X�`�����X�g��W�J
	std::ifstream file{ "data\\TXT\\texture_path.txt" };

	if (!file)
	{ // �W�J�Ɏ��s
		assert(false);
	}

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	for (int i = 0; i < static_cast<int>(TYPE::MAX); i++)
	{
		// �e�N�X�`�����i�[��
		std::string filename{};

		// �e�N�X�`�������擾����
		std::getline(file, filename);

		// �e�N�X�`���̐���
		HRESULT hr = D3DXCreateTextureFromFileA(pDev,
			filename.c_str(),
			&m_apTexTemp[i]);

		if (FAILED(hr))
		{ // �e�N�X�`���������s

			// �t�@�C�������
			file.close();

			assert(false);
		}
	}

	// �t�@�C�������
	file.close();

	return S_OK;
}

//============================================================================
// ���
//============================================================================
void CTexture_Manager::Release()
{
	if (m_pInstance != nullptr)
	{
		// �e�N�X�`����j��
		m_pInstance->Unload();

		// �����������
		delete m_pInstance;
	
		// �|�C���^��������
		m_pInstance = nullptr;
	}
}

//============================================================================
// �e�N�X�`�����擾
//============================================================================
LPDIRECT3DTEXTURE9 CTexture_Manager::GetTexture(TYPE type)
{
	if (m_apTexTemp[static_cast<int>(type)] == nullptr)
	{ // �e�N�X�`���擾�s�\
		assert(false);
	}

	return m_apTexTemp[static_cast<int>(type)];
}

//============================================================================
// �e�N�X�`���}�l�[�W���[���擾
//============================================================================
CTexture_Manager* CTexture_Manager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// ����
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// �R���X�g���N�^
//============================================================================
CTexture_Manager::CTexture_Manager()
{
	for (int i = 0; i < static_cast<int>(TYPE::MAX); i++)
	{
		m_apTexTemp[i] = nullptr;	// �e�N�X�`�����̏�����
	}
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CTexture_Manager::~CTexture_Manager()
{

}

//============================================================================
// ����
//============================================================================
void CTexture_Manager::Create()
{
	if (m_pInstance != nullptr)
	{ // ��d�����֎~
		assert(false);
	}

	// �C���X�^���X�𐶐�
	m_pInstance = DBG_NEW CTexture_Manager{};
}

//============================================================================
// �I������
//============================================================================
void CTexture_Manager::Unload()
{
	for (int i = 0; i < static_cast<int>(TYPE::MAX); i++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexTemp[i] != nullptr)
		{
			m_apTexTemp[i]->Release();
			m_apTexTemp[i] = nullptr;
		}
	}
}