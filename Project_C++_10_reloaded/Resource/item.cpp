//============================================================================
// 
// �A�C�e�� [item.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "item.h"
#include "manager.h"
#include "physics.h"
#include "block.h"
#include "particle.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CItem::CItem() : CObject_2D(static_cast<int>(LAYER::BACK_MIDDLE))
{
	m_velocity = { 0.0f, 0.0f, 0.0f };	// �����x
	m_posTarget = { 0.0f, 0.0f, 0.0f };	// �ڕW�ʒu
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CItem::~CItem()
{
	// �p�[�e�B�N���𐶐�
	for (int i = 0; i < 10; i++)
	{
		CParticle::Create(
			GetPos(),	// �ʒu
			GetSize(),	// �T�C�Y
			atan2f((float)(rand() % 314), (float)(rand() % 314)) * (rand() % 314));	// ��Ԋp�x
	}
}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CItem::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_2D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CItem::Uninit()
{
	// ���N���X�̏I������
	CObject_2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CItem::Update()
{
	// ���݈ʒu���擾�A�ȍ~���̃R�s�[��ڕW�ʒu�Ƃ��ĕύX�������Ă���
	m_posTarget = GetPos();

	// �ړ�
	Translation();

	// �d�͗���
	CPhysics::GetInstance()->Gravity(m_velocity);

	// �ʒu�𒲐��A���̏����̏I���ɖڕW�ʒu�𔽉f������
	AdjustPos();

	// ���N���X�̍X�V
	CObject_2D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CItem::Draw()
{
	// ���N���X�̕`�揈��
	CObject_2D::Draw();
}

//============================================================================
// ����
//============================================================================
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X�𐶐�
	CItem* pItem = DBG_NEW CItem;

	if (pItem == nullptr)
	{ // �������s
		assert(false);
	}

	pItem->SetType(TYPE::ITEM);	// �^�C�v��ݒ�

	pItem->Init();			// ���N���X�̏����ݒ�
	pItem->SetPos(pos);		// �ʒu�̐ݒ�
	pItem->SetSize(size);	// �T�C�Y�̐ݒ�

	// �e�N�X�`����ݒ�
	pItem->BindTex(CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::ITEM_000));

	return pItem;
}

//============================================================================
// �ړ�
//============================================================================
void CItem::Translation()
{
	// ���̈ړ�
	m_posTarget.x += -0.5f;
}

//============================================================================
// �ʒu����
//============================================================================
void CItem::AdjustPos()
{
	// �����x���ʒu��ϓ�
	m_posTarget += m_velocity;

	// �����蔻��
	Collision();

	// �T�C�Y���擾
	D3DXVECTOR3 fSize = GetSize();

	// ��ʂ̍��E�[�ɓ��B�ł��ꂼ�ꃋ�[�v
	if (m_posTarget.x - fSize.x > SCREEN_WIDTH)
	{
		// �ʒu�����[�֐ݒ�
		m_posTarget.x = 0.0f - fSize.x;
	}
	else if (m_posTarget.x + fSize.x < 0.0f)
	{
		// �ʒu���E�[�֐ݒ�
		m_posTarget.x = SCREEN_WIDTH + fSize.x;
	}

	// ��ʂ̉��[�ɓ��B�ŉ��~����
	if (m_posTarget.y + fSize.y > SCREEN_HEIGHT)
	{
		// �ʒu�����[�ɐݒ�
		m_posTarget.y = SCREEN_HEIGHT - fSize.y;

		// Y�������̉����x�����Z�b�g
		m_velocity.y = 0.0f;
	}

	// �ʒu��ݒ�
	SetPos(m_posTarget);
}

//============================================================================
// �����蔻��
//============================================================================
void CItem::Collision()
{
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// �I�u�W�F�N�g�����擾
			CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{ // ��񂪂Ȃ���΃R���e�B�j���[
				continue;
			}

			if (pObject->GetType() != CObject::TYPE::BLOCK)
			{ // �u���b�N�^�C�v�ȊO�̓R���e�B�j���[
				continue;
			}

			// �I�u�W�F�N�g�N���X���u���b�N�N���X�փ_�E���L���X�g
			CBlock* pBlock = dynamic_cast<CBlock*>(pObject);

			if (pBlock == nullptr)
			{ // �_�E���L���X�g���s
				assert(false);
			}

			// �u���b�N�ƏՓ˂���ꍇ
			if (m_posTarget.x + GetSize().x >= pBlock->GetPos().x - pBlock->GetSize().x &&
				m_posTarget.x - GetSize().x <= pBlock->GetPos().x + pBlock->GetSize().x &&
				m_posTarget.y + GetSize().y >= pBlock->GetPos().y - pBlock->GetSize().y &&
				m_posTarget.y - GetSize().y <= pBlock->GetPos().y + pBlock->GetSize().y)
			{
				// �ߋ��̈ʒu���ǂ��炩�̎������ɏd�Ȃ��Ă������ŏ�������
				if (GetPos().x + GetSize().x > pBlock->GetPos().x - pBlock->GetSize().x &&
					GetPos().x - GetSize().x < pBlock->GetPos().x + pBlock->GetSize().x)
				{
					if (GetPos().y < pBlock->GetPos().y)
					{
						// �ʒu�����̃u���b�N�̏�[�ɐݒ�
						m_posTarget.y = -GetSize().y + (pBlock->GetPos().y - pBlock->GetSize().y);

						// Y�������̉����x�����Z�b�g
						m_velocity.y = 0.0f;
					}
					else if (GetPos().y > pBlock->GetPos().y)
					{
						// �ʒu�����̃u���b�N�̉��[�ɐݒ�
						m_posTarget.y = GetSize().y + (pBlock->GetPos().y + pBlock->GetSize().y);
					}
				}
				else
				{
					if (GetPos().x < pBlock->GetPos().x)
					{
						// �ʒu�����̃u���b�N�̍��[�ɐݒ�
						m_posTarget.x = -GetSize().x + (pBlock->GetPos().x - pBlock->GetSize().x);
					}
					else if (GetPos().x > pBlock->GetPos().x)
					{
						// �ʒu�����̃u���b�N�̉E�[�ɐݒ�
						m_posTarget.x = GetSize().x + (pBlock->GetPos().x + pBlock->GetSize().x);
					}
				}
			}
		}
	}
}