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

	CCamera();	// �f�t�H���g�R���X�g���N�^
	~CCamera();	// �f�X�g���N�^

	HRESULT Init();		// �����ݒ�
	void Update();		// �X�V����
	void SetCameraBG();	// �w�i�p�J�������Z�b�g
	void SetCamera();	// �J�������Z�b�g
	
	D3DXVECTOR3 GetPos();			// �ʒu���擾
	void SetPos(D3DXVECTOR3 pos);	// �ʒu��ݒ�

	D3DXVECTOR3 GetPosTarget();					// �ڕW�ʒu���擾
	void SetPosTarget(D3DXVECTOR3 posTarget);	// �ڕW�ʒu��ݒ�

	float GetDistance();				// �ԋ������擾
	void SetDistance(float fDistance);	// �ԋ�����ݒ�

	D3DXVECTOR3 GetRot();	// �������擾

private:

	//****************************************************
	// �A���J�[�|�C���g�\���̂��`
	//****************************************************
	struct AnchorPoint
	{
		D3DXVECTOR3 pos;		// ���W
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 stepRot;	// ����������
		D3DXVECTOR3 stepPos;	// ���W������
		int nNumStep;			// �X�e�b�v��
		bool bSet;				// �����ʂ̃Z�b�g�t���O
	};

	void ImportAnchorPoint();	// �A���J�[�|�C���g��ǂݍ���
	void UpdateScreen();		// �X�N���[���p�̍X�V
	void Control();				// �J��������
	void Rotation();			// ��]
	void Translation();			// �ړ�
	void RestrictYaw();			// ���[�p�͈̔͂𐧌�
	void RestrictPitch();		// �s�b�`�p�͈̔͂𐧌�
	void CalcPosV();			// ���_�ʒu���Z�o
	void CalcPosR();			// �����_�ʒu���Z�o
	void UpdateBG();			// �w�i�p�̍X�V
	void CalcMtxProjection();	// �v���W�F�N�V�����s��v�Z
	void CalcMtxView();			// �r���[�s��v�Z

	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_posTarget;					// �ڕW�ʒu
	D3DXVECTOR3 m_posV;							// ���_�ʒu
	D3DXVECTOR3 m_posTargetV;					// �ڕW���_�ʒu
	D3DXVECTOR3 m_posR;							// �����_�ʒu
	D3DXVECTOR3 m_posTargetR;					// �ڕW�����_�ʒu
	D3DXVECTOR3 m_rot;							// ����
	D3DXVECTOR3 m_rotTarget;					// �ڕW����
	float m_fDistance;							// ���_ -> �����_�Ԃ̋���
	std::vector<AnchorPoint> m_vAnchorPoint;	// �A���J�[�|�C���g
	D3DXVECTOR3 m_posBG;						// �w�i�ʒu
	D3DXVECTOR3 m_posTargetBG;					// �w�i�ڕW�ʒu
	D3DXVECTOR3 m_posVBG;						// �w�i���_�ʒu
	D3DXVECTOR3 m_posRBG;						// �w�i�����_�ʒu
	D3DXVECTOR3 m_rotBG;						// �w�i����
	D3DXVECTOR3 m_rotTargetBG;					// �w�i�ڕW����
	float m_fDistanceBG;						// �w�i���_ -> �����_�Ԃ̋���
	D3DXVECTOR3 m_vecU;							// ������x�N�g��
	D3DXMATRIX m_mtxProjection;					// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;						// �r���[�}�g���b�N�X
	float m_fAdjust;							// ���Փx��
};

#endif // _CAMERA_H_