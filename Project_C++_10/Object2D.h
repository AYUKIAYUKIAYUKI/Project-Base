//============================================================================
// 
// 2D�I�u�W�F�N�g�Ǘ��A�w�b�_�t�@�C�� [object2D.h]
// Author : ���c����
// 
//============================================================================

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_	// ��d�C���N���[�h�h�~

// �C���N���[�h�t�@�C��
#include "object.h"

// 2D�I�u�W�F�N�g�Ǘ��N���X
class CObject2D : public CObject
{
public:
	CObject2D();				// �R���X�g���N�^
	~CObject2D();				// �f�X�g���N�^
	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��
	static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTex;			// �e�N�X�`���̃|�C���^
	int m_nCntTexChange;				// �e�N�X�`���ύX�Ǘ�
	int m_nCntTexPattern;				// �e�N�X�`���p�^�[���Ǘ�
	D3DXVECTOR3 m_pos;					// ���S���W
	D3DXVECTOR3 m_rot;					// ��]��
	float m_fAngle;						// �p�x
	D3DXVECTOR3 m_size;					// �傫��
	float m_fLength;					// �Ίp��
};

#endif // _OBJECT2D_H_