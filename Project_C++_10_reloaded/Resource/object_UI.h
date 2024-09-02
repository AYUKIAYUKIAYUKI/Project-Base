//============================================================================
// 
// UI�I�u�W�F�N�g�Ǘ��A�w�b�_�t�@�C�� [object_UI.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBJECT_UI_H_
#define _OBJECT_UI_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.h"
#include "object_2D.h"

//****************************************************
// UI�I�u�W�F�N�g�N���X
//****************************************************
class CObject_UI : public CObject_2D
{
public:

	CObject_UI();												// �f�t�H���g�R���X�g���N�^
	CObject_UI(int nPriority = static_cast<int>(LAYER::UI));	// �`��D��x�w��R���X�g���N�^
	~CObject_UI() override;										// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	void SetAppear();		// �o���\��
	void SetDisappear();	// ���ŗ\��

	D3DXVECTOR3 GetPosTarget();					// �ڕW���W���擾
	void SetPosTarget(D3DXVECTOR3 posTarget);	// �ڕW���W��ݒ�

	D3DXVECTOR3 GetRotTarget();					// �ڕW�������擾
	void SetRotTarget(D3DXVECTOR3 rotTarget);	// �ڕW������ݒ�

	D3DXVECTOR3 GetSizeTarget();				// �ڕW�T�C�Y���擾
	void SetSizeTarget(D3DXVECTOR3 sizeTarget);	// �ڕW�T�C�Y��ݒ�

	D3DXCOLOR GetColTarget();			// �ڕW�F
	void SetColTarget(D3DXCOLOR col);	// �ڕW�F

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

#endif // _OBJECT_UI_H_