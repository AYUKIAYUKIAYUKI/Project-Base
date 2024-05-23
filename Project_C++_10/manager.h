//============================================================================
// 
// �}�l�[�W���[�A�w�b�_�t�@�C�� [managaer.h]
// Author : ���c����
// 
//============================================================================

#ifndef _MANAGER_H_
#define _MANAGER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "renderer.h"
#include "input.h"
#include "sound.h"

//****************************************************
// �}�l�[�W���[�N���X
//****************************************************
class CManager
{
public:
	CManager();		// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// �����ݒ�
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��

	// �����_���[�擾
	static CRenderer* GetRenderer() {
		return m_pRenderer;
	}

	// �L�[�{�[�h�擾
	static CInputKeyboard* GetKeyboard() {
		return m_pKeyboard;
	}

	// �p�b�h�擾
	static CInputPad* GetPad() {
		return m_pPad;
	}

	// �T�E���h�擾
	static CSound* GetSound() {
		return m_pSound;
	}

private:
	static CRenderer* m_pRenderer;		// �����_���[�Ǘ�
	static CInputKeyboard* m_pKeyboard;	// �L�[�{�[�h�Ǘ�
	static CInputPad* m_pPad;			// �p�b�h�Ǘ�
	static CSound* m_pSound;			// �T�E���h�Ǘ�
};

#endif // _MANAGER_H_
