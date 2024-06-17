//============================================================================
// 
// �����A�w�b�_�t�@�C�� [number.h]
// Author : ���c����
// 
//============================================================================

#ifndef _NUMBER_H_
#define _NUMBER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"

//****************************************************
// �i���o�[�N���X
//****************************************************
class CNumber : public CObject_2D
{
public:

	CNumber();				// �R���X�g���N�^
	~CNumber() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��
	
	void SetNumber(int nNum);	// ������ݒ�

	static CNumber* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����

private:

	void Animation();	// �A�j���[�V����

	int m_nNum;	// �����̊��蓖��
};

#endif // _NUMBER_H_