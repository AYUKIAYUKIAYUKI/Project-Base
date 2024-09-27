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
	m_pDestText{ nullptr },
	m_pBestText{ nullptr }
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

	// �I���t�F�[�Y�Ȃ�ō��L�^�𐶐�
	if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::C_FINISH)
	{
		if (!m_pBestText)
		{
			// �������W�p
			D3DXVECTOR3 InitPos{ (SCREEN_WIDTH * 0.5f), -100.0f, 0.0f };

			// �e�L�X�g�𐶐�
			m_pBestText = CText::Create(CTexture_Manager::TYPE::RECORDBEST);
			m_pBestText->SetPos(InitPos);
			m_pBestText->SetAppear(true);

			for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
			{
				// �����𐶐�
				m_apBestNum[nCntNum] = CNumber::Create();
				m_apBestNum[nCntNum]->SetPos(InitPos);
				m_apBestNum[nCntNum]->SetAppear(true);
			}
		}
		else
		{ // �����ς݂̏ꍇ�͖ڕW�l�ݒ�

			m_pBestText->SetPosTarget({ SCREEN_WIDTH * 0.625f, SCREEN_HEIGHT * 0.15f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
			m_pBestText->SetSizeTarget({ 140.0f, 30.0f, 0.0f });

			// �ݒ�p���ʏ��
			CopyPosTarget = m_pBestText->GetPosTarget();
			fSizeX = 42.5f;	// ���ʉ��T�C�Y

			// �J�E���g���̃R�s�[
			nCopy = CRecord_Dest::ImportBestRecord();

			// ��������ׂ�
			for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
			{
				// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
				CopyPosTarget.x = m_pBestText->GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f) + 210.0f;

				// �擪���W���琔�������Ԃ悤�ɒ���
				CopyPosTarget.x += -fSizeX * nCntNum;
				m_apBestNum[nCntNum]->SetPosTarget(CopyPosTarget);

				// �����̖ڕW�T�C�Y��ݒ�
				m_apBestNum[nCntNum]->SetSizeTarget({ fSizeX, 30.0f, 0.0f });

				// ������ݒ�
				m_apBestNum[nCntNum]->SetNumber(nCopy % 10);

				// �������炷
				nCopy /= 10;
			}
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
// �ō��L�^�\�L�������\��
//============================================================================
void CRecord_Dest::SetDisappearBest()
{
	m_pBestText->SetDisappear(true);
	m_pBestText = nullptr;
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++) {
		m_apBestNum[nCntNum]->SetDisappear(true);
		m_apBestNum[nCntNum] = nullptr;
	}
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

	//// �����_���ȍ��W��ݒ�
	//pRecord->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
	//				(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
	//				0.0f });

	//// �T�C�Y�̐ݒ�
	//pRecord->SetSize({ 0.0f, 0.0f, 0.0f });

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
	int nBestTime{ std::stoi(vStr.front().substr(vStr.front().find("b") + 2, vStr.front().find(","))) };

	// �x�X�g���ƃ��X�g�����ׂ�
	if (pRecord->m_nCntDest > nBestTime)
	{
		// �x�X�g�������Ă����Ȃ�X�V
		nBestTime = pRecord->m_nCntDest;
	}

	// ���X�g��������������
	vStr.front() = "b:" + std::to_string(nBestTime) + ",";

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