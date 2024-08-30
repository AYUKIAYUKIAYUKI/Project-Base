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
	CObject_2D{ static_cast<int>(LAYER::UI) },
	m_bAppear{ false },
	m_bDisappear{ false },
	m_posTarget{ 0.0f, 0.0f, 0.0f }
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

	// �o��
	m_bAppear = true;
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
	HRESULT hr = CObject_2D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CSquare::Uninit()
{
	// ���N���X�̏I������
	CObject_2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CSquare::Update()
{
	// �o��
	Appear();

	// ����
	Disappear();

	// ���N���X�̍X�V
	CObject_2D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CSquare::Draw()
{
	// ���N���X�̕`�揈��
	CObject_2D::Draw();
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

		// �I�����Ă���}�X��h�炷
		if (nSquareCnt == nSelect)
		{
			posNew = {
				(SCREEN_WIDTH * 0.5f),
				(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
				0.0f };
		}
		else
		{
			posNew = { 
				(SCREEN_WIDTH * 0.5f) + (150.0f * nSquareCnt) - (nSelect * 150.0f),
				SCREEN_HEIGHT * 0.75f + +CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
				0.0f };
		}

		// �ڕW���W��V�������̂�
		pSquare->m_posTarget = posNew;
		
		// �ڕW���W�֔���
		D3DXVECTOR3 pos{ pSquare->GetPos() };
		pos += (pSquare->m_posTarget - pos) * 0.05f;
		pSquare->SetPos(pos);


		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		// ��������ׂ�
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			// ���S���W����A���ΓI�Ȑ擪�̈ʒu��ݒ�
			pos.x = pSquare->GetPos().x + (25.0f * 0.5f) * (MAX_DIGIT * 0.5f);

			// �����Ƃɏ���̍��W�֕␳
			pos.x +=  -25.0f * i;
			pSquare->m_apNumber[i]->SetPos(pos);
		}

		// �J�E���g���̃R�s�[
		int nCopy{ nSquareCnt };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
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
// �}�X�ڂ���ׂ� (�s�K�v)
//============================================================================
void CSquare::LineUpAll(int nSelect)
{
	// �}�X�ڃ^�O�̃I�u�W�F�N�g��S�Ď擾
	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);

	// �}�X���J�E���g
	int nSquareCnt{ 0 };

	// �I�u�W�F�N�g���Ȃ��Ȃ�܂�
	while (pObj[nSquareCnt])
	{
		// �}�X�ڃN���X�Ƀ_�E���L���X�g
		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);

		// �ڕW���W��ݒ�
		pSquare->m_posTarget = { (SCREEN_WIDTH * 0.5f) + (150.0f * nSquareCnt) - (nSelect * 150.0f), SCREEN_HEIGHT * 0.5f, 0.0f };

		// ���֐i�߂�
		nSquareCnt++;
	}
}

//============================================================================
// ����
//============================================================================
CSquare* CSquare::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X�𐶐�
	CSquare* pSquare = DBG_NEW CSquare;

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

	// 2D�I�u�W�F�N�g�Ƀ_�E���L���X�g
	CObject_2D* pObj2D = CUtility::GetInstance()->DownCast<CObject_2D, CObject>(pSquare);

	// �A���t�@�l��ݒ�
	pObj2D->SetAlpha(0.0f);

	return pSquare;
}

//============================================================================
// �o��
//============================================================================
void CSquare::Appear()
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
void CSquare::Disappear()
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