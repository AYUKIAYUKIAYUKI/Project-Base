//============================================================================
// 
// ���� [number.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "number.h"
#include "utility.h"

// �e�N�X�`���ݒ�p
#include "texture_manager.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CNumber::CNumber() : 
	CObject_UI{ static_cast<int>(LAYER::UI) },	// �`��D��x�̎w��
	m_nNum{ 0 }									// �����̊��蓖��
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CNumber::~CNumber()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CNumber::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CNumber::Uninit()
{
	// ���N���X�̏I������
	CObject_UI::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CNumber::Update()
{
	// �A�j���[�V����
	Animation();

	// ���N���X�̍X�V
	CObject_UI::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CNumber::Draw()
{
	// ���N���X�̕`�揈��
	CObject_UI::Draw();
}

//============================================================================
// ����
//============================================================================
CNumber* CNumber::Create()
{
	// �C���X�^���X�𐶐�
	CNumber* pNumber = DBG_NEW CNumber;

	if (pNumber == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pNumber->SetType(TYPE::NONE);

	// �����ݒ�
	pNumber->Init();

	// �����_���ȍ��W
	D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 5.0f, (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 5.0f, 0.0f };

	// �ʒu�̐ݒ�
	pNumber->SetPos(pos);

	// �T�C�Y�̐ݒ�
	//pNumber->SetSize({ 0.0f, 0.0f, 0.0f });

	// �A���t�@�l�̐ݒ�
	pNumber->SetAlpha(0.0f);

	// ���e�N�X�`��������
	pNumber->SetTexWidth(0.1f);

	// �c�e�N�X�`�����c��
	pNumber->SetTexHeight(1.0f);

	// �e�N�X�`����ݒ�
	pNumber->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::NUMBER_00));

	return pNumber;
}

//============================================================================
// ����
//============================================================================
CNumber* CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X�𐶐�
	CNumber* pNumber = DBG_NEW CNumber;

	if (pNumber == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pNumber->SetType(TYPE::NONE);

	// �����ݒ�
	pNumber->Init();

	// �ʒu�̐ݒ�
	pNumber->SetPos(pos);

	// �T�C�Y�̐ݒ�
	pNumber->SetSize(size);

	// ���e�N�X�`��������
	pNumber->SetTexWidth(0.1f);

	// �c�e�N�X�`�����c��
	pNumber->SetTexHeight(1.0f);

	// �e�N�X�`����ݒ�
	pNumber->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::NUMBER_00));

	return pNumber;
}

//============================================================================
// ������ݒ�
//============================================================================
void CNumber::SetNumber(int nNum)
{
	m_nNum = nNum;
}

//============================================================================
// �A�j���[�V����
//============================================================================
void CNumber::Animation()
{
	// ���e�N�X�`����ޏ��擾
	int nTexPatternU = GetNowPatternU();

	// ���e�N�X�`����ނ����蓖��
	nTexPatternU = m_nNum;

	// ���e�N�X�`����ޏ��ݒ�
	SetNowPatternU(nTexPatternU);
}