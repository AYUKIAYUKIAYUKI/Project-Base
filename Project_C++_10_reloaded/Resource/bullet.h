//============================================================================
// 
// �e�A�w�b�_�t�@�C�� [bullet.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BULLET_H_
#define _BULLET_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_billboard.h"

//****************************************************
// �e�N���X
//****************************************************
class CBullet : public CObject_billboard
{
public:

	CBullet();				// �f�t�H���g�R���X�g���N�^
	CBullet(int nDuration);	// �����ݒ�R���X�g���N�^
	~CBullet() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����

private:

	void Translate();	// �ړ�
	bool Collision();	// �����蔻��

	D3DXVECTOR3 m_posTarget;	// �ڕW���W
	D3DXVECTOR3 m_velocity;		// �����x
	int m_nDuration;			// ����
};

#endif // _BULLET_H_