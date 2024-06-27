//============================================================================
// 
// �������Z [physics.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "physics.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
const float CPhysics::GRAVITY_FORCE = -0.3f;	// �d��
CPhysics* CPhysics::m_pInstance = nullptr;		// �C���X�^���X���

//============================================================================
// �d�͗���
//============================================================================
void CPhysics::Gravity(D3DXVECTOR3& vec)
{
	vec.y += GRAVITY_FORCE;
}

//============================================================================
// ���`�̏Փ˔���
//============================================================================
bool CPhysics::Sphere(const D3DXVECTOR3& posSelf, const float& fRadiusSelf, const D3DXVECTOR3& posTarget, const float& fRadiusTarget)
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
// �����`�̏Փ˔���
//============================================================================
bool CPhysics::Cube(const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget)
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
bool CPhysics::CubeResponse(D3DXVECTOR3& posDest, D3DXVECTOR3& velocity, const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget)
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
// ����
//============================================================================
HRESULT CPhysics::Create()
{
	if (m_pInstance == nullptr)
	{
		// �C���X�^���X�𐶐�
		m_pInstance = DBG_NEW CPhysics();
	}

	if (m_pInstance == nullptr)
	{
		// �������s
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// �j��
//============================================================================
void CPhysics::Release()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;		// ���������
		m_pInstance = nullptr;	// �|�C���^��������
	}
}

//============================================================================
// �C���X�^���X���擾
//============================================================================
CPhysics* CPhysics::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// �擾���s
		assert(false);
	}

	return m_pInstance;
}

//============================================================================
// �R���X�g���N�^
//============================================================================
CPhysics::CPhysics()
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPhysics::~CPhysics()
{

}