//============================================================================
// 
// ���� [explosion.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "explosion.h"

// �e�N�X�`���擾�p
#include "texture_manager.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CExplosion::CExplosion() :
	CObject_billboard{ static_cast<int>(LAYER::FRONT_MIDDLE) },	// ���N���X�̃R���X�g���N�^
	m_nCntTexChange{ 0 }										// �e�N�X�`���ύX�Ǘ�
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CExplosion::~CExplosion()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CExplosion::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_billboard::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CExplosion::Uninit()
{
	// ���N���X�̏I������
	CObject_billboard::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CExplosion::Update()
{
	// �A�j���[�V����
	if (!Animation())
	{ // �j������Ă�����X�V�I��
		return;
	}

	// ���N���X�̍X�V
	CObject_billboard::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CExplosion::Draw()
{
	// ���N���X�̕`�揈��
	CObject_billboard::Draw();
}

//============================================================================
// ����
//============================================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X�𐶐�
	CExplosion* pExplosion = DBG_NEW CExplosion;

	if (pExplosion == nullptr)
	{ // �������s
		assert(false);
	}

	pExplosion->SetType(TYPE::NONE);	// �^�C�v��ݒ�

	pExplosion->Init();			// ���N���X�̏����ݒ�
	pExplosion->SetPos(pos);	// �ʒu�̐ݒ�
	pExplosion->SetSize(size);	// �T�C�Y�̐ݒ�

	pExplosion->SetTexWidth(1.0f / 8.0f);	// ���e�N�X�`��������
	pExplosion->SetTexHeight(1.0f);			// �c�e�N�X�`�����c��

	// �e�N�X�`����ݒ�
	pExplosion->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::EXPLOSION_000));

	return pExplosion;
}

//============================================================================
// �A�j���[�V����
//============================================================================
bool CExplosion::Animation()
{
	// �e�N�X�`���ύX�Ǘ��J�E���g�A�b�v
	m_nCntTexChange++;

	if (m_nCntTexChange >= 5)
	{
		// ���e�N�X�`����ޏ��擾
		int nTexPatternU = GetNowPatternU();

		// ���e�N�X�`����ޕύX
		nTexPatternU++;

		if (nTexPatternU >= 8)
		{
			// ���g��j��
			CObject::SetRelease();

			// �I��
			return false;
		}

		// ���e�N�X�`����ޏ��ݒ�
		SetNowPatternU(nTexPatternU);

		// �ύX�Ǘ��J�E���g�����Z�b�g
		m_nCntTexChange = 0;
	}

	return true;
}