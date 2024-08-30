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
	CObject_2D{ static_cast<int>(LAYER::UI) },
	m_bAppear{ false },
	m_bDisappear{ false },
	m_nCntFrame{ 0 },
	m_nTimer{ 0 },
	m_posTarget{ 0.0f, 0.0f, 0.0f }
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// �������̃|�C���^��������
		m_apNumber[i] = nullptr;

		// �����𐶐�
		m_apNumber[i] = CNumber::Create(
			{ 0.0f, 0.0f, 0.0f },		// ���W
			{ 25.0f, 20.0f, 0.0f });	// �T�C�Y
	}

	// �o��
	m_bAppear = true;
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
	HRESULT hr = CObject_2D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CTimer::Uninit()
{
	// ���N���X�̏I������
	CObject_2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CTimer::Update()
{
	// �ڕW���W�֔���
	D3DXVECTOR3 pos{ GetPos() };
	pos += (m_posTarget - pos) * 0.05f;
	SetPos(pos);

	// ��������ׂ�
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
		pos.x = GetPos().x + (25.0f * MAX_DIGIT * 0.5f) - (25.0f * 0.5f);

		// �����Ƃɏ���̍��W�֕␳
		pos.x += -25.0f * i;
		m_apNumber[i]->SetPos(pos);
	}

	// ���N���X�̍X�V
	CObject_2D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CTimer::Draw()
{
	// ���N���X�̕`�揈��
	CObject_2D::Draw();
}

//============================================================================
// �t�F�[�Y�ɂ�郂�[�h�ؑ�
//============================================================================
void CTimer::SwitchControlByPahse(int nSelect)
{
	// �^�C��������
	CObject* pObj = CObject::FindObject(CObject::TYPE::TIMER);
	CTimer* pTimer = CUtility::GetInstance()->DownCast<CTimer, CObject>(pObj);

	// �ڕW���W��ݒ肵�A�k�킷
	pTimer->m_posTarget = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f, };
	
	if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::SELECT)
	{
		// �^�C���̓ǂݍ���
		pTimer->m_nTimer = pTimer->ImportTimer(nSelect);
	}
	else if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::INGAME)
	{
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
// �^�C���̏����o��
//============================================================================
void CTimer::ExportTimer(int nTimer)
{
	// �X�e�[�W���ƂɃe�L�X�g�Ƀ^�C����ۑ�
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
	if (!m_bAppear)
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
		m_bAppear = false;
	}
}

//============================================================================
// ����
//============================================================================
void CTimer::Disappear()
{
	if (!m_bDisappear)
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
		m_bDisappear = false;

		// �j���\��
		SetRelease();
	}
}