//=============================================================================
//
// �}�X�� [square.cpp]
// Author : ���c����
//
//=============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "square.h"
#include "utility.h"

// �X�e�[�W���擾�p
#include "game_manager.h"

// �e�N�X�`���擾�p
#include "texture_manager.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CSquare::CSquare() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_pCrown{ nullptr }
{
	// �����𐶐�
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// �����̃|�C���^��������
		m_apNumber[nCntNum] = nullptr;
	
		m_apNumber[nCntNum] = CNumber::Create();

		// �����̐ݒ�
		m_apNumber[nCntNum]->SetRot({ 0.0f, 0.0f, D3DX_PI * 10.0f });

		// �ڕW�T�C�Y�̐ݒ�
		m_apNumber[nCntNum]->SetSizeTarget({ 25.0f, 20.0f, 0.0f });

		// �����̏o���\��
		m_apNumber[nCntNum]->SetAppear(true);
	}

	// �o���\��
	SetAppear(true);
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CSquare::~CSquare()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CSquare::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CSquare::Uninit()
{
	// ���N���X�̏I������
	CObject_UI::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CSquare::Update()
{
	// �ڕW���W��
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), GetPosTarget(), 0.065f));

	// �ڕW������
	SetRot(CUtility::GetInstance()->AdjustToTarget(GetRot(), GetRotTarget(), 0.05f));

	// �ڕW�T�C�Y��
	SetSize(CUtility::GetInstance()->AdjustToTarget(GetSize(), GetSizeTarget(), 0.03f));

	// ���N���X�̍X�V
	CObject_UI::Update();

	//////////////////////////////////////////////////
	//////////////////////////////////////////////////

	// �����̂�
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// �ڕW���W��
		m_apNumber[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetPos(), m_apNumber[nCntNum]->GetPosTarget(), 0.065f));
	
		// �ڕW������
		m_apNumber[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetRot(), m_apNumber[nCntNum]->GetRotTarget(), 0.1f));

		// �ڕW�T�C�Y��
		m_apNumber[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetSize(), m_apNumber[nCntNum]->GetSizeTarget(), 0.03f));
	}
}

//============================================================================
// �`�揈��
//============================================================================
void CSquare::Draw()
{
	// ���N���X�̕`�揈��
	CObject_UI::Draw();
}

//============================================================================
// �}�X�ڂ𓮍�
//============================================================================
void CSquare::ControlAll(int nSelect)
{
	// �}�X�ڃ^�O�̃I�u�W�F�N�g��S�Ď擾
	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);

	// �}�X���J�E���g
	/* �I���}�X�̒ǉ��ɂ��A�J�E���g��1��O�͈̔͂���s��*/
	int nSquareCnt{ -1 };

	// �I�u�W�F�N�g���Ȃ��Ȃ�܂�
	while (pObj[nSquareCnt + 1])
	{
		// �}�X�ڃN���X�փ_�E���L���X�g
		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt + 1]);

		// �V�K���W���
		D3DXVECTOR3 posNew{ 0.0f, 0.0f, 0.0f };

		// �V�K�������
		D3DXVECTOR3 rotNew{ 0.0f, 0.0f, 0.0f };

		// �V�K�T�C�Y���
		D3DXVECTOR3 sizeNew{ 0.0f, 0.0f, 0.0f };

		if (nSquareCnt == nSelect)
		{ // �I�����Ă���}�X���g��

			posNew = {
				(SCREEN_WIDTH * 0.5f),
				(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
				0.0f };

			rotNew = { 0.0f, 0.0f, D3DX_PI };

			sizeNew = { 60.0f, 60.0f, 0.0f };
		}
		else
		{ // �ʏ�}�X���k��

			posNew = { 
				(SCREEN_WIDTH * 0.5f) + (150.0f * (nSquareCnt)) - (nSelect * 150.0f),
				SCREEN_HEIGHT * 0.75f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
				0.0f };

			sizeNew = { 40.0f, 40.0f, 0.0f };
		}

		// �ڕW���W��V�������̂�
		pSquare->SetPosTarget(posNew);

		// �ڕW������V�������̂�
		pSquare->SetRotTarget(rotNew);

		// �ڕW�T�C�Y��V�������̂�
		pSquare->SetSizeTarget(sizeNew);
		
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		// �J�E���g���̃R�s�[
		int nCopy{ nSquareCnt + 1 };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// �V�����T�C�Y���쐬
			sizeNew = { 0.0f, 0.0f, 0.0f };

			if (nSquareCnt == -1 || nSquareCnt == CGameManager::GetInstance()->GetMaxStage())
			{ // �I���}�X�̐�����\�����Ȃ�
				sizeNew = { 0.0f, 0.0f, 0.0f };
			}
			else if (nSquareCnt == nSelect)
			{ // �I�����Ă���}�X�̐������g��
				sizeNew = { 37.5f, 30.0f, 0.0f };
			}
			else
			{ // �ʏ�}�X�̐������k��
				sizeNew = { 25.0f, 20.0f, 0.0f };
			}

			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			posNew.x = pSquare->GetPosTarget().x + (sizeNew.x * MAX_DIGIT * 0.5f) - (sizeNew.x * 0.5f);

			// �擪���W���琔�������Ԃ悤�ɒ���
			posNew.x += -sizeNew.x * nCntNum;
			pSquare->m_apNumber[nCntNum]->SetPosTarget(posNew);

			// �ڕW�T�C�Y��ݒ�
			pSquare->m_apNumber[nCntNum]->SetSizeTarget(sizeNew);

			// ������ݒ�
			pSquare->m_apNumber[nCntNum]->SetNumber(nCopy % 10);

			// �������炷
			nCopy /= 10;
		}

		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		if (nSquareCnt == -1 || nSquareCnt == CGameManager::GetInstance()->GetMaxStage())
		{
			nSquareCnt++;
			continue;
		}

		if (!pSquare->m_pCrown)
		{ // �������쐬����Ă��Ȃ����

			// �V�K�쐬
			pSquare->m_pCrown = CCrown::Create();

			// �A�`�[�u�����Ԃ��擾
			std::vector<bool> CollectAchieve{ CGameManager::GetInstance()->GetCollectAchieve() };
	
			// �ǂ�ȉ�����t����̂�����
			if (CollectAchieve[nSquareCnt])
			{ // �A�`�[�u���擾���Ă���

				// �D�݂̐F��
				pSquare->m_pCrown->SetCol(D3DXCOLOR{ 1.0f, 1.0f, 1.0f, pSquare->m_pCrown->GetAlpha() });
			}
			else
			{ // �A�`�[�u���擾���Ă��Ȃ�

				// �����ۂ�
				pSquare->m_pCrown->SetCol(D3DXCOLOR{ 0.15f, 0.15f, 0.15f, pSquare->m_pCrown->GetAlpha() });
			}

			// �o���ݒ�
			pSquare->m_pCrown->SetAppear(true);
		}
		else
		{
			if (nSelect == nSquareCnt)
			{
				// �ڕW������ݒ�
				pSquare->m_pCrown->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, D3DX_PI * -4.0f });

				// �ڕW���W��ݒ�
				D3DXVECTOR3 NewPosTarget{ pSquare->GetPosTarget() };
				NewPosTarget.y += -100.0f;
				pSquare->m_pCrown->SetPosTarget(NewPosTarget);

				// �ڕW�T�C�Y��ݒ�
				pSquare->m_pCrown->SetSizeTarget(D3DXVECTOR3{ 35.0f, 35.0f, 0.0f });
			}
			else
			{
				// �ڕW������ݒ�
				pSquare->m_pCrown->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });

				// �ڕW���W��ݒ�
				D3DXVECTOR3 NewPosTarget{ pSquare->GetPosTarget() };
				NewPosTarget.y += -75.0f;
				pSquare->m_pCrown->SetPosTarget(NewPosTarget);

				// �ڕW�T�C�Y��ݒ�
				pSquare->m_pCrown->SetSizeTarget(D3DXVECTOR3{ 20.0f, 20.0f, 0.0f });
			}
		}

		// ���֐i�߂�
		nSquareCnt++;
	}
}

//============================================================================
// �}�X�ڂ���ď���
//============================================================================
void CSquare::SetDisappearAll()
{
	// �}�X�ڃ^�O�̃I�u�W�F�N�g��S�Ď擾
	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);

	// �}�X���J�E���g
	int nSquareCnt{ 0 };

	// �I�u�W�F�N�g���Ȃ��Ȃ�܂�
	while (pObj[nSquareCnt])
	{
		// �}�X�ڃN���X�փ_�E���L���X�g
		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);

		// �ڕW������ݒ�
		pSquare->SetRotTarget({ 0.0f, 0.0f, -D3DX_PI * 3.0f });

		// �ڕW�T�C�Y��ݒ�
		pSquare->SetSizeTarget(pSquare->GetSize() * 3.0f);

		// �����\��
		pSquare->SetDisappear(true);

		/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////

		// �����������\��
		pSquare->DisappearNumber();

		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
		
		if (pSquare->m_pCrown)
		{ // �������쐬����Ă����
			
			// �ڕW���W��ݒ�
			D3DXVECTOR3 NewPos{ pSquare->m_pCrown->GetPos() };
			NewPos.y = SCREEN_HEIGHT;
			pSquare->m_pCrown->SetPosTarget(NewPos);
			
			// �����\��
			pSquare->m_pCrown->SetDisappear(true);
		}

		nSquareCnt++;
	}
}

////============================================================================
//// �}�X�ڂ𑦍��Ɉ�ď����\��
////============================================================================
//void CSquare::InstantDisappearAll()
//{
//	// �}�X�ڃ^�O�̃I�u�W�F�N�g��S�Ď擾
//	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);
//
//	// �}�X���J�E���g
//	int nSquareCnt{ 0 };
//
//	// �I�u�W�F�N�g���Ȃ��Ȃ�܂�
//	while (pObj[nSquareCnt])
//	{
//		// �}�X�ڃN���X�փ_�E���L���X�g
//		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);
//
//		// �j���\��
//		pSquare->Release();
//
//		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
//		{
//			// �j���\��
//			pSquare->m_apNumber[nCntNum]->Release();
//		}
//
//		nSquareCnt++;
//	}
//}

////============================================================================
//// �}�X�ڂ���ׂ� (�s�K�v)
////============================================================================
//void CSquare::LineUpAll(int nSelect)
//{
//	// �}�X�ڃ^�O�̃I�u�W�F�N�g��S�Ď擾
//	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);
//
//	// �}�X���J�E���g
//	int nSquareCnt{ 0 };
//
//	// �I�u�W�F�N�g���Ȃ��Ȃ�܂�
//	while (pObj[nSquareCnt])
//	{
//		// �}�X�ڃN���X�Ƀ_�E���L���X�g
//		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);
//
//		// �ڕW���W��ݒ�
//		pSquare->SetPosTarget({ (SCREEN_WIDTH * 0.5f) + (150.0f * nSquareCnt) - (nSelect * 150.0f), SCREEN_HEIGHT * 0.5f, 0.0f });
//
//		// ���֐i�߂�
//		nSquareCnt++;
//	}
//}

//============================================================================
// �擪�E�����̐F��ݒ肷��
//============================================================================
void CSquare::SetColorFrontAndBack()
{
	// �}�X�ڃ^�O�̃I�u�W�F�N�g��S�Ď擾
	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);

	// �}�X���J�E���g
	/* �I���}�X�̒ǉ��ɂ��A�J�E���g��1��O�͈̔͂���s��*/
	int nSquareCnt{ -1 };

	// �I�u�W�F�N�g���Ȃ��Ȃ�܂�
	while (pObj[nSquareCnt + 1])
	{
		if (nSquareCnt == -1 || nSquareCnt == CGameManager::GetInstance()->GetMaxStage())
		{ // �擪�E�����̃I�u�W�F�N�g�̂�
			
			// �}�X�ڃN���X�փ_�E���L���X�g
			CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt + 1]);

			// �D���ȐF��
			pSquare->SetCol(D3DXCOLOR{ 0.0f, 1.0f, 1.0f, 0.0f });
		}

		nSquareCnt++;
	}
}

//============================================================================
// ����
//============================================================================
CSquare* CSquare::Create()
{
	// �C���X�^���X�𐶐�
	CSquare* pSquare = DBG_NEW CSquare{};

	if (pSquare == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pSquare->SetType(TYPE::SQUARE);

	// ���N���X�̏����ݒ�
	pSquare->Init();

	// �����_���ȍ��W��ݒ�
	pSquare->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					0.0f });

	// �T�C�Y�̐ݒ�
	pSquare->SetSize({ 0.0f, 0.0f, 0.0f });

	// �e�N�X�`����ݒ�
	pSquare->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::SQUARE_00));

	// UI�I�u�W�F�N�g�Ƀ_�E���L���X�g
	CObject_UI* pObjUI = CUtility::GetInstance()->DownCast<CObject_UI, CObject>(pSquare);

	// �A���t�@�l��ݒ�
	pObjUI->SetAlpha(0.0f);

	return pSquare;
}

//============================================================================
// �o��
//============================================================================
void CSquare::Appear()
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
void CSquare::Disappear()
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
// ����������
//============================================================================
void CSquare::DisappearNumber()
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// �����_���ȍ��W
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 1.5f, (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 1.5f, 0.0f };

		// �����̖ڕW���W��ݒ�
		m_apNumber[nCntNum]->SetPosTarget(pos);

		// �����̖ڕW������ݒ�
		m_apNumber[nCntNum]->SetRotTarget({ 0.0f, 0.0f, -D3DX_PI * 2.0f });

		// �����̖ڕW�T�C�Y��ݒ�
		m_apNumber[nCntNum]->SetSizeTarget({ 0.0f, 0.0f, 0.0f });
	
		// �����\��
		m_apNumber[nCntNum]->SetDisappear(true);
	}
}