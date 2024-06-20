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
#include "object_X.h"

//****************************************************
// �v���C���[�N���X
//****************************************************
class CPlayer : public CObject_X
{
public:

	//****************************************************
	// �v���C���[�̏��
	//****************************************************
	enum class STATE
	{
		NONE = 0,	// ����
		DEFAULT,	// �ʏ�
		CHANGING,	// �ϐg�J�n
		FLYING,		// ��s
		RETURNING,	// �ϐg����
		MAX,
	};

	CPlayer();				// �R���X�g���N�^
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

	void Walking();			// ���s
	void Rotation();		// ��]
	void Braking();			// ��������
	void Flying();			// ��s
	void Rolling();			// ����
	void AirResistance();	// ��C��R
	void AdjustPos();		// �ʒu�𒲐�
	bool Collision();		// �����蔻��
	void FinishTransform();	// �ϐg����
	void Recoil();			// ����

	STATE m_state;				// ���
	bool m_bMetamorphose;		// �ϐg����
	int m_nCntMetamorphose;		// �ϐg����
	D3DXVECTOR3 m_velocity;		// �����x
	float m_fAngleFlying;		// ��s����
	D3DXVECTOR3 m_posTarget;	// �ڕW�ʒu
	D3DXVECTOR3 m_rotTarget;	// �ڕW����

	int m_nTestExplosionCnt;	// ����̓e�X�g�p�ł�
};

#endif // _PALYER_H_