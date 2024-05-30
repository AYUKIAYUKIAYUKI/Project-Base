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

	static const int TEXTURE_DIVIDE_U;	// �e�N�X�`����U����������
	static const int TEXTURE_DIVIDE_V;	// �e�N�X�`����V����������
	static const float MAX_VELOCITY;	// �����x���
	static const float JUMP_FORCE;		// �W�����v��
	static const float BRAKING_FORCE;	// ������
	static const float GRAVITY_FORCE;	// �d��

	void Control();			// ����
	//void Scaling();		// �g�k
	//void Rotation();		// ��]
	//void Translation();	// �ړ�
	void Braking();			// ��������
	void GravityFall();		// �d�͉���
	void AdjustPos();		// �ʒu�𒲐�
	void Collision();		// �����蔻��
	void Animation();		// �A�j���[�V����
	
	int m_nCntTexChange;	// �e�N�X�`���ύX�Ǘ�
	int m_nLeftNumJump;		// �W�����v�\��
	D3DXVECTOR3 m_velocity;	// �����x
	D3DXVECTOR3 m_pos_tgt;	// �ڕW�ʒu
	D3DXVECTOR3 m_rot_tgt;	// �ڕW����
};

#endif // _PALYER_H_