//============================================================================
// 
// �v���C���[�A�w�b�_�t�@�C�� [player.h]
// Author : ���c����
// 
//============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "objectX.h"

//****************************************************
// �v���C���[�N���X
//****************************************************
class CPlayer : public CObjectX
{
public:

	CPlayer();			// �R���X�g���N�^
	~CPlayer() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CPlayer* Create(D3DXVECTOR3 pos);	// ����

private:

	static const float MAX_VELOCITY;	// �����x���
	static const float JUMP_FORCE;		// �W�����v��
	static const float BRAKING_FORCE;	// ������

	void Control();		// ����
	void Rotation();	// ��]
	void Braking();		// ��������
	void GravityFall();	// �d�͉���
	void AdjustPos();	// �ʒu�𒲐�
	void Collision();	// �����蔻��

	int m_nLeftNumJump;			// �W�����v�\��
	D3DXVECTOR3 m_velocity;		// �����x
	D3DXVECTOR3 m_posTarget;	// �ڕW�ʒu
	D3DXVECTOR3 m_rotTarget;	// �ڕW����

	int m_nTestExplosionCnt;	// ����̓e�X�g�p�ł�
};

#endif // _PALYER_H_