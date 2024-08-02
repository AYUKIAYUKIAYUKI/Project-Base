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

	// ���Z����
	template <typename T> bool DecrementUntilGone(T& base, T value);

	// ��Z����
	//template <typename T> bool DecayUntilGone(T& bas, T value);

	// ��������
	template <typename T> T GetRandomValue();

	// �_�E���L���X�g
	template <typename T1, typename T2> T1* DownCast(T2* pBase);

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

//============================================================================
// ���Z����
//============================================================================
template <typename T> bool CUtility::DecrementUntilGone(T& base, T value)
{
	if (base > 0)
	{
		base += value;

		return false;
	}

	return true;
}

//============================================================================
// ��������
//============================================================================
template <typename T> T CUtility::GetRandomValue()
{
	// ���l�̎��͈͂�ݒ�
	const int nRange = 180;

	// �{�͈̔͂��烉���_���Ȑ����𐶐�
	int random{ rand() % (nRange * 2) };

	// ���Ƃ͈̔͂𒴂��Ă����ꍇ�����𔽓]
	if (random > nRange)
	{
		random %= nRange;
		random *= -1;
	}

	// �������w�肳�ꂽ�^�ɃL���X�g
	return static_cast<T>(random);
}

//============================================================================
// �_�E���L���X�g
//============================================================================
template <typename T1, typename T2> T1* CUtility::DownCast(T2* pBase)
{
	// �����̃I�u�W�F�N�g���w�肳�ꂽ�N���X�Ƀ_�E���L���X�g
	T1* pObj{ dynamic_cast<T1*>(pBase) };

	// �_�E���L���X�g���s
	if (!pObj)
	{
		assert(false);
	}

	return pObj;
}

#endif // _UTILITY_H_