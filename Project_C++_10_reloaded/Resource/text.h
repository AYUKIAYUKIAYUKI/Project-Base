//============================================================================
// 
// �e�L�X�g�A�w�b�_�t�@�C�� [text.h]
// Author : ���c����
// 
//============================================================================

#ifndef _TEXT_H_
#define _TEXT_H_// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_UI.h"
#include "texture_manager.h"

//****************************************************
// �e�L�X�g�N���X
//****************************************************
class CText : public CObject_UI
{
public:

	CText();			// �f�t�H���g�R���X�g���N�^
	~CText() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CText* Create(CTexture_Manager::TYPE tex);	// ����

private:

	void Appear() override;		// �o��
	void Disappear() override;	// ����
};

#endif // _TEXT_H_