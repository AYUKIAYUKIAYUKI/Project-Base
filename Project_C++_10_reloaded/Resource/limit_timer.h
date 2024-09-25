//============================================================================
// 
// ���~�b�g�^�C���A�w�b�_�t�@�C�� [limit_timer.h]
// Author : ���c����
// 
//============================================================================

#ifndef _LIMIT_TIMER_H_
#define _LIMIT_TIMER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_UI.h"
#include "number.h"
#include "text.h"
#include "game_manager.h"

//****************************************************
// ���~�b�g�^�C���N���X
//****************************************************
class CLimit_Timer : public CObject_UI
{
public:

	CLimit_Timer();				// �f�t�H���g�R���X�g���N�^
	~CLimit_Timer() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CLimit_Timer* Create();	// ����

private:

	static const int MAX_DIGIT = 2;	// �ő包��

	void Decrement();				// ���Ԍ���
	void TimerReset();				// ���ԃ��Z�b�g
	void Appear() override;			// �o��
	void Disappear() override;		// ����

	int m_nCntFrame;				// �t���[���J�E���g
	int m_nTimer;					// �^�C�����
	CText* m_pText;					// �e�L�X�g���
	CNumber* m_apNumber[MAX_DIGIT];	// �������
};

#endif	// _LIMIT_TIMER_H_