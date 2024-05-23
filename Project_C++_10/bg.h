//============================================================================
// 
// �w�i�A�w�b�_�t�@�C�� [bg.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BG_H_
#define _BG_H_	// ��d�C���N���[�h�h�~

// �C���N���[�h�t�@�C��
#include "object.h"

// �v���C���[�N���X
class CBg : public CObject
{
public:
	CBg();						// �R���X�g���N�^
	~CBg();						// �f�X�g���N�^
	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��
	static CBg* Create();		// ����

private:
	void Translation();	// �ړ�

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTex;			// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_pos;					// ���S���W
	D3DXVECTOR3 m_size;					// �傫��
	float m_fLength;					// �Ίp��
};

#endif // _BG_H_