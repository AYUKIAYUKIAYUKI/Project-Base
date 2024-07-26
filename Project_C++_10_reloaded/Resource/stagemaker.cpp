//============================================================================
// 
// �X�e�[�W���[�J�[ [stagemaker.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "stagemaker.h"
#include "manager.h"

#include "block.h"
#include "block_destructible.h"
#include "dummy.h"
#include "start.h"
#include "goal.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
CStageMaker* CStageMaker::m_pInstance = nullptr;	// �X�e�[�W���[�J�[�̃|�C���^

//============================================================================
// ����
//============================================================================
void CStageMaker::Create()
{
	if (m_pInstance != nullptr)
	{ // ��d�����֎~
		assert(false);
	}

	// �C���X�^���X�𐶐�
	m_pInstance = DBG_NEW CStageMaker{};
}

//============================================================================
// �����ݒ�
//============================================================================
void CStageMaker::Init()
{

}

//============================================================================
// ���
//============================================================================
void CStageMaker::Release()
{
	if (m_pInstance != nullptr)
	{
		// �I������
		m_pInstance->Uninit();

		// �����������
		delete m_pInstance;

		// �|�C���^��������
		m_pInstance = nullptr;
	}
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
}

//============================================================================
// �X�e�[�W�ǂݍ���
//============================================================================
void CStageMaker::Import(std::string path)
{
	// �X�e�[�W�ۑ�����W�J
	std::ifstream Import(path);

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
		std::string str_pos[3];

		for (int i = 0; i < 3; i++)
		{
			// ���l�����̂ݒ��o����
			str_pos[i] = str.substr(str.find(":") + 1, str.find(",") - (str.find(":") + 1));

			// �s�K�v�ɂȂ����������폜����
			str.erase(0, str.find(",") + 1);
		}

		// ���o�������l�����W�ɕϊ�
		pos.x = std::stof(str_pos[0]);
		pos.y = std::stof(str_pos[1]);
		pos.z = std::stof(str_pos[2]);

		// ��ނ����ʂ��镶���i�[��
		std::string str_type;

		// ��ނ𒊏o����
		str_type = str.substr(str.find(":") + 1, str.find(",") - (str.find(":") + 1));

		// ��ނɉ����Đ�������
		if (str_type == "block")
		{ // �u���b�N
			CBlock::Create(pos);
		}
		else if (str_type == "destructible")
		{ // ��u���b�N
			CBlockDestructible::Create(pos);
		}
		else if (str_type == "start")
		{ // �X�^�[�g
			CStart::Create(pos);
		}
		else if (str_type == "goal")
		{ // �S�[��
			CGoal::Create(pos);
		}
		else
		{ // �s��
			assert(false);
			//CBlock::Create(pos);
		}
	}

	Import.close();	// �t�@�C�������
}

//============================================================================
// �z�u���̎�ނ��Q��
//============================================================================
int& CStageMaker::GetPatternRef()
{
	return m_nPattern;
}

//============================================================================
// �擾
//============================================================================
CStageMaker* CStageMaker::GetInstance()
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
CStageMaker::CStageMaker() : m_nPattern{ 0 }	// �z�u���̎�ގ���
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CStageMaker::~CStageMaker()
{

}

//============================================================================
// ����
//============================================================================
void CStageMaker::Control()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_F2))
	{
		// �X�^�[�g�^�C�v�̃I�u�W�F�N�g���擾
		CObject* pStart = CObject::FindObject(CObject::TYPE::START);

		// �S�[���^�C�v�̃I�u�W�F�N�g���擾
		CObject* pGoal = CObject::FindObject(CObject::TYPE::GOAL);

		if (pStart == nullptr || pGoal == nullptr)
		{ // �X�^�[�g�E�S�[���^�C�v�̃I�u�W�F�N�g�̔����Ɏ��s
			CManager::GetRenderer()->SetTimeString("�y�X�^�[�g�E�S�[���̔z�u��񂪈ُ�ł��I�z", 180);
		}
		else
		{
			// �X�e�[�W�����o��
			Export();
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_Q))
	{
		m_nPattern > 0 ? m_nPattern-- : m_nPattern = 3;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_E))
	{
		m_nPattern < 3 ? m_nPattern++ : m_nPattern = 0;
	}

	CManager::GetRenderer()->SetDebugString("���݂̔z�u���̎��:" + std::to_string(m_nPattern));

	if (CManager::GetKeyboard()->GetTrigger(DIK_F3))
	{
		// �X�e�[�W�ǂݍ���
		Import("Data\\TXT\\stage.txt");
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		// �ݒu
		Register();
	}
}

//============================================================================
// �ݒu
//============================================================================
void CStageMaker::Register()
{
	// �_�~�[���擾
	CDummy* pDummy = CDummy::DownCast(CObject::FindObject(CObject::TYPE::DUMMY));

	// �_�~�[�̈ʒu�ɃI�u�W�F�N�g����
	switch (m_nPattern)
	{
	case 0:
		CBlock::Create(pDummy->GetPos());
		break;

	case 1:
		CBlockDestructible::Create(pDummy->GetPos());
		break;

	case 2:

		// �X�^�[�g�^�C�v�̃I�u�W�F�N�g������
		if (!CObject::FindObject(CObject::TYPE::START))
		{
			CStart::Create(pDummy->GetPos());
		}
		else
		{
			CManager::GetRenderer()->SetTimeString("�y�X�^�[�g�͂��łɔz�u����Ă��܂��z", 60);
		}

		break;

	case 3:

		// �X�^�[�g�^�C�v�̃I�u�W�F�N�g������
		if (!CObject::FindObject(CObject::TYPE::GOAL))
		{
			CGoal::Create(pDummy->GetPos());
		}
		else
		{
			CManager::GetRenderer()->SetTimeString("�y�S�[���͂��łɔz�u����Ă��܂��z", 60);
		}

		break;

	default:
		assert(false);
		break;
	}
}

//============================================================================
// �X�e�[�W�����o��
//============================================================================
void CStageMaker::Export()
{
	// �X�e�[�W�z�u���������o���W�J
	std::ofstream Export("Data\\TXT\\stage.txt");

	// �X�^�[�g�I�u�W�F�N�g���擾
	CStart* pStart = CStart::DownCast(CObject::FindObject(CObject::TYPE::START));

	// ���������o��
	Output(Export, pStart->GetPos(), "start");

	// �S�[���I�u�W�F�N�g���擾
	CGoal* pGoal = CGoal::DownCast(CObject::FindObject(CObject::TYPE::GOAL));

	// ���������o��
	Output(Export, pGoal->GetPos(), "goal");

	// �u���b�N�^�C�v�̃I�u�W�F�N�g�����ׂĎ擾
	CObject** pObject = CObject::FindAllObject(CObject::TYPE::BLOCK);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �u���b�N�N���X�փ_�E���L���X�g
		CBlock* pBlock = CBlock::DownCast(pObject[nCntObj]);

		// ���������o��
		Output(Export, pBlock->GetPos(), "block");
	}

	// ��u���b�N�^�C�v�̃I�u�W�F�N�g�����ׂĎ擾
	pObject = CObject::FindAllObject(CObject::TYPE::DESTRUCTIBLE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ��u���b�N�N���X�փ_�E���L���X�g
		CBlockDestructible* pDestructible = CBlockDestructible::DownCast(pObject[nCntObj]);

		// ���������o��
		Output(Export, pDestructible->GetPos(), "destructible");
	}

	Export.close();	// �t�@�C�������

	// �f�o�b�O�\���̊��Ԃ�ݒ�
	CManager::GetRenderer()->SetTimeString("�y�X�e�[�W�������o���܂����z", 180);
}

//============================================================================
// ��񏑂��o��
//============================================================================
void CStageMaker::Output(std::ofstream& file, D3DXVECTOR3 pos, std::string str)
{
	// ���W�������o��
	file << std::fixed << std::setprecision(1) << "X:" << pos.x << ",";
	file << std::fixed << std::setprecision(1) << "Y:" << pos.y << ",";
	file << std::fixed << std::setprecision(1) << "Z:" << pos.z << ",";

	// ��ނ������o��
	file << "type:" << str << "," << std::endl;
}