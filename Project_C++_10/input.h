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

// �v���v���Z�b�T�f�B���N�e�B�u
#define LEFT_JOYSTICK_CONVERT 0	// ���X�e�B�b�N���͂�ϊ�

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

// �p�b�h�N���X
class CInputPad : public CInput
{
public:
	// �p�b�h�̃L�[����
	enum JOYKEY
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGHT,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_L3,
		JOYKEY_R3,
		JOYKEY_L,
		JOYKEY_R,
		JOYKEY_NONE1,
		JOYKEY_NONE2,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX,
	};

	// �X�e�B�b�N�̌X�����
	typedef struct
	{
		SHORT X;
		SHORT Y;
	} JOYSTICK;

	CInputPad();					// �R���X�g���N�^
	~CInputPad();					// �f�X�g���N�^
	HRESULT Init();					// �����ݒ�
	void Uninit() override;			// �I������
	void Update() override;			// �X�V����
	bool GetPress(JOYKEY Key);		// �v���X���擾
	bool GetTrigger(JOYKEY Key);	// �g���K�[���擾
	JOYSTICK GetJoyStickL();		// ���X�e�B�b�N�̌X���擾
	JOYSTICK GetJoyStickR();		// �E�X�e�B�b�N�̌X���擾

private:
	void AdjustJoyStick();	// �X�e�B�b�N�̒���

	XINPUT_STATE m_aKeyState;			// �v���X���
	XINPUT_STATE m_aKeyStateTrigger;	// �g���K�[���
};

#endif // _INPUT_H_