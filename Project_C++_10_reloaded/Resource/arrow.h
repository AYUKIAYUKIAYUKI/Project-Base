//============================================================================
// 
// ���A�w�b�_�t�@�C�� [arrow.h]
// Author : ���c����
// 
//============================================================================

#ifndef _ARROW_H_
#define _ARROW_H_// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_3D.h"

//****************************************************
// ���N���X
//****************************************************
class CArrow : public CObject_3D
{
public:

	CArrow();			// �f�t�H���g�R���X�g���N�^
	~CArrow() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	void SetAppear();		// �o���ݒ�
	void SetDisappear();	// ���Őݒ�

	D3DXVECTOR3 GetPosTarget();					// �ڕW���W���擾
	void SetPosTarget(D3DXVECTOR3 posTarget);	// �ڕW���W��ݒ�

	D3DXVECTOR3 GetRotTarget();					// �ڕW�������擾
	void SetRotTarget(D3DXVECTOR3 rotTarget);	// �ڕW������ݒ�

	D3DXVECTOR3 GetSizeTarget();				// �ڕW�T�C�Y���擾
	void SetSizeTarget(D3DXVECTOR3 sizeTarget);	// �ڕW�T�C�Y��ݒ�

	static CArrow* Create();	// ����

private:

	virtual void Appear();		// �o��
	virtual void Disappear();	// ����

	bool m_bAppear;				// �o���t���O
	bool m_bDisappear;			// ���Ńt���O
	D3DXVECTOR3 m_posTarget;	// �ڕW���W
	D3DXVECTOR3 m_rotTarget;	// �ڕW����
	D3DXVECTOR3 m_sizeTarget;	// �ڕW�T�C�Y
	D3DXCOLOR m_colTarget;		// �ڕW�F
};

#endif // _ARROW_H_