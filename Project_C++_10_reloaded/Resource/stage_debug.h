//============================================================================
// 
// �X�e�[�W�f�o�b�O�A�w�b�_�t�@�C�� [stage_debug.h]
// Author : ���c����
// 
//============================================================================

#ifndef _STAGE_DEBUG_H_
#define _STAGE_DEBUG_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "scene.h"

//****************************************************
// �X�e�[�W�f�o�b�O�N���X
//****************************************************
class CStage_Debug : public CScene
{
public:

	CStage_Debug();// �R���X�g���N�^
	~CStage_Debug();// �f�X�g���N�^

private:

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��
};

#endif // _STAGE_DEBUG_H_