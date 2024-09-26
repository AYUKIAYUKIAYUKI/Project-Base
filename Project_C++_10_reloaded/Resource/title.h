//============================================================================
// 
// �^�C�g���A�w�b�_�t�@�C�� [title.h]
// Author : ���c����
// 
//============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "scene.h"

// �^�C�g���\���p
#include "bg.h"
#include "text.h"

//****************************************************
// �^�C�g���N���X
//****************************************************
class CTitle : public CScene
{
public:

	CTitle();			// �R���X�g���N�^
	~CTitle() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

private:

	//****************************************************
	// UI�^�C�v
	//****************************************************
	enum class UI_TYPE
	{
		NORMAL = 0,
		CHALLENGE,
		CURSOR,
		MAX
	};

	CBg* m_pBg;										// �w�i���̃|�C���^
	CText* m_pUI[static_cast<int>(UI_TYPE::MAX)];	// UI�p
	int m_nSelect;									// ���[�h�I�����
};

#endif // _TITLE_H_