//============================================================================
// 
// 3D�I�u�W�F�N�g�Ǘ��A�w�b�_�t�@�C�� [object3D.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object.h"

//****************************************************
// 3D�I�u�W�F�N�g�N���X
//****************************************************
class CObject3D : public CObject
{
public:

	CObject3D(int nPriority = static_cast<int>(LAYER::FRONT));	// �R���X�g���N�^
	~CObject3D() override;										// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	void BindTex(LPDIRECT3DTEXTURE9 pTex);	// �e�N�X�`������

	D3DXVECTOR3 GetPos();			// ���S�ʒu�擾
	void SetPos(D3DXVECTOR3 pos);	// ���S�ʒu�ݒ�

	D3DXVECTOR3 GetRot();			// �����擾
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�

	D3DXVECTOR3 GetSize();			// �T�C�Y�擾
	void SetSize(D3DXVECTOR3 size);	// �T�C�Y�ݒ�

	float GetLength();	// �W�J�p�Ίp���擾

	static CObject3D* Create();	// ����

private:

	void SetMtxWorld();	// ���[���h�s��ݒ�

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTex;			// �e�N�X�`���̃|�C���^

	D3DXVECTOR3 m_pos;		// ���S�ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_size;		// �T�C�Y
	float m_fLength;		// �W�J�p�Ίp��
	float m_fAngle;			// �Ίp���p�p�x
	D3DXMATRIX m_mtxWorld;	// ���[���h�s��
};

#endif // _OBJECT3D_H_