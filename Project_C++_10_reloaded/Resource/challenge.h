//============================================================================
// 
// �`�������W�A�w�b�_�t�@�C�� [challenge.h]
// Author : ���c����
// 
//============================================================================

#ifndef _CHALLENGE_H_
#define _CHALLENGE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "scene.h"

//****************************************************
// �`�������W�N���X
//****************************************************
class CChallenge : public CScene
{
public:

	CChallenge();			// �f�t�H���g�R���X�g���N�^
	~CChallenge() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��
};

#endif // _CHALLENGE_H_