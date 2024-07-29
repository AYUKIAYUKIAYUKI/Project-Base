//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �T�E���h�N���X
//****************************************************
class CSound
{
public:

	//****************************************************
	// �T�E���h�ꗗ
	//****************************************************
	enum SOUND_LABEL
	{
		SOUND_LABEL_00 = 0,	// �_�~�[
		SOUND_LABEL_MAX,
	};

	CSound();	// �R���X�g���N�^
	~CSound();	// �f�X�g���N�^

	HRESULT Init(HWND hWnd);				// �����ݒ�
	void Uninit(void);						// �I������
	HRESULT PlaySound(SOUND_LABEL label);	// �Đ�
	void Stop(SOUND_LABEL label);			// ��~ (�I��)
	void Stop(void);						// ��~ (�S��)
	void SetVol(int label);					// ���ʂ�ݒ�
	float GetVol(int label);				// ���ʂ��擾

private:

	//****************************************************
	// �T�E���h���̍\����
	//****************************************************
	struct SOUNDINFO
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
		float fVolume;			// ����
	};

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);	// �`�����N�̃`�F�b�N
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// �`�����N�f�[�^�̓ǂݍ���

	IXAudio2* m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX];				// �T�E���h��� (��)
};

#endif	// _SOUND_H_
