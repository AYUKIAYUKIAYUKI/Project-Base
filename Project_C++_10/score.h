//============================================================================
// 
// �X�R�A�A�w�b�_�t�@�C�� [score.h]
// Author : ���c����
// 
//============================================================================

#ifndef _SCORE_H_
#define _SCORE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object2D.h"

//****************************************************
// �X�R�A�N���X
//****************************************************
class CScore : public CObject2D
{
public:

	CScore();			// �R���X�g���N�^
	~CScore() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CScore* Create();	// ����

private:

	void Translate();	// �ړ�
	void Progress();	// ���Ԍo��
};

#endif // _SCORE_H_