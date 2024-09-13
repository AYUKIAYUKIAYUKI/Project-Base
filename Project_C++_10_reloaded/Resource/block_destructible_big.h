//============================================================================
// 
// ��ł��u���b�N�A�w�b�_�t�@�C�� [block_destructible_big.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BLOCK_DESTRUCRTIBLE_BIG_H_
#define _BLOCK_DESTRUCRTIBLE_BIG_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// ��ł��u���b�N�N���X
//****************************************************
class CBlockDestructibleBig : public CObject_X
{
public:

	CBlockDestructibleBig();				// �f�t�H���g�R���X�g���N�^
	CBlockDestructibleBig(LAYER priority);	// �v���C�I���e�B�w��R���X�g���N�^
	~CBlockDestructibleBig() override;		// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��
	bool Damage(int nAtk = -1);	// �_���[�W����

	static CBlockDestructibleBig* Create(D3DXVECTOR3 pos);	// ����

private:

	int m_nLife;	// ���C�t
};

#endif // _BLOCK_DESTRUCTIBLE_BIG_H_