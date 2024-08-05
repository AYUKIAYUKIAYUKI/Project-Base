//============================================================================
// 
// ���G�t�F�N�g�A�w�b�_�t�@�C�� [star.h]
// Author : ���c����
// 
//============================================================================

#ifndef _STAR_H_
#define _STAR_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// ���G�t�F�N�g�N���X
//****************************************************
class CStar : public CObject_X
{
public:

	CStar();	// �R���X�g���N�^
	~CStar();	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3& GetVelocity();				// �����x���擾
	void SetVelocity(D3DXVECTOR3 velocity);	// �����x��ݒ�

	static CStar* Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity);	// ����

private:

	D3DXVECTOR3 m_velocity;	// �����x
};

#endif	// _STAR_H_