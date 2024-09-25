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
#include "barrier_manager.h"
#include "block_destructible.h"
#include "leaf.h"
#include "player.h"
#include "player_state.h"
#include "record.h"
#include "square.h"
#include "timer.h"
#include "tutorial_manager.h"

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
	// ���x����ǂݍ���
	ImportLevel();
}

//============================================================================
// �����ݒ�ƃt�F�[�Y�ݒ�
//============================================================================
void CGameManager::Init(PHASE phase)
{
	// �t�F�[�Y�ݒ�
	m_phase = phase;

	// ���x����ǂݍ���
	ImportLevel();

	// �`�������W���[�h���n�܂�Ƃ���
	if (phase == PHASE::C_START)
	{
		// �`���[�g���A����\�����Ȃ�
		m_bEndTutorial = 1;
	}
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
	// �O�̂��߃`���[�g���A���}�l�[�W���[��j��
	CTutorial_Manager::DeleteInstance();
}

//============================================================================
// �X�V����
//============================================================================
void CGameManager::Update()
{
	if (m_bEndTutorial)
	{
		// BG�J�����̊ԋ�����ݒ�
		CManager::GetCamera()->SetDistanceBG(CUtility::GetInstance()->AdjustToTarget(CManager::GetCamera()->GetDistanceBG(), 25.0f, 0.025f));

		// BG�J�����̖ڕW���W��ݒ�
		CManager::GetCamera()->SetPosBG(CUtility::GetInstance()->AdjustToTarget(CManager::GetCamera()->GetPosBG(), D3DXVECTOR3{ -3.0f, 0.0f, 0.0f }, 0.025f));
	}

	// �L�[�{�[�h���擾
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	// �p�b�h���擾
	CInputPad* pPad = CManager::GetPad();

	// ���E�̓��͏��
	static DWORD dwOldInput{ 0 };
	static bool bInputLeft{ false };
	static bool bInputRight{ false };

	// �E�^���g���K�[����
	if (pPad->GetJoyStickL().X > 0 && dwOldInput == 0)
	{
		bInputRight = true;
	}
	else
	{
		bInputRight = false;
	}

	// ���^���g���K�[����
	if (pPad->GetJoyStickL().X < 0 && dwOldInput == 0)
	{
		bInputLeft = true;
	}
	else
	{
		bInputLeft = false;
	}

	// �ߋ��̓��͏���ێ�
	dwOldInput = pPad->GetJoyStickL().X;

	switch (m_phase)
	{
	case PHASE::SELECT:
	
		// �t���ϐ����̍X�V
		//CLeaf::UpdateToCreate();

		if (pKeyboard->GetTrigger(DIK_A) && m_nSelectLevel > -1 ||
			pPad->GetTrigger(CInputPad::JOYKEY::LEFT) && m_nSelectLevel > -1 ||
			bInputLeft && m_nSelectLevel > -1)
		{
			m_nSelectLevel--;

			// �I����
			CSound::GetInstance()->Play(CSound::LABEL::SELECT);
		}
		else if (pKeyboard->GetTrigger(DIK_D) && m_nSelectLevel < m_nMaxStage ||
			pPad->GetTrigger(CInputPad::JOYKEY::RIGHT) && m_nSelectLevel < m_nMaxStage ||
			bInputRight && m_nSelectLevel < m_nMaxStage)
		{
			m_nSelectLevel++;

			// �I����
			CSound::GetInstance()->Play(CSound::LABEL::SELECT);
		}

		// �}�X�ڂ𓮍�
		CSquare::ControlAll(m_nSelectLevel);

		// �^�C���𓮍�
		CTimer::SwitchControlByPahse(m_nSelectLevel);

		if (pKeyboard->GetTrigger(DIK_RETURN) || pPad->GetTrigger(CInputPad::JOYKEY::START) || pPad->GetTrigger(CInputPad::JOYKEY::A) ||
			pPad->GetTrigger(CInputPad::JOYKEY::B) || pPad->GetTrigger(CInputPad::JOYKEY::X) || pPad->GetTrigger(CInputPad::JOYKEY::Y))
		{
			// ���艹
			CSound::GetInstance()->Play(CSound::LABEL::DEFINE);

			// �X�e�[�W�͈̔͊O��I�����Ă�����
			if (m_nSelectLevel < 0 || m_nSelectLevel >= m_nMaxStage)
			{
				// �^�C�g����ʂ�
				//CFakeScreen::GetInstance()->SetFade(CScene::MODE::RESULT);
				CFakeScreen::GetInstance()->SetFade(CScene::MODE::TITLE);

				return;
			}

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

		// �X�e�[�W�Ƀo���A�𐶐�����
		CBarrier_Manager::CreateStageBarrier();

		// �v���C���[�̐���
		CPlayer::Create();

		// ���x���i�s�t�F�[�Y��
		m_phase = PHASE::INGAME;

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("���x���J�n");
#endif	// _DEBUG

		break;

	case PHASE::INGAME:

		// �������
		if (!m_bEndTutorial)
		{
			// �`���[�g���A���̍X�V
			CTutorial_Manager::UpdateTutorial();
		}

		// �t���ϐ����̍X�V
		//CLeaf::UpdateToCreate();

		// �^�C���̓���
		CTimer::SwitchControlByPahse(m_nSelectLevel);

		// �X�e�[�W�Z���N�g�ɖ߂�
		if (pKeyboard->GetTrigger(DIK_BACK) || pPad->GetTrigger(CInputPad::JOYKEY::START) || pPad->GetTrigger(CInputPad::JOYKEY::BACK))
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

				// ���S��
				CSound::GetInstance()->Play(CSound::LABEL::DIE);
			}
		}

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("�C���Q�[��");
#endif	// _DEBUG

		break;

	case PHASE::FINISH:

		// �������
		if (!m_bEndTutorial)
		{
			// �`���[�g���A���I��
			m_bEndTutorial = true;

			// �`���[�g���A���}�l�[�W���[��j��
			CTutorial_Manager::DeleteInstance();
		}

		// �S�[�����ɃA�`�[�u�����g��������Ȃ����
		if (!CObject::FindObject(CObject::TYPE::ACHIEVE))
		{
			// �I�����Ă��郌�x���̃A�`�[�u������ς݂�
			m_vbCollectAchieve[m_nSelectLevel] = true;
		}

		// ���R�[�h�𐶐�
		CRecord::Create();

		// �}�X�ڂ��X�e�[�W������ + �Q�[���I���}�X
		for (int i = 0; i < m_nMaxStage + 2; i++)
		{
			CSquare::Create();
		}

		// �擪�E�����̐F��ݒ肷��
		CSquare::SetColorFrontAndBack();

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

		// �������
		if (!m_bEndTutorial)
		{
			// �`���[�g���A���I��
			m_bEndTutorial = true;

			// �`���[�g���A���}�l�[�W���[��j��
			CTutorial_Manager::DeleteInstance();
		}

		// ���R�[�h�𐶐�
		CRecord::Create();

		// �}�X�ڂ��X�e�[�W������ + �Q�[���I���}�X
		for (int i = 0; i < m_nMaxStage + 2; i++)
		{
			CSquare::Create();
		}

		// �擪�E�����̐F��ݒ肷��
		CSquare::SetColorFrontAndBack();

		// ���x���I���t�F�[�Y��
		m_phase = PHASE::SELECT;

		// �\����
		CSound::GetInstance()->Play(CSound::LABEL::DISPLAY);

#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString("���^�C�A");
#endif	// _DEBUG

		break;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

	case PHASE::C_START:

		// �X�N���[����ʓ��̉������
		CObject::ReleaseScreen();

		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////

		// KARIHAIKEI�̐���
		KARIHAIKEI::Create();

		// �`�������W�X�e�[�W��ǂݍ���
		CStageMaker::GetInstance()->Import();

		// �X�e�[�W�Ƀo���A�𐶐�����
		CBarrier_Manager::CreateStageBarrier();

		// �v���C���[�̐���
		CPlayer::Create();

		// ���x���i�s�t�F�[�Y��
		m_phase = PHASE::C_INGAME;

		break;

	case PHASE::C_INGAME:

		// ���~�b�g�^�C���̓���

		break;

	case PHASE::C_FINISH:

		// �j��L�^�������o��


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
// �X�e�[�W�����擾
//============================================================================
int CGameManager::GetMaxStage()
{
	return m_nMaxStage;
}

//============================================================================
// �I�����x���ԍ����擾
//============================================================================
int CGameManager::GetSelectLevel()
{
	return m_nSelectLevel;
}

//============================================================================
// �A�`�[�u�����Ԃ��擾
//============================================================================
std::vector<bool> CGameManager::GetCollectAchieve()
{
	return m_vbCollectAchieve;
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
	m_bEndTutorial{ false },
	m_phase{ PHASE::NONE },	// �t�F�[�Y����
	m_nMaxStage{ 0 },		// �X�e�[�W��
	m_nSelectLevel{ 0 },	// ���x���I��
	m_stagePath{},			// �X�e�[�W�p�X
	m_vbCollectAchieve{}	// �A�`�[�u������
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

		// �����Ԃ̊g��
		m_vbCollectAchieve.push_back(false);

		// �X�e�[�W�����J�E���g�A�b�v
		nCntStage++;
	}

	// �X�e�[�W����ێ�
	m_nMaxStage = nCntStage;
}