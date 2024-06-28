//============================================================================
// 
// �X�^�[�g�A�w�b�_�t�@�C�� [start.h]
// Author : ���c����
// 
//============================================================================

#ifndef _START_H_
#define _START_H_// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// �X�^�[�g�N���X
//****************************************************
class CStart : CObject_X
{
public:

	CStart();			// �R���X�g���N�^
	~CStart() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3* GetPos();	// �ʒu�����擾

	static CStart* Create(D3DXVECTOR3 pos);	// ����

private:

	D3DXVECTOR3 m_pos;	// ���g�̈ʒu��ێ�
};

#endif // _START_H_