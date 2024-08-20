//============================================================================
// 
// �e�A�w�b�_�t�@�C�� [bullet.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BULLET_H_
#define _BULLET_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_billboard.h"

//****************************************************
// �e�N���X
//****************************************************
class CBullet : public CObject_billboard
{
public:

	CBullet();				// �f�t�H���g�R���X�g���N�^
	~CBullet() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����
};

#endif // _BULLET_H_