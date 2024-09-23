//============================================================================
// 
// �`���[�g���A���A�w�b�_�t�@�C�� [tutorial_manager.h]
// Author : ���c����
// 
//============================================================================

#ifndef _TUTORIAL_MANAGER_H_
#define _TUTORIAL_MANAGER_H	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "hand.h"
#include "input_ui.h"
#include "text.h"
#include "texture_manager.h"

//****************************************************
// �`���[�g���A���}�l�[�W���[�N���X
//****************************************************
class CTutorial_Manager
{
public:

	static void UpdateTutorial();					// �`���[�g���A���̍X�V
	static void DeleteInstance();					// �폜
	static CTexture_Manager::TYPE GetTexType();		// �e�N�X�`���^�C�v���擾

private:

	CTutorial_Manager();	// �f�t�H���g�R���X�g���N�^
	~CTutorial_Manager();	// �f�X�g���N�^

	void CreateText();		// �e�L�X�g�̐���
	void DeleteText();		// �e�L�X�g�̍폜
	void CheckPlayerPos();	// �v���C���[�̍��W���m�F
	
	static void CreateInstance();	// ����

	int m_nCnt09;						// 09�p�J�E���g
	CText* m_pText;						// �e�L�X�g�̃|�C���^
	CHand* m_apHand[2];					// ��Ƃ��̃|�C���^
	CInput_UI* m_apInput_UI[3];			// �C���v�b�gUI�̃|�C���^
	CTexture_Manager::TYPE m_TexType;	// �e�N�X�`���^�C�v��ێ�

	static CTutorial_Manager* m_pInstance;	// ���N���X�̃|�C���^
};

#endif	// _TUTORIAL_MANAGER_H