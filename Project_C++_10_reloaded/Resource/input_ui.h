//============================================================================
// 
// �C���v�b�gUI�A�w�b�_�t�@�C�� [input_ui.h]
// Author : ���c����
// 
//============================================================================

#ifndef _INPUT_UI_H_
#define _INPUT_UI_H_// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_3D.h"
#include "texture_manager.h"

//****************************************************
// �C���v�b�gUI�N���X
//****************************************************
class CInput_UI : public CObject_3D
{
public:

	CInput_UI();			// �f�t�H���g�R���X�g���N�^
	~CInput_UI() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	void SetAppear();		// �o���ݒ�
	void SetDisappear();	// ���Őݒ�

	D3DXVECTOR3 GetPosTarget();					// �ڕW���W���擾
	void SetPosTarget(D3DXVECTOR3 posTarget);	// �ڕW���W��ݒ�

	D3DXVECTOR3 GetRotTarget();					// �ڕW�������擾
	void SetRotTarget(D3DXVECTOR3 rotTarget);	// �ڕW������ݒ�

	D3DXVECTOR3 GetSizeTarget();				// �ڕW�T�C�Y���擾
	void SetSizeTarget(D3DXVECTOR3 sizeTarget);	// �ڕW�T�C�Y��ݒ�

	static CInput_UI* Create(CTexture_Manager::TYPE TexType);	// ����

private:

	virtual void Appear();		// �o��
	virtual void Disappear();	// ����

	void UpdateCNT();	// CNT�̍X�V
	void UpdateBoard();	// �{�[�h�̍X�V
	void UpdateSpeech();	// �ӂ������̍X�V

	int m_nType;						// ���
	CTexture_Manager::TYPE m_TexType;	// �e�N�X�`���^�C�v��ێ�
	int m_nDuration;					// �ėp�J�E���g
	bool m_bAppear;						// �o���t���O
	bool m_bDisappear;					// ���Ńt���O
	D3DXVECTOR3 m_posTarget;			// �ڕW���W
	D3DXVECTOR3 m_rotTarget;			// �ڕW����
	D3DXVECTOR3 m_sizeTarget;			// �ڕW�T�C�Y
	D3DXCOLOR m_colTarget;				// �ڕW�F
};

#endif // _INPUT_UI_