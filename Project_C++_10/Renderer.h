//============================================================================
// 
// �����_���[�Ǘ��A�w�b�_�t�@�C�� [renderer.h]
// Author : ���c����
// 
//============================================================================

#ifndef _RENDERER_H_
#define _RENDERER_H_	// ��d�C���N���[�h�h�~

// �C���N���[�h�t�@�C��
//#include "main.h"

#include <windows.h>
#include "d3dx9.h"

// �����_���[�N���X
class CRenderer
{
public:
	CRenderer();							// �R���X�g���N�^
	~CRenderer();							// �f�X�g���N�^
	HRESULT Init(HWND hWnd, BOOL bWindiw);	// �����ݒ�
	void Uninit();							// �I������
	void Update();							// �X�V����
	void Draw();							// �`�揈��
	LPDIRECT3DDEVICE9 GetDeviece();			// �f�o�C�X�̎擾

private:
	LPDIRECT3D9 m_pD3D;				// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// �f�o�C�X
};

#endif // _RENDERER_H_