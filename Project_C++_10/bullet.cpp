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
#include "score.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CBullet::CBullet() : CObject2D(LAYER::BACK_MIDDLE)
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
	if (!CollisionEnemy())
	{ // �j������Ă�����X�V�I��
		return;
	}

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
	LPDIRECT3DTEXTURE9 pTex = CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::BULLET_000);

	// �e�N�X�`����ݒ�
	pBullet->BindTex(pTex);

	return pBullet;
}

//============================================================================
// �ړ�
//============================================================================
void CBullet::Translation()
{
	// �ʒu���擾
	D3DXVECTOR3 pos = CObject2D::GetPos();

	// �ݒ肳�ꂽ�p�x�ɔ��ł���
	pos.x += sinf(m_fFlyAngle) * 3.0f;
	pos.y += cosf(m_fFlyAngle) * 3.0f;

	// �ʒu��ݒ�
	CObject2D::SetPos(pos);
}

//============================================================================
// �����蔻��
//============================================================================
bool CBullet::CollisionEnemy()
{
	for (int nCntPriority = 0; nCntPriority < MAX_LAYER; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// �I�u�W�F�N�g�����擾
			CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{ // ��񂪂Ȃ���΃R���e�B�j���[
				continue;
			}

			if (pObject->GetType() != CObject::TYPE::ENEMY)
			{ // �G�l�~�[�^�C�v�ȊO�̓R���e�B�j���[
				continue;
			}

			// �I�u�W�F�N�g�N���X���G�l�~�[�N���X�փ_�E���L���X�g
			CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObject);

			if (pEnemy == nullptr)
			{ // �_�E���L���X�g���s
				assert(false);
			}

			// �G�ƏՓ˂�����
			if (CObject2D::GetPos().x + CObject2D::GetSize().x >= pEnemy->GetPos().x - pEnemy->GetSize().x &&
				CObject2D::GetPos().x - CObject2D::GetSize().x <= pEnemy->GetPos().x + pEnemy->GetSize().x &&
				CObject2D::GetPos().y + CObject2D::GetSize().y >= pEnemy->GetPos().y - pEnemy->GetSize().y &&
				CObject2D::GetPos().y - CObject2D::GetSize().y <= pEnemy->GetPos().y + pEnemy->GetSize().y)
			{
				// �X�R�A�C���X�^���X���擾
				CObject* pFindObject = FindScoreInstance();

				// �I�u�W�F�N�g�N���X���G�l�~�[�N���X�փ_�E���L���X�g
				CScore* pScore = dynamic_cast<CScore*>(pFindObject);

				if (pScore == nullptr)
				{ // �_�E���L���X�g���s
					assert(false);
				}

				// �X�R�A�����Z
				pScore->SetScore(pScore->GetScore() + 123456);

				// �����𐶐�
				CExplosion::Create(
					CObject2D::GetPos(),		// ���S�ʒu
					{ 40.0f, 40.0f, 0.0f });	// �T�C�Y

				// ���g��j��
				CObject::Release();

				// �G�l�~�[��j��
				pObject->Release();

				// �I��
				return false;
			}
		}
	}

	return true;
}

//============================================================================
// ���Ԍo��
//============================================================================
bool CBullet::Progress()
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

		// �I��
		return false;
	}

	return true;
}