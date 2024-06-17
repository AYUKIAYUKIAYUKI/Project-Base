//============================================================================
// 
// �w�i�A�w�b�_�t�@�C�� [bg.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BG_H_
#define _BG_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"

//****************************************************
// �w�i�N���X
//****************************************************
class CBg : public CObject_2D
{
public:

	CBg();				// �R���X�g���N�^
	~CBg() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CBg* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����

private:

	void PAKUPAKU();	// �p�N�p�N���܂�

	int m_nCntPAKU;	// �p�N�p�N��
	int m_nDelayPAKU;	// �p�N�p�N�x��
};

#endif // _BG_H_