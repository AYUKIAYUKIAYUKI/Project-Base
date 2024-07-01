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
#include "object_X.h"

//****************************************************
// �O���錾
//****************************************************
class CPlayerStateManager;	// �v���C���[��ԊǗ��N���X

//****************************************************
// �v���C���[�N���X
//****************************************************
class CPlayer : public CObject_X
{
public:

	CPlayer();				// �R���X�g���N�^
	~CPlayer() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3 GetVelocity();				// �����x���擾
	void SetVelocity(D3DXVECTOR3 velocity);	// �����x��ݒ�

	float GetAngleFlying();						// ��s�������擾
	void SetAngleFlying(float fAngleFlying);	// ��s������ݒ�

	D3DXVECTOR3 GetPosTarget();					// �ڕW�ʒu���擾
	void SetPosTarget(D3DXVECTOR3 posTarget);	// �ڕW�ʒu��ݒ�

	D3DXVECTOR3 GetRotTarget();					// �ڕW�������擾
	void SetRotTarget(D3DXVECTOR3 rotTarget);	// �ڕW������ݒ�

	CPlayerStateManager* GetStateManager();	// ��ԊǗ��擾

	static CPlayer* Create(D3DXVECTOR3 pos);	// ����

	bool AdjustPos();	// �ʒu�𒲐�

private:

	bool Collision();	// �����蔻��

	CPlayerStateManager* m_pStateManager;	// ��ԊǗ�

	D3DXVECTOR3 m_velocity;		// �����x
	D3DXVECTOR3 m_posTarget;	// �ڕW�ʒu
	D3DXVECTOR3 m_rotTarget;	// �ڕW����
	float m_fAngleFlying;		// ��s����
};

#endif // _PALYER_H_