//============================================================================
// 
// �v���C���[��ԊǗ��A�w�b�_�t�@�C�� [player_state.h]
// Author : ���c����
// 
//============================================================================

#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "player.h"

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
		NONE = 0,	// ����
		DEFAULT,	// �ʏ���
		BEGINNING,	// �ϐg�J�n
		FLYING,		// ��s���
		STOPPING,	// �ϐg��~
		MISS,		// ���s���
		GOAL,		// �S�[����
		MAX,
	};

	CPlayerState();				// �R���X�g���N�^
	virtual ~CPlayerState();	// �f�X�g���N�^

	virtual void Enter() = 0;				// �ύX�J�n
	void RegisterPlayer(CPlayer* pPlayer);	// �v���C���[��o�^
	virtual void Update() = 0;				// �X�V
	virtual void Exit() = 0;				// �ύX�I��

protected:

	CPlayer* m_pPlayer;	// �v���C���[�̃|�C���^
};

//****************************************************
// �v���C���[�ʏ��ԃN���X
//****************************************************
class CPlayerStateDefault : public CPlayerState
{
public:

	CPlayerStateDefault();				// �R���X�g���N�^
	~CPlayerStateDefault() override;	// �f�X�g���N�^

	void Enter() override;	// �ύX�J�n
	void Update() override;	// �X�V
	void Exit() override;	// �ύX�I��

private:

	static const float MAX_WALK_VELOCITY;	// ���s���̍ő�����x
	static const float BRAKING_WALK_SPEED;	// ���s���̐�����

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

	void Enter() override;	// �ύX�J�n
	void Update() override;	// �X�V
	void Exit() override;	// �ύX�I��

private:

	static const int BEGIN_CNT_MAX;		// �ϐg�K�v����
	static const float BEGIN_FLOATING;	// �ϐg���㏸��
	static const float BEGIN_SPINNING;	// �ϐg����]��

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

	void Enter() override;	// �ύX�J�n
	void Update() override;	// �X�V
	void Exit() override;	// �ύX�I��

private:

	static const float MAX_FLY_VELOCITY;	// ��s���̍ő�����x
	static const float FLY_SPEED;			// ��s���x

	bool Control();		// ���c
	void Rotation();	// ��]
	void Braking();		// ��������
};

//****************************************************
// �v���C���[�ϐg��~�N���X
//****************************************************
class CPlayerStateStopping : public CPlayerState
{
public:

	CPlayerStateStopping();				// �R���X�g���N�^
	~CPlayerStateStopping() override;	// �f�X�g���N�^

	void Enter() override;	// �ύX�J�n
	void Update() override;	// �X�V
	void Exit() override;	// �ύX�I��

private:

	static const int STOP_CNT_MAX;		// �ϐg��~�K�v����
	static const float RECOIL_SPEED;	// �����ړ����x

	void Rolling();	// ��]
	void Recoil();	// ����

	int m_nCntStopMetamorphose;	// �ϐg���ԃJ�E���g
};

//****************************************************
// �v���C���[���s��ԃN���X
//****************************************************
class CPlayerStateMistook : public CPlayerState
{
public:

	CPlayerStateMistook();				// �R���X�g���N�^
	~CPlayerStateMistook() override;	// �f�X�g���N�^

	void Enter() override;	// ����ύX
	void Update() override;	// �X�V
	void Exit() override;	// �ύX�I��

private:

	static const float MAX_WARP_SPEED;	// �����ړ����x�̏��

	void FindStartObject();	// �X�^�[�g�I�u�W�F�N�g�̈ʒu������
	void Respawn();			// ���X�|�[��

	D3DXVECTOR3 m_posStartObject;	// �X�^�[�g�I�u�W�F�N�g�̈ʒu
};

//****************************************************
// �v���C���[�S�[����N���X
//****************************************************
class CPlayerStateGoal : public CPlayerState
{
public:

	CPlayerStateGoal();				// �R���X�g���N�^
	~CPlayerStateGoal() override;	// �f�X�g���N�^

	void Enter() override;	// ����ύX
	void Update() override;	// �X�V
	void Exit() override;	// �ύX�I��
};

//****************************************************
// �v���C���[��ԃ}�l�[�W���[�N���X
//****************************************************
class CPlayerStateManager
{
public:

	CPlayerStateManager();	// �R���X�g���N�^
	~CPlayerStateManager();	// �f�X�g���N�^

	void CheckStateChange();				// ��Ԃ̕ύX���m�F
	void Init(CPlayer* pPlayer);			// �����ݒ�
	void RegisterPlayer(CPlayer* pPlayer);	// �v���C���[��o�^
	void Uninit();							// �I������

	CPlayer* GetPlayer();								// �v���C���[���擾
	CPlayerState* GetState();							// ��Ԃ��擾
	CPlayerState::STATE GetPendingState();				// �ύX�\��̏�Ԃ��擾
	void SetPendingState(CPlayerState::STATE state);	// �ύX�\��̏�Ԃ�ݒ�

private:

	void Create(CPlayerState::STATE state);	// �V���ȏ�Ԃ𐶐�

	CPlayer* m_pPlayer;					// �v���C���[�̃|�C���^
	CPlayerState* m_pState;				// ��Ԃ̃|�C���^
	CPlayerState::STATE m_PendingState;	// �ύX�\��̏��
};

#endif // _PLAYER_STATE_H_