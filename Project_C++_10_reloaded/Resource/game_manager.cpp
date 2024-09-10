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
#include "utility.h"
#include "sound.h"

// �t�F�[�h�擾�p
#include "manager.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �I�u�W�F�N�g�����p
#include "block_destructible.h"
#include "leaf.h"
#include "player.h"
#include "player_state.h"
#include "record.h"
#include "square.h"
#include "timer.h"

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
#ifdef _DEBUG
	// �X�e�[�W����\��
	std::string str = "�y���݂̃X�e�[�W:" + std::to_string(m_nMaxStage - m_stagePath.size()) + "/" + std::to_string(m_nMaxStage) + "�z";
	CRenderer::GetInstance()->SetDebugString(str);
#endif	// _DEBUG

	switch (m_phase)
	{
	case PHASE::SELECT:
	
		// �t���ϐ����̍X�V
		//CLeaf::UpdateToCreate();

		if (CManager::GetKeyboard()->GetTrigger(DIK_A) && m_nSelectLevel > 0)
		{
			m_nSelectLevel--;

			// �I����
			CSound::GetInstance()->Play(CSound::LABEL::SELECT);
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_D) && m_nSelectLevel < m_nMaxStage - 1)
		{
			m_nSelectLevel++;

			// �I����
			CSound::GetInstance()->Play(CSound::LABEL::SELECT);
		}

		// �}�X�ڂ𓮍�
		CSquare::ControlAll(m_nSelectLevel);

		// �^�C���𓮍�
		CTimer::SwitchControlByPahse(m_nSelectLevel);

		if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
		{
			// �E�F�[�u���~���A�X�^�[�g�t�F�[�Y�ֈڍs
			CFakeScreen::GetInstance()->StopWave(PHASE::START);

			// ���R�[�h�������\��
			CObject* pObj = CObject::FindObject(CObject::TYPE::RECORD);
			CRecord* pRecord = CUtility::GetInstance()->DownCast<CRecord, CObject>(pObj);
			pRecord->SetDisappearExtra();

			// �}�X�ڂ�S�����\��
			CSquare::SetDisappearAll();

			// �^�C�}�[���Z�b�g
			CTimer::TimerReset();

			// ���艹
			CSound::GetInstance()->Play(CSound::LABEL::DEFINE);
		}

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("���x���I�� : " + std::to_string(m_nSelectLevel));
#endif	// _DEBUG

		break;

	case PHASE::START:

		// �X�N���[����ʓ��̉������
		CObject::ReleaseScreen();

		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////

		// KARIHAIKEI�̐���
		KARIHAIKEI::Create();

		// �X�e�[�W��ǂݍ���
		CStageMaker::GetInstance()->Import(m_stagePath[m_nSelectLevel]);

		// �v���C���[�̐���
		CPlayer::Create();

		// ���x���i�s�t�F�[�Y��
		m_phase = PHASE::INGAME;

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("���x���J�n");
#endif	// _DEBUG

		break;

	case PHASE::INGAME:

		// �t���ϐ����̍X�V
		//CLeaf::UpdateToCreate();

		// �^�C���̓���
		CTimer::SwitchControlByPahse(m_nSelectLevel);

		// �X�e�[�W�Z���N�g�ɖ߂�
		if (CManager::GetKeyboard()->GetTrigger(DIK_BACK))
		{
			// �v���C���[������
			CObject* pFind = CObject::FindObject(CObject::TYPE::PLAYER);
			CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(pFind);

			// �S�[����ԂłȂ����
			if (typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerStateGoal))
			{
				// �E�F�[�u�������I��
				CFakeScreen::GetInstance()->StopWave();

				// ���x���I���t�F�[�Y�ֈڍs
				/* �E�F�[�u���o�R���Ȃ��ƃo�O��܂� */
				CFakeScreen::GetInstance()->SetWave(CGameManager::PHASE::RETIRE);

				// �v���C���[���S�[�����Ԃ�
				pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::GOAL);

				// �^�C�}�[���Z�b�g
				CTimer::TimerReset();
			}
		}

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("�C���Q�[��");
#endif	// _DEBUG

		break;

	case PHASE::FINISH:

		// ���R�[�h�𐶐�
		CRecord::Create();

		// �}�X�ڂ��X�e�[�W������
		for (int i = 0; i < m_nMaxStage; i++)
		{
			CSquare::Create({ 0.0f, 0.0f, 0.0f });
		}

		// �^�C���������o��
		CTimer::ExportTimer(m_nSelectLevel);

		// ���x���I���t�F�[�Y��
		m_phase = PHASE::SELECT;

		// �\����
		CSound::GetInstance()->Play(CSound::LABEL::DISPLAY);
		
#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("���x���I��");
#endif	// _DEBUG

		break;

	case PHASE::RETIRE:

		// ���R�[�h�𐶐�
		CRecord::Create();

		// �}�X�ڂ��X�e�[�W������
		for (int i = 0; i < m_nMaxStage; i++)
		{
			CSquare::Create({ 0.0f, 0.0f, 0.0f });
		}

		// ���x���I���t�F�[�Y��
		m_phase = PHASE::SELECT;

		// ���S��
		CSound::GetInstance()->Play(CSound::LABEL::DIE);

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("���^�C�A");
#endif	// _DEBUG

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
// �I�����x���ԍ����擾
//============================================================================
int CGameManager::GetSelectLevel()
{
	return m_nSelectLevel;
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
	m_nSelectLevel{ 0 },	// ���x���I��
	m_stagePath{}			// �X�e�[�W�p�X
{
	// �^�C���𐶐�
	CTimer::Create();
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
		// �X�e�[�W�t�@�C���̃p�X�����𒊏o��
		std::string path = str.substr(0, str.find(","));

		// �p�X��ێ����Ă���
		m_stagePath.push_back(path);

		// �X�e�[�W�����J�E���g�A�b�v
		nCntStage++;
	}

	// �X�e�[�W����ێ�
	m_nMaxStage = nCntStage;
}