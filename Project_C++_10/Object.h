//============================================================================
// 
// �I�u�W�F�N�g�Ǘ��A�w�b�_�t�@�C�� [Object.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_	// ��d�C���N���[�h�h�~

// �C���N���[�h�t�@�C��
#include "main.h"

// �I�u�W�F�N�g�N���X
class CObject
{
private:
	static const int MAX_OBJ = 64;		// �I�u�W�F�N�g�ő吔

public:
	CObject();					// �R���X�g���N�^
	virtual ~CObject() = 0;		// �f�X�g���N�^
	virtual HRESULT Init() = 0;	// �����ݒ�
	virtual void Uninit() = 0;	// �I������
	virtual void Update() = 0;	// �X�V����
	virtual void Draw() = 0;	// �`�揈��
	static void ReleaseAll();	// �S�I�u�W�F�N�g�������
	static void UpdateAll();	// �S�I�u�W�F�N�g�X�V����
	static void DrawAll();		// �S�I�u�W�F�N�g�`�揈��

protected:
	void Release();	// �ʉ������

private:
	static CObject* m_apObject[MAX_OBJ];	// �I�u�W�F�N�g�Ǘ�
	int m_nID;								// �������g��ID
	static int m_nNumAll;					// �I�u�W�F�N�g����
};

#endif // _RENDERER_H_