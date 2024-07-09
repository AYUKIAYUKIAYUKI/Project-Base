//============================================================================
// 
// �Q�[���}�l�[�W���[�A�w�b�_�t�@�C�� [game_manager.h]
// Author : ���c����
// 
//============================================================================

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �Q�[���}�l�[�W���[�N���X
//****************************************************
class CGameManager
{
public:

	//****************************************************
	// �Q�[���t�F�[�Y����
	//****************************************************
	enum class PHASE
	{
		NONE = 0,	// ����
		BEGIN,		// �J�n
		PLAY,		// �Q�[����
		END,		// �I��
		MAX,
	};

	CGameManager();		// �R���X�g���N�^
	~CGameManager();	// �f�X�g���N�^

	void Init();	// �����ݒ�
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Create();	// ����
	void Release();	// ���

	void SetPhase(PHASE phase);	// �t�F�[�Y��ݒ�

	static CGameManager* GetInstance();	// �擾

private:

	void ImportLevel();	// ���x���ǂݍ���

	PHASE m_phase;		// �t�F�[�Y����
	int m_nMaxStage;	// �X�e�[�W��
	std::vector<std::string> m_stagePath;	// �X�e�[�W�p�X

	static CGameManager* m_pGameManager;	// ���N���X���
};

#endif // _GAME_MANAGERH_