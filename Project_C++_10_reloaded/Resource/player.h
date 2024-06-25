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
// �O���錾
//****************************************************
class CPlayerStateManager;	// �v���C���[��ԊǗ��N���X

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

	CPlayerStateManager* m_pStateManager;	// ��ԊǗ�

	bool m_bMetamorphose;		// �ϐg����
	int m_nCntMetamorphose;		// �ϐg����
	D3DXVECTOR3 m_velocity;		// �����x
	float m_fAngleFlying;		// ��s����
	D3DXVECTOR3 m_posTarget;	// �ڕW�ʒu
	D3DXVECTOR3 m_rotTarget;	// �ڕW����

	int m_nTestExplosionCnt;	// ����̓e�X�g�p�ł�
};

//****************************************************
// �v���C���[��ԃN���X
//****************************************************
class CPlayerState
{
public:

	//****************************************************
	// ��Ԃ�����
	//****************************************************
	enum class STATE
	{
		DEFAULT = 0,	// �ʏ�
		FLYING,			// ��s
		MAX,
	};

	CPlayerState();				// �R���X�g���N�^
	virtual ~CPlayerState();	// �f�X�g���N�^

	virtual void Enter() = 0;	// �J�n
	virtual void Update() = 0;	// �X�V
	virtual void Exit() = 0;	// �I��

private:

	virtual void Control() = 0;		// ����
	virtual void Rotation() = 0;	// ��]
	virtual void Braking() = 0;		// ��������
};

//****************************************************
// �v���C���[�ʏ��ԃN���X
//****************************************************
class CPlayerStateDefault : public CPlayerState
{
public:

	CPlayerStateDefault();				// �R���X�g���N�^
	~CPlayerStateDefault() override;	// �f�X�g���N�^

	void Enter() override;	// �J�n
	void Update() override;	// �X�V
	void Exit() override;	// �I��

private:

	void Control() override;	// ����
	void Rotation() override;	// ��]
	void Braking() override;	// ��������
};

//****************************************************
// �v���C���[��s��ԃN���X
//****************************************************
class CPlayerStateFlying : public CPlayerState
{
public:

	CPlayerStateFlying();			// �R���X�g���N�^
	~CPlayerStateFlying() override;	// �f�X�g���N�^

	void Enter() override;	// �J�n
	void Update() override;	// �X�V
	void Exit() override;	// �I��

private:

	void Control() override;	// ����
	void Rotation() override;	// ��]
	void Braking() override;	// ��������
};

//****************************************************
// �v���C���[��ԊǗ��N���X
//****************************************************
class CPlayerStateManager
{
public:

	CPlayerStateManager();	// �R���X�g���N�^
	~CPlayerStateManager();	// �f�X�g���N�^

	void Init();	// �����ݒ�
	void Uninit();	// �I������

	void ChangeState(CPlayerState::STATE state);	// ��Ԃ�ύX

	CPlayerState* GetState();	// ��Ԃ��擾

private:
	
	CPlayerState* Create(CPlayerState::STATE state);	// �V���ȏ�Ԃ𐶐�

	CPlayerState* m_pState;	// ��Ԃ�ێ�
};

#endif // _PALYER_H_