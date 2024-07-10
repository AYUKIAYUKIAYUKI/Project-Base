//============================================================================
// 
// �I�u�W�F�N�g�Ǘ��A�w�b�_�t�@�C�� [object.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �I�u�W�F�N�g�N���X
//****************************************************
class CObject
{
public:

	static const int MAX_OBJ = 512;		// �I�u�W�F�N�g�ő吔

	//****************************************************
	// �I�u�W�F�N�g�̎�ގ���
	//****************************************************
	enum class TYPE
	{
		NONE = 0,	// ����
		PLAYER,		// �v���C���[
		DUMMY,		// �_�~�[
		ENEMY,		// �G�l�~�[
		BLOCK,		// �u���b�N
		ITEM,		// �A�C�e��
		START,		// �X�^�[�g
		GOAL,		// �S�[��
		SCORE,		// �X�R�A
		MAX,
	};

	//****************************************************
	// �I�u�W�F�N�g�̃��C���[����
	//****************************************************
	enum class LAYER
	{
		NONE = 0,		// ����
		BACK,			// �w�i
		BACK_MIDDLE,	// ��둤
		FRONT_MIDDLE,	// �O��
		FRONT,			// �O�i
		UI,				// UI
		MAX,
	};

	CObject(int nPriority = static_cast<int>(LAYER::MAX) - 1);	// �R���X�g���N�^
	virtual ~CObject() = 0;										// �f�X�g���N�^

	virtual HRESULT Init() = 0;	// �����ݒ�
	virtual void Uninit() = 0;	// �I������
	virtual void Update() = 0;	// �X�V����
	virtual void Draw() = 0;	// �`�揈��

	static void ReleaseAll();	// �S�I�u�W�F�N�g�������
	static void UpdateAll();	// �S�I�u�W�F�N�g�X�V����
	static void DrawAll();		// �S�I�u�W�F�N�g�`�揈��

	static CObject* GetObject(int nPriority, int nID);	// �I�u�W�F�N�g���擾
	static int GetNumAll();								// �I�u�W�F�N�g�����擾

	void Release();	// �ʉ������ (��)
	
	TYPE GetType();	// �I�u�W�F�N�g�̃^�C�v���擾

	static CObject* FindObject(TYPE type);		// ����^�C�v�̃I�u�W�F�N�g�T��
	static CObject** FindAllObject(TYPE type);	// ����^�C�v�̃I�u�W�F�N�g�����ׂĒT��

protected:

	void SetType(TYPE type);	// �^�C�v�ݒ�

private:

	static CObject* m_apObject[static_cast<int>(LAYER::MAX)][MAX_OBJ];	// �I�u�W�F�N�g�Ǘ�
	static CObject* m_apFind[MAX_OBJ];									// �������ꂽ�I�u�W�F�N�g�ێ��p
	static int m_nNumAll;												// �I�u�W�F�N�g����

	int m_nPriority;	// �`��D��x
	int m_nID;			// �������g��ID
	TYPE m_type;		// �^�C�v���� 
};

#endif // _OBJECT_H_