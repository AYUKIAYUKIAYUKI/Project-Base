//============================================================================
// 
// �v���C���[3D�A�w�b�_�t�@�C�� [player3D.h]
// Author : ���c����
// 
//============================================================================

#ifndef _PLAYER3D_H_
#define _PLAYER3D_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "objectX.h"

//****************************************************
// �v���C���[3D�N���X
//****************************************************
class CPlayer3D : public CObjectX
{
public:

	CPlayer3D();			// �R���X�g���N�^
	~CPlayer3D() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CPlayer3D* Create(D3DXVECTOR3 pos);	// ����

private:

	static const float MAX_VELOCITY;	// �����x���
	static const float BRAKING_FORCE;	// ������

	void Control();			// ����
	void Rotation();		// ��]
	void Braking();			// ��������
	void AdjustPos();		// �ʒu�𒲐�

	D3DXVECTOR3 m_velocity;		// �����x
	D3DXVECTOR3 m_posTarget;	// �ڕW�ʒu
	D3DXVECTOR3 m_rotTarget;	// �ڕW����
};

#endif // _PALYER3D_H_