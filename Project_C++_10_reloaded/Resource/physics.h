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

	void Gravity();				// �d�͗���
	bool Collision_Sphere();	// ���̂̏Փ˔���
	bool Collision_Cube();		// �����̂̏Փ˔���
	bool Collision_Response();	// �����o������

	static HRESULT Create();	// ����
	static void Release();		// �j��
	static CPhysics* GetInstance();	// �C���X�^���X���擾

private:

	CPhysics();		// �R���X�g���N�^
	~CPhysics();	// �f�X�g���N�^

	static CPhysics* m_pInstance;	// �C���X�^���X���
};

#endif // _PHISICS_H_