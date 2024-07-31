//============================================================================
// 
// �֗��֐��Q [utility.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "utility.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
const float CUtility::GRAVITY_FORCE = -0.15f;	// �d��
CUtility* CUtility::m_pInstance = nullptr;		// �֗��֐��Q

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CUtility::Init()
{
	return S_OK;
}

//============================================================================
// �j��
//============================================================================
void CUtility::Release()
{
	if (m_pInstance != nullptr)
	{
		// �I������
		m_pInstance->Uninit();

		// ���������
		delete m_pInstance;	

		// �|�C���^��������
		m_pInstance = nullptr;
	}
}

//============================================================================
// �֗��֐��Q���擾
//============================================================================
CUtility* CUtility::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// ����
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// �J�E���g�_�E��
//============================================================================
bool CUtility::CountDown(int& nDuration)
{
	if (nDuration > 0)
	{
		nDuration--;

		return false;
	}

	return true;
}

//============================================================================
// �d�͗���
//============================================================================
void CUtility::Gravity(D3DXVECTOR3& vec)
{
	vec.y += GRAVITY_FORCE;
}

//============================================================================
// ���`�̏Փ˔���
//============================================================================
bool CUtility::OnlySphere(const D3DXVECTOR3& posSelf, const float& fRadiusSelf, const D3DXVECTOR3& posTarget, const float& fRadiusTarget)
{
	// �ڕW�n�_�ւ̃x�N�g�����Z�o
	D3DXVECTOR3 vec = posTarget - posSelf;

	// ���݂��̋������A���݂��̔��a�̘a�ȉ��ł���ΏՓ�
	if (sqrtf(vec.x * vec.x + vec.y * vec.y) <= (fRadiusSelf + fRadiusTarget))
	{
		return 1;
	}

	return 0;
}

//============================================================================
// ���Ɨ����̂̓����蔻��
//============================================================================
bool CUtility::SphereAndCube(const D3DXVECTOR3& posSph, const float& fRadius, const D3DXVECTOR3& posCube, const D3DXVECTOR3& size)
{
	// �S�Ă̎��������炨�݂��ɂ߂荞��ł���Ƃ��Փ�
	if (posSph.x + fRadius > posCube.x - size.x &&
		posSph.x - fRadius < posCube.x + size.x &&
		posSph.y + fRadius > posCube.y - size.y &&
		posSph.y - fRadius < posCube.y + size.y &&
		posSph.z + fRadius > posCube.z - size.z &&
		posSph.z - fRadius < posCube.z + size.z)
	{
		return 1;
	}

	return 0;
}

//============================================================================
// �����`�̏Փ˔���
//============================================================================
bool CUtility::OnlyCube(const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget)
{
	// �S�Ă̎��������炨�݂��ɂ߂荞��ł���Ƃ��Փ�
	if (posSelf.x + sizeSelf.x > posTarget.x - sizeTarget.x &&
		posSelf.x - sizeSelf.x < posTarget.x + sizeTarget.x &&
		posSelf.y + sizeSelf.y > posTarget.y - sizeTarget.y &&
		posSelf.y - sizeSelf.y < posTarget.y + sizeTarget.y &&
		posSelf.z + sizeSelf.z > posTarget.z - sizeTarget.z &&
		posSelf.z - sizeSelf.z < posTarget.z + sizeTarget.z)
	{
		return 1;
	}

	return 0;
}

//============================================================================
// �����o������
//============================================================================
bool CUtility::CubeResponse(D3DXVECTOR3& posDest, D3DXVECTOR3& velocity, const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget)
{
	// �ߋ��̈ʒu���ǂ��炩�̎������ɏd�Ȃ��Ă������ŏ�������
	if (posSelf.x + sizeSelf.x > posTarget.x - sizeTarget.x &&
		posSelf.x - sizeSelf.x < posTarget.x + sizeTarget.x)
	{
		// Y�������̉����x�����Z�b�g
		velocity.y = 0.0f;

		if (posSelf.y < posTarget.y)
		{
			// �ʒu�����̃u���b�N�̏�[�ɐݒ�
			posDest.y = -sizeSelf.y + (posTarget.y - sizeTarget.y);
		}
		else if (posSelf.y > posTarget.y)
		{
			// �ʒu�����̃u���b�N�̉��[�ɐݒ�
			posDest.y = sizeSelf.y + (posTarget.y + sizeTarget.y);
		}

		return 1;
	}
	else if (posSelf.y + sizeSelf.y > posTarget.y - sizeTarget.y &&
		posSelf.y - sizeSelf.y < posTarget.y + sizeTarget.y)
	{
		// X�������̉����x�����Z�b�g
		velocity.x = 0.0f;

		if (posSelf.x < posTarget.x)
		{
			// �ʒu�����̃u���b�N�̍��[�ɐݒ�
			posDest.x = -sizeSelf.x + (posTarget.x - sizeTarget.x);
		}
		else if (posSelf.x > posTarget.x)
		{
			// �ʒu�����̃u���b�N�̉E�[�ɐݒ�
			posDest.x = sizeSelf.x + (posTarget.x + sizeTarget.x);
		}

		return 1;
	}

	return 0;
}

//============================================================================
// �R���X�g���N�^
//============================================================================
CUtility::CUtility()
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CUtility::~CUtility()
{

}

//============================================================================
// ����
//============================================================================
void CUtility::Create()
{
	if (m_pInstance != nullptr)
	{ // ��d�����֎~
		assert(false);
	}

	// �C���X�^���X�𐶐�
	m_pInstance = DBG_NEW CUtility{};
}

//============================================================================
// �I������
//============================================================================
void CUtility::Uninit()
{

}