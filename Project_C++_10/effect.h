//============================================================================
// 
// �G�t�F�N�g�A�w�b�_�t�@�C�� [effect.h]
// Author : ���c����
// 
//============================================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object2D.h"

//****************************************************
// �G�l�~�[�N���X
//****************************************************
class CEffect : public CObject2D
{
public:

	CEffect();				// �R���X�g���N�^
	~CEffect() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����

private:

	bool Progress();	// ���Ԍo��
};

#endif // _EFFECT_H_