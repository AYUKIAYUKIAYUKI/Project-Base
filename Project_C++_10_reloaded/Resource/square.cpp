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
	CObject_2D{ static_cast<int>(LAYER::UI) }
{

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
		// 2D�I�u�W�F�N�g�Ƀ_�E���L���X�g
		CObject_2D* pObj2D = CUtility::GetInstance()->DownCast<CObject_2D, CObject>(pObj[nSquareCnt]);

		// ���W�𔽉f�����Ă���
		pObj2D->SetPos({ (SCREEN_WIDTH * 0.5f) + (150.0f * nSquareCnt) - (nSelect * 150.0f), SCREEN_HEIGHT * 0.5f, 0.0f });

		// ���֐i�߂�
		nSquareCnt++;
	}
}

//============================================================================
// �}�X�ڂ���ׂ�
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
		// 2D�I�u�W�F�N�g�Ƀ_�E���L���X�g
		CObject_2D* pObj2D = CUtility::GetInstance()->DownCast<CObject_2D, CObject>(pObj[nSquareCnt]);

		// ���W�𔽉f�����Ă���
		pObj2D->SetPos({ (SCREEN_WIDTH * 0.5f) + (150.0f * nSquareCnt) - (nSelect * 150.0f), SCREEN_HEIGHT * 0.5f, 0.0f });

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

	// �ʒu�̐ݒ�
	pSquare->SetPos(pos);

	// �T�C�Y�̐ݒ�
	pSquare->SetSize({ 50.0f, 50.0f, 0.0f });

	// �e�N�X�`����ݒ�
	pSquare->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::SQUARE_00));

	return pSquare;
}