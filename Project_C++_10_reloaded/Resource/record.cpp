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

// �}�X�ڏ��擾�p
#include "square.h"
#include "game_manager.h"

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

	for (int nCntBack = 0; nCntBack < MAX_BACK; nCntBack++)
	{
		// �߂�}�[�N���̃|�C���^��������
		m_apBack[nCntBack] = nullptr;

		// �e�L�X�g�𐶐�
		m_apBack[nCntBack] = CText::Create(CTexture_Manager::TYPE::BACK);

		// �����_���ȍ��W
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 5.0f, (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 5.0f, 0.0f };

		// �������W�̐ݒ�
		m_apBack[nCntBack]->SetPos(pos);

		// ���������̐ݒ�
		m_apBack[nCntBack]->SetRot({ 0.0f, 0.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.5f });

		// �߂�}�[�N�̏o���\��
		m_apBack[nCntBack]->SetAppear(true);
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

	// �}�X�ڂɖ߂�}�[�N����ׂ�
	LayoutBackAtSquare();
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

	// �߂�}�[�N�̏����\��
	for (int nCntBack = 0; nCntBack < MAX_BACK; nCntBack++)
	{
		// �����_���ȍ��W
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>(), (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>(), 0.0f };

		// �ڕW���W�̐ݒ�
		m_apBack[nCntBack]->SetPosTarget(pos);

		// �ڕW�����̐ݒ�
		m_apBack[nCntBack]->SetRotTarget({ 0.0f, 0.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.1f });

		// �����\��
		m_apBack[nCntBack]->SetDisappear(true);
	}
}

//============================================================================
// ����
//============================================================================
CRecord* CRecord::Create()
{
	// �C���X�^���X�𐶐�
	CRecord* pRecord = DBG_NEW CRecord{};

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

//============================================================================
// �^�C���̓ǂݍ���
//============================================================================
int CRecord::ImportRecord(int nSelect)
{
	// �L���X�e�[�W��I�����Ă��Ȃ��ꍇ�͖���
	if (nSelect < 0 || nSelect >= CGameManager::GetInstance()->GetMaxStage())
	{
		return 0;
	}

	// �e�L�X�g���s���Ƃɕێ�����
	std::vector<std::string> vStr{};

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
// �}�X�ڂɖ߂�}�[�N����ׂ�
//============================================================================
void CRecord::LayoutBackAtSquare()
{
	// �����\��Ȃ疳��
	if (m_apBack[0]->GetDisappear())
	{
		return;
	}

	// �}�X�ڃ^�O�̃I�u�W�F�N�g�����ׂĎ擾
	CObject** pObject = CObject::FindAllObject(CObject::TYPE::SQUARE);

	for (int nCntObj = -1, nCntBack = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj + 1] == nullptr)
		{
			break;
		}

		// �擪�E�����̃}�X�̂�
		if (nCntObj == -1 || nCntObj == CGameManager::GetInstance()->GetMaxStage())
		{
			// �}�X�ڃN���X�փ_�E���L���X�g
			CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObject[nCntObj + 1]);

			// �}�X�ڂƖ߂�}�[�N�̍��W�𓯊�
			m_apBack[nCntBack]->SetPosTarget(pSquare->GetPosTarget());

			// �V�����ڕW�T�C�Y���쐬
			D3DXVECTOR3 NewSizeTarget{ 0.0f, 0.0f, 0.0f };

			if (nCntObj == CGameManager::GetInstance()->GetSelectLevel())
			{ // ���̃}�X�ڂ�I�����Ă�����
				NewSizeTarget = { 40.0f, 40.0f, 0.0f };
			}
			else
			{ // �I������Ă��Ȃ�
				NewSizeTarget = { 25.0f, 25.0f, 0.0f };
			}
			
			// �V�����ڕW�T�C�Y�𔽉f
			m_apBack[nCntBack]->SetSizeTarget(NewSizeTarget);

			nCntBack++;
		}
	}
}