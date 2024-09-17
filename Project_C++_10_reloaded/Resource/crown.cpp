//=============================================================================
//
// ���� [crown.cpp]
// Author : ���c����
//
//=============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "crown.h"
#include "utility.h"

// �e�N�X�`���擾�p
#include "texture_manager.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CCrown::CCrown() :
	CObject_UI{ static_cast<int>(LAYER::UI) }
{
	// �o���\��
	SetAppear(true);
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CCrown::~CCrown()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CCrown::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CCrown::Uninit()
{
	// ���N���X�̏I������
	CObject_UI::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CCrown::Update()
{
	// �ڕW���W��
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), GetPosTarget(), 0.065f));

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
void CCrown::Draw()
{
	// ���N���X�̕`�揈��
	CObject_UI::Draw();
}

//============================================================================
// ����
//============================================================================
CCrown* CCrown::Create()
{
	// �C���X�^���X�𐶐�
	CCrown* pCrown = DBG_NEW CCrown{};

	if (pCrown == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pCrown->SetType(TYPE::NONE);

	// ���N���X�̏����ݒ�
	pCrown->Init();

	// �����_���ȍ��W��ݒ�
	pCrown->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					0.0f });

	// �T�C�Y�̐ݒ�
	pCrown->SetSize({ 0.0f, 0.0f, 0.0f });

	// �e�N�X�`����ݒ�
	pCrown->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::CROWN));

	// UI�I�u�W�F�N�g�Ƀ_�E���L���X�g
	CObject_UI* pObjUI = CUtility::GetInstance()->DownCast<CObject_UI, CObject>(pCrown);

	// �A���t�@�l��ݒ�
	pObjUI->SetAlpha(0.0f);

	return pCrown;
}

//============================================================================
// �o��
//============================================================================
void CCrown::Appear()
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
void CCrown::Disappear()
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