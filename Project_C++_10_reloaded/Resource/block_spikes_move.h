//============================================================================
// 
// �Ƃ��ړ��u���b�N�A�w�b�_�t�@�C�� [block_spikes_move.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BLOCK_SPIKES_MOVE_H_
#define _BLOCK_SPIKES_MOVE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// �Ƃ��ړ��u���b�N�N���X
//****************************************************
class CBlockSpikesMove : public CObject_X
{
public:

	CBlockSpikesMove();					// �f�t�H���g�R���X�g���N�^
	CBlockSpikesMove(LAYER priority);	// �v���C�I���e�B�w��R���X�g���N�^
	~CBlockSpikesMove() override;		// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3 GetPosHold();			// �z�[���h���W���擾
	void SetPosHold(D3DXVECTOR3 pos);	// �z�[���h���W��ݒ�

	float GetAngleInit();					// �����p�x���擾
	void SetAngleInit(float fAngleInit);	// �����p�x��ݒ�

	float GetAngle();				// �p�x���擾
	void SetAngle(float fAngle);	// �p�x��ݒ�

	float GetAdder();				// �����ʂ��擾
	void SetAdder(float fAdder);	// �����ʂ�ݒ�

	float GetCoeff();				// ���f�W�����擾
	void SetCoeff(float fCoeff);	// ���f�W����ݒ�

	static CBlockSpikesMove* Create(D3DXVECTOR3 pos, float fAngle, float fAdder, float fCoeff);		// ����
	static void ResetAngleAll();																	// �p�x����ă��Z�b�g

private:

	void Translate();	// �ړ�

	D3DXVECTOR3 m_posHold;	// �z�[���h���W
	float m_fAngle;			// �p�x
	float m_fAngleInit;		// �����p�x
	float m_fAdder;			// ������
	float m_fCoeff;			// ���f�W��
};

#endif // _BLOCK_SPIKES_MOVE_H_