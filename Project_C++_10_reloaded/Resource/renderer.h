//============================================================================
// 
// �����_���[�Ǘ��A�w�b�_�t�@�C�� [renderer.h]
// Author : ���c����
// 
//============================================================================

#ifndef _RENDERER_H_
#define _RENDERER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "texture.h"
#include "model_X.h"

//****************************************************
// �����_���[�N���X
//****************************************************
class CRenderer
{
public:

	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^

	HRESULT Init(HWND hWnd, BOOL bWindiw);	// �����ݒ�
	void Uninit();							// �I������
	void Update();							// �X�V����
	void Draw();							// �`�揈��
	void PrintDebug();						// �f�o�b�O�\��

	void SetDebugString(std::string str);			// �f�o�b�O������ɒǉ�
	void SetTimeString(std::string str, int nCnt);	// �������f�o�b�O������ɒǉ�

	LPDIRECT3DDEVICE9 GetDeviece();		// �f�o�C�X�̎擾
	CTexture* GetTextureInstane();		// �e�N�X�`���Ǘ��̎擾
	CModel_X* GetModelInstane();		// ���f���Ǘ��̎擾

private:

	LPDIRECT3D9 m_pD3D;									// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;						// �f�o�C�X
	LPD3DXFONT m_pFont;									// �t�H���g
	std::string m_debugStr;								// �\���p������
	std::vector<std::pair<std::string, int>> m_timeStr;	// ������������
	CTexture* m_pTexture;								// �e�N�X�`���Ǘ�
	CModel_X* m_pModel_X;								// X���f���Ǘ�
};

#endif // _RENDERER_H_