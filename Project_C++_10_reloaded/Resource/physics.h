//============================================================================
// 
// �������Z�A�w�b�_�t�@�C�� [physics.h]
// Author : ���c����
// 
//============================================================================

#ifndef _PHISICS_H_
#define _PHISICS_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �������Z�N���X
//****************************************************
class CPhysics
{
public:

	void Gravity(D3DXVECTOR3& vec);	// �d�͗���

	bool Sphere(const D3DXVECTOR3& posSelf, const float& fRadiusSelf, const D3DXVECTOR3& posTarget, const float& fRadiusTarget);	// ���̂̏Փ˔���
	bool Cube(const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget);	// �����̂̏Փ˔���
	bool CubeResponse(D3DXVECTOR3& posDest, D3DXVECTOR3& velocity, const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget);	// �����o������

	static HRESULT Create();		// ����
	static void Release();			// �j��
	static CPhysics* GetInstance();	// �C���X�^���X���擾

private:

	static const float GRAVITY_FORCE;	// �d��

	CPhysics();		// �R���X�g���N�^
	~CPhysics();	// �f�X�g���N�^

	static CPhysics* m_pInstance;	// �C���X�^���X���
};

#endif // _PHISICS_H_