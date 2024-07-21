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
class CGameManager final
{
public:

	//****************************************************
	// �Q�[���t�F�[�Y����
	//****************************************************
	enum class PHASE
	{
		NONE = 0,	// ����
		START,		// ���x���J�n
		INGAME,		// �Q�[���i�s
		FINISH,		// ���x���I��
		END,		// �Q�[���I��
		MAX,
	};

	void Create();	// ����
	void Init();	// �����ݒ�
	void Release();	// ���
	void Uninit();	// �I������
	void Update();	// �X�V����

	PHASE GetPhase();			// �t�F�[�Y�擾
	void SetPhase(PHASE phase);	// �t�F�[�Y�ݒ�

	static CGameManager* GetInstance();	// �Q�[���}�l�[�W���[���擾

private:

	CGameManager();		// �R���X�g���N�^
	~CGameManager();	// �f�X�g���N�^

	void ImportLevel();	// ���x���ǂݍ���

	PHASE m_phase;							// �t�F�[�Y����
	int m_nMaxStage;						// �X�e�[�W��
	int m_nCntGoal;							// �S�[����J�E���g
	std::vector<std::string> m_stagePath;	// �X�e�[�W�p�X

	static CGameManager* m_pInstance;	// �Q�[���}�l�[�W���[
};

#endif // _GAME_MANAGER_H_