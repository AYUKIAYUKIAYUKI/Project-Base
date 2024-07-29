//============================================================================
// 
// X���f���}�l�[�W���[�A�w�b�_�t�@�C�� [model_X_manager.h]
// Author : ���c����
// 
//============================================================================

#ifndef _MODEL_X_MANAGER_H_
#define _MODEL_X_MANAGER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// X���f���}�l�[�W���[�N���X
//****************************************************
class CModel_X_Manager final
{
public:

	//****************************************************
	// ���f������
	//****************************************************
	enum class TYPE
	{
		PLAYER_000 = 0,	// �v���C���[1
		PLAYER_001,		// �v���C���[2
		PLAYER_002,		// �v���C���[3
		PLAYER_003,		// �v���C���[4
		PLAYER_004,		// �v���C���[5
		PLAYER_005,		// �v���C���[�S�[��
		BLOCK_000,		// �u���b�N0
		DESTRUCTIBLE,	// ��u���b�N
		START,			// �X�^�[�g
		GOAL,			// �S�[��
		LINE_X,			// X��
		LINE_Y,			// Y��
		MAX,
	};

	//****************************************************
	// ���f�����̍\���̂̒�`
	//****************************************************
	struct MODEL
	{
		D3DXVECTOR3 size;			// �T�C�Y
		LPD3DXMESH pMesh;			// ���b�V�����
		LPD3DXBUFFER pBuffMat;		// �}�e���A�����
		DWORD dwNumMat;				// �}�e���A���̐�
		LPDIRECT3DTEXTURE9* ppTex;	// �e�N�X�`�����
	};

	HRESULT Load();	// ���f���Ǎ�
	void Release();	// ���

	MODEL* GetModel(TYPE type);	// ���f�����擾

	static CModel_X_Manager* GetInstance();	// X���f���}�l�[�W���[���擾

private:

	CModel_X_Manager();		// �R���X�g���N�^
	~CModel_X_Manager();	// �f�X�g���N�^

	void Create();									// ����
	D3DXVECTOR3 ImportSize(std::string filename);	// �T�C�Y�ǂݍ���
	void Unload();									// ���f���j��

	MODEL m_apModelTemp[static_cast<int>(TYPE::MAX)];	// X���f�����

	static CModel_X_Manager* m_pInstnce;	// X���f���}�l�[�W���[
};

#endif // _MODEL_X_MANAGER_H_