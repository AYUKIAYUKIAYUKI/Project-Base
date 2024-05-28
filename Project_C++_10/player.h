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

	CPlayer();				// �R���X�g���N�^
	~CPlayer() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����

private:

	void Control();			// ����
	//void Scaling();		// �g�k
	//void Rotation();		// ��]
	//void Translation();	// �ړ�
	void GravityFall();		// �d�͉���
	void Collision();		// �����蔻��
	void AdjustPos();		// �ʒu�𒲐�
	void Animation();		// �A�j���[�V����
	
	int m_nCntTexChange;	// �e�N�X�`���ύX�Ǘ�
	D3DXVECTOR3 m_velocity;	// �����x
	D3DXVECTOR3 m_pos_tgt;	// �ڕW�ʒu
	D3DXVECTOR3 m_rot_tgt;	// �ڕW����
};

#endif // _PALYER_H_