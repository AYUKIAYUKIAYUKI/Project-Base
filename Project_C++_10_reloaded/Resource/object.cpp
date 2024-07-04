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
CObject* CObject::m_apObject[static_cast<int>(LAYER::MAX)][MAX_OBJ] = {};	// �I�u�W�F�N�g�Ǘ�
CObject* CObject::m_apFindObject[MAX_OBJ] = {};							// �������ꂽ�I�u�W�F�N�g�ێ��p
int CObject::m_nNumAll = 0;													// �I�u�W�F�N�g����

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
			return;										// �I��
		}
	}

	// �I�u�W�F�N�g����ɓ��B���A�V�K�����Ɏ��s
	assert(false);
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
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
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
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
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
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
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
// �I�u�W�F�N�g�̃^�C�v���擾
//============================================================================
CObject::TYPE CObject::GetType()
{
	return m_type;
}

//============================================================================
// ����^�C�v�̃I�u�W�F�N�g��T��
//============================================================================
CObject* CObject::FindObject(TYPE type)
{
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPriority][nCntObj] == nullptr)
			{ // ��񂪂Ȃ���΃R���e�B�j���[
				continue;
			}

			if (m_apObject[nCntPriority][nCntObj]->GetType() == type)
			{ // �^�C�v��v�Ȃ�Ԃ�
				return m_apObject[nCntPriority][nCntObj];
			}
		}
	}

	// �����Ɏ��s
	assert(false);

	return nullptr;
}

//============================================================================
// ����^�C�v�̃I�u�W�F�N�g�����ׂĒT��
//============================================================================
CObject** CObject::FindAllObject(TYPE type)
{
	// ������������
	int nCntFind = 0;

	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
		{
			if (m_apObject[nCntPriority][nCntObj] == nullptr)
			{ // ��񂪂Ȃ���΃R���e�B�j���[
				continue;
			}

			if (m_apObject[nCntPriority][nCntObj]->GetType() == type)
			{ // �^�C�v��v�Ȃ�ێ�
				m_apFindObject[nCntFind] = m_apObject[nCntPriority][nCntObj];

				// �����̏��Ԃ��J�E���g�A�b�v
				nCntFind++;
			}
		}
	}

	return m_apFindObject;
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