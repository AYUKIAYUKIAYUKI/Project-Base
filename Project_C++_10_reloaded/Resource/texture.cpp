//============================================================================
// 
// �e�N�X�`���Ǘ� [texture.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "texture.h"

#include "manager.h"
#include "renderer.h"

//****************************************************
// �ÓI�����o�̏�����
//****************************************************
LPDIRECT3DTEXTURE9 CTexture::m_apTexTemp[static_cast<int>(TEX_TYPE::MAX)];	// �e�N�X�`���Ǘ�

//============================================================================
// �R���X�g���N�^
//============================================================================
CTexture::CTexture()
{
	for (int i = 0; i < static_cast<int>(TEX_TYPE::MAX); i++)
	{
		m_apTexTemp[i] = nullptr;	// �e�N�X�`�����̏�����
	}
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CTexture::~CTexture()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CTexture::Load()
{
	// �e�N�X�`�����Ǘ��t�@�C����W�J
	std::ifstream file("data\\TXT\\texture_path.txt");

	if (!file)
	{ // �W�J�Ɏ��s
		assert(false);
	}

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	for (int i = 0; i < static_cast<int>(TEX_TYPE::MAX); i++)
	{
		// �e�N�X�`�����i�[��
		std::string filename;

		// �e�N�X�`�������擾����
		std::getline(file, filename);

		// �e�N�X�`���̐���
		HRESULT hr = D3DXCreateTextureFromFileA(pDev,
			filename.c_str(),
			&m_apTexTemp[i]);

		if (FAILED(hr))
		{ // �e�N�X�`���������s
			file.close();	// �t�@�C�������
			assert(false);
		}
	}

	file.close();	// �t�@�C�������

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CTexture::Unload()
{
	for (int i = 0; i < static_cast<int>(TEX_TYPE::MAX); i++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexTemp[i] != nullptr)
		{
			m_apTexTemp[i]->Release();
			m_apTexTemp[i] = nullptr;
		}
	}
}

//============================================================================
// �e�N�X�`�����擾
//============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEX_TYPE type)
{
	if (m_apTexTemp[static_cast<int>(type)] == nullptr)
	{ // �e�N�X�`���擾�s�\
		assert(false);
	}

	return m_apTexTemp[static_cast<int>(type)];
}