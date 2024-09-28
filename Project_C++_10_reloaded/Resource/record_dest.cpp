//=============================================================================
//
// �j��L�^ [record_dest.cpp]
// Author : ���c����
//
//=============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "record_dest.h"
#include "utility.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �e�N�X�`���擾�p
#include "texture_manager.h"

// �Q�[���}�l�[�W���[�擾
#include "game_manager.h"

// �v���C���[�̏�Ԏ擾�p
#include "player.h"
#include "player_state.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CRecord_Dest::CRecord_Dest() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_nCntDest{ 0 },
	m_bTimeUp{ false },
	m_pDestText{ nullptr },
	m_pBestText{ nullptr },
	m_pFailed{ nullptr }
{
	// �������W�p
	D3DXVECTOR3 InitPos{ (SCREEN_WIDTH * 0.5f), -100.0f, 0.0f };

	// �e�L�X�g�𐶐�
	m_pDestText = CText::Create(CTexture_Manager::TYPE::RECORDDEST);
	m_pDestText->SetPos(InitPos);
	m_pDestText->SetAppear(true);

	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// �������̃|�C���^��������
		m_apDestNum[nCntNum] = nullptr;
		m_apBestNum[nCntNum] = nullptr;

		// �����𐶐�
		m_apDestNum[nCntNum] = CNumber::Create();
		m_apDestNum[nCntNum]->SetPos(InitPos);
		m_apDestNum[nCntNum]->SetAppear(true);

		/* �����s�b�^�V�Ȃ̂ł��łɂ���������� */
		m_apUI[nCntNum] = nullptr;
	}

	// �o���\��
	SetAppear(true);
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CRecord_Dest::~CRecord_Dest()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CRecord_Dest::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CRecord_Dest::Uninit()
{
	// ���N���X�̏I������
	CObject_UI::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CRecord_Dest::Update()
{
	// ���N���X�̍X�V
	CObject_UI::Update();

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	/* �ݒ�n�� */

	// �t�F�[�Y�ɂ��UI���앪��
	if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::C_FINISH)
	{ // �ō��L�^�E�I�����𐶐��A�ʏ�L�^���g��

		// �v���C���[������
		CObject* pFind = CObject::FindObject(CObject::TYPE::PLAYER);

		// �v���C���[���������
		if (pFind)
		{
			// �v���C���[�̉����x�𖳂���
			CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(pFind);
			pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });
		}

		// �^�C���A�b�v���Ă��鎞
		if (m_bTimeUp)
		{
			if (!m_pFailed)
			{
				// ���s�\�����o��
				m_pFailed = CText::Create(CTexture_Manager::TYPE::FAILED);

				// �����ݒ�
				m_pFailed->SetPos({ SCREEN_WIDTH,  SCREEN_HEIGHT * 0.5f, 0.0f});
				m_pFailed->SetSizeTarget({ 100.0f, 20.0f, 0.0f });
			}
			else
			{
				// �ڕW���W��ݒ�
				m_pFailed->SetPosTarget({ SCREEN_WIDTH * 0.675f,  SCREEN_HEIGHT * 0.5f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
			}
		}

		///////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////

		m_pDestText->SetPosTarget({ SCREEN_WIDTH * 0.425f, SCREEN_HEIGHT * 0.5f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
		m_pDestText->SetSizeTarget({ 200.0f, 40.0f, 0.0f });

		// �ݒ�p���ʏ��
		D3DXVECTOR3 CopyPosTarget{ m_pDestText->GetPosTarget() };
		float fSizeX{ 55.0f };	// ���ʉ��T�C�Y

		// ��������ׂ�
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			CopyPosTarget.x = m_pDestText->GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f) + 300.0f;

			// �擪���W���琔�������Ԃ悤�ɒ���
			CopyPosTarget.x += -fSizeX * nCntNum;
			m_apDestNum[nCntNum]->SetPosTarget(CopyPosTarget);

			// �����̖ڕW�T�C�Y��ݒ�
			m_apDestNum[nCntNum]->SetSizeTarget({ fSizeX, 40.0f, 0.0f });
		}

		// �J�E���g���̃R�s�[
		int nCopy{ m_nCntDest };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// ������ݒ�
			m_apDestNum[nCntNum]->SetNumber(nCopy % 10);

			// �������炷
			nCopy /= 10;
		}
		
		/////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		
		if (!m_pBestText)
		{
			// �������W�p
			D3DXVECTOR3 InitPos{ (SCREEN_WIDTH * 0.5f), -100.0f, 0.0f };

			// �e�L�X�g�𐶐�
			m_pBestText = CText::Create(CTexture_Manager::TYPE::RECORDBEST);
			m_pBestText->SetPos(InitPos);
			m_pBestText->SetAppear(true);

			// �����𐶐�
			for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
			{
				m_apBestNum[nCntNum] = CNumber::Create();
				m_apBestNum[nCntNum]->SetPos(InitPos);
				m_apBestNum[nCntNum]->SetAppear(true);
			}

			// �I�����𐶐�
			m_apUI[0] = CText::Create(CTexture_Manager::TYPE::QUIT);
			m_apUI[1] = CText::Create(CTexture_Manager::TYPE::RETRY);
			m_apUI[2] = CText::Create(CTexture_Manager::TYPE::CURSOR);
			for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
			{
				m_apUI[nCntNum]->SetPos(InitPos);
				m_apUI[nCntNum]->SetAppear(true);
			}
		}
		else
		{ // �����ς݂̏ꍇ�͖ڕW�l�ݒ�

			m_pBestText->SetPosTarget({ SCREEN_WIDTH * 0.425f, SCREEN_HEIGHT * 0.25f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
			m_pBestText->SetSizeTarget({ 200.0f, 40.0f, 0.0f });

			// �ݒ�p���ʏ��
			CopyPosTarget = m_pBestText->GetPosTarget();
			fSizeX = 55.0f;	// ���ʉ��T�C�Y

			// �J�E���g���̃R�s�[
			nCopy = CRecord_Dest::ImportBestRecord();

			// ��������ׂ�
			for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
			{
				// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
				CopyPosTarget.x = m_pBestText->GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f) + 300.0f;

				// �擪���W���琔�������Ԃ悤�ɒ���
				CopyPosTarget.x += -fSizeX * nCntNum;
				m_apBestNum[nCntNum]->SetPosTarget(CopyPosTarget);

				// �����̖ڕW�T�C�Y��ݒ�
				m_apBestNum[nCntNum]->SetSizeTarget({ fSizeX, 40.0f, 0.0f });

				// ������ݒ�
				m_apBestNum[nCntNum]->SetNumber(nCopy % 10);

				// �������炷
				nCopy /= 10;
			}

			// �I�����ɖڕW���W��ݒ�
			m_apUI[0]->SetPosTarget({ SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.75f, 0.0f });
			m_apUI[1]->SetPosTarget({ SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.75f, 0.0f });
			
			// �I�����ɖڕW�T�C�Y��ݒ�
			m_apUI[0]->SetSizeTarget({ 100.0f, 30.0f, 0.0f });
			m_apUI[1]->SetSizeTarget({ 125.0f, 30.0f, 0.0f });
			m_apUI[2]->SetSizeTarget({ 30.0f, 30.0f, 0.0f });

			// �I���ɉ����Ă���ɕω�
			/* �J�[�\�����W�̓e�L�X�g�������̃T�C�Y���҂����� */
			if (CGameManager::GetInstance()->GetSelectChallenge() == 0)
			{
				m_apUI[0]->SetCol({ 1.0f, 1.0f, 1.0f, m_apUI[1]->GetCol().a });
				m_apUI[0]->SetPosTarget({ SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.75f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
				m_apUI[1]->SetCol({ 0.5f, 0.5f, 0.5f, m_apUI[1]->GetCol().a });
				m_apUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.35f - 150.0f, SCREEN_HEIGHT * 0.75f, 0.0f });
			}
			else
			{
				m_apUI[0]->SetCol({ 0.5f, 0.5f, 0.5f, m_apUI[0]->GetCol().a });
				m_apUI[1]->SetCol({ 1.0f, 1.0f, 1.0f, m_apUI[0]->GetCol().a });
				m_apUI[1]->SetPosTarget({ SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.75f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
				m_apUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.65f - 175.0f, SCREEN_HEIGHT * 0.75f, 0.0f });
			}
		}
	}
	else
	{ // �ʏ�L�^���k��

		m_pDestText->SetPosTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.15f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
		m_pDestText->SetSizeTarget({ 140.0f, 30.0f, 0.0f });

		// �ݒ�p���ʏ��
		D3DXVECTOR3 CopyPosTarget{ m_pDestText->GetPosTarget() };
		float fSizeX{ 42.5f };	// ���ʉ��T�C�Y

		// ��������ׂ�
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			CopyPosTarget.x = m_pDestText->GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f) + 210.0f;

			// �擪���W���琔�������Ԃ悤�ɒ���
			CopyPosTarget.x += -fSizeX * nCntNum;
			m_apDestNum[nCntNum]->SetPosTarget(CopyPosTarget);

			// �����̖ڕW�T�C�Y��ݒ�
			m_apDestNum[nCntNum]->SetSizeTarget({ fSizeX, 30.0f, 0.0f });
		}

		// �J�E���g���̃R�s�[
		int nCopy{ m_nCntDest };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// ������ݒ�
			m_apDestNum[nCntNum]->SetNumber(nCopy % 10);

			// �������炷
			nCopy /= 10;
		}
	}

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	/* ���f�n�� */

	// �����n��
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		if (m_apDestNum[nCntNum])
		{
			m_apDestNum[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apDestNum[nCntNum]->GetPos(), m_apDestNum[nCntNum]->GetPosTarget(), 0.075f));
			m_apDestNum[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apDestNum[nCntNum]->GetRot(), m_apDestNum[nCntNum]->GetRotTarget(), 0.075f));
			m_apDestNum[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apDestNum[nCntNum]->GetSize(), m_apDestNum[nCntNum]->GetSizeTarget(), 0.05f));
		}

		if (m_apBestNum[nCntNum])
		{
			m_apBestNum[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apBestNum[nCntNum]->GetPos(), m_apBestNum[nCntNum]->GetPosTarget(), 0.075f));
			m_apBestNum[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apBestNum[nCntNum]->GetRot(), m_apBestNum[nCntNum]->GetRotTarget(), 0.075f));
			m_apBestNum[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apBestNum[nCntNum]->GetSize(), m_apBestNum[nCntNum]->GetSizeTarget(), 0.05f));
		}
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CRecord_Dest::Draw()
{
	// ���N���X�̕`�揈��
	CObject_UI::Draw();
}

//============================================================================
// �j��L�^�����Z�b�g
//============================================================================
void CRecord_Dest::ResetCntDest()
{
	m_nCntDest = 0;
}

//============================================================================
// �ō��L�^�\�L�E�I�����������\��
//============================================================================
void CRecord_Dest::SetDisappearBestAndUI()
{
	// ���}���u
	if (m_pBestText) {
		m_pBestText->SetDisappear(true);
		m_pBestText = nullptr;
	}

	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++) {
		if (m_apBestNum[nCntNum]) {
			m_apBestNum[nCntNum]->SetDisappear(true);
			m_apBestNum[nCntNum] = nullptr;
		}
	}

	for (int nCntUI = 0; nCntUI < 3; nCntUI++) {
		if (m_apUI[nCntUI]) {
			m_apUI[nCntUI]->SetDisappear(true);
			m_apUI[nCntUI] = nullptr;
		}
	}

	if (m_pFailed) {
		m_pFailed->SetDisappear(true);
		m_pFailed = nullptr;
	}

	// �^�C���A�b�v��������Z�b�g
	m_bTimeUp = false;
}

//============================================================================
// �^�C���A�b�v������o��
//============================================================================
void CRecord_Dest::SetTimeUp()
{
	m_bTimeUp = true;
}

//============================================================================
// �^�C���A�b�v����擾
//============================================================================
bool CRecord_Dest::GetTimeUp()
{
	return m_bTimeUp;
}

//============================================================================
// ����
//============================================================================
CRecord_Dest* CRecord_Dest::Create()
{
	// �C���X�^���X�𐶐�
	CRecord_Dest* pRecord{ DBG_NEW CRecord_Dest() };

	if (pRecord == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pRecord->SetType(TYPE::RECORD);

	// �����ݒ�
	pRecord->Init();

	return pRecord;
}

//============================================================================
// �j��L�^�̑���
//============================================================================
void CRecord_Dest::AddDest()
{
	// �j��L�^���擾
	CObject* pFind{ CObject::FindObject(CObject::TYPE::RECORD) };
	CRecord_Dest* pRecord{ CUtility::GetInstance()->DownCast<CRecord_Dest, CObject>(pFind) };

	// ����
	pRecord->m_nCntDest++;

	// �\���g�嗦
	float fScaleCoeff{ 1.2f };

	// �\�����g��
	pRecord->m_pDestText->SetSize({ 140.0f * fScaleCoeff, 30.0f * fScaleCoeff, 0.0f });

	// �ݒ�p���ʏ��
	D3DXVECTOR3 CopyPos{ pRecord->m_pDestText->GetPos() };
	float fSizeX{ 42.5f * fScaleCoeff };	// ���ʉ��T�C�Y

	// �������L�����ׂ�
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
		CopyPos.x = pRecord->m_pDestText->GetPos().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f) + (210.0f * fScaleCoeff);

		// �擪���W���琔�������Ԃ悤�ɒ���
		CopyPos.x += -fSizeX * nCntNum;
		pRecord->m_apDestNum[nCntNum]->SetPos(CopyPos);

		// �����̃T�C�Y��ݒ�
		pRecord->m_apDestNum[nCntNum]->SetSize({ fSizeX, 30.0f * fScaleCoeff, 0.0f });
	}
}

//============================================================================
// �j��L�^�̏����o��
//============================================================================
void CRecord_Dest::ExportRecord()
{
	// �e�L�X�g���s���Ƃɕێ�����
	std::vector<std::string> vStr;

	// ���x���t�@�C����W�J
	std::ifstream Import{ "Data\\TXT\\dest_record.txt" };

	if (!Import)
	{ // �W�J���s
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("�y�x���z�j��L�^�Ɏ��s���܂���", 300);
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

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	// �j��L�^���擾
	CObject* pFind{ CObject::FindObject(CObject::TYPE::RECORD) };
	CRecord_Dest* pRecord{ CUtility::GetInstance()->DownCast<CRecord_Dest, CObject>(pFind) };

	// �x�X�g���𔲂��o��
	int nBest{ std::stoi(vStr.front().substr(vStr.front().find("b") + 2, vStr.front().find(","))) };

	// �x�X�g���ƃ��X�g�����ׂ�
	if (pRecord->m_nCntDest > nBest)
	{
		// �x�X�g�������Ă����Ȃ�X�V
		nBest = pRecord->m_nCntDest;
	}

	// ���X�g��������������
	vStr.front() = "b:" + std::to_string(nBest) + ",";

	// ���x���t�@�C����W�J
	std::ofstream Export{ "Data\\TXT\\dest_record.txt" };

	if (!Export)
	{ // �W�J���s
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("�y�x���z�j��L�^�̏����o���Ɏ��s���܂���", 300);
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
// �j��L�^�̓ǂݍ���
//============================================================================
int CRecord_Dest::ImportBestRecord()
{
	// �j��L�^�t�@�C����W�J
	std::ifstream Import{ "Data\\TXT\\dest_record.txt" };

	if (!Import)
	{ // �W�J���s
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("�j��L�^�̓ǂݍ��݂Ɏ��s���܂���", 300);
#endif	// _DEBUG

		return 0;
#endif
	}

	// ���͊i�[��
	std::string str{ };

	// �e�L�X�g��ǂݎ��
	std::getline(Import, str);

	// �t�@�C���̃x�X�g�����𒊏o
	std::string best = str.substr(str.find("b:") + 2, str.find(","));

	// �����l�ɕϊ�
	return std::stoi(best);
}

//============================================================================
// �o��
//============================================================================
void CRecord_Dest::Appear()
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
void CRecord_Dest::Disappear()
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