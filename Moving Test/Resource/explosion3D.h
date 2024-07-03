//============================================================================
// 
// 3D�����A�w�b�_�t�@�C�� [explosion3D.h]
// Author : ���c����
// 
//============================================================================

#ifndef _EXPLOSION3D_H_
#define _EXPLOSION3D_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "objectBillboard.h"

//****************************************************
// 3D�G�N�X�v���[�W�����N���X
//****************************************************
class CExplosion3D : public CObjectBillboard
{
public:

	CExplosion3D();			// �R���X�g���N�^
	~CExplosion3D() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CExplosion3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����

private:

	bool Animation();	// �A�j���[�V����

	int m_nCntTexChange;	// �e�N�X�`���ύX�Ǘ�
};

#endif // _EXPLOSION3D_H_