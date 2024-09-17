//============================================================================
// 
// �����A�w�b�_�t�@�C�� [crown.h]
// Author : ���c����
// 
//============================================================================

#ifndef _CROWN_H_
#define _CROWN_H_// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_UI.h"
#include "texture_manager.h"

//****************************************************
// �����N���X
//****************************************************
class CCrown : public CObject_UI
{
public:

	CCrown();			// �f�t�H���g�R���X�g���N�^
	~CCrown() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CCrown* Create();	// ����

private:

	void Appear() override;		// �o��
	void Disappear() override;	// ����
};

#endif // _TEXT_H_