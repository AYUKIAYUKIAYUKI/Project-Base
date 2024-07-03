//============================================================================
// 
// �n�ʁA�w�b�_�t�@�C�� [field.h]
// Author : ���c����
// 
//============================================================================

#ifndef _FIELD_H_
#define _FIELD_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object3D.h"

//****************************************************
// �t�B�[���h�N���X
//****************************************************
class CField : public CObject3D
{
public:

	CField();			// �R���X�g���N�^
	~CField() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CField* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����
};

#endif // _FIELD_H_