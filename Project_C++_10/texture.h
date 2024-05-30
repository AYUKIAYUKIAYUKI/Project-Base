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

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	HRESULT Load();	// �e�N�X�`���Ǎ�
	void Unload();	// �e�N�X�`���j��

	LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE type);	// �e�N�X�`�����擾

private:

	static LPDIRECT3DTEXTURE9 m_apTexTemp[TEX_TYPE::MAX];	// �e�N�X�`���Ǘ�
};

#endif // _ENEMY_H_