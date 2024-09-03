//=============================================================================
//
// �^�C�� [timer.cpp]
// Author : ���c����
//
//=============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "timer.h"
#include "utility.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �e�N�X�`���擾�p
#include "texture_manager.h"

// �v���C���[�̏�Ԏ擾�p
#include "player.h"
#include "player_state.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CTimer::CTimer() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_nCntFrame{ 0 },
	m_nTimer{ 0 }
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// �������̃|�C���^��������
		m_apNumber[nCntNum] = nullptr;

		// �����𐶐�
		m_apNumber[nCntNum] = CNumber::Create();

		// �����_���ȍ��W
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f), 0.0f, 0.0f };

		// �������W�̐ݒ�
		m_apNumber[nCntNum]->SetPos(pos);

		// ���������̐ݒ�
		m_apNumber[nCntNum]->SetRot({ 0.0f, 0.0f, D3DX_PI * 2.0f });

		// �����̏o���\��
		m_apNumber[nCntNum]->SetAppear(true);
	}

	// �o���\��
	SetAppear(true);
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CTimer::~CTimer()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CTimer::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CTimer::Uninit()
{
	// ���N���X�̏I������
	CObject_UI::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CTimer::Update()
{
	// �ڕW���W��
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), GetPosTarget(), 0.05f));

	// ���N���X�̍X�V
	CObject_UI::Update();

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	// �����̂�
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// �ڕW���W��
		m_apNumber[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetPos(), m_apNumber[nCntNum]->GetPosTarget(), 0.075f));

		// �ڕW������
		m_apNumber[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetRot(), m_apNumber[nCntNum]->GetRotTarget(), 0.075f));

		// �ڕW�T�C�Y��
		m_apNumber[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetSize(), m_apNumber[nCntNum]->GetSizeTarget(), 0.05f));
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CTimer::Draw()
{
	// ���N���X�̕`�揈��
	CObject_UI::Draw();
}

//============================================================================
// �t�F�[�Y�ɂ�铮��ؑ�
//============================================================================
void CTimer::SwitchControlByPahse(int nSelect)
{
	// �^�C��������
	CObject* pObj = CObject::FindObject(CObject::TYPE::TIMER);
	CTimer* pTimer = CUtility::GetInstance()->DownCast<CTimer, CObject>(pObj);

	if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::SELECT)
	{
		// �ڕW���W��ݒ肵�A�k�킷
		pTimer->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f, });
		
		// ��������ׂ�
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			D3DXVECTOR3 pos = pTimer->GetPosTarget();
			pos.x = pTimer->GetPosTarget().x + (25.0f * MAX_DIGIT * 0.5f) - (25.0f * 0.5f);

			// �擪���W���琔�������Ԃ悤�ɒ���
			pos.x += -25.0f * nCntNum;
			pTimer->m_apNumber[nCntNum]->SetPosTarget(pos);

			// �����̖ڕW�T�C�Y��ݒ�
			pTimer->m_apNumber[nCntNum]->SetSizeTarget({ 25.0f, 20.0f, 0.0f });
		}

		// �^�C���̓ǂݍ���
		pTimer->m_nTimer = pTimer->ImportTimer(nSelect);
	}
	else if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::INGAME)
	{
		// �ڕW���W��ݒ肵�A�k�킷
		pTimer->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.15f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f, });

		// ��������ׂ�
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			D3DXVECTOR3 pos = pTimer->GetPosTarget();
			pos.x = pTimer->GetPosTarget().x + (37.5f * MAX_DIGIT * 0.5f) - (37.5f * 0.5f);

			// �擪���W���琔�������Ԃ悤�ɒ���
			pos.x += -37.5f * nCntNum;
			pTimer->m_apNumber[nCntNum]->SetPosTarget(pos);

			// �����̖ڕW�T�C�Y��ݒ�
			pTimer->m_apNumber[nCntNum]->SetSizeTarget({ 37.5f, 30.0f, 0.0f });
		}

		// �v���C���[������
		CObject* pFind = CObject::FindObject(CObject::TYPE::PLAYER);
		CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(pFind);

		// �S�[����ԂłȂ����
		if (typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerState::STATE::GOAL))
		{
			// �t���[���J�E���g
			pTimer->m_nCntFrame++;

			if (pTimer->m_nCntFrame > 60)
			{
				// �J�E���g���Z�b�g
				pTimer->m_nCntFrame = 0;
			
				// �^�C�}�[�i�s
				pTimer->m_nTimer++;
			}
		}
		//else
		//{
		//	// �^�C���������o��
		//	ExportTimer(pTimer->m_nTimer);
		//}
	}

	// �J�E���g���̃R�s�[
	int nCopy{ pTimer->m_nTimer };

	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// ������ݒ�
		pTimer->m_apNumber[nCntNum]->SetNumber(nCopy % 10);

		// �������炷
		nCopy /= 10;
	}
}

//============================================================================
// ���ԃ��Z�b�g (��)
//============================================================================
void CTimer::TimerReset()
{
	// �^�C��������
	CObject* pObj = CObject::FindObject(CObject::TYPE::TIMER);
	CTimer* pTimer = CUtility::GetInstance()->DownCast<CTimer, CObject>(pObj);

	// ���Ԃ����Z�b�g
	pTimer->m_nCntFrame = 0;
	pTimer->m_nTimer = 0;
}

//============================================================================
// �^�C���̏����o��
//============================================================================
void CTimer::ExportTimer(int nTimer)
{
	//// �X�e�[�W�z�u���������o���W�J
	//std::ofstream Export("Data\\TXT\\stage.txt");
}

//============================================================================
// ����
//============================================================================
CTimer* CTimer::Create()
{
	// �C���X�^���X�𐶐�
	CTimer* pTimer = DBG_NEW CTimer;

	if (pTimer == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pTimer->SetType(TYPE::TIMER);

	// ���N���X�̏����ݒ�
	pTimer->Init();

	// �����_���ȍ��W��ݒ�
	pTimer->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					0.0f });

	// �T�C�Y�̐ݒ�
	pTimer->SetSize({ 0.0f, 0.0f, 0.0f });

	return pTimer;
}

//============================================================================
// �^�C���̓ǂݍ���
//============================================================================
int CTimer::ImportTimer(int nSelect)
{
	std::ifstream Import("Data\\TXT\\timer.txt");

	if (!Import)
	{ // �W�J���s
#if 0
		assert(false);
#else
		CRenderer::GetInstance()->SetDebugString("�y�x���z�^�C�����̓ǂݍ��݂Ɏ��s���܂���");
		return 0;
#endif
	}
	else
	{
		// ���͊i�[��
		std::string str{};

		// �e�L�X�g��ǂݎ��
		for (int i = 0; i < nSelect + 1; i++)
		{
			std::getline(Import, str);
		}

		return std::stoi(str);
	}
}

//============================================================================
// �o��
//============================================================================
void CTimer::Appear()
{
	if (!GetAppear())
	{
		return;
	}

	// �A���t�@�l���擾
	float& fAlpha{ GetAlpha() };

	// ���X�ɓo��
	fAlpha += 0.025f;

	// �ő�l�ɓ��B�ŌŒ�
	if (fAlpha > 1.0f)
	{
		fAlpha = 1.0f;

		// �o���I��
		SetAppear(false);
	}
}

//============================================================================
// ����
//============================================================================
void CTimer::Disappear()
{
	if (!GetDisappear())
	{
		return;
	}

	// �A���t�@�l���擾
	float& fAlpha{ GetAlpha() };

	// ���X�ɏ���
	fAlpha += -0.05f;

	// �Œ�l�ɓ��B�ŌŒ�
	if (fAlpha < 0.0f)
	{
		fAlpha = 0.0f;

		// �o���I��
		SetDisappear(false);

		// �j���\��
		SetRelease();
	}
}