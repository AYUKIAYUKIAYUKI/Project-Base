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
		BG_000 = 0,		// �w�i
		PLAYER_000,		// �v���C���[
		BULLET_000,		// �e
		EXPLOSION_000,	// ����
		ENEMY_000,		// �G
		MAX,
	};

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	HRESULT Load();	// �e�N�X�`���Ǎ�
	void Unload();	// �e�N�X�`���j��

	LPDIRECT3DTEXTURE9 GetTex(TEX_TYPE type);	// �e�N�X�`�����擾

private:

	static const int MAX_TEX = 64;	// �ő�e�N�X�`����

	// ������͍폜����->���ƃe�N�X�`���}�l�[�W���[�͏����I�Ƀ����_���[�̃����o�̕����y����
	const char* m_aFilename[TEX_TYPE::MAX] = {
		"data\\TEXTURE\\KOME.png",
		"data\\TEXTURE\\runningman000.png",
		"data\\TEXTURE\\bullet000.png",
		"data\\TEXTURE\\explosion000.png",
		"data\\TEXTURE\\AL-1S.png",
	};

	static LPDIRECT3DTEXTURE9 m_apTexTemp[MAX_TEX];	// �e�N�X�`���Ǘ�
};

#endif // _ENEMY_H_