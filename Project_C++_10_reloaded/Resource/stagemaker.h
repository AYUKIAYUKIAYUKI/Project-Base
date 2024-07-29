//============================================================================
// 
// �X�e�[�W���[�J�[ [stagemaker.cpp]
// Author : ���c����
// 
//============================================================================

#ifndef _SATEGEMAKER_H_
#define _SATEGEMAKER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �X�e�[�W���[�J�[�N���X
//****************************************************
class CStageMaker final
{
public:

	void Create();	// ����
	void Init();	// �����ݒ�
	void Release();	// ���
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Import(std::string path);	// �X�e�[�W�ǂݍ���

	int& GetPatternRef();	// �z�u���̎�ނ��Q��

	static CStageMaker* GetInstance();	// �X�e�[�W���[�J�[���擾

private:

	CStageMaker();	// �R���X�g���N�^
	~CStageMaker();	// �f�X�g���N�^

	void Control();		// ����
	void Register();	// �ݒu
	void Export();		// �X�e�[�W�����o��
	void Output(std::ofstream& file, D3DXVECTOR3 pos, std::string str);	// ��񏑂��o��

	int m_nPattern;	// �z�u���̎�ނ�����

	static CStageMaker* m_pInstance;	// �X�e�[�W���[�J�[
};

#endif // _SATEGEMAKER_H_