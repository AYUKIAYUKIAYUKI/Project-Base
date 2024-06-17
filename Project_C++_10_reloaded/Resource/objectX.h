//============================================================================
// 
// X�I�u�W�F�N�g�A�w�b�_�t�@�C�� [object3D.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBJECTX_H_
#define _OBJECTX_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.h"
#include "main.h"

//****************************************************
// X�I�u�W�F�N�g�N���X
//****************************************************
class CObjectX : public CObject
{
public:

	CObjectX(int nPriority = static_cast<int>(LAYER::FRONT));	// �R���X�g���N�^
	~CObjectX() override;										// �f�X�g���N�^

	HRESULT Init() override;		// �����ݒ�
	void Uninit() override;			// �I������
	void Update() override;			// �X�V����
	void Draw() override;			// �`�揈��

	void BindModel(MODEL* pModel);	// ���f������

	D3DXVECTOR3 GetPos();			// �ʒu�擾
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�

	D3DXVECTOR3 GetRot();			// �����擾
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�

	D3DXVECTOR3 GetSize();			// �T�C�Y�擾
	void SetSize(D3DXVECTOR3 size);	// �T�C�Y�ݒ�

	virtual CObjectX* Create();	// ����

private:

	void SetMtxWorld();	// ���[���h�s��ݒ�

	MODEL* m_pModel;		// ���f�����
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_size;		// �T�C�Y
	D3DXMATRIX m_mtxWorld;	// ���[���h�s��
};

#endif // _OBJECTX_H_