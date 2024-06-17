//============================================================================
// 
// �J�����A�w�b�_�t�@�C�� [camera.h]
// Author : ���c����
// 
//============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �J�����N���X
//****************************************************
class CCamera
{
public:

	CCamera();	// �R���X�g���N�^
	~CCamera();	// �f�X�g���N�^

	HRESULT Init();		// �����ݒ�
	void Update();		// �X�V����
	void SetCamera();	// �J�������Z�b�g
	
	D3DXVECTOR3 GetRot();	// �������擾

private:

	void Control();				// �J��������
	void Rotation();			// ��]
	void Translation();			// �ړ�
	void RestrictYaw();			// ���[�p�͈̔͂𐧌�
	void RestrictPitch();		// �s�b�`�p�͈̔͂𐧌�
	void CalcPosV();			// ���_�ʒu���Z�o
	void CalcPosR();			// �����_�ʒu���Z�o
	void CalcMtxProjection();	// �v���W�F�N�V�����s��v�Z
	void CalcMtxView();			// �r���[�s��v�Z

	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_posTarget;	// �ڕW�ʒu
	D3DXVECTOR3 m_posV;			// ���_�ʒu
	D3DXVECTOR3 m_posTargetV;	// �ڕW���_�ʒu
	D3DXVECTOR3 m_posR;			// �����_�ʒu
	D3DXVECTOR3 m_posTargetR;	// �ڕW�����_�ʒu
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_rotTarget;	// �ڕW����
	float m_fDistance;			// ���_ -> �����_�Ԃ̋���
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
};

#endif // _CAMERA_H_