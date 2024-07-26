//============================================================================
// 
// �֗��֐��Q�A�w�b�_�t�@�C�� [utility.h]
// Author : ���c����
// 
//============================================================================

#ifndef _UTILITY_H_
#define _UTILITY_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �֗��֐��Q�N���X
//****************************************************
class CUtility final
{
public:

	HRESULT Init();	// �����ݒ�
	void Release();	// �j��

	static CUtility* GetInstance();	// �֗��֐��Q���擾

	// �d�͗���
	void Gravity(D3DXVECTOR3& vec);

	// ���̂̏Փ˔���
	bool OnlySphere(const D3DXVECTOR3& posSelf, const float& fRadiusSelf, const D3DXVECTOR3& posTarget, const float& fRadiusTarget);

	// ���̂Ɨ����̂̏Փ˔���
	bool SphereAndCube(const D3DXVECTOR3& posSph, const float& fRadius, const D3DXVECTOR3& posCube, const D3DXVECTOR3& size);

	// �����̂̏Փ˔���
	bool OnlyCube(const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget);

	// �����o������
	bool CubeResponse(D3DXVECTOR3& posDest, D3DXVECTOR3& velocity, const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget);

private:

	static const float GRAVITY_FORCE;	// �d��

	CUtility();		// �R���X�g���N�^
	~CUtility();	// �f�X�g���N�^

	void Create();	// ����
	void Uninit();	// �I������

	static CUtility* m_pInstance;	// �֗��֐��Q
};

#endif // _UTILITY_H_