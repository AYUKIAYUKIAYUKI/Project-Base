//============================================================================
// 
// �G�A�w�b�_�t�@�C�� [enemy.h]
// Author : ���c����
// 
//============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// �G�l�~�[�N���X
//****************************************************
class CEnemy : public CObject_X
{
public:

	CEnemy();				// �f�t�H���g�R���X�g���N�^
	CEnemy(LAYER priority);	// �v���C�I���e�B�w��R���X�g���N�^
	~CEnemy() override;		// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��
	bool Collision();			// �����蔻��

	static CEnemy* Create(D3DXVECTOR3 pos);		// ����

private:

	int m_nCast;	// �U���Ԋu
};

#endif // _ENEMY_H_