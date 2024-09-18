//============================================================================
// 
// �o���A�A���J�[�A�w�b�_�t�@�C�� [barrier_anchor.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BARRIER_ANCHOR_H_
#define _BARRIER_ANCHOR_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// �o���A�A���J�[�N���X
//****************************************************
class CBarrier_Anchor : public CObject_X
{
public:

	CBarrier_Anchor();	// �f�t�H���g�R���X�g���N�^
	~CBarrier_Anchor();	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CBarrier_Anchor* Create(D3DXVECTOR3 Pos);	// ����
};

#endif	// _BARRIER_ANCHOR_H_