//=============================================================================
//
// �e�L�X�g [text.cpp]
// Author : ���c����
//
//=============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "text.h"
#include "utility.h"

// �e�N�X�`���擾�p
#include "texture_manager.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CText::CText() :
	CObject_UI{ static_cast<int>(LAYER::UI) }
{
	// �o���\��
	SetAppear(true);
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CText::~CText()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CText::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CText::Uninit()
{
	// ���N���X�̏I������
	CObject_UI::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CText::Update()
{
	// �ڕW���W��
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), GetPosTarget(), 0.05f));

	// �ڕW������
	SetRot(CUtility::GetInstance()->AdjustToTarget(GetRot(), GetRotTarget(), 0.05f));

	// �ڕW�T�C�Y��
	SetSize(CUtility::GetInstance()->AdjustToTarget(GetSize(), GetSizeTarget(), 0.05f));

	// ���N���X�̍X�V
	CObject_UI::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CText::Draw()
{
	// ���N���X�̕`�揈��
	CObject_UI::Draw();
}

//============================================================================
// ����
//============================================================================
CText* CText::Create(CTexture_Manager::TYPE tex)
{
	// �C���X�^���X�𐶐�
	CText* pText = DBG_NEW CText{};

	if (pText == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pText->SetType(TYPE::NONE);

	// ���N���X�̏����ݒ�
	pText->Init();

	// �����_���ȍ��W��ݒ�
	pText->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					0.0f });

	// �T�C�Y�̐ݒ�
	pText->SetSize({ 0.0f, 0.0f, 0.0f });

	// �e�N�X�`����ݒ�
	pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(tex));

	// UI�I�u�W�F�N�g�Ƀ_�E���L���X�g
	CObject_UI* pObjUI = CUtility::GetInstance()->DownCast<CObject_UI, CObject>(pText);

	// �A���t�@�l��ݒ�
	pObjUI->SetAlpha(0.0f);

	return pText;
}

//============================================================================
// �o��
//============================================================================
void CText::Appear()
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
void CText::Disappear()
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