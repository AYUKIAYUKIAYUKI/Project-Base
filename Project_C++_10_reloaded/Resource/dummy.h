//============================================================================
// 
// �_�~�[�A�w�b�_�t�@�C�� [dummy.h]
// Author : ���c����
// 
//============================================================================

#ifndef _DUMMY_H_
#define _DUMMY_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// �_�~�[�N���X
//****************************************************
class CDummy : public CObject_X
{
public:

	CDummy();				// �R���X�g���N�^
	~CDummy() override;		// �f�X�g���N�^

	HRESULT Init() override;		// �����ݒ�
	void Uninit() override;			// �I������
	void Update() override;			// �X�V����
	void Draw() override;			// �`�揈��
	void Control();					// ����
	void ChangeModel(int nPattern);	// ���f����ύX

	static CDummy* Create();	// ����

private:

	void Translate();	// �ړ�
};

#endif // _DUMMY_H_