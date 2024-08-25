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
#include "utility.h"

// �L�[�{�[�h�擾�p
#include "manager.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �I�u�W�F�N�g�z�u�p
#include "block.h"
#include "block_destructible.h"
#include "block_spikes.h"
#include "dummy.h"
#include "enemy.h"
#include "goal.h"
#include "line.h"
#include "start.h"

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

	// ���f���p�^�[�����n�p
	int nPattern = 0;

	// �z�u���[�h�Ȃ猻�݂̃��f���A�ҏW���[�h�Ȃ炻��ȊO���w��
	m_bModify ? nPattern = -1 : nPattern = m_nPattern;
	
	// ���f����ݒ�
	m_pDummy->ChangeModel(nPattern);
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
		else if (str_type == "spikes")
		{ // �Ƃ��u���b�N
			CBlockSpikes::Create(pos);
		}
		else if (str_type == "enemy")
		{ // �G�l�~�[
			CEnemy::Create(pos);
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
CStageMaker::CStageMaker() :
	m_nPattern{ 0 },	// �\�����̎�ގ���
	m_bModify{ false },	// �ҏW�؂�ւ�
	m_nID{ 0 },			// �ҏW����\����������
	m_pDummy{ nullptr }	// �\�����̃_�~�[���
{
	// �X�e�[�W�f�o�b�O���[�h�̂�
	if (CManager::GetScene()->GetMode() == CScene::MODE::STAGE)
	{
		// �\�����̃_�~�[�𐶐�
		m_pDummy = CDummy::Create();

		// �_�~�[�擾���s
		if (!m_pDummy)
		{
			assert(false);
		}

		// �O���b�h���C���𐶐�
		CLine::CreateGrid();
	}
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
			CRenderer::GetInstance()->SetTimeString("�y�X�^�[�g�E�S�[���̔z�u��񂪈ُ�ł��I�z", 180);
		}
		else
		{
			// �X�e�[�W�����o��
			Export();
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_F3))
	{
		// �X�e�[�W�ǂݍ��� (��)
		Import("Data\\TXT\\stage01.txt");
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
	{
		// �ҏW�؂�ւ�
		m_bModify = !m_bModify;
	}

	if (!m_bModify)
	{
		CRenderer::GetInstance()->SetDebugString("���݂̃��[�h -> �z�u");

		// �_�~�[����
		m_pDummy->Control();

		// ���씽�f
		m_pDummy->Update();

		if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
		{
			// �ݒu
			Register();
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD4))
		{
			m_nPattern > 0 ? m_nPattern-- : m_nPattern = 5;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD6))
		{
			m_nPattern < 5 ? m_nPattern++ : m_nPattern = 0;
		}

		CRenderer::GetInstance()->SetDebugString("���݂̍\�����̎��:" + std::to_string(m_nPattern));
	}
	else
	{
		CRenderer::GetInstance()->SetDebugString("���݂̃��[�h -> �ҏW");

		if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD4))
		{
			m_nID--;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD6))
		{
			m_nID++;
		}

		CRenderer::GetInstance()->SetDebugString("���݂̍\������ID:" + std::to_string(m_nID));
	
		// �ҏW
		Modify();
	}
}

//============================================================================
// �ݒu
//============================================================================
void CStageMaker::Register()
{
	// �_�~�[�̈ʒu���擾
	D3DXVECTOR3 pos = m_pDummy->GetPos();

	// �_�~�[�̈ʒu�ɃI�u�W�F�N�g����
	switch (m_nPattern)
	{
	case 0:
		CBlock::Create(pos);
		break;

	case 1:
		CBlockDestructible::Create(pos);
		break;

	case 2:
		CBlockSpikes::Create(pos);
		break;

	case 3:
		CEnemy::Create(pos);
		break;

	case 4:

		// �X�^�[�g�^�C�v�̃I�u�W�F�N�g������
		if (!CObject::FindObject(CObject::TYPE::START))
		{
			CStart::Create(pos);
		}
		else
		{
			CRenderer::GetInstance()->SetTimeString("�y�X�^�[�g�͂��łɔz�u����Ă��܂��z", 60);
		}

		break;

	case 5:

		// �X�^�[�g�^�C�v�̃I�u�W�F�N�g������
		if (!CObject::FindObject(CObject::TYPE::GOAL))
		{
			CGoal::Create(pos);
		}
		else
		{
			CRenderer::GetInstance()->SetTimeString("�y�S�[���͂��łɔz�u����Ă��܂��z", 60);
		}

		break;

	default:
		assert(false);
		break;
	}
}

//============================================================================
// �ҏW
//============================================================================
void CStageMaker::Modify()
{
	// �I�u�W�F�N�g���X�g�̐擪���擾
	CObject* pObj = CObject::GetObject(static_cast<int>(CObject::LAYER::FRONT_MIDDLE));

	// �ҏW����ID�܂ŃI�u�W�F�N�g����������
	for (int i = 0; i < m_nID; i++)
	{
		// �I�u�W�F�N�g��������Ȃ���ΏI��
		if (!pObj)
		{
			return;
		}

		// ���̃I�u�W�F�N�g�̃|�C���^���R�s�[
		CObject* pNext = pObj->GetNext();

		// ���̃I�u�W�F�N�g����
		pObj = pNext;
	}

	// �I�u�W�F�N�g��������Ȃ���ΏI��
	if (pObj == nullptr)
	{
		return;
	}

	// �I�u�W�F�N�g��X�I�u�W�F�N�g�Ƀ_�E���L���X�g
	CObject_X* pX = CUtility::GetInstance()->DownCast<CObject_X, CObject>(pObj);

	// �_�~�[�̍��W���I�u�W�F�N�g�̍��W�ɓ���
	m_pDummy->SetPos(pX->GetPos());

	// �_�~�[����
	m_pDummy->Control();

	// ���씽�f
	m_pDummy->Update();

	// ���W�𔽉f
	pX->SetPos(m_pDummy->GetPos());
	pX->Update();
}

//============================================================================
// �X�e�[�W�����o��
//============================================================================
void CStageMaker::Export()
{
	// �X�e�[�W�z�u���������o���W�J
	std::ofstream Export("Data\\TXT\\stage.txt");

	// �X�^�[�g�I�u�W�F�N�g���擾
	CStart* pStart = CUtility::GetInstance()->DownCast<CStart, CObject>(CObject::FindObject(CObject::TYPE::START));

	// ���������o��
	Output(Export, pStart->GetPos(), "start");

	// �S�[���I�u�W�F�N�g���擾
	CGoal* pGoal = CUtility::GetInstance()->DownCast<CGoal, CObject>(CObject::FindObject(CObject::TYPE::GOAL));

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
		CBlock* pBlock = CUtility::GetInstance()->DownCast<CBlock, CObject>(pObject[nCntObj]);

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
		CBlockDestructible* pDestructible = CUtility::GetInstance()->DownCast<CBlockDestructible, CObject>(pObject[nCntObj]);

		// ���������o��
		Output(Export, pDestructible->GetPos(), "destructible");
	}

	// �Ƃ��u���b�N�^�C�v�̃I�u�W�F�N�g�����ׂĎ擾
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �Ƃ��u���b�N�N���X�փ_�E���L���X�g
		CBlockSpikes* pDestructible = CUtility::GetInstance()->DownCast<CBlockSpikes, CObject>(pObject[nCntObj]);

		// ���������o��
		Output(Export, pDestructible->GetPos(), "spikes");
	}

	// �G�l�~�[�^�C�v�̃I�u�W�F�N�g�����ׂĎ擾
	pObject = CObject::FindAllObject(CObject::TYPE::ENEMY);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �G�l�~�[�u���b�N�N���X�փ_�E���L���X�g
		CEnemy* pEnemy = CUtility::GetInstance()->DownCast<CEnemy, CObject>(pObject[nCntObj]);

		// ���������o��
		Output(Export, pEnemy->GetPos(), "enemy");
	}

	Export.close();	// �t�@�C�������

	// �f�o�b�O�\���̊��Ԃ�ݒ�
	CRenderer::GetInstance()->SetTimeString("�y�X�e�[�W�������o���܂����z", 180);
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