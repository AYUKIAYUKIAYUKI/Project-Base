//============================================================================
// 
// �}�X�ځA�w�b�_�t�@�C�� [square.h]
// Author : ���c����
// 
//============================================================================

#ifndef _SQUARE_H_
#define _SQUARE_H_// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_UI.h"
#include "number.h"

//****************************************************
// �}�X�ڃN���X
//****************************************************
class CSquare : public CObject_UI
{
public:

	CSquare();				// �f�t�H���g�R���X�g���N�^
	~CSquare() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static void ControlAll(int nSelect);		// �}�X�ڂ𓮍�
	static void DisappearAll();					// �}�X�ڂ�S����
	//static void LineUpAll(int nSelect);		// �}�X�ڂ���ׂ� (�s�K�v)
	static CSquare* Create(D3DXVECTOR3 pos);	// ����

private:

	static const int MAX_DIGIT = 2;	// �ő包��

	void Appear() override;		// �o��
	void Disappear() override;	// ����
	void DisappearNumber();		// ����������

	CNumber* m_apNumber[MAX_DIGIT];	// ����
};

#endif // _SQUARE_H_