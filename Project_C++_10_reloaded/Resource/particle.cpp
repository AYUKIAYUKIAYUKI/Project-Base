//============================================================================
// 
// �p�[�e�B�N�� [particle.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "particle.h"
#include "manager.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CParticle::CParticle() : CObject_2D(static_cast<int>(LAYER::FRONT_MIDDLE))
{
	m_fFlyAngle = 0.0f;	// ��Ԋp�x
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CParticle::~CParticle()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CParticle::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_2D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CParticle::Uninit()
{
	// ���N���X�̏I������
	CObject_2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CParticle::Update()
{
	// �ړ�
	Translate();

	// ���Ԍo��
	if (!Progress())
	{ // �j������Ă�����X�V�I��
		return;
	}

	// ���N���X�̍X�V
	CObject_2D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CParticle::Draw()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// �A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���N���X�̕`�揈��
	CObject_2D::Draw();

	// �A���t�@�u�����f�B���O���̐ݒ��߂�
	pDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//============================================================================
// ����
//============================================================================
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fFlyAngle)
{
	// �C���X�^���X�𐶐�
	CParticle* pParticle = DBG_NEW CParticle;

	if (pParticle == nullptr)
	{ // �������s
		assert(false);
	}

	pParticle->SetType(TYPE::NONE);	// �^�C�v��ݒ�

	pParticle->Init();			// ���N���X�̏����ݒ�
	pParticle->SetPos(pos);		// �ʒu�̐ݒ�
	pParticle->SetSize(size);	// �T�C�Y�̐ݒ�

	pParticle->m_fFlyAngle = fFlyAngle;	// ��Ԋp�x�̐ݒ�

	// �e�N�X�`����ݒ�
	pParticle->BindTex(CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::EFFECT_000));

	return pParticle;
}

//============================================================================
// �ړ�
//============================================================================
void CParticle::Translate()
{
	// �ʒu�����擾
	D3DXVECTOR3 pos = GetPos();

	// �ݒ肳�ꂽ�p�x�ɔ��ł���
	pos.x += sinf(m_fFlyAngle) * 1.0f;
	pos.y += cosf(m_fFlyAngle) * 1.0f;

	// �ʒu��ݒ�
	SetPos(pos);
}

//============================================================================
// ���Ԍo��
//============================================================================
bool CParticle::Progress()
{
	// �T�C�Y���擾
	D3DXVECTOR3 size = GetSize();

	// �k��
	size.x += -0.25f;
	size.y += -0.25f;

	// ���Ԃ����^�C�~���O�ŏ���
	if (size.x <= 0)
	{
		// ���g��j��
		CObject::Release();

		// �I��
		return false;
	}

	// �T�C�Y��ݒ�
	SetSize(size);

	return true;
}