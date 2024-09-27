//============================================================================
// 
// �Q�[���}�l�[�W���[�A�w�b�_�t�@�C�� [game_manager.h]
// Author : ���c����
// 
//============================================================================

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "text.h"

//****************************************************
// �Q�[���}�l�[�W���[�N���X
//****************************************************
class CGameManager final
{
public:

	//****************************************************
	// �Q�[���t�F�[�Y����
	//****************************************************
	enum class PHASE
	{
		NONE = 0,	// ����
		SELECT,		// ���x���I��
		START,		// ���x���J�n
		INGAME,		// ���x���i�s
		FINISH,		// ���x���I��
		RETIRE,		// ���x�����^�C�A
		C_START,	// �`�������W�J�n
		C_INGAME,	// �`�������W�i�s
		C_FINISH,	// �`�������W�I��
		MAX,
	};

	void Create();			// ����
	void Init();			// �����ݒ�
	void Init(PHASE phase);	// �����ݒ�ƃt�F�[�Y�ݒ�
	void Release();			// ���
	void Uninit();			// �I������
	void Update();			// �X�V����

	PHASE GetPhase();			// �t�F�[�Y�擾
	void SetPhase(PHASE phase);	// �t�F�[�Y�ݒ�

	bool GetEndTutorial();					// �`���[�g���A���I���t���O���擾
	int GetMaxStage();						// �X�e�[�W�����擾
	int GetSelectLevel();					// �I�����x���ԍ����擾
	std::vector<bool> GetCollectAchieve();	// �A�`�[�u������

	static CGameManager* GetInstance();	// �Q�[���}�l�[�W���[���擾

private:

	//****************************************************
	// �v���r���[�t�F�[�Y����
	//****************************************************
	enum class PREVIEW
	{
		NONE = 0,	// ����
		BIGEN,		// �J�n
		SHOWING,	// ������
		END,		// �I��
		MAX,
	};

	CGameManager();		// �f�t�H���g�R���X�g���N�^
	~CGameManager();	// �f�X�g���N�^

	void ImportLevel();		// ���x���ǂݍ���
	void StartPreview();	// �v���r���[�J�n
	void StagePreview();	// �X�e�[�W�v���r���[
	void ChallengeResult();	// �`�������W���U���g

	bool m_bEndTutorial;					// �`���[�g���A���m�F
	PHASE m_phase;							// �t�F�[�Y����
	int m_nMaxStage;						// �X�e�[�W��
	int m_nSelectLevel;						// ���x���I��
	int m_nOldSelectLevel;					// �ߋ��̃��x���I��
	std::vector<std::string> m_stagePath;	// �X�e�[�W�p�X
	std::vector<bool> m_vbCollectAchieve;	// �A�`�[�u������
	int m_nSelectChallenge;					// �`�������W�I��
	PREVIEW m_Preview;						// �v���r���[���
	int m_nCntPreview;						// �v���r���[�ҋ@�J�E���g

	static CGameManager* m_pInstance;	// �Q�[���}�l�[�W���[
};

#endif // _GAME_MANAGER_H_