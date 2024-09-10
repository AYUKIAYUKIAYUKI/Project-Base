//=============================================================================
//
// ���R�[�h [record.cpp]
// Author : ���c����
//
//=============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "record.h"
#include "utility.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �e�N�X�`���擾�p
#include "texture_manager.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CRecord::CRecord() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_pText{ nullptr }
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// �������̃|�C���^��������
		m_apNumber[nCntNum] = nullptr;

		// �����𐶐�
		m_apNumber[nCntNum] = CNumber::Create();

		// �����_���ȍ��W
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 5.0f, (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 5.0f, 0.0f };

		// �������W�̐ݒ�
		m_apNumber[nCntNum]->SetPos(pos);

		// ���������̐ݒ�
		m_apNumber[nCntNum]->SetRot({ 0.0f, 0.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.5f });

		// �����̏o���\��
		m_apNumber[nCntNum]->SetAppear(true);
	}

	// �o���\��
	SetAppear(true);
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CRecord::~CRecord()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CRecord::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CRecord::Uninit()
{
	// ���N���X�̏I������
	CObject_UI::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CRecord::Update()
{
	// �ڕW���W��ݒ肵�A�k�킷
	SetPosTarget({ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.25f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f, });

	// �ڕW���W��
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), GetPosTarget(), 0.05f));

	// ���N���X�̍X�V
	CObject_UI::Update();

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	// �ڕW���W�̃R�s�[���쐬
	D3DXVECTOR3 CopyPosTarget{ GetPosTarget() };

	// ���ʉ��T�C�Y��ݒ�
	float fSizeX{ 24.75f };

	// �x�X�g�^�C���̓ǂݍ���
	int nBestTime{ ImportRecord(CGameManager::GetInstance()->GetSelectLevel()) };

	// �����̂�
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// �����\��łȂ����
		if (!m_apNumber[nCntNum]->GetDisappear())
		{
			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			CopyPosTarget.x = GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f);

			// �擪���W���琔�������Ԃ悤�ɒ���
			CopyPosTarget.x += -fSizeX * nCntNum;
			m_apNumber[nCntNum]->SetPosTarget(CopyPosTarget);

			// �����̖ڕW�T�C�Y��ݒ�
			m_apNumber[nCntNum]->SetSizeTarget({ fSizeX, 17.5f, 0.0f });
		}

		// �ڕW���W��
		m_apNumber[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetPos(), m_apNumber[nCntNum]->GetPosTarget(), 0.075f));

		// �ڕW������
		m_apNumber[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetRot(), m_apNumber[nCntNum]->GetRotTarget(), 0.075f));

		// �ڕW�T�C�Y��
		m_apNumber[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetSize(), m_apNumber[nCntNum]->GetSizeTarget(), 0.05f));

		// ������ݒ�
		m_apNumber[nCntNum]->SetNumber(nBestTime % 10);

		// �������炷
		nBestTime /= 10;
	}

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	if (!m_pText)
	{
		// �e�L�X�g����������Ă��Ȃ���ΐ���
		m_pText = CText::Create(CTexture_Manager::TYPE::BESTTIME);

		// �ڕW�T�C�Y��ݒ�
		m_pText->SetSizeTarget({ 159.75f, 22.5f, 0.0f });
	}

	// �����\��łȂ����
	if (!m_pText->GetDisappear())
	{
		// �e�L�X�g�����ɕt����
		CopyPosTarget.x += -195.0f;
		m_pText->SetPosTarget(CopyPosTarget);
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CRecord::Draw()
{
	// ���N���X�̕`�揈��
	CObject_UI::Draw();
}

//============================================================================
// ��������\��
//============================================================================
void CRecord::SetDisappearExtra()
{
	// �{�̂̏����\��
	SetDisappear(true);

	// �����̏����\��
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// �����_���ȍ��W
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>(), (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>(), 0.0f };

		// �ڕW���W�̐ݒ�
		m_apNumber[nCntNum]->SetPosTarget(pos);

		// �ڕW�����̐ݒ�
		m_apNumber[nCntNum]->SetRotTarget({ 0.0f, 0.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.1f });

		// �����\��
		m_apNumber[nCntNum]->SetDisappear(true);
	}

	// �ڕW���W�̐ݒ�
	m_pText->SetPosTarget({ SCREEN_WIDTH, 0.0f, 0.0f });

	// �ڕW�T�C�Y�̐ݒ�
	m_pText->SetSizeTarget({ 0.0f, 0.0f, 0.0f });

	// �e�L�X�g�̏����\��
	m_pText->SetDisappear(true);
}

//============================================================================
// ����
//============================================================================
CRecord* CRecord::Create()
{
	// �C���X�^���X�𐶐�
	CRecord* pRecord = DBG_NEW CRecord;

	if (pRecord == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pRecord->SetType(TYPE::RECORD);

	// ���N���X�̏����ݒ�
	pRecord->Init();

	// �����_���ȍ��W��ݒ�
	pRecord->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					0.0f });

	// �T�C�Y�̐ݒ�
	pRecord->SetSize({ 0.0f, 0.0f, 0.0f });

	return pRecord;
}

//============================================================================
// �^�C���̓ǂݍ���
//============================================================================
int CRecord::ImportRecord(int nSelect)
{
	// �e�L�X�g���s���Ƃɕێ�����
	std::vector<std::string> vStr;

	// ���x���t�@�C����W�J
	std::ifstream Import{ "Data\\TXT\\level.txt" };

	if (!Import)
	{ // �W�J���s
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("�y�x���z���x�����E�^�C���̓ǂݍ���(3)�Ɏ��s���܂���", 300);
#endif	// _DEBUG

		return 0;
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

	// �x�X�g�^�C�����𔲂��o��
	int nBestTime{ std::stoi(vStr[nSelect].substr(vStr[nSelect].find("b") + 2, vStr[nSelect].find(","))) };

	return nBestTime;
}

//============================================================================
// �o��
//============================================================================
void CRecord::Appear()
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
void CRecord::Disappear()
{
	if (!GetDisappear())
	{
		return;
	}

	// �A���t�@�l���擾
	float& fAlpha{ GetAlpha() };

	// ���X�ɏ���
	fAlpha += -0.03f;

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