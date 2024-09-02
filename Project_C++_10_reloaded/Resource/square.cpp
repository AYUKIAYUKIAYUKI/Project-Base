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
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// �����̃|�C���^��������
		m_apNumber[i] = nullptr;
	
		m_apNumber[i] = CNumber::Create(
			{ 0.0f, 0.0f, 0.0f },		// ���W
			{ 25.0f, 20.0f, 0.0f });	// �T�C�Y
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
	// ���N���X�̍X�V
	CObject_UI::Update();
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
			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			posNew = pSquare->GetPos();
			posNew.x = pSquare->GetPos().x + (25.0f * MAX_DIGIT * 0.5f) - (25.0f * 0.5f);

			// �����Ƃɏ���̍��W�֕␳
			posNew.x += -25.0f * nCntNum;
			pSquare->m_apNumber[nCntNum]->SetPos(posNew);

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

		// �V�K�������
		D3DXVECTOR3 rotNew{ 0.0f, 0.0f, -D3DX_PI };

		// �V�K�T�C�Y���
		D3DXVECTOR3 sizeNew{ 100.0f, 100.0f, 0.0f };

		// �ڕW������V�������̂�
		pSquare->SetRotTarget(rotNew);

		// �ڕW�T�C�Y��V�������̂�
		pSquare->SetSizeTarget(sizeNew);

		// �����\��
		pSquare->SetDisappear(true);

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
	pSquare->SetSize({ 50.0f, 50.0f, 0.0f });

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