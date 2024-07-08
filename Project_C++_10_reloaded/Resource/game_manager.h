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

	CGameManager();		// �R���X�g���N�^
	~CGameManager();	// �f�X�g���N�^

	void Init();	// �����ݒ�
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Create();	// ����
	void Release();	// ���

	static CGameManager* GetInstance();	// �擾

private:

	static CGameManager* m_pGameManager;	// ���N���X���
};

#endif // _GAME_MANAGERH_