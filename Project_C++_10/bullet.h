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
#include "object2D.h"

//****************************************************
// �o���b�g�N���X
//****************************************************
class CBullet : public CObject2D
{
public:

	CBullet();				// �R���X�g���N�^
	~CBullet() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nRemain, float fFlyAngle);	// ����

private:

	void Translation();	// �ړ�
	void Progress();	// ���Ԍo��

	int m_nRemain;		// �g�p����
	float m_fFlyAngle;	// ��Ԋp�x
};

#endif // _PALYER_H_