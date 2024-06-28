//============================================================================
// 
// �t�F�[�h�J�ڏ����A�w�b�_�t�@�C�� [fade.h]
// Author : ���c����
// 
//============================================================================

#ifndef _FADE_H_
#define _FADE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "scene.h"

//****************************************************
// �t�F�[�h�N���X
//****************************************************
class CFade
{
public:

	CFade();	// �R���X�g���N�^
	~CFade();	// �f�X�g���N�^

	HRESULT Init();	// �����ݒ�
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��

	void SetFade(CScene::MODE mode);	// �t�F�[�h�ݒ�

private:

	void FadeIn();	// �t�F�[�h�C��
	void FadeOut();	// �t�F�[�h�A�E�g
	void SetVtx();	// ���_���̐ݒ�

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	CScene::MODE m_NextMode;			// ���̃��[�h
	bool m_bFadeIn;						// �t�F�[�h�C������
	bool m_bFadeOut;					// �t�F�[�h�A�E�g����
	float m_fBrightness;				// ���x
};

#endif // _FADE_H_