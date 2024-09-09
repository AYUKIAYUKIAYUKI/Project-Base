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
	m_nTimer{ 0 },
	m_pText{ nullptr }
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// �������̃|�C���^��������
		m_apNumber[nCntNum] = nullptr;

		// �����𐶐�
		m_apNumber[nCntNum] = CNumber::Create();

		// �����_���ȍ��W
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f), -100.0f, 0.0f };

		// �������W�̐ݒ�
		m_apNumber[nCntNum]->SetPos(pos);

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
		if (!pTimer->m_pText)
		{
			// �e�L�X�g����������Ă��Ȃ���ΐ���
			pTimer->m_pText = CText::Create(CTexture_Manager::TYPE::LASTTIME);

			// �ڕW�T�C�Y��ݒ�
			pTimer->m_pText->SetSizeTarget({ 159.75, 22.5f, 0.0f });
		}

		// �ڕW���W��ݒ肵�A�k�킷
		pTimer->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f, });
		
		// �ڕW���W�̃R�s�[���쐬
		D3DXVECTOR3 CopyPosTarget{ pTimer->GetPosTarget() };

		// ��������ׂ�
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			CopyPosTarget.x = pTimer->GetPosTarget().x + (25.0f * MAX_DIGIT * 0.5f) - (25.0f * 0.5f);

			// �擪���W���琔�������Ԃ悤�ɒ���
			CopyPosTarget.x += -25.0f * nCntNum;
			pTimer->m_apNumber[nCntNum]->SetPosTarget(CopyPosTarget);

			// �����̖ڕW�T�C�Y��ݒ�
			pTimer->m_apNumber[nCntNum]->SetSizeTarget({ 25.0f, 20.0f, 0.0f });
		}

		// �^�C���̓ǂݍ���
		pTimer->m_nTimer = pTimer->ImportTimer(nSelect);

		// �e�L�X�g�����ɕt����
		CopyPosTarget.x += -200.0f;
		pTimer->m_pText->SetPosTarget(CopyPosTarget);
	}
	else if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::INGAME)
	{
		if (pTimer->m_pText)
		{
			// �e�L�X�g����������Ă���Ώ���
			pTimer->m_pText->SetDisappear(true);

			// �ڕW���W��ݒ�
			pTimer->m_pText->SetPosTarget({ 0.0f, 0.0f, 0.0f });

			//// �ڕW�T�C�Y��ݒ�
			//pTimer->m_pText->SetSizeTarget({ 0.0f, 0.0f, 0.0f });

			// �|�C���^��������
			pTimer->m_pText = nullptr;
		}

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
void CTimer::ExportTimer(int nSelect)
{
	// �e�L�X�g���s���Ƃɕێ�����
	std::vector<std::string> vStr;
	//vStr.reserve(1);

	// ���x���t�@�C����W�J
	std::ifstream Import{ "Data\\TXT\\level.txt" };

	if (!Import)
	{ // �W�J���s
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("�y�x���z���x�����E�^�C���̓ǂݍ���(2)�Ɏ��s���܂���", 300);
#endif	// _DEBUG

		return;
#endif
	}

	// �e�L�X�g���i�[
	std::string str;

	// �t�@�C������s���A����S�Ď擾����
	while (std::getline(Import, str))
	{
		vStr.push_back(str);
	}

	// �t�@�C�������
	Import.close();

	// �^�C��������
	CObject* pObj = CObject::FindObject(CObject::TYPE::TIMER);
	CTimer* pTimer = CUtility::GetInstance()->DownCast<CTimer, CObject>(pObj);

	// �V��ł������x���̃^�C����������������
	vStr[nSelect] = vStr[nSelect].substr(0, vStr[nSelect].find(",") + 1) + std::to_string(pTimer->m_nTimer) + ",";

	// ���x���t�@�C����W�J
	std::ofstream Export{ "Data\\TXT\\level.txt" };

	if (!Export)
	{ // �W�J���s
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("�y�x���z���x�����E�^�C���̏����o���Ɏ��s���܂���", 300);
#endif	// _DEBUG

		return;
#endif
	}

	// �ύX�����������ł��Ƃ̃t�@�C�����X�V����
	for (auto&& it : vStr)
	{
		Export << it.c_str() << std::endl;
	}

	// �t�@�C�������
	Export.close();
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
	// ���x���t�@�C����W�J
	std::ifstream Import{ "Data\\TXT\\level.txt" };

	if (!Import)
	{ // �W�J���s
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("�y�x���z���x�����E�^�C���̓ǂݍ���(1)�Ɏ��s���܂���", 300);
#endif	// _DEBUG

		return 0;
#endif
	}

	// ���͊i�[��
	std::string str{ };

	// �e�L�X�g��ǂݎ��
	for (int i = 0; i <= nSelect; i++)
	{
		// �w��ԍ��̍s�֐i�߂�
		std::getline(Import, str);
	}

	// �X�e�[�W�t�@�C���̃^�C�������𒊏o
	std::string timer = str.substr(str.find(",") + 1, str.find(",") - 1);

	// �����l�ɕϊ�
	return std::stoi(timer);
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