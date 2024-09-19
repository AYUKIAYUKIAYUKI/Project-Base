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
#include "text.h"

//****************************************************
// �`���[�g���A���}�l�[�W���[�N���X
//****************************************************
class CTutorial_Manager
{
public:

	static void UpdateTutorial();	// �`���[�g���A���̍X�V
	static void DeleteInstance();	// �폜

private:

	CTutorial_Manager();	// �f�t�H���g�R���X�g���N�^
	~CTutorial_Manager();	// �f�X�g���N�^

	void CreateText();		// �e�L�X�g�̐���
	void DeleteText();		// �e�L�X�g�̍폜
	void CheckPlayerPos();	// �v���C���[�̍��W���m�F
	
	static void CreateInstance();	// ����

	CText* m_pText;	// �e�L�X�g�̃|�C���^

	static CTutorial_Manager* m_pInstance;	// ���N���X�̃|�C���^
};

#endif	// _TUTORIAL_MANAGER_H