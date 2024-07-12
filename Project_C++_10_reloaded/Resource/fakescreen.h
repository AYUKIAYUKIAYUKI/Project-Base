//============================================================================
// 
// �^���X�N���[���A�w�b�_�t�@�C�� [fakescreen.h]
// Author : ���c����
// 
//============================================================================

#ifndef _FAKESCREEN_H_
#define _FAKESCREEN_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �^���X�N���[���|���S���N���X
//****************************************************
class CFakeScreen
{
public:

	CFakeScreen();	// �R���X�g���N�^
	~CFakeScreen();	// �f�X�g���N�^

	HRESULT Init();	// �����ݒ�
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��
	void Create();	// ����
	void Release();	// ���

	LPDIRECT3DTEXTURE9 GetTexture();	// �e�N�X�`�������擾
	LPDIRECT3DSURFACE9 GetSurface();	// �T�[�t�F�C�X�����擾

	static CFakeScreen* GetInstance();	// �擾

private:

	void Move();	// �ړ�
	void SetVtx();	// ���_���̐ݒ�

	static CFakeScreen* m_pInstance;	// ���N���X���

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTex;			// �e�N�X�`�����̃|�C���^
	LPDIRECT3DSURFACE9 m_pSurface;		// �T�[�t�F�C�X���̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_size;					// �T�C�Y
};

#endif // _FAKESCREEN_H_