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
#include "model.h"

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

	LPDIRECT3DDEVICE9 GetDeviece();	// �f�o�C�X�̎擾
	CTexture* GetTextureInstane();	// �e�N�X�`���Ǘ��̎擾
	CModel* GetModelInstane();		// ���f���Ǘ��̎擾

private:

	LPDIRECT3D9 m_pD3D;				// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// �f�o�C�X
	CTexture* m_pTexture;			// �e�N�X�`���Ǘ�
	CModel* m_pModel;				// ���f���Ǘ�
};

#endif // _RENDERER_H_