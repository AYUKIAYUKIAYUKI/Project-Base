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

	CDummy(int& nPattern);	// �R���X�g���N�^
	~CDummy();				// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CDummy* Create(D3DXVECTOR3 pos, int& nPattern);	// ����
	static CDummy* DownCast(CObject* pObject);				// �_�E���L���X�g

private:

	void Control();			// ����
	void CheckPattern();	// �_�~�[�̎�ނ��m�F

	int& m_nPatternRef;	// �z�u���̎�ނ��Q��
};

#endif // _DUMMY_H_