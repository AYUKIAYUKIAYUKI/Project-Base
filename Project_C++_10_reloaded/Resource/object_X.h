//============================================================================
// 
// X�I�u�W�F�N�g�A�w�b�_�t�@�C�� [object_X.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBJECT_X_H_
#define _OBJECT_X_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "model_X.h"
#include "object.h"

//****************************************************
// X�I�u�W�F�N�g�N���X
//****************************************************
class CObject_X : public CObject
{
public:

	CObject_X(int nPriority = static_cast<int>(LAYER::FRONT));	// �R���X�g���N�^
	~CObject_X() override;										// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	void BindModel(CModel_X::MODEL* pModel);	// ���f������

	D3DXVECTOR3 GetPos();			// �ʒu�擾
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�

	D3DXVECTOR3 GetRot();			// �����擾
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�

	D3DXVECTOR3 GetSize();			// �T�C�Y�擾
	void SetSize(D3DXVECTOR3 size);	// �T�C�Y�ݒ�

	virtual CObject_X* Create();	// ����

private:

	void SetMtxWorld();	// ���[���h�s��ݒ�

	CModel_X::MODEL* m_pModel;	// ���f�����
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_size;			// �T�C�Y
	D3DXMATRIX m_mtxWorld;		// ���[���h�s��
};

#endif // _OBJECT_X_H_