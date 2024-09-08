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

// �e�N�X�`���擾�p
#include "texture_manager.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CSquare::CSquare() :
	CObject_UI{ static_cast<int>(LAYER::UI) }
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
	int nSquareCnt{ 0 };

	// �I�u�W�F�N�g���Ȃ��Ȃ�܂�
	while (pObj[nSquareCnt])
	{
		// �}�X�ڃN���X�փ_�E���L���X�g
		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);

		// �V�K���W���
		D3DXVECTOR3 posNew{ 0.0f, 0.0f, 0.0f };

		// �V�K�������
		D3DXVECTOR3 rotNew{ 0.0f, 0.0f, 0.0f };

		// �V�K�T�C�Y���
		D3DXVECTOR3 sizeNew{ 0.0f, 0.0f, 0.0f };

		// �I�����Ă���}�X�̂ݓ���
		if (nSquareCnt == nSelect)
		{
			posNew = {
				(SCREEN_WIDTH * 0.5f),
				(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
				0.0f };

			rotNew = { 0.0f, 0.0f, D3DX_PI };

			sizeNew = { 60.0f, 60.0f, 0.0f };
		}
		else
		{
			posNew = { 
				(SCREEN_WIDTH * 0.5f) + (150.0f * nSquareCnt) - (nSelect * 150.0f),
				SCREEN_HEIGHT * 0.75f + +CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
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
		int nCopy{ nSquareCnt };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			D3DXVECTOR3 size{ 0.0f, 0.0f, 0.0f };

			// �I�����Ă���}�X�̐����̂݊g��
			if (nSquareCnt == nSelect)
			{	
				size = { 37.5f, 30.0f, 0.0f };
			}
			else
			{
				size = { 25.0f, 20.0f, 0.0f };
			}

			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			posNew.x = pSquare->GetPosTarget().x + (size.x * MAX_DIGIT * 0.5f) - (size.x * 0.5f);

			// �擪���W���琔�������Ԃ悤�ɒ���
			posNew.x += -size.x * nCntNum;
			pSquare->m_apNumber[nCntNum]->SetPosTarget(posNew);

			// �ڕW�T�C�Y�𔽉f
			pSquare->m_apNumber[nCntNum]->SetSizeTarget(size);

			// ������ݒ�
			pSquare->m_apNumber[nCntNum]->SetNumber(nCopy % 10);

			// �������炷
			nCopy /= 10;
		}

		// ���֐i�߂�
		nSquareCnt++;
	}
}

//============================================================================
// �}�X�ڂ�S����
//============================================================================
void CSquare::DisappearAll()
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
		pSquare->SetRotTarget({ 0.0f, 0.0f, -D3DX_PI * 2.0f });

		// �ڕW�T�C�Y��ݒ�
		pSquare->SetSizeTarget(pSquare->GetSize() * 2.0f);

		// �����\��
		pSquare->SetDisappear(true);

		/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// �����_���ȍ��W
			D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 1.5f, (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 1.5f, 0.0f };
			
			// �����̖ڕW���W��ݒ�
			pSquare->m_apNumber[nCntNum]->SetPosTarget(pos);

			// �����̖ڕW������ݒ�
			pSquare->m_apNumber[nCntNum]->SetRotTarget({ 0.0f, 0.0f, -D3DX_PI * 2.0f });

			// �����̖ڕW�T�C�Y��ݒ�
			pSquare->m_apNumber[nCntNum]->SetSizeTarget({ 0.0f, 0.0f, 0.0f });
		}

		// �����������\��
		pSquare->DisappearNumber();

		nSquareCnt++;
	}
}

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
// ����
//============================================================================
CSquare* CSquare::Create(D3DXVECTOR3 pos)
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
		m_apNumber[nCntNum]->SetDisappear(true);
	}
}