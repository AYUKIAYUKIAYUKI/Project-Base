//============================================================================
// 
// ��u���b�N�A�w�b�_�t�@�C�� [block_destructible.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BLOCK_DESTRUCRTIBLE_H_
#define _BLOCK_DESTRUCRTIBLE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"
#include "rubble.h"

//****************************************************
// ��u���b�N�N���X
//****************************************************
class CBlockDestructible : public CObject_X
{
public:

	CBlockDestructible();				// �f�t�H���g�R���X�g���N�^
	CBlockDestructible(LAYER priority);	// �v���C�I���e�B�w��R���X�g���N�^
	~CBlockDestructible() override;		// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CBlockDestructible* Create(D3DXVECTOR3 pos);	// ����
};

#endif // _BLOCK_DESTRUCTIBLE_H_