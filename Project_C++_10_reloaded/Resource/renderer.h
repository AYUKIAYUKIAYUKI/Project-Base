//============================================================================
// 
// �����_���[�Ǘ��A�w�b�_�t�@�C�� [renderer.h]
// Author : ���c����
// 
//============================================================================

#ifndef _RENDERER_H_
#define _RENDERER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �����_���[�N���X
//****************************************************
class CRenderer final
{
public:

	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^

	HRESULT Init(HWND hWnd, BOOL bWindiw);	// �����ݒ�
	void Release();							// ���
	void Update();							// �X�V����
	void Draw();							// �`�揈��
	void PrintDebug();						// �f�o�b�O�\��

	static CRenderer* GetInstance();	// �����_���[���擾

	LPDIRECT3DDEVICE9 GetDeviece();		// �f�o�C�X�̎擾
	LPDIRECT3DTEXTURE9 GetTexture();	// �e�N�X�`�������擾
	LPDIRECT3DSURFACE9 GetSurface();	// �T�[�t�F�C�X�����擾

	void SetDebugString(std::string str);			// �f�o�b�O������ɒǉ�
	void SetTimeString(std::string str, int nCnt);	// �������f�o�b�O������ɒǉ�

private:

	void Create();			// ����
	HRESULT CreateTex();	// ���j�^�[�p�e�N�X�`���̐���
	void Uninit();			// �I������

	static CRenderer* m_pRenderer;	// �����_���[

	LPDIRECT3D9 m_pD3D;									// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;						// �f�o�C�X
	LPD3DXFONT m_pFont;									// �t�H���g
	LPDIRECT3DTEXTURE9 m_pMonitorTex;					// ���j�^�[�p�e�N�X�`���|�C���^
	LPDIRECT3DSURFACE9 m_pMonitorSurface;				// ���j�^�[�p�T�[�t�F�C�X�|�C���^
	std::string m_debugStr;								// �\���p������
	std::vector<std::pair<std::string, int>> m_timeStr;	// ������������
};

#endif // _RENDERER_H_