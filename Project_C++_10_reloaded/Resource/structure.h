//============================================================================
// 
// �X�g���N�`���[�Ǘ��A�w�b�_�t�@�C�� [structure.h]
// Author : ���c����
// 
//============================================================================

#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_	// ��d�C���N���[�h�h�~

////****************************************************
//// �X�g���N�`���[�N���X
////****************************************************
//class CStructure
//{
//public:
//
//	static const int MAX_OBJ = 512;	// �I�u�W�F�N�g�̍ő吔
//
//	//****************************************************
//	// �I�u�W�F�N�g�̎�ގ���
//	//****************************************************
//	enum class TYPE
//	{
//		NONE = 0,		// ����
//		PLAYER,			// �v���C���[
//		DUMMY,			// �_�~�[
//		ENEMY,			// �G�l�~�[
//		BLOCK,			// �u���b�N
//		DESTRUCTIBLE,	// ��u���b�N
//		SPIKES,			// �g�Q�u���b�N
//		ITEM,			// �A�C�e��
//		START,			// �X�^�[�g
//		GOAL,			// �S�[��
//		SCORE,			// �X�R�A
//		MAX,
//	};
//
//	CStructure(int nPriority = static_cast<int>(LAYER::MAX) - 1);	// �R���X�g���N�^
//	~CStructure() = 0;										// �f�X�g���N�^
//
//	virtual HRESULT Init() = 0;	// �����ݒ�
//	virtual void Uninit() = 0;	// �I������
//	virtual void Update() = 0;	// �X�V����
//	virtual void Draw() = 0;	// �`�揈��
//	void Release();				// �ʉ������
//
//	TYPE GetType();				// �^�C�v���擾
//	void SetType(TYPE type);	// �^�C�v��ݒ�
//
//	bool GetDeath();				// ���S�t���O�擾
//	void SetDeath(bool bDetected);	// ���S�t���O�ݒ�
//
//	static void ReleaseAll();	// �S�I�u�W�F�N�g�������
//	static void UpdateAll();	// �S�I�u�W�F�N�g�X�V����
//	static void DrawAll();		// �S�I�u�W�F�N�g�`�揈��
//
//	static CObject* GetObject(int nPriority);	// �擪�I�u�W�F�N�g�̃|�C���^�擾
//	static CObject* FindObject(TYPE type);		// ����^�C�v�̃I�u�W�F�N�g�T��
//	static CObject** FindAllObject(TYPE type);	// ����^�C�v�̃I�u�W�F�N�g�����ׂĒT��
//
//private:
//
//	static CObject* m_apFind[MAX_OBJ];							// �������ꂽ�I�u�W�F�N�g�ێ��p
//	static int m_nNumAll;										// �I�u�W�F�N�g����
//	static CObject* m_pTop[static_cast<int>(LAYER::MAX)];		// �擪�I�u�W�F�N�g�̃|�C���^
//	static CObject* m_pCur[static_cast<int>(LAYER::MAX)];		// �I�[�I�u�W�F�N�g�̃|�C���^
//
//	int m_nPriority;	// �`��D��x
//	CObject* m_pPrev;	// �O�̃I�u�W�F�N�g�̃|�C���^
//	CObject* m_pNext;	// ���̃I�u�W�F�N�g�̃|�C���^
//	TYPE m_type;		// �^�C�v���� 
//	bool m_bDeath;		// ���S�t���O
//};

#endif // _OBJECT_H_