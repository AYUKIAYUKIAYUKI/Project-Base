//============================================================================
// 
// �X�e�[�W�쐬 [stagemaker.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "stagemaker.h"
#include "manager.h"

#include "block.h"
#include "dummy.h"
#include "line.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
CStageMaker* CStageMaker::m_pStageMaker = nullptr;	// ���g�̃C���X�^���X

//============================================================================
// �R���X�g���N�^
//============================================================================
CStageMaker::CStageMaker()
{
	m_pStageMaker = nullptr;	// ���g�̃C���X�^���X

	m_nCntMessage = 0;	// ���b�Z�[�W�\������
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CStageMaker::~CStageMaker()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CStageMaker::Init()
{
	// �O���b�h���C������
	CLine::CreateGrid();

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CStageMaker::Uninit()
{

}

//============================================================================
// �X�V����
//============================================================================
void CStageMaker::Update()
{
	// ����
	Control();

	// �f�o�b�O�\�� (�X�e�[�W�����o��)
	if (m_nCntMessage > 0)
	{
		m_nCntMessage--;

		// �f�o�b�O�\��
		CManager::GetRenderer()->SetDebugString("�y�X�e�[�W�������o���܂����z");
	}
}

//============================================================================
// �X�e�[�W�ǂݍ���
//============================================================================
void CStageMaker::Import()
{
	// �X�e�[�W�ۑ�����W�J
	std::ifstream Import("Data\\TXT\\stage.txt");

	if (!Import)
	{ // �W�J�Ɏ��s
		assert(false);
	}

	// ���͊i�[��
	std::string str;

	// �e�L�X�g��ǂݎ��
	while (std::getline(Import, str))
	{
		// ���W�i�[��
		D3DXVECTOR3 pos = {};

		// ���l�ƂȂ镶���i�[��
		std::string strf;

		// ���l�𒊏o����
		strf = str.substr(str.find("X") + 2, str.find(" / "));

		int i = 0;

		// ���o�������l�����W�ɕϊ�
		pos.x = std::stof(strf);
		pos.y = 0.0f;
		pos.z = 0.0f;

		// �u���b�N�𐶐�
		CBlock::Create(pos);
	}

	Import.close();	// �t�@�C�������
}

//============================================================================
// ����
//============================================================================
HRESULT CStageMaker::Create()
{
	if (m_pStageMaker == nullptr)
	{
		// �C���X�^���X�𐶐�
		m_pStageMaker = DBG_NEW CStageMaker();
	}

	if (m_pStageMaker == nullptr)
	{
		// �������s
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// �j��
//============================================================================
void CStageMaker::Release()
{
	if (m_pStageMaker != nullptr)
	{
		// �����������
		delete m_pStageMaker;

		// �|�C���^��������
		m_pStageMaker = nullptr;
	}
}

//============================================================================
// �X�e�[�W�쐬�N���X�擾
//============================================================================
CStageMaker* CStageMaker::GetInstance()
{
	return m_pStageMaker;
}

//============================================================================
// ����
//============================================================================
void CStageMaker::Control()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_F2))
	{
		// �X�e�[�W�����o��
		Export();
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_F3))
	{
		// �X�e�[�W�ǂݍ���
		Import();
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		// �ݒu
		Regist();
	}
}

//============================================================================
// �ݒu
//============================================================================
void CStageMaker::Regist()
{
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(CObject::LAYER::MAX); nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// �I�u�W�F�N�g�����擾
			CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{ // ��񂪂Ȃ���΃R���e�B�j���[
				continue;
			}

			if (pObject->GetType() == CObject::TYPE::DUMMY)
			{ // �_�~�[�^�C�v�Ȃ�

				// �I�u�W�F�N�g�N���X���_�~�[�N���X�փ_�E���L���X�g
				CDummy* pDummy = dynamic_cast<CDummy*>(pObject);

				if (pDummy == nullptr)
				{ // �_�E���L���X�g���s
					assert(false);
				}

				// �_�~�[�̈ʒu�Ƀu���b�N�𐶐�
				CBlock::Create(pDummy->GetPos());
			}
		}
	}
}

//============================================================================
// �X�e�[�W�����o��
//============================================================================
void CStageMaker::Export()
{
	// �X�e�[�W�z�u���������o���W�J
	std::ofstream Export("Data\\TXT\\stage.txt");

	for (int nCntPriority = 0; nCntPriority < static_cast<int>(CObject::LAYER::MAX); nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// �I�u�W�F�N�g�����擾
			CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{ // ��񂪂Ȃ���΃R���e�B�j���[
				continue;
			}

			if (pObject->GetType() == CObject::TYPE::BLOCK)
			{ // �u���b�N�^�C�v�Ȃ�

				// �I�u�W�F�N�g�N���X���u���b�N�N���X�փ_�E���L���X�g
				CBlock* pBlock = dynamic_cast<CBlock*>(pObject);

				if (pBlock == nullptr)
				{ // �_�E���L���X�g���s
					assert(false);
				}

				// ���W�������o��
				Export << std::fixed << std::setprecision(1) << "X:" << pBlock->GetPos().x << " / " << "Y:" << pBlock->GetPos().y << " / " << "Z:" << pBlock->GetPos().z << std::endl;

				// �f�o�b�O�\���̊��Ԃ�ݒ�
				m_nCntMessage = 180;
			}
		}
	}

	Export.close();	// �t�@�C�������
}