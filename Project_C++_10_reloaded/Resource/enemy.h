//============================================================================
// 
// �G�l�~�[�A�w�b�_�t�@�C�� [enemy.h]
// Author : ���c����
// 
//============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"

//****************************************************
// �G�l�~�[�N���X
//****************************************************
class CEnemy : public CObject_2D
{
public:

	CEnemy();			// �R���X�g���N�^
	~CEnemy() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����

	D3DXVECTOR3 GetVelocity() { return m_velocity; }

private:

	static const float MAX_VELOCITY;	// �����x���
	static const float JUMP_FORCE;		// �W�����v��
	static const float BRAKING_FORCE;	// ������

	void Translation();	// �ړ�
	void Braking();		// ��������
	void AdjustPos();	// �ʒu����

	D3DXVECTOR3 m_velocity;		// �����x
	D3DXVECTOR3 m_posTarget;	// �ڕW�ʒu
	D3DXVECTOR3 m_rotTarget;	// �ڕW����
};

#endif // _ENEMY_H_