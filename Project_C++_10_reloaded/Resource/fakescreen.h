//============================================================================
// 
// �^���X�N���[���A�w�b�_�t�@�C�� [fakescreen.h]
// Author : ���c����
// 
//============================================================================

#ifndef _FAKESCREEN_H_
#define _FAKESCREEN_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "game_manager.h"

//****************************************************
// �^���X�N���[���N���X
//****************************************************
class CFakeScreen
{
public:

	CFakeScreen();	// �R���X�g���N�^
	~CFakeScreen();	// �f�X�g���N�^

	HRESULT Init();								// �����ݒ�
	void Uninit();								// �I������
	void Update();								// �X�V����
	void Draw();								// �`�揈��
	void Create();								// ����
	void Release();								// ���
	void SetWave(CGameManager::PHASE phase);	// �E�F�[�u�ݒ�

	LPDIRECT3DTEXTURE9 GetTexture();	// �e�N�X�`�������擾
	LPDIRECT3DSURFACE9 GetSurface();	// �T�[�t�F�C�X�����擾

	static CFakeScreen* GetInstance();	// �擾

private:

	static const int SPLIT_ALONG_X_AXIS;	// X�������̕�����
	static const int SPLIT_ALONG_Y_AXIS;	// Y�������̕�����

	void CalcMesh();			// ���b�V�����̌v�Z
	HRESULT CreateVtxBuff();	// ���_�o�b�t�@�̐���
	HRESULT CreateIdxBuff();	// �C���f�b�N�X�o�b�t�@�̐���
	HRESULT CreateTex();		// �e�N�X�`���̐���
	void WaveIn();				// �E�F�[�u�C��
	void WaveOut();				// �E�F�[�u�A�E�g
	void SetVtx();				// ���_���̐ݒ�

	static CFakeScreen* m_pInstance;	// ���N���X���

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTex;			// �e�N�X�`�����̃|�C���^
	LPDIRECT3DSURFACE9 m_pSurface;		// �T�[�t�F�C�X���̃|�C���^
	int m_nNumVtx;						// ���_��
	int m_nNumPolygon;					// �|���S����
	int m_nNumDegenerated;				// �k�ރ|���S����
	int m_nNumIndex;					// �C���f�b�N�X���F
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_size;					// �T�C�Y
	CGameManager::PHASE m_NextPhase;	// ���̃t�F�[�Y
	bool m_bWaveIn;						// �E�F�[�u�C������
	bool m_bWaveOut;					// �E�F�[�u�A�E�g����
	float m_fBrightness;				// ���x
	float m_fPosDistortion;				// ���W�ϓ��p
	float m_fAddDistortion;				// �䂪�ݑ�����
};

#endif // _FAKESCREEN_H_