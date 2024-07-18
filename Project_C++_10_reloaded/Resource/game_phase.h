////============================================================================
//// 
//// �Q�[���t�F�[�Y�A�w�b�_�t�@�C�� [game_phase.h]
//// Author : ���c����
//// 
////============================================================================
//
//#ifndef _GAME_PHASE_H_
//#define _GAME_PHASE_H_	// ��d�C���N���[�h�h�~
//
////****************************************************
//// �C���N���[�h�t�@�C��
////****************************************************
//#include "game_manager.h"
//
////****************************************************
//// �Q�[���t�F�[�Y�N���X
////****************************************************
//class CGamePhase
//{
//public:
//
//	CGamePhase();			// �R���X�g���N�^
//	virtual ~CGamePhase();	// �f�X�g���N�^
//
//	virtual void Enter() = 0;	// �ύX�J�n
//	virtual void Update() = 0;	// �X�V
//	virtual void Exit() = 0;	// �ύX�I��
//};
//
////****************************************************
//// ���x���J�n�t�F�[�Y�N���X
////****************************************************
//class CGamePhase_Start : public CGamePhase
//{
//public:
//
//	CGamePhase_Start();				// �R���X�g���N�^
//	virtual ~CGamePhase_Start();	// �f�X�g���N�^
//
//	void Enter() override;	// �ύX�J�n
//	void Update() override;	// �X�V
//	void Exit() override;	// �ύX�I��
//};
//
////****************************************************
//// �Q�[���i�s�t�F�[�Y�N���X
////****************************************************
//class CGamePhase_Ingame : public CGamePhase
//{
//public:
//
//	CGamePhase_Ingame();			// �R���X�g���N�^
//	virtual ~CGamePhase_Ingame();	// �f�X�g���N�^
//
//	void Enter() override;	// �ύX�J�n
//	void Update() override;	// �X�V
//	void Exit() override;	// �ύX�I��
//};
//
////****************************************************
//// ���x���I���t�F�[�Y�N���X
////****************************************************
//class CGamePhase_Finish : public CGamePhase
//{
//public:
//
//	CGamePhase_Finish();			// �R���X�g���N�^
//	virtual ~CGamePhase_Finish();	// �f�X�g���N�^
//
//	void Enter() override;	// �ύX�J�n
//	void Update() override;	// �X�V
//	void Exit() override;	// �ύX�I��
//};
//
////****************************************************
//// �Q�[���t�F�[�Y�}�l�[�W���[�N���X
////****************************************************
//class CGamePhaseManager
//{
//public:
//
//	CGamePhaseManager();	// �R���X�g���N�^
//	~CGamePhaseManager();	// �f�X�g���N�^
//
//	void CheckPhaseChange();	// �t�F�[�Y�̕ύX���m�F
//	void Init();				// �����ݒ�
//	void Uninit();				// �I������
//
//	CGameManager::PHASE GetPendingPhase();				// �ύX�\��̃t�F�[�Y���擾
//	void SetPendingPhase(CGameManager::PHASE phase);	// �ύX�\��̃t�F�[�Y��ݒ�
//
//private:
//
//	void Create(CGameManager::PHASE phase);	// �V���ȃt�F�[�Y�𐶐�
//
//	CGamePhase* m_pPhase;				// �t�F�[�Y�̃|�C���^
//	CGameManager::PHASE m_PendingPhase;	// �ύX�\��̃t�F�[�Y
//};
//
//#endif // _GAME_PHASE_H_