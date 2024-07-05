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
#include "start.h"
#include "goal.h"

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
	m_nCntTEST = 0;		// ������
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

	if (m_nCntTEST > 0)
	{
		m_nCntTEST--;

		// �f�o�b�O�\��
		CManager::GetRenderer()->SetDebugString("�y�X�^�[�g�E�S�[���̔z�u��񂪈ُ�ł��I�z");
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
			//assert(false);
			CBlock::Create(pos);
		}
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
		// �X�^�[�g�^�C�v�̃I�u�W�F�N�g���擾
		CObject* pStart = CObject::FindObject(CObject::TYPE::START);

		// �S�[���^�C�v�̃I�u�W�F�N�g���擾
		CObject* pGoal = CObject::FindObject(CObject::TYPE::GOAL);

		if (pStart == nullptr || pGoal == nullptr)
		{ // �X�^�[�g�E�S�[���^�C�v�̃I�u�W�F�N�g�̔����Ɏ��s
			m_nCntTEST = 180;
		}
		else
		{
			// �X�e�[�W�����o��
			Export();
		}
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
	//�_�~�[���擾
	CDummy* pDummy = CDummy::DownCast(CObject::FindObject(CObject::TYPE::DUMMY));

	// �_�~�[�̈ʒu�Ƀu���b�N�𐶐�
	CBlock::Create(pDummy->GetPos());
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

	Export.close();	// �t�@�C�������

	// �f�o�b�O�\���̊��Ԃ�ݒ�
	m_nCntMessage = 180;
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