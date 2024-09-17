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
		SELECT,		// ���x���I��
		START,		// ���x���J�n
		INGAME,		// ���x���i�s
		FINISH,		// ���x���I��
		RETIRE,		// ���^�C�A
		MAX,
	};

	void Create();	// ����
	void Init();	// �����ݒ�
	void Release();	// ���
	void Uninit();	// �I������
	void Update();	// �X�V����

	PHASE GetPhase();			// �t�F�[�Y�擾
	void SetPhase(PHASE phase);	// �t�F�[�Y�ݒ�

	int GetMaxStage();						// �X�e�[�W�����擾
	int GetSelectLevel();					// �I�����x���ԍ����擾
	std::vector<bool> GetCollectAchieve();	// �A�`�[�u������

	static CGameManager* GetInstance();	// �Q�[���}�l�[�W���[���擾

private:

	CGameManager();		// �f�t�H���g�R���X�g���N�^
	~CGameManager();	// �f�X�g���N�^

	void ImportLevel();	// ���x���ǂݍ���

	PHASE m_phase;							// �t�F�[�Y����
	int m_nMaxStage;						// �X�e�[�W��
	int m_nSelectLevel;						// ���x���I��
	std::vector<std::string> m_stagePath;	// �X�e�[�W�p�X
	std::vector<bool> m_vbCollectAchieve;	// �A�`�[�u������

	static CGameManager* m_pInstance;	// �Q�[���}�l�[�W���[
};

#endif // _GAME_MANAGER_H_