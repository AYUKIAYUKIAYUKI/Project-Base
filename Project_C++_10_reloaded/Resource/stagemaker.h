//============================================================================
// 
// �X�e�[�W���[�J�[ [stagemaker.cpp]
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
// �X�e�[�W���[�J�[�N���X
//****************************************************
class CStageMaker
{
public:

	CStageMaker();	// �R���X�g���N�^
	~CStageMaker();	// �f�X�g���N�^

	void Init();	// �����ݒ�
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Create();	// ����
	void Release();	// ���
	void Import(std::string path);	// �X�e�[�W�ǂݍ���

	static CStageMaker* GetInstance();	// �擾

private:

	void Control();	// ����
	void Regist();	// �ݒu
	void Export();	// �X�e�[�W�����o��
	void Output(std::ofstream& file, D3DXVECTOR3 pos, std::string str);	// ��񏑂��o��

	static CStageMaker* m_pStageMaker;	// ���N���X���
};

#endif // _SATEGEMAKER_H_