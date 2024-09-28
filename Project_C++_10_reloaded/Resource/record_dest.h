//============================================================================
// 
// �j��L�^�A�w�b�_�t�@�C�� [record_dest.h]
// Author : ���c����
// 
//============================================================================

#ifndef _RECORD_DEST_H_
#define _RECORD_DEST_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_UI.h"
#include "number.h"
#include "text.h"

//****************************************************
// �j��L�^�N���X
//****************************************************
class CRecord_Dest : public CObject_UI
{
public:

	CRecord_Dest();				// �f�t�H���g�R���X�g���N�^
	~CRecord_Dest() override;	// �f�X�g���N�^

	HRESULT Init() override;		// �����ݒ�
	void Uninit() override;			// �I������
	void Update() override;			// �X�V����
	void Draw() override;			// �`�揈��
	void ResetCntDest();			// �j��L�^�����Z�b�g
	void SetDisappearBestAndUI();	// �ō��L�^�\���E�I����������
	void SetTimeUp();				// ���Ԑ؂ꔻ��

	static CRecord_Dest* Create();	// ����
	static void AddDest();			// �j��L�^�̑���
	static void ExportRecord();		// �j��L�^�̏����o��

private:

	static const int MAX_DIGIT = 3;	// �ő包��

	void Appear() override;			// �o��
	void Disappear() override;		// ����
	int ImportBestRecord();			// �ō��L�^�̓ǂݍ���

	int m_nCntDest;						// �j��L�^
	bool m_bTimeUp;						// ���Ԑ؂ꔻ��
	CText* m_pDestText;					// ����e�L�X�g
	CNumber* m_apDestNum[MAX_DIGIT];	// ���񐔎����
	CText* m_pBestText;					// �ō��e�L�X�g
	CNumber* m_apBestNum[MAX_DIGIT];	// �ō��������
	CText* m_apUI[3];					// ���U���g�pUI
	CText* m_pFailed;					// ���s���p�e�L�X�g
};

#endif	// _RECORD_DEST_H_