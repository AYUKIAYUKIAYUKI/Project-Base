//============================================================================
// 
// �A�`�[�u�A�w�b�_�t�@�C�� [achievement.h]
// Author : ���c����
// 
//============================================================================

#ifndef _ACHIEVEMENT_H_
#define _ACHIEVEMENT_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// �A�`�[�u�N���X
//****************************************************
class CAchieve : public CObject_X
{
public:

	CAchieve();					// �f�t�H���g�R���X�g���N�^
	CAchieve(LAYER priority);	// �v���C�I���e�B�w��R���X�g���N�^
	~CAchieve() override;		// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CAchieve* Create(D3DXVECTOR3 pos);	// ����
};

#endif // _ACHIEVEMENT_H_