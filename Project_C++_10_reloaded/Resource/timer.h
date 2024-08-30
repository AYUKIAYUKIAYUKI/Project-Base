//============================================================================
// 
// �^�C���A�w�b�_�t�@�C�� [timer.h]
// Author : ���c����
// 
//============================================================================

#ifndef _TIMER_H_
#define _TIMER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"
#include "number.h"
#include "game_manager.h"

//****************************************************
// �^�C���N���X
//****************************************************
class CTimer : public CObject_2D
{
public:

	CTimer();			// �f�t�H���g�R���X�g���N�^
	~CTimer() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CTimer* Create();						// ����
	static void SwitchControlByPahse(int nSelect);	// �t�F�[�Y�ɂ�铮��ؑ�
	static void ExportTimer(int nTimer);			// �^�C���̏����o��

private:

	static const int MAX_DIGIT = 4;	// �ő包��

	int ImportTimer(int nSelect);	// �^�C���̓ǂݍ���
	void Appear();					// �o��
	void Disappear();				// ����

	bool m_bAppear;					// �o���t���O
	bool m_bDisappear;				// ���Ńt���O
	int m_nCntFrame;				// �t���[���J�E���g
	int m_nTimer;					// �^�C�����
	D3DXVECTOR3 m_posTarget;		// �ڕW���W
	CNumber* m_apNumber[MAX_DIGIT];	// �������
};

#endif	// _TIMER_H_