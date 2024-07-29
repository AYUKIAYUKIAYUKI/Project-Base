//============================================================================
// 
// �e�N�X�`���}�l�[�W���[�A�w�b�_�t�@�C�� [texture_manager.h]
// Author : ���c����
// 
//============================================================================

#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �e�N�X�`���}�l�[�W���[�N���X
//****************************************************
class CTexture_Manager final
{
public:

	//****************************************************
	// �e�N�X�`������
	//****************************************************
	enum class TYPE
	{
		BG_000 = 0,		// �w�i0
		BG_001,			// �w�i1
		BLOCK_000,		// �u���b�N0
		BULLET_000,		// �e0
		EFFECT_000,		// �G�t�F�N�g0
		ENEMY_000,		// �G0
		EXPLOSION_000,	// ����0
		ITEM_000,		// �A�C�e��0
		NUMBER_000,		// ����0
		PLAYER_000,		// �v���C���[0
		PLAYER_001,		// �v���C���[1
		MAX,
	};

	HRESULT Load();	// �e�N�X�`���Ǎ�
	void Release();	// ���

	LPDIRECT3DTEXTURE9 GetTexture(TYPE type);	// �e�N�X�`�����擾

	static CTexture_Manager* GetInstance();	// �e�N�X�`���}�l�[�W���[���擾

private:

	CTexture_Manager();		// �R���X�g���N�^
	~CTexture_Manager();	// �f�X�g���N�^

	void Create();	// ����
	void Unload();	// �e�N�X�`���j��

	LPDIRECT3DTEXTURE9 m_apTexTemp[static_cast<int>(TYPE::MAX)];	// �e�N�X�`�����

	static CTexture_Manager* m_pInstance;	// �e�N�X�`���}�l�[�W���[
};

#endif // _TEXTURE_H_