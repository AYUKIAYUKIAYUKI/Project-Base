//============================================================================
// 
// �e [bullet.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "bullet.h"
#include "manager.h"
#include "enemy.h"
#include "effect.h"
#include "explosion.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CBullet::CBullet() : CObject2D::CObject2D()
{
	m_nRemain = 0;		// �g�p����
	m_fFlyAngle = 0;	// ��Ԋp�x
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CBullet::~CBullet()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CBullet::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CBullet::Uninit()
{
	// ���N���X�̏I������
 	CObject2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CBullet::Update()
{
	// �ړ�
	Translation();

	// �����蔻��
	if (CollisionEnemy())
	{
		return;
	}

	// ���Ԍo��
	Progress();

	// ���N���X�̍X�V
	CObject2D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CBullet::Draw()
{
	// ���N���X�̕`�揈��
	CObject2D::Draw();
}

//============================================================================
// ����
//============================================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nRemain, float fFlyAngle)
{
	CBullet* pBullet = new CBullet;

	// �����o���Ă����珉���ݒ�
	if (pBullet != nullptr)
	{
		pBullet->SetType(TYPE::NONE);	// �^�C�v��ݒ�

		pBullet->Init();		// ���N���X�̏����ݒ�
		pBullet->SetPos(pos);	// ���S�ʒu�̐ݒ�
		pBullet->SetSize(size);	// �T�C�Y�̐ݒ�

		pBullet->m_nRemain = nRemain;		// �g�p���Ԃ̐ݒ�
		pBullet->m_fFlyAngle = fFlyAngle;	// ��Ԋp�x�̐ݒ�
	}

	// �e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 pTex = CManager::GetTexture()->GetTex(CTexture::TEX_TYPE::BULLET_000);

	// �e�N�X�`����ݒ�
	pBullet->BindTex(pTex);

	return pBullet;
}

//============================================================================
// �ړ�
//============================================================================
void CBullet::Translation()
{
	// ���S�ʒu�����擾
	D3DXVECTOR3 pos = CObject2D::GetPos();

	// �ݒ肳�ꂽ�p�x�ɔ��ł���
	pos.x += sinf(m_fFlyAngle) * 3.0f;
	pos.y += cosf(m_fFlyAngle) * 3.0f;

	// ���S�ʒu��ݒ�
	CObject2D::SetPos(pos);
}

//============================================================================
// �����蔻��
//============================================================================
bool CBullet::CollisionEnemy()
{
	// �I�u�W�F�N�g�̑������擾
	//int nMaxObj = CObject::GetNumAll();

	for (int nCntObj = 0; nCntObj < 64; nCntObj++)
	{
		// �I�u�W�F�N�g�����擾
		CObject* pObject = CObject::GetObject(nCntObj);

		if (pObject == nullptr)
		{ // �J�E���g�G���[
			continue;
		}

		// �G�Ƃ̓����蔻����s��
		if (pObject->GetType() == CObject::TYPE::ENEMY)
		{
			// �I�u�W�F�N�g�N���X���G�l�~�[�N���X�փ_�E���L���X�g
			CEnemy* pEnemy = (CEnemy*)pObject;

			// �Փ˂�����
			if (CObject2D::GetPos().x + CObject2D::GetSize().x >= pEnemy->GetPos().x - pEnemy->GetSize().x &&
				CObject2D::GetPos().x - CObject2D::GetSize().x <= pEnemy->GetPos().x + pEnemy->GetSize().x &&
				CObject2D::GetPos().y + CObject2D::GetSize().y >= pEnemy->GetPos().y - pEnemy->GetSize().y &&
				CObject2D::GetPos().y - CObject2D::GetSize().y <= pEnemy->GetPos().y + pEnemy->GetSize().y)
			{
				// �����𐶐�
				CExplosion::Create(
					CObject2D::GetPos(),		// ���S�ʒu
					{ 40.0f, 40.0f, 0.0f });	// �T�C�Y

				// ���g��j��
				CObject::Release();

				// �G�l�~�[��j��
				pObject->Release();

				return true;
			}
		}
	}

	return false;
}

//============================================================================
// ���Ԍo��
//============================================================================
void CBullet::Progress()
{
	// �g�p���ԃJ�E���g�_�E��
	m_nRemain--;

	// �G�t�F�N�g����
	CEffect::Create(CObject2D::GetPos(),	// ���S�ʒu
		CObject2D::GetSize());				// �T�C�Y

	// �g�p���Ԃ��Ȃ��Ȃ�Ə���
	if (m_nRemain <= 0)
	{
		// ���g��j��
		CObject::Release();

		// �����𐶐�
		CExplosion::Create(
			CObject2D::GetPos(),		// ���S�ʒu
			{ 40.0f, 40.0f, 0.0f });	// �T�C�Y
	}
}