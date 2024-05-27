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
CParticle::CParticle() : CObject2D::CObject2D()
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
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CParticle::Uninit()
{
	// ���N���X�̏I������
	CObject2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CParticle::Update()
{
	// �ړ�
	Translate();

	// ���Ԍo��
	Progress();

	// ���N���X�̍X�V
	CObject2D::Update();
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
	CObject2D::Draw();

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
	CParticle* pParticle = new CParticle;

	// �����o���Ă����珉���ݒ�
	if (pParticle != nullptr)
	{
		pParticle->SetType(TYPE::NONE);	// �^�C�v��ݒ�

		pParticle->Init();			// ���N���X�̏����ݒ�
		pParticle->SetPos(pos);		// ���S�ʒu�̐ݒ�
		pParticle->SetSize(size);	// �T�C�Y�̐ݒ�

		pParticle->m_fFlyAngle = fFlyAngle;	// ��Ԋp�x�̐ݒ�
	}

	// �e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 pTex = CManager::GetTexture()->GetTex(CTexture::TEX_TYPE::EFFECT_000);

	// �e�N�X�`����ݒ�
	pParticle->BindTex(pTex);

	return pParticle;
}

//============================================================================
// �ړ�
//============================================================================
void CParticle::Translate()
{
	// ���S�ʒu�����擾
	D3DXVECTOR3 pos = CObject2D::GetPos();

	// �ݒ肳�ꂽ�p�x�ɔ��ł���
	pos.x += sinf(m_fFlyAngle) * 1.0f;
	pos.y += cosf(m_fFlyAngle) * 1.0f;

	// ���S�ʒu��ݒ�
	CObject2D::SetPos(pos);
}

//============================================================================
// ���Ԍo��
//============================================================================
void CParticle::Progress()
{
	// �T�C�Y�����擾
	D3DXVECTOR3 size = CObject2D::GetSize();

	// �k��
	size.x += -0.25f;
	size.y += -0.25f;

	// ���Ԃ����^�C�~���O�ŏ���
	if (size.x <= 0)
	{
		CObject::Release();	// ���g��j��
	}

	// �T�C�Y����ݒ�
	CObject2D::SetSize(size);
}