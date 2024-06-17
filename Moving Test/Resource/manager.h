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
#include "camera.h"
#include "light.h"
#include "input.h"
#include "sound.h"
#include "scene.h"

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

	static CRenderer* GetRenderer();			// �����_���[�擾
	static CCamera* GetCamera();				// �J�����擾
	static CLight* GetLight();					// ���C�g�擾
	static CInputKeyboard* GetKeyboard();		// �L�[�{�[�h�擾
	static CInputPad* GetPad();					// �p�b�h�擾
	static CSound* GetSound();					// �T�E���h�擾
	static CScene* GetScene();					// �V�[���擾
	static void SetScene(CScene::MODE mode);	// �V�[���ݒ�

private:

	static CRenderer* m_pRenderer;		// �����_���[�Ǘ�
	static CCamera* m_pCamera;			// �J�����Ǘ�
	static CLight* m_pLight;			// ���C�g�Ǘ�
	static CInputKeyboard* m_pKeyboard;	// �L�[�{�[�h�Ǘ�
	static CInputPad* m_pPad;			// �p�b�h�Ǘ�
	static CSound* m_pSound;			// �T�E���h�Ǘ�
	static CScene* m_pScene;			// �V�[���Ǘ�
};

#endif // _MANAGER_H_