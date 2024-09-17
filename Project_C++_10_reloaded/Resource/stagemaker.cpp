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
#include "achievement.h"
#include "block.h"
#include "block_destructible.h"
#include "block_destructible_big.h"
#include "block_spikes.h"
#include "block_spikes_move.h"
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
		else if (str_type == "dest_big")
		{ // ��ł��u���b�N
			CBlockDestructibleBig::Create(pos);
		}
		else if (str_type == "spikes")
		{ // �Ƃ��u���b�N
			CBlockSpikes::Create(pos);
		}
		else if (str_type == "spikes_move")
		{ // �Ƃ��ړ��u���b�N
			float fAngleInit{ std::stof(str.substr(str.find("i:") + 2, str.find(","))) };
			float fAdder{ std::stof(str.substr(str.find("a:") + 2, str.find(","))) };
			float fCoeff{ std::stof(str.substr(str.find("c:") + 2, str.find(","))) };
			CBlockSpikesMove::Create(pos, fAngleInit, fAdder, fCoeff);
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
		else if (str_type == "archieve")
		{ // �A�`�[�u
			CAchieve::Create(pos);
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
	m_nPattern{ 0 },		// �\�����̎�ގ���
	m_fAngleInit{ 0.0f },	// �����p�x
	m_fAdder{ 0.0f },		// ������
	m_fCoeff{ 1.0f },		// ���f�W��
	m_bModify{ false },		// �ҏW�؂�ւ�
	m_nID{ 0 },				// �ҏW����\����������
	m_pDummy{ nullptr }		// �\�����̃_�~�[���
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
		Import("Data\\TXT\\stage.txt");
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
			m_nPattern > 0 ? m_nPattern-- : m_nPattern = 8;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD6))
		{
			m_nPattern < 8 ? m_nPattern++ : m_nPattern = 0;
		}

		CRenderer::GetInstance()->SetDebugString("���݂̍\�����̎��:" + std::to_string(m_nPattern));
	}
	else
	{
		CRenderer::GetInstance()->SetDebugString("���݂̃��[�h -> �ҏW");

		if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD0))
		{
			m_nID = 0;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD4))
		{
			m_nID--;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD6))
		{
			m_nID++;
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD8))
		{
			m_nID++;
		}

		CRenderer::GetInstance()->SetDebugString("���݂̍\������ID:" + std::to_string(m_nID));

		if (CManager::GetKeyboard()->GetPress(DIK_RCONTROL))
		{
			// ��ĕҏW
			ModifyAll();
		}
		else
		{
			// �ҏW
			Modify();
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_F4))
	{
		// �Ƃ��ړ��u���b�N�̊p�x����ă��Z�b�g
		CBlockSpikesMove::ResetAngleAll();
	}
}

//============================================================================
// �Ƃ��p����
//============================================================================
void CStageMaker::ControlSpikes()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_R))
	{
		m_fAngleInit += D3DX_PI * 0.1f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_F))
	{
		m_fAngleInit += D3DX_PI * -0.1f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_V))
	{
		m_fAngleInit = 0.0f;
	}

	if (m_fAngleInit > D3DX_PI)
	{
		m_fAngleInit += -D3DX_PI * 2.0f;
	}
	else if (m_fAngleInit < -D3DX_PI)
	{
		m_fAngleInit += D3DX_PI * 2.0f;
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_T))
	{
		m_fAdder += 0.01f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_G))
	{
		m_fAdder += -0.01f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_B))
	{
		m_fAdder = 0.0f;
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_Y))
	{
		m_fCoeff += 1.0f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_H))
	{
		m_fCoeff += -1.0f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_N))
	{
		m_fCoeff = 1.0f;
	}

	CRenderer::GetInstance()->SetDebugString("�����p�x : " + std::to_string(m_fAngleInit));
	CRenderer::GetInstance()->SetDebugString("������ : " + std::to_string(m_fAdder));
	CRenderer::GetInstance()->SetDebugString("���f�W�� : " + std::to_string(m_fCoeff));
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
		CBlockDestructibleBig::Create(pos);
		break;

	case 3:
		CBlockSpikes::Create(pos);
		break;

	case 4:
		CBlockSpikesMove::Create(pos, m_fAngleInit, m_fAdder, m_fCoeff);
		break;

	case 5:
		CEnemy::Create(pos);
		break;

	case 6:

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

	case 7:

		// �S�[���^�C�v�̃I�u�W�F�N�g������
		if (!CObject::FindObject(CObject::TYPE::GOAL))
		{
			CGoal::Create(pos);
		}
		else
		{
			CRenderer::GetInstance()->SetTimeString("�y�S�[���͂��łɔz�u����Ă��܂��z", 60);
		}

		break;

	case 8:

		// �A�`�[�u�^�C�v�̃I�u�W�F�N�g������
		if (!CObject::FindObject(CObject::TYPE::ACHIEVE))
		{
			CAchieve::Create(pos);
		}
		else
		{
			CRenderer::GetInstance()->SetTimeString("�y�A�`�[�u�͂��łɔz�u����Ă��܂��z", 60);
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
	CObject* pObj = CObject::GetObject(static_cast<int>(CObject::LAYER::MIDDLE));

	// �ҏW����ID�܂ŃI�u�W�F�N�g����������
	for (int i = 0; i < m_nID; i++)
	{
		// �I�u�W�F�N�g���Ȃ���Ό����I��
		if (!pObj)
		{
			break;
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

	if (CManager::GetKeyboard()->GetTrigger(DIK_BACK))
	{
		// �폜
		pObj->SetRelease();

		return;
	}

	// �I�u�W�F�N�g��X�I�u�W�F�N�g�Ƀ_�E���L���X�g
	CObject_X* pX = CUtility::GetInstance()->DownCast<CObject_X, CObject>(pObj);

	if (typeid(*pX) == typeid(CStart))
	{ // ���̃I�u�W�F�N�g���X�^�[�g�I�u�W�F�N�g�Ȃ�

		// X�I�u�W�F�N�g���X�^�[�g�I�u�W�F�N�g�Ƀ_�E���L���X�g
		CStart* pStart = CUtility::GetInstance()->DownCast<CStart, CObject_X>(pX);

		// �_�~�[�̍��W���I�u�W�F�N�g�̍��W�ɓ���
		m_pDummy->SetPos(pStart->GetActualPos());

		// �_�~�[����
		m_pDummy->Control();

		// ���씽�f
		m_pDummy->Update();

		// ���W�𔽉f
		pStart->SetActualPos(m_pDummy->GetPos());
		pStart->SetPos(m_pDummy->GetPos());
		pStart->Update();
	}
	else if (typeid(*pX) == typeid(CGoal))
	{ // ���̃I�u�W�F�N�g���S�[���I�u�W�F�N�g�Ȃ�

		// X�I�u�W�F�N�g���S�[���I�u�W�F�N�g�Ƀ_�E���L���X�g
		CGoal* pGoal = CUtility::GetInstance()->DownCast<CGoal, CObject_X>(pX);

		// �_�~�[�̍��W���I�u�W�F�N�g�̍��W�ɓ���
		m_pDummy->SetPos(pGoal->GetActualPos());

		// �_�~�[����
		m_pDummy->Control();

		// ���씽�f
		m_pDummy->Update();

		// ���W�𔽉f
		pGoal->SetActualPos(m_pDummy->GetPos());
		pGoal->SetPos(m_pDummy->GetPos());
		pGoal->Update();
	}
	else if (typeid(*pX) == typeid(CBlockSpikesMove))
	{ // ���̃I�u�W�F�N�g���Ƃ��ړ��u���b�N�Ȃ�

		// X�I�u�W�F�N�g���Ƃ��ړ��u���b�N�Ƀ_�E���L���X�g
		CBlockSpikesMove* pSpikeMove = CUtility::GetInstance()->DownCast<CBlockSpikesMove, CObject_X>(pX);

		// �_�~�[�̍��W���I�u�W�F�N�g�̍��W�ɓ���
		m_pDummy->SetPos(pSpikeMove->GetPosHold());

		// �_�~�[����
		m_pDummy->Control();

		// ���씽�f
		m_pDummy->Update();

		// ���W�E�ǉ����l�𔽉f
		pSpikeMove->SetPosHold(m_pDummy->GetPos());

		// �ݒ肳��Ă����ǉ������擾
		m_fAngleInit = pSpikeMove->GetAngleInit();
		m_fAdder = pSpikeMove->GetAdder();
		m_fCoeff = pSpikeMove->GetCoeff();
	
		// �Ƃ��p����
		ControlSpikes();

		// �ύX�����ǉ����𔽉f
		pSpikeMove->SetAngleInit(m_fAngleInit);
		pSpikeMove->SetAdder(m_fAdder);
		pSpikeMove->SetCoeff(m_fCoeff);
	}
	else
	{
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
}

//============================================================================
// ��ĕҏW
//============================================================================
void CStageMaker::ModifyAll()
{
	// ����p���W
	D3DXVECTOR3 ControlPos{ 0.0f, 0.0f, 0.0f };

	// Y�������ɃO���b�h�ړ�
	if (CManager::GetKeyboard()->GetTrigger(DIK_W))
	{
		ControlPos.y += 5.0f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_S))
	{
		ControlPos.y += -5.0f;
	}

	// X�����ɃO���b�h�ړ�
	if (CManager::GetKeyboard()->GetTrigger(DIK_A))
	{
		ControlPos.x += -5.0f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_D))
	{
		ControlPos.x += 5.0f;
	}

	// �I�u�W�F�N�g���X�g�̐擪���擾
	CObject* pObj = CObject::GetObject(static_cast<int>(CObject::LAYER::MIDDLE));

	// �I�u�W�F�N�g���Ȃ��Ȃ�܂�
	while (pObj)
	{
		// ���̃I�u�W�F�N�g�̃|�C���^���R�s�[
		CObject* pNext = pObj->GetNext();

		// �I�u�W�F�N�g��X�I�u�W�F�N�g�Ƀ_�E���L���X�g
		CObject_X* pX = CUtility::GetInstance()->DownCast<CObject_X, CObject>(pObj);

		// 
		pX->SetPos(pX->GetPos() + ControlPos);

		// ���̃I�u�W�F�N�g����
		pObj = pNext;
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
	CStart* pStart = CUtility::GetInstance()->DownCast<CStart, CObject>(CObject::FindObject(CObject::TYPE::START));

	// ���������o��
	Output(Export, pStart->GetActualPos(), "start");

	// �S�[���I�u�W�F�N�g���擾
	CGoal* pGoal = CUtility::GetInstance()->DownCast<CGoal, CObject>(CObject::FindObject(CObject::TYPE::GOAL));

	// ���������o��
	Output(Export, pGoal->GetActualPos(), "goal");

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

	// ��ł��u���b�N�^�C�v�̃I�u�W�F�N�g�����ׂĎ擾
	pObject = CObject::FindAllObject(CObject::TYPE::DEST_BIG);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ��ł��u���b�N�N���X�փ_�E���L���X�g
		CBlockDestructibleBig* pDestructible = CUtility::GetInstance()->DownCast<CBlockDestructibleBig, CObject>(pObject[nCntObj]);

		// ���������o��
		Output(Export, pDestructible->GetPos(), "dest_big");
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

	// �Ƃ��ړ��u���b�N�^�C�v�̃I�u�W�F�N�g�����ׂĎ擾
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES_MOVE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �Ƃ��ړ��u���b�N�N���X�փ_�E���L���X�g
		CBlockSpikesMove* pSpike_Move = CUtility::GetInstance()->DownCast<CBlockSpikesMove, CObject>(pObject[nCntObj]);

		// ���������o��
		Output(Export, pSpike_Move->GetPosHold(), "spikes_move", pSpike_Move->GetAngleInit(), pSpike_Move->GetAdder(), pSpike_Move->GetCoeff());
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

	// �A�`�[�u�^�C�v�̃I�u�W�F�N�g�����ׂĎ擾
	pObject = CObject::FindAllObject(CObject::TYPE::ACHIEVE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �A�`�[�u�N���X�փ_�E���L���X�g
		CAchieve* pAchieve = CUtility::GetInstance()->DownCast<CAchieve, CObject>(pObject[nCntObj]);

		// ���������o��
		Output(Export, pAchieve->GetPos(), "archieve");
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

//============================================================================
// ��񏑂��o��
//============================================================================
void CStageMaker::Output(std::ofstream& file, D3DXVECTOR3 pos, std::string str, float fAngleInit, float fAdder, float fCoeff)
{
	// ���W�������o��
	file << std::fixed << std::setprecision(1) << "X:" << pos.x << ",";
	file << std::fixed << std::setprecision(1) << "Y:" << pos.y << ",";
	file << std::fixed << std::setprecision(1) << "Z:" << pos.z << ",";

	// ��ނ������o��
	file << "type:" << str << ",";

	// �ǉ����l�������o��
	file << std::fixed << std::setprecision(3) << "i:" << fAngleInit << ",";
	file << std::fixed << std::setprecision(3) << "a:" << fAdder << ",";
	file << std::fixed << std::setprecision(3) << "c:" << fCoeff << "," << std::endl;
}