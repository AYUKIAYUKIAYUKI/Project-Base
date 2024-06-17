//============================================================================
// 
// �p�[�e�B�N���A�w�b�_�t�@�C�� [particle.h]
// Author : ���c����
// 
//============================================================================

#ifndef _PARTICLE_H_
#define _PARTICLE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_2D.h"

//****************************************************
// �p�[�e�B�N���N���X
//****************************************************
class CParticle : public CObject_2D
{
public:

	CParticle();			// �R���X�g���N�^
	~CParticle() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fFlyAngle);	// ����

private:

	void Translate();	// �ړ�
	bool Progress();	// ���Ԍo��

	float m_fFlyAngle;	// ��Ԋp�x
};

#endif // _EFFECT_H_