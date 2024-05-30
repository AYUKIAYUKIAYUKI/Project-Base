//============================================================================
// 
// �I�u�W�F�N�g�Ǘ� [object.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.h"
#include "main.h"

//****************************************************
// �ÓI�����o�̏�����
//****************************************************
const float CObject::GRAVITY_FORCE = 0.25f;				// �d��
CObject* CObject::m_apObject[MAX_LAYER][MAX_OBJ] = {};	// �I�u�W�F�N�g�Ǘ�
int CObject::m_nNumAll = 0;								// �I�u�W�F�N�g����

//============================================================================
// �R���X�g���N�^
//============================================================================
CObject::CObject(int nPriority) : m_nPriority(nPriority), m_nID(0), m_type(TYPE::NONE)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		if (m_apObject[m_nPriority][nCntObj] == nullptr)
		{
			m_apObject[m_nPriority][nCntObj] = this;	// �������g�̃|�C���^����
			m_nID = nCntObj;							// �������g��ID����
			m_nNumAll++;								// �������J�E���g�A�b�v
			break;
		}
	}
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CObject::~CObject()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CObject::Init()
{
	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CObject::Uninit()
{

}

//============================================================================
// �X�V����
//============================================================================
void CObject::Update()
{

}

//============================================================================
// �`�揈��
//============================================================================
void CObject::Draw()
{

}

//============================================================================
// �S�������
//============================================================================
void CObject::ReleaseAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_LAYER; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPriority][nCntObj] != nullptr)
			{
				m_apObject[nCntPriority][nCntObj]->Release();	// �������
			}
		}
	}
}

//============================================================================
// �S�X�V����
//============================================================================
void CObject::UpdateAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_LAYER; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPriority][nCntObj] != nullptr)
			{
				m_apObject[nCntPriority][nCntObj]->Update();	// �X�V����
			}
		}
	}
}

//============================================================================
// �S�`�揈��
//============================================================================
void CObject::DrawAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_LAYER; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPriority][nCntObj] != nullptr)
			{
				m_apObject[nCntPriority][nCntObj]->Draw();	// �`�揈��
			}
		}
	}
}

//============================================================================
// �I�u�W�F�N�g���擾
//============================================================================
CObject* CObject::GetObject(int nPriority, int nID)
{
	return m_apObject[nPriority][nID];
}

//============================================================================
// �I�u�W�F�N�g�����擾
//============================================================================
int CObject::GetNumAll()
{
	return m_nNumAll;
}

//============================================================================
// �^�C�v�擾
//============================================================================
CObject::TYPE CObject::GetType()
{
	return m_type;
}

//============================================================================
// �X�R�A�C���X�^���X��T��
//============================================================================
CObject* CObject::FindScoreInstance()
{
	for (int nCntPriority = 0; nCntPriority < MAX_LAYER; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPriority][nCntObj] == nullptr)
			{ // ��񂪂Ȃ���΃R���e�B�j���[
				continue;
			}

			if (m_apObject[nCntPriority][nCntObj]->GetType() == CObject::TYPE::SCORE)
			{ // �X�R�A�^�C�v�Ȃ烊�^�[��
				return m_apObject[nCntPriority][nCntObj];
			}
		}
	}

	// �����ł��Ȃ���΃G���[
	assert(false);

	return nullptr;
}

//============================================================================
// �^�C�v�ݒ�
//============================================================================
void CObject::SetType(TYPE type) 
{
	m_type = type;
}

//============================================================================
// �������
//============================================================================
void CObject::Release()
{
	int nPriority = m_nPriority;	// �v���C�I���e�B���R�s�[���Ă���
	int nID = m_nID;				// ID���R�s�[���Ă���

	if (m_apObject[nPriority][nID] != nullptr)
	{
		m_apObject[nPriority][nID]->Uninit();	// �I������
		delete m_apObject[nPriority][nID];		// �����������
		m_apObject[nPriority][nID] = nullptr;	// �|�C���^��������
		m_nNumAll--;							// �������J�E���g�_�E��
	}
}