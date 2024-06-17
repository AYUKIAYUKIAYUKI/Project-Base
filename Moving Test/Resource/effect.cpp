//============================================================================
// 
// �G�t�F�N�g [effect.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "effect.h"
#include "manager.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CEffect::CEffect() : CObject2D(static_cast<int>(LAYER::BACK_MIDDLE))
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CEffect::~CEffect()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CEffect::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CEffect::Uninit()
{
	// ���N���X�̏I������
	CObject2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CEffect::Update()
{
	// ���Ԍo��
	if (!Progress())
	{ // �j������Ă�����X�V�I��
		return;
	}

	// ���N���X�̍X�V
	CObject2D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CEffect::Draw()
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
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X�𐶐�
	CEffect* pEffect = DBG_NEW CEffect;

	if (pEffect == nullptr)
	{ // �������s
		assert(false);
	}

	pEffect->SetType(TYPE::NONE);	// �^�C�v��ݒ�

	pEffect->Init();		// ���N���X�̏����ݒ�
	pEffect->SetPos(pos);	// ���S�ʒu�̐ݒ�
	pEffect->SetSize(size);	// �T�C�Y�̐ݒ�

	// �e�N�X�`����ݒ�
	pEffect->BindTex(CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::EFFECT_000));

	return pEffect;
}

//============================================================================
// ���Ԍo��
//============================================================================
bool CEffect::Progress()
{
	// �T�C�Y���擾
	D3DXVECTOR3 size = GetSize();

	// �k��
	size.x += size.x * -0.05f;
	size.y += size.y * -0.05f;

	// �����Ȃ��Ȃ����^�C�~���O�ŏ���
	if (size.x <= 0.25f)
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