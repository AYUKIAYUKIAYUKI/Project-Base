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

	static const float MAX_VELOCITY;	// �����x���
	static const float JUMP_FORCE;		// �W�����v��
	static const float BRAKING_FORCE;	// ������

	CPlayer();				// �R���X�g���N�^
	~CPlayer() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3 GetVelocity();				// �����x���擾
	void SetVelocity(D3DXVECTOR3 velocity);	// �����x��ݒ�

	float GetAngleFlying();						// ��s�������擾
	void SetAngleFlying(float fAngleFlying);	// ��s������ݒ�

	D3DXVECTOR3 GetPosTarget();					// �ڕW�ʒu���擾
	void SetPosTarget(D3DXVECTOR3 posTarget);	// �ڕW�ʒu��ݒ�

	D3DXVECTOR3 GetRotTarget();					// �ڕW�������擾
	void SetRotTarget(D3DXVECTOR3 rotTarget);	// �ڕW������ݒ�

	CPlayerStateManager* GetStateManager();	// ��ԊǗ��擾

	static CPlayer* Create(D3DXVECTOR3 pos);	// ����

	bool AdjustPos();	// �ʒu�𒲐�

private:

	bool Collision();	// �����蔻��

	CPlayerStateManager* m_pStateManager;	// ��ԊǗ�

	D3DXVECTOR3 m_velocity;		// �����x
	float m_fAngleFlying;		// ��s����
	D3DXVECTOR3 m_posTarget;	// �ڕW�ʒu
	D3DXVECTOR3 m_rotTarget;	// �ڕW����
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
		BEGINNING,		// �ϐg�J�n
		FLYING,			// ��s
		STOPPING,		// �ϐg��~
		MAX,
	};

	CPlayerState();				// �R���X�g���N�^
	virtual ~CPlayerState();	// �f�X�g���N�^

	virtual void Init();		// �����ݒ�
	virtual void Update();		// �X�V
	virtual void Exit() = 0;	// �I��

	void SetPlayerInstance(CPlayer* player);	// �v���C���[���̐ݒ�

protected:

	CPlayer* m_pPlayer;	// �v���C���[�C���X�^���X�ւ̃|�C���^
};

//****************************************************
// �v���C���[�ʏ��ԃN���X
//****************************************************
class CPlayerStateDefault : public CPlayerState
{
public:

	CPlayerStateDefault();				// �R���X�g���N�^
	~CPlayerStateDefault() override;	// �f�X�g���N�^

	void Init() override;	// �����ݒ�
	void Update() override;	// �X�V
	void Exit() override;	// �I��

private:

	bool Walk();		// ����
	void Rotation();	// ��]
	void Braking();		// ��������
};

//****************************************************
// �v���C���[�ϐg�J�n�N���X
//****************************************************
class CPlayerStateBeginning : public CPlayerState
{
public:

	CPlayerStateBeginning();			// �R���X�g���N�^
	~CPlayerStateBeginning() override;	// �f�X�g���N�^

	void Init() override;	// �����ݒ�
	void Update() override;	// �X�V
	void Exit() override;	// �I��

private:

	static const int END_CNT = 45;	// �ϐg�K�v����

	int m_nCntMetamorphose;	// �ϐg���ԃJ�E���g
};

//****************************************************
// �v���C���[��s��ԃN���X
//****************************************************
class CPlayerStateFlying : public CPlayerState
{
public:

	CPlayerStateFlying();			// �R���X�g���N�^
	~CPlayerStateFlying() override;	// �f�X�g���N�^

	void Init() override;	// �J�n
	void Update() override;	// �X�V
	void Exit() override;	// �I��

private:

	bool Flying();		// ����
	void Rotation();	// ��]
	void Braking();		// ��������
	void Finish();		// �ϐg����
	void Recoil();		// ����
};

//****************************************************
// �v���C���[�ϐg��~�N���X
//****************************************************
class CPlayerStateStopping : public CPlayerState
{
public:

	CPlayerStateStopping();			// �R���X�g���N�^
	~CPlayerStateStopping() override;	// �f�X�g���N�^

	void Init() override;	// �����ݒ�
	void Update() override;	// �X�V
	void Exit() override;	// �I��

private:

	static const int END_CNT = 45;	// �ϐg��~�K�v����

	int m_nCntStopMetamorphose;	// �ϐg���ԃJ�E���g
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

	CPlayer* GetPlayerInstance();				// �v���C���[�C���X�^���X�̎擾
	void SetPlayerInstance(CPlayer* player);	// �v���C���[�C���X�^���X�̐ݒ�

	void ChangeState(CPlayerState::STATE state);	// ��Ԃ�ύX

	CPlayerState* GetState();	// ��Ԃ��擾

private:
	
	void Create(CPlayerState::STATE state);	// �V���ȏ�Ԃ𐶐�

	CPlayer* m_pPlayer;		// �v���C���[�C���X�^���X�ւ̃|�C���^
	CPlayerState* m_pState;	// ��Ԃ�ێ�
};

#endif // _PALYER_H_