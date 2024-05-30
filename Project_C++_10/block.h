//============================================================================
// 
// �u���b�N�A�w�b�_�t�@�C�� [block.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BLOCK_H_
#define _BLOCK_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object2D.h"

//****************************************************
// �u���b�N�N���X
//****************************************************
class CBlock : public CObject2D
{
public:

	CBlock();				// �R���X�g���N�^
	~CBlock() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CBlock* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����
};

#endif // _BLOCK_H_