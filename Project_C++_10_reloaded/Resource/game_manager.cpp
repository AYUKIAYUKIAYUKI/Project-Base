//============================================================================
// 
// �Q�[���}�l�[�W���[ [game_manager.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "game_manager.h"
#include "stagemaker.h"
#include "fakescreen.h"

// �t�F�[�h�擾�p
#include "manager.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �I�u�W�F�N�g�����p
#include "block_destructible.h"
#include "leaf.h"
#include "player.h"
#include "score.h"

// �e�X�g�p
#include "KARIHAIKEI.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
CGameManager* CGameManager::m_pInstance = nullptr;	// �Q�[���}�l�[�W���[�̃|�C���^

//============================================================================
// ����
//============================================================================
void CGameManager::Create()
{
	if (m_pInstance != nullptr)
	{ // ��d�����֎~
		assert(false);
	}

	// �Q�[���}�l�[�W���[�𐶐�
	m_pInstance = DBG_NEW CGameManager{};
}

//============================================================================
// �����ݒ�
//============================================================================
void CGameManager::Init()
{
	// ���x���J�n�t�F�[�Y��
	m_phase = PHASE::START;

	// ���x����ǂݍ���
	ImportLevel();
}

//============================================================================
// ���
//============================================================================
void CGameManager::Release()
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
void CGameManager::Uninit()
{

}

//============================================================================
// �X�V����
//============================================================================
void CGameManager::Update()
{
	// �X�e�[�W����\��
	std::string str = "�y���݂̃X�e�[�W:" + std::to_string(m_nMaxStage - m_stagePath.size()) + "/" + std::to_string(m_nMaxStage) + "�z";
	CRenderer::GetInstance()->SetDebugString(str);

	switch (m_phase)
	{
	case PHASE::NONE:

		// �����f�o�b�O

		CRenderer::GetInstance()->SetDebugString("����");

		break;

	case PHASE::START:

		// �S�I�u�W�F�N�g�������
		CObject::ReleaseAll();

		// KARIHAIKEI�̐���
		KARIHAIKEI::Create();

		// �X�e�[�W��ǂݍ���
		CStageMaker::GetInstance()->Import(m_stagePath[0]);

		// �擪�v�f���폜����
		m_stagePath.erase(m_stagePath.begin());

		// �v���C���[�̐���
		CPlayer::Create({ 0.0f, 0.0f, 0.0f });	// �ʒu

		// �X�R�A�̐���
		CScore::Create(
			{ 25.0f, 30.0f, 0.0f },	// �ʒu
			25.0f);					// ����̔z�u�Ԋu

		// ���x���i�s�t�F�[�Y��
		m_phase = PHASE::INGAME;

		CRenderer::GetInstance()->SetDebugString("���x���J�n");

		break;

	case PHASE::INGAME:

		CRenderer::GetInstance()->SetDebugString("�C���Q�[��");

		// �t���ϐ����̍X�V
		CLeaf::UpdateToCreate();

		break;

	case PHASE::FINISH:

		// �ǂݍ��ރX�e�[�W���Ȃ��Ȃ�����
		if (!m_stagePath.size())
		{
			// �Q�[���I���t�F�[�Y��
			m_phase = PHASE::END;
		}
		else
		{
			// ���x���J�n�t�F�[�Y�֖߂�
			m_phase = PHASE::START;
		}
		
		CRenderer::GetInstance()->SetDebugString("���x���I��");

		break;

	case PHASE::END:

		// �E�F�[�u��~
		CFakeScreen::GetInstance()->StopWave();

		// �t�F�[�Y����������
		m_phase = PHASE::NONE;

		// ���U���g��ʂ֑J��
		CFakeScreen::GetInstance()->SetFade(CScene::MODE::RESULT);

		CRenderer::GetInstance()->SetDebugString("�Q�[���I��");

		break;

	default:

		// �t�F�[�Y�G���[
		assert(false);
		
		break;
	}
}

//============================================================================
// �t�F�[�Y�擾
//============================================================================
CGameManager::PHASE CGameManager::GetPhase()
{
	return m_phase;
}

//============================================================================
// �t�F�[�Y�ݒ�
//============================================================================
void CGameManager::SetPhase(PHASE phase)
{
	m_phase = phase;
}

//============================================================================
// �Q�[���}�l�[�W���[���擾
//============================================================================
CGameManager* CGameManager::GetInstance()
{
	// �I�u�W�F�N�g���������
	if (m_pInstance == nullptr)
	{
		// ����
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CGameManager::CGameManager() : 
	m_phase{ PHASE::NONE },	// �t�F�[�Y����
	m_nMaxStage{ 0 },		// �X�e�[�W��
	m_nCntGoal{ 0 },		// �S�[����J�E���g
	m_stagePath{}			// �X�e�[�W�p�X
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CGameManager::~CGameManager()
{

}

//============================================================================
// ���x���ǂݍ���
//============================================================================
void CGameManager::ImportLevel()
{
	std::ifstream Import("Data\\TXT\\level.txt");

	if (!Import)
	{ // �W�J���s
		assert(false);
	}

	// ���͊i�[��
	std::string str;

	// �X�e�[�W�J�E���g
	int nCntStage = 0;

	// �e�L�X�g��ǂݎ��
	while (std::getline(Import, str))
	{
		// �X�e�[�W�̃p�X��ێ�
		m_stagePath.push_back(str);

		// �X�e�[�W�����J�E���g�A�b�v
		nCntStage++;
	}

	// �X�e�[�W����ێ�
	m_nMaxStage = nCntStage;
}