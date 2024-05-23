//============================================================================
// 
// �}�l�[�W���[�A�w�b�_�t�@�C�� [managaer.h]
// Author : ���c����
// 
//============================================================================

#ifndef _MANAGER_H_
#define _MANAGER_H_	// ��d�C���N���[�h�h�~

// �C���N���[�h�t�@�C��
#include "renderer.h"
#include "input.h"

// �}�l�[�W���[�N���X
class CManager
{
public:
	CManager();		// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// �����ݒ�
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��
	static CRenderer* GetRenderer();		// �����_���[�擾
	static CInputKeyboard* GetKeyboard();	// �L�[�{�[�h�擾
	static CInputPad* GetPad();				// �p�b�h�擾

private:
	static CRenderer* m_pRenderer;		// �����_���[�Ǘ�
	static CInputKeyboard* m_pKeyboard;	// �L�[�{�[�h�Ǘ�
	static CInputPad* m_pPad;			// �p�b�h�Ǘ�
};

#endif // _MANAGER_H_
