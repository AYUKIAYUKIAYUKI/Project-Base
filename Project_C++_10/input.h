//============================================================================
// 
// ���͏����Ǘ��A�w�b�_�t�@�C�� [input.h]
// Author : ���c����
// 
//============================================================================

#ifndef _INPUT_H_
#define _INPUT_H_	// ��d�C���N���[�h�h�~

// �}�N����`
#define MAX_KEY	256	// �L�[�ő吔

// �C���v�b�g�N���X
class CInput
{
public:
	CInput();					// �R���X�g���N�^
	~CInput();					// �f�X�g���N�^
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// �����ݒ�
	virtual void Uninit();		// �I������
	virtual void Update() = 0;	// �X�V����

protected:
	static LPDIRECTINPUT8 m_Input;	// DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8 m_pDevice;	// ���̓f�o�C�X
};

// �L�[�{�[�h�N���X
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();			// �R���X�g���N�^
	~CInputKeyboard();			// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	bool GetPress(int nKey);	// �v���X���擾
	bool GetTrigger(int nKey);	// �g���K�[���擾

private:
	BYTE m_aKeyState[MAX_KEY];			// �v���X���
	BYTE m_aKeyStateTrigger[MAX_KEY];	// �g���K�[���
};

#endif // _INPUT_H_