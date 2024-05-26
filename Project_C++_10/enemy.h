//============================================================================
// 
// �G�l�~�[�A�w�b�_�t�@�C�� [enemy.h]
// Author : ���c����
// 
//============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object2D.h"

//****************************************************
// �G�l�~�[�N���X
//****************************************************
class CEnemy : public CObject2D
{
public:

	CEnemy();				// �R���X�g���N�^
	~CEnemy() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����

private:

	void Rotation();	// ��]
	void Translation();	// �ړ�

	D3DXVECTOR3 m_rot_tgt;	// �ڕW����
};

#endif // _ENEMY_H_