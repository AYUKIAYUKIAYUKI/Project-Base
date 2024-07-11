//============================================================================
// 
// �e�X�g�p�|���S���A�w�b�_�t�@�C�� [test_polygon_2D.h]
// Author : ���c����
// 
//============================================================================

#ifndef _TEST_POLYGON_2D_H_
#define _TEST_POLYGON_2D_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �e�X�g�p�|���S���N���X
//****************************************************
class CTestPolygon2D
{
public:

	CTestPolygon2D();	// �R���X�g���N�^
	~CTestPolygon2D();	// �f�X�g���N�^

	HRESULT Init();	// �����ݒ�
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��
	void Create();	// ����
	void Release();	// ���

	static CTestPolygon2D* GetInstance();	// �擾

private:

	static CTestPolygon2D* m_pInstance;	// ���N���X���

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTex;			// �e�N�X�`�����̃|�C���^
	LPDIRECT3DSURFACE9 m_pSurface;		// �T�[�t�F�C�X���̃|�C���^
};

#endif // _TEST_POLYGON_2D_H_