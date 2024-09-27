//=============================================================================
//
// ���~�b�g�^�C�� [limit_timer.cpp]
// Author : ���c����
//
//=============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "limit_timer.h"
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
CLimit_Timer::CLimit_Timer() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_nCntFrame{ 0 },
	m_nTimer{ 30 },
	m_pText{ nullptr }
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// �������̃|�C���^��������
		m_apNumber[nCntNum] = nullptr;

		// �����𐶐�
		m_apNumber[nCntNum] = CNumber::Create();

		// �V�������W���쐬
		D3DXVECTOR3 NewPos{ SCREEN_WIDTH * 0.6f, 0.0f, 0.0f };

		// �������W�̐ݒ�
		m_apNumber[nCntNum]->SetPos(NewPos);
		m_apNumber[nCntNum]->SetPosTarget(NewPos);

		// ���������̐ݒ�
		//m_apNumber[nCntNum]->SetRot({ 0.0f, 0.0f, D3DX_PI * 2.0f });

		// �����̏o���\��
		m_apNumber[nCntNum]->SetAppear(true);
	}

	// �o���\��
	SetAppear(true);
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CLimit_Timer::~CLimit_Timer()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CLimit_Timer::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CLimit_Timer::Uninit()
{
	// ���N���X�̏I������
	CObject_UI::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CLimit_Timer::Update()
{
	// ���Ԍ���
	Decrement();

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

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	// �����\��Ȃ�t���i�������\���
	if (GetDisappear())
	{
		m_pText->SetDisappear(true);

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// �ڕW���W��
			m_apNumber[nCntNum]->SetDisappear(true);
		}
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CLimit_Timer::Draw()
{
	// ���N���X�̕`�揈��
	CObject_UI::Draw();
}

//============================================================================
// �^�C�������擾
//============================================================================
int CLimit_Timer::GetTimer()
{
	return m_nTimer;
}

//============================================================================
// ���Ԍ���
//============================================================================
void CLimit_Timer::Decrement()
{
	// �`�������W���ɓ���
	if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::C_INGAME)
	{
		if (!m_pText)
		{
			// �e�L�X�g����������Ă��Ȃ���ΐ���
			m_pText = CText::Create(CTexture_Manager::TYPE::LIMITTIME);

			// �V�������W���쐬
			D3DXVECTOR3 NewPos{ SCREEN_WIDTH * 0.6f, 0.0f, 0.0f };

			// �������W�̐ݒ�
			m_pText->SetPos(NewPos);
			m_pText->SetPosTarget(NewPos);

			// �����T�C�Y��ݒ�
			m_pText->SetSizeTarget({ 130.0f, 30.0f, 0.0f });
		}

		// �e�L�X�g�̖ڕW���W��ݒ肵�A�k�킷
		SetPosTarget({ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.15f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f, });

		// �e�L�X�g�p�̖ڕW���W�̃R�s�[���쐬
		D3DXVECTOR3 CopyPosTarget{ GetPosTarget() };

		// ���ʉ��T�C�Y��ݒ�
		float fSizeX{ 24.75f };

		// ��������ׂ�
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			CopyPosTarget.x = GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f);

			// �擪���W���琔�������Ԃ悤�ɒ���
			CopyPosTarget.x += -fSizeX * nCntNum;
			m_apNumber[nCntNum]->SetPosTarget(CopyPosTarget);

			// �����̖ڕW�T�C�Y��ݒ�
			m_apNumber[nCntNum]->SetSizeTarget({ fSizeX, 17.5f, 0.0f });
		}

		// �e�L�X�g�����ɕt����
		CopyPosTarget.x += -195.0f;
		m_pText->SetPosTarget(CopyPosTarget);

		// �����̖ڕW���W��ݒ肵�A�k�킷
		SetPosTarget({ SCREEN_WIDTH * 0.78f, SCREEN_HEIGHT * 0.15f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f, });

		// �����p�̖ڕW���W�̃R�s�[���쐬
		CopyPosTarget = GetPosTarget();

		// ���ʉ��T�C�Y��ݒ�
		fSizeX = 42.5f;

		// ��������ׂ�
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			CopyPosTarget.x = GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f);

			// �擪���W���琔�������Ԃ悤�ɒ���
			CopyPosTarget.x += -fSizeX * nCntNum;
			m_apNumber[nCntNum]->SetPosTarget(CopyPosTarget);

			// �����̖ڕW�T�C�Y��ݒ�
			m_apNumber[nCntNum]->SetSizeTarget({ fSizeX, 30.0f, 0.0f });
		}

		// �v���C���[������
		CObject* pFind = CObject::FindObject(CObject::TYPE::PLAYER);

		// �v���C���[���������
		if (pFind)
		{
			CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(pFind);

			// �S�[����ԂłȂ����
			if (typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerStateGoal))
			{
				if (m_nTimer > 0)
				{
					// �t���[���J�E���g
					m_nCntFrame++;

					if (m_nCntFrame > 60)
					{
						// �J�E���g���Z�b�g
						m_nCntFrame = 0;

						// �^�C�}�[����
						m_nTimer--;
					}
				}
				else
				{
					// �����~�X��Ԃ�
					pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::MISS);

					// ���̏�Ɍł��Ă��܂�
					pPlayer->SetPos(pPlayer->GetPos());
					pPlayer->SetPosTarget(pPlayer->GetPos());
				}
			}
		}

		// �J�E���g���̃R�s�[
		int nCopy{ m_nTimer };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// ������ݒ�
			m_apNumber[nCntNum]->SetNumber(nCopy % 10);

			// �������炷
			nCopy /= 10;
		}
	}
}

//============================================================================
// ���ԃ��Z�b�g
//============================================================================
void CLimit_Timer::TimerReset()
{
	// �^�C��������
	CObject* pObj = CObject::FindObject(CObject::TYPE::TIMER);
	CLimit_Timer* pTimer = CUtility::GetInstance()->DownCast<CLimit_Timer, CObject>(pObj);

	// ���Ԃ����Z�b�g
	pTimer->m_nCntFrame = 0;
	pTimer->m_nTimer = 0;
}

//============================================================================
// ����
//============================================================================
CLimit_Timer* CLimit_Timer::Create()
{
	// �C���X�^���X�𐶐�
	CLimit_Timer* pLimit_Timer = DBG_NEW CLimit_Timer;

	if (pLimit_Timer == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pLimit_Timer->SetType(TYPE::TIMER);

	// ���N���X�̏����ݒ�
	pLimit_Timer->Init();

	// �V�������W��ݒ�
	pLimit_Timer->SetPos({ 0.0f, 0.0f, 0.0f });

	// �T�C�Y�̐ݒ�
	pLimit_Timer->SetSize({ 0.0f, 0.0f, 0.0f });

	return pLimit_Timer;
}

//============================================================================
// �o��
//============================================================================
void CLimit_Timer::Appear()
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
void CLimit_Timer::Disappear()
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