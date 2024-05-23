//============================================================================
// 
// �v���C���[�A�w�b�_�t�@�C�� [player.h]
// Author : ���c����
// 
//============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object2D.h"

//****************************************************
// �v���C���[�N���X
//****************************************************
class CPlayer : public CObject2D
{
public:
	CPlayer();					// �R���X�g���N�^
	~CPlayer();					// �f�X�g���N�^
	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����

private:
	void Scaling();		// �g�k
	void Rotation();	// ��]
	void Translation();	// �ړ�
	void Animation();	// �A�j���[�V����

	int m_nCntTexChange;	// �e�N�X�`���ύX�Ǘ�
	int m_nCntTexPattern;	// �e�N�X�`���p�^�[���Ǘ�
	D3DXVECTOR3 m_pos;		// ���S���W
	D3DXVECTOR3 m_rot;		// ��]��
	float m_fAngle;			// �p�x
	D3DXVECTOR3 m_size;		// �傫��
	float m_fLength;		// �Ίp��
};

#endif // _PALYER_H_