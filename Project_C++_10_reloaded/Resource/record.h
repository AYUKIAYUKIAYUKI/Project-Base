//============================================================================
// 
// ���R�[�h�A�w�b�_�t�@�C�� [record.h]
// Author : ���c����
// 
//============================================================================

#ifndef _RECORD_H_
#define _RECORD_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_UI.h"
#include "number.h"
#include "text.h"
#include "game_manager.h"

//****************************************************
// ���R�[�h�N���X
//****************************************************
class CRecord : public CObject_UI
{
public:

	CRecord();				// �f�t�H���g�R���X�g���N�^
	~CRecord() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��
	void SetDisappearExtra();	// ��������\��

	static CRecord* Create();	// ����

private:

	static const int MAX_DIGIT = 3;	// �ő包��
	static const int MAX_BACK = 2;	// �߂�}�[�N�p�ő吔

	void Appear() override;			// �o��
	void Disappear() override;		// ����
	int ImportRecord(int nSelect);	// �x�X�g�^�C���̓ǂݍ���
	void LayoutBackAtSquare();		// �}�X�ڂɖ߂�}�[�N����ׂ�

	CText* m_pText;					// �e�L�X�g���
	CNumber* m_apNumber[MAX_DIGIT];	// �������
	CText* m_apBack[MAX_BACK];		// �߂�}�[�N�p�e�L�X�g���
};

#endif	// _RECORD_H_