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
		KARIHAIKEI = 0,	// ���w�i
		PLAYER_000,		// �v���C���[000
		PLAYER_001,		// �v���C���[001
		PLAYER_002,		// �v���C���[002
		PLAYER_003,		// �v���C���[003
		PLAYER_004,		// �v���C���[004
		PLAYER_005,		// �v���C���[005
		BLOCK_000,		// �u���b�N000
		DESTRUCTIBLE,	// ��u���b�N
		SPIKES,			// �Ƃ��u���b�N
		ENEMY,			// �G�l�~�[
		START,			// �X�^�[�g
		GOAL,			// �S�[��
		LINE_X,			// X��
		LINE_Y,			// Y��
		RIPPLE00,		// �g��00
		RIPPLE01,		// �g��01
		RIPPLE02,		// �g��02
		RIPPLE03,		// �g��03
		STAR00,			// ��00
		STAR01,			// ��01
		PARTICLE00,		// ���q00
		PARTICLE01,		// ���q01
		PARTICLE02,		// ���q02
		PARTICLE03,		// ���q03
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