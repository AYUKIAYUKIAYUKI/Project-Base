//============================================================================
// 
// �o���A�}�l�[�W���[�A�w�b�_�t�@�C�� [barrier_manager.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BARRIER_MANAGER_H_
#define _BARRIER_MANAGER_H	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "barrier.h"
#include "barrier_anchor.h"

//****************************************************
// �o���A�}�l�[�W���[�N���X
//****************************************************
class CBarrier_Manager
{
public:

	CBarrier_Manager();		// �f�t�H���g�R���X�g���N�^
	~CBarrier_Manager();	// �f�X�g���N�^

	static void CreateStageBarrier();	// �X�e�[�W�Ƀo���A�𐶐�����
};

#endif	// _BARRIER_MANAGER_H