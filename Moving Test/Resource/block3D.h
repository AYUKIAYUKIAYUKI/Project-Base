//============================================================================
// 
// 3D�u���b�N�A�w�b�_�t�@�C�� [block3D.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BLOCK3D_H_
#define _BLOCK3D_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "objectX.h"

//****************************************************
// 3D�u���b�N�N���X
//****************************************************
class CBlock3D : public CObjectX
{
public:

	CBlock3D();				// �R���X�g���N�^
	~CBlock3D() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CBlock3D* Create(D3DXVECTOR3 pos);	// ����
};

#endif // _BLOCK3D_H_