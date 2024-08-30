////============================================================================
//// 
//// �X�R�A�A�w�b�_�t�@�C�� [score.h]
//// Author : ���c����
//// 
////============================================================================
//
//#ifndef _SCORE_H_
//#define _SCORE_H_	// ��d�C���N���[�h�h�~
//
////****************************************************
//// �C���N���[�h�t�@�C��
////****************************************************
//#include "object.h"
//#include "number.h"
//
////****************************************************
//// �X�R�A�N���X
////****************************************************
//class CScore : public CObject
//{
//public:
//
//	CScore();			// �R���X�g���N�^
//	~CScore() override;	// �f�X�g���N�^
//
//	HRESULT Init() override;	// �����ݒ�
//	void Uninit() override;		// �I������
//	void Update() override;		// �X�V����
//	void Draw() override;		// �`�揈��
//
//	int GetScore();				// ���݂̃X�R�A�擾
//	void SetScore(int nScore);	// ���݂̃X�R�A�ݒ�
//
//	static CScore* Create(D3DXVECTOR3 pos, float fSpan);	// ����
//
//private:
//
//	void Adjust();		// �ϓ�����
//	void Animation();	// �A�j���[�V����
//
//	static const int MAX_DIGIT = 6;			// ����
//	static const int MAX_SCORE = 999999;	// ����l
//
//	static CNumber* m_apNumber[MAX_DIGIT];	// �����Ǘ�
//
//	int m_nScore;		// ���݂̃X�R�A
//	int m_nScore_old;	// �ߋ��̃X�R�A
//	D3DXVECTOR3 m_pos;	// ����̐擪�ʒu
//	float m_fSpan;		// ����̔z�u�Ԋu
//};
//
//#endif // _SCORE_H_