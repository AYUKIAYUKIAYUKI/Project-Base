//============================================================================
// 
// [KARIHAIKEI.h]
// Author : ���c����
// 
//============================================================================

#ifndef _KARIHAIKEI_H_
#define _KARIHAIKEI_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// 
//****************************************************
class KARIHAIKEI : public CObject_X
{
public:

	KARIHAIKEI();			// �f�t�H���g�R���X�g���N�^
	~KARIHAIKEI() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static KARIHAIKEI* Create();	// ����
};

#endif // _KARIHAIKEI_H_