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
		BG_000 = 0,		// �w�i000
		LOGO,			// �^�C�g�����S
		NORMAL,			// �m�[�}�����[�h
		CHALLENGE,		// �`�������W���[�h
		CURSOR,			// �J�[�\��
		BG_001,			// �w�i001
		ARROW,			// ���
		RING,			// �����O
		SQUARE_00,		// �}�X��1
		LEAF_00,		// �t����00
		LEAF_01,		// �t����01
		LEAF_02,		// �t����02
		LEAF_03,		// �t����03
		LEAF_04,		// �t����04
		NUMBER_00,		// ����00
		LASTTIME,		// ���X�g�^�C��
		BESTTIME,		// �x�X�g�^�C��
		LIMITTIME,		// �c�莞��
		BACK,			// �߂�}�[�N
		CROWN,			// ����
		TEXT00,			// �e�L�X�g00
		TEXT01,			// �e�L�X�g01
		TEXT02,			// �e�L�X�g02
		TEXT03,			// �e�L�X�g03
		TEXT04,			// �e�L�X�g04
		TEXT05,			// �e�L�X�g05
		TEXT06,			// �e�L�X�g06
		TEXT07,			// �e�L�X�g07
		TEXT08,			// �e�L�X�g08
		TEXT09,			// �e�L�X�g09
		TEXT10,			// �e�L�X�g10
		TEXT11,			// �e�L�X�g11
		TEXT12,			// �e�L�X�g12
		LHAND,			// ����
		LHAND_SL,		// ����SL
		LHAND_SR,		// ����SR
		LHAND_SU,		// ����SU
		LHAND_SD,		// ����SD
		LHAND_JL,		// ����JL
		LHAND_JR,		// ����JR
		LHAND_JU,		// ����JU
		LHAND_JD,		// ����JD
		RHAND,			// �E��
		RHAND_A,		// �E��A
		RHAND_B,		// �E��B
		RHAND_X,		// �E��X
		RHAND_Y,		// �E��Y
		CNT,			// �R���g���[���[
		CNT_M0,			// �R���g���[���[M0
		CNT_M1,			// �R���g���[���[M1
		CNT_M2,			// �R���g���[���[M2
		CNT_M3,			// �R���g���[���[M3
		CNT_B0,			// �R���g���[���[B0
		CNT_B1,			// �R���g���[���[B1
		BOARD,			// �{�[�h
		SPEECH,			// �ӂ�����
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

#endif // _TEXTURE_MANAGER_H_