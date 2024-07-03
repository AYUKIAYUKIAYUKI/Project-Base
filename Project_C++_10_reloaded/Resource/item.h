//============================================================================
// 
// �A�C�e���A�w�b�_�t�@�C�� [item.h]
// Author : ���c����
// 
//============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"

//****************************************************
// �A�C�e���N���X
//****************************************************
class CItem : public CObject_2D
{
public:

	CItem();			// �R���X�g���N�^
	~CItem() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����

private:

	void Translation();	// �ړ�
	void AdjustPos();	// �ʒu�𒲐�
	void Collision();	// �����蔻��

	D3DXVECTOR3 m_velocity;		// �����x
	D3DXVECTOR3 m_posTarget;	// �ڕW�ʒu
};

#endif // _ITEM_H_