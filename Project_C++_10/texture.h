//============================================================================
// 
// �e�N�X�`���Ǘ��A�w�b�_�t�@�C�� [texture.h]
// Author : ���c����
// 
//============================================================================

#ifndef _TEXTURE_H_
#define _TEXTURE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �e�N�X�`���N���X
//****************************************************
class CTexture
{
public:

	//****************************************************
	// �e�N�X�`������
	//****************************************************
	enum TEX_TYPE
	{
		BG_000 = 0,		// �w�i000
		BG_001,			// �w�i001
		NUMBER_000,		// ����000
		PLAYER_000,		// �v���C���[000
		BLOCK_000,		// �u���b�N000
		BULLET_000,		// �e000
		EFFECT_000,		// �G�t�F�N�g000
		EXPLOSION_000,	// ����000
		ENEMY_000,		// �G000
		MAX,
	};

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	HRESULT Load();	// �e�N�X�`���Ǎ�
	void Unload();	// �e�N�X�`���j��

	LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE type);	// �e�N�X�`�����擾

private:

	static LPDIRECT3DTEXTURE9 m_apTexTemp[TEX_TYPE::MAX];	// �e�N�X�`���Ǘ�
};

#endif // _ENEMY_H_