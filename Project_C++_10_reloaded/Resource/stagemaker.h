//============================================================================
// 
// �X�e�[�W�쐬 [stagemaker.cpp]
// Author : ���c����
// 
//============================================================================

#ifndef _SATEGEMAKER_H_
#define _SATEGEMAKER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************}
#include "block.h"

//****************************************************
// �X�e�[�W�쐬�N���X
//****************************************************
class CStageMaker
{
public:

	CStageMaker();	// �R���X�g���N�^
	~CStageMaker();	// �f�X�g���N�^

	HRESULT Init();	// �����ݒ�
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Import();	// �X�e�[�W�ǂݍ���

	D3DXVECTOR3 GetPos();	// �ʒu���擾

	static HRESULT Create();			// ����
	static void Release();				// �j��
	static CStageMaker* GetInstance();	// �X�e�[�W�쐬�N���X�擾

private:

	void Control();	// ����
	void Export();	// �X�e�[�W�����o��

	static CStageMaker* m_pStageMaker;	// ���g�̃C���X�^���X
};

#endif // _SATEGEMAKER_H_