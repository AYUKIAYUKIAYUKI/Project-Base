//============================================================================
// 
// �S�[���A�w�b�_�t�@�C�� [goal.h]
// Author : ���c����
// 
//============================================================================

#ifndef _GOAL_H_
#define _GOAL_H_// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// �S�[���N���X
//****************************************************
class CGoal : public CObject_X
{
public:

	CGoal();			// �f�t�H���g�R���X�g���N�^
	~CGoal() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3 GetActualPos();			// �����W���擾
	void SetActualPos(D3DXVECTOR3 Pos);	// �����W��ݒ�

	static CGoal* Create(D3DXVECTOR3 Pos);	// ����

private:

	D3DXVECTOR3 m_ActualPos;	// �����W
	D3DXVECTOR3 m_PosTarget;	// �ڕW���W
	D3DXVECTOR3 m_RotTarget;	// �ڕW����
	float m_fScaleTarget;		// �ڕW�k��
};

#endif // _GOAL_H_