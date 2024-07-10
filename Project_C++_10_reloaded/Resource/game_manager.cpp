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
#include "manager.h"

// �I�u�W�F�N�g�����p
#include "player.h"
#include "score.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
CGameManager* CGameManager::m_pGameManager = nullptr;	// ���N���X���

//============================================================================
// �R���X�g���N�^
//============================================================================
CGameManager::CGameManager()
{
	m_phase = PHASE::NONE;		// �t�F�[�Y����
	m_nMaxStage = 0;			// �X�e�[�W��
	m_pGameManager = nullptr;	// ���N���X���̏�����
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CGameManager::~CGameManager()
{

}

//============================================================================
// �����ݒ�
//============================================================================
void CGameManager::Init()
{
	// �J�n�t�F�[�Y��
	m_phase = PHASE::BEGIN;

	// ���x����ǂݍ���
	ImportLevel();
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
	CManager::GetRenderer()->SetDebugString(str);

	switch (m_phase)
	{
	case PHASE::NONE:

		// �����f�o�b�O

		break;

	case PHASE::BEGIN:

		if (!m_stagePath.size())
		{ // �ǂݍ��ރX�e�[�W���Ȃ��Ȃ�����

			// ���U���g��ʂ֑J��
			CManager::GetFade()->SetFade(CScene::MODE::RESULT);

			// �t�F�[�Y�������s��Ȃ�
			m_phase = PHASE::NONE;

			// �ȍ~�̏������s��Ȃ�
			return;
		}

		// �S�I�u�W�F�N�g�������
		CObject::ReleaseAll();

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

		// �v���C�t�F�[�Y��
		m_phase = PHASE::PLAY;

		break;

	case PHASE::PLAY:

		break;

	case PHASE::END:
	
		// �ĊJ�n
		m_phase = PHASE::BEGIN;

		break;

	default:

		// �t�F�[�Y�G���[
		assert(false);
		
		break;
	}
}

//============================================================================
// ����
//============================================================================
void CGameManager::Create()
{
	if (m_pGameManager != nullptr)
	{ // ��d�����֎~
		assert(false);
	}

	// �C���X�^���X�𐶐�
	m_pGameManager = DBG_NEW CGameManager;
}

//============================================================================
// ���
//============================================================================
void CGameManager::Release()
{
	if (m_pGameManager != nullptr)
	{
		// �I������
		m_pGameManager->Uninit();

		// �����������
		delete m_pGameManager;

		// �|�C���^��������
		m_pGameManager = nullptr;
	}
}

//============================================================================
// �t�F�[�Y��ݒ�
//============================================================================
void CGameManager::SetPhase(PHASE phase)
{
	m_phase = phase;
}

//============================================================================
// �擾
//============================================================================
CGameManager* CGameManager::GetInstance()
{
	if (m_pGameManager == nullptr)
	{
		// ����
		m_pGameManager->Create();
	}

	return m_pGameManager;
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