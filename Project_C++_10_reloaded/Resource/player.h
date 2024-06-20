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
// ��s�錾
//****************************************************
class CStatePlayer;	// �v���C���[��ԃN���X

//****************************************************
// �v���C���[�N���X
//****************************************************
class CPlayer : public CObject_X
{
public:

	CPlayer();				// �R���X�g���N�^
	~CPlayer() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3* GetVelocity();				// �����x���擾
	void SetVelocity(D3DXVECTOR3 velocity);	// �����x��ݒ�

	float* GetAngleFlying();					// ��s�������擾
	void SetAngleFlying(float fAngleFlying);	// ��s������ݒ�

	D3DXVECTOR3* GetPosTarget();				// �ڕW�ʒu���擾
	void SetPosTarget(D3DXVECTOR3 posTarget);	// �ڕW�ʒu��ݒ�

	D3DXVECTOR3* GetRotTarget();				// �ڕW�������擾
	void SetRotTarget(D3DXVECTOR3 rotTarget);	// �ڕW������ݒ�

	static CPlayer* Create(D3DXVECTOR3 pos);	// ����

private:

	static const float MAX_VELOCITY;	// �����x���
	static const float JUMP_FORCE;		// �W�����v��
	static const float BRAKING_FORCE;	// ������

	CPlayer* GetSelf();		// ���g�̃|�C���^���擾
	void AdjustPos();		// �ʒu�𒲐�
	bool Collision();		// �����蔻��
	void FinishTransform();	// �ϐg����

	CStatePlayer* m_state;		// ���
	D3DXVECTOR3 m_velocity;		// �����x
	float m_fAngleFlying;		// ��s����
	D3DXVECTOR3 m_posTarget;	// �ڕW�ʒu
	D3DXVECTOR3 m_rotTarget;	// �ڕW����

	int m_nTestExplosionCnt;	// ����̓e�X�g�p�ł�
};

//****************************************************
// �v���C���[��ԃN���X
//****************************************************
class CStatePlayer
{
public:

	virtual ~CStatePlayer();	// �f�X�g���N�^

	virtual void Update() = 0;	// �X�V

	void SetInstance(CPlayer* player);	// �v���C���[�̃C���X�^���X��ݒ�

protected:

	CStatePlayer();	// �R���X�g���N�^
	CPlayer* m_player;			// �v���C���[�̃C���X�^���X

private:

	virtual void Control() = 0;		// ����
	virtual void Rotation() = 0;	// ��]
	virtual void Braking() = 0;		// ��������

	bool m_bMetamorphose;		// �ϐg����
	int m_nCntMetamorphose;		// �ϐg����
};

//****************************************************
// �v���C���[�ʏ��ԃN���X
//****************************************************
class CStateDefaultPlayer : public CStatePlayer
{
public:

	~CStateDefaultPlayer() override;	// �f�X�g���N�^

	void Update() override;	// �X�V

private:

	void Control() override;	// ����
	void Rotation() override;	// ��]
	void Braking() override;	// ��������
};

//****************************************************
// �v���C���[��s��ԃN���X
//****************************************************
class CStateFlyingPlayer : public CStatePlayer
{
public:

	~CStateFlyingPlayer() override;	// �f�X�g���N�^

	void Update() override;	// �X�V

private:

	void Control() override;	// ����
	void Rotation() override;	// ��]
	void Braking() override;	// ��������
	void Recoil();				// ����
};

#endif // _PALYER_H_