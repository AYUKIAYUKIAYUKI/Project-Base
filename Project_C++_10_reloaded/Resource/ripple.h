//============================================================================
// 
// �g��G�t�F�N�g�A�w�b�_�t�@�C�� [ripple.h]
// Author : ���c����
// 
//============================================================================

#ifndef _RIPPLE_H_
#define _RIPPLE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// �g��G�t�F�N�g�N���X
//****************************************************
class CRipple : public CObject_X
{
public:

	CRipple();	// �R���X�g���N�^
	~CRipple();	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3& GetVelocity();				// �����x���擾
	void SetVelocity(D3DXVECTOR3 velocity);	// �����x��ݒ�

	static CRipple* Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity);	// ����

private:

	D3DXVECTOR3 m_velocity;	// �����x
};

#endif	// _RIPPLE_H_