//============================================================================
// 
// X���f���Ǘ� [model_X.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "model_X.h"
#include "manager.h"

//****************************************************
// �ÓI�����o�̏�����
//****************************************************
CModel_X::MODEL CModel_X::m_apModelTemp[static_cast<int>(MODEL_TYPE::MAX)];	// ���f���Ǘ�

//============================================================================
// �R���X�g���N�^
//============================================================================
CModel_X::CModel_X()
{
	for (int i = 0; i < static_cast<int>(MODEL_TYPE::MAX); i++)
	{
		// ���f�����̏�����
		m_apModelTemp[i].pMesh = nullptr;
		m_apModelTemp[i].pBuffMat = nullptr;
		m_apModelTemp[i].dwNumMat = 0;
		m_apModelTemp[i].ppTex = nullptr;
	}
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CModel_X::~CModel_X()
{

}

//============================================================================
// ���f���ǂݍ���
//============================================================================
HRESULT CModel_X::Load()
{
	// ���f�����Ǘ��t�@�C����W�J
	std::ifstream file("data\\TXT\\model_path.txt");

	if (!file)
	{ // �W�J�Ɏ��s
		assert(false);
	}

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	for (int nCntModel = 0; nCntModel < static_cast<int>(MODEL_TYPE::MAX); nCntModel++)
	{
		// ���f�����i�[��
		std::string filename;

		// ���f�������擾����
		std::getline(file, filename);

		// ���f���t�@�C���̎擾
		HRESULT hr = D3DXLoadMeshFromX(filename.c_str(),
			D3DXMESH_SYSTEMMEM,
			pDev,
			nullptr,
			&m_apModelTemp[nCntModel].pBuffMat,
			nullptr,
			&m_apModelTemp[nCntModel].dwNumMat,
			&m_apModelTemp[nCntModel].pMesh);

		if (FAILED(hr))
		{ // �擾���s
			file.close();	// �t�@�C�������
			assert(false);
		}

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_apModelTemp[nCntModel].pBuffMat->GetBufferPointer();

		// �}�e���A���̐����̃e�N�X�`���|�C���^���m��
		m_apModelTemp[nCntModel].ppTex = DBG_NEW LPDIRECT3DTEXTURE9 [static_cast<int>(m_apModelTemp[nCntModel].dwNumMat)];

		// �}�e���A�����e�N�X�`���̗L�����m�F
		for (int nCntMat = 0; nCntMat < static_cast<int>(m_apModelTemp[nCntModel].dwNumMat); nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != nullptr)
			{
				// �e�N�X�`����ǂݎ�ꂽ�琶��
				hr = D3DXCreateTextureFromFileA(pDev,
					pMat[nCntMat].pTextureFilename,
					&m_apModelTemp[nCntModel].ppTex[nCntMat]);

				if (FAILED(hr))
				{ // �������s
					assert(false);
				}
			}
			else
			{
				// �ǂݎ��Ȃ���Ώ�����
				m_apModelTemp[nCntModel].ppTex[nCntMat] = nullptr;
			}
		}
	}

	file.close();	// �t�@�C�������

	return S_OK;
}

//============================================================================
// ���f���j��
//============================================================================
void CModel_X::Unload()
{
	for (int i = 0; i < static_cast<int>(MODEL_TYPE::MAX); i++)
	{
		// �e�N�X�`���|�C���^�̔j��
		if (m_apModelTemp[i].ppTex != nullptr)
		{
			// �e�N�X�`���̔j��
			for (int nCntMat = 0; nCntMat < static_cast<int>(m_apModelTemp[i].dwNumMat); nCntMat++)
			{
				if (m_apModelTemp[i].ppTex[nCntMat] != nullptr)
				{
					m_apModelTemp[i].ppTex[nCntMat]->Release();
					m_apModelTemp[i].ppTex[nCntMat] = nullptr;
				}
			}

			delete[] m_apModelTemp[i].ppTex;
			m_apModelTemp[i].ppTex = nullptr;
		}

		// ���b�V���̔j��
		if (m_apModelTemp[i].pMesh != nullptr)
		{
			m_apModelTemp[i].pMesh->Release();
			m_apModelTemp[i].pMesh = nullptr;
		}

		// �}�e���A���̔j��
		if (m_apModelTemp[i].pBuffMat != nullptr)
		{
			m_apModelTemp[i].pBuffMat->Release();
			m_apModelTemp[i].pBuffMat = nullptr;
		}
	}
}

//============================================================================
// ���f�����擾
//============================================================================
CModel_X::MODEL* CModel_X::GetModel(MODEL_TYPE type)
{
	if (&m_apModelTemp[static_cast<int>(type)].pMesh == nullptr)
	{ // ���f���擾�s�\
		assert(false);
	}

	return &m_apModelTemp[static_cast<int>(type)];
}