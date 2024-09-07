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

// �I�u�W�F�N�g���p 
//#include "block.h"
//#include "block_destructible.h"
//#include "block_spikes.h"

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
// �d�͗���
//============================================================================
void CUtility::Gravity(D3DXVECTOR3& vec)
{
	vec.y += GRAVITY_FORCE;
}

//============================================================================
// ���`���m�̏Փ˔���
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
// �����`���m�̏Փ˔���
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
// �����̓��m�̉����o������
//============================================================================
bool CUtility::OnlyCube(D3DXVECTOR3& posDest, D3DXVECTOR3& velocity, const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget)
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
// �\�����Ƃ̓����蔻��
//============================================================================
const type_info& CUtility::CollisionToStructure()
{
	//// �u���b�N�^�O���擾
	//CObject** pObject = CObject::FindAllObject(CObject::TYPE::BLOCK);

	//for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	//{
	//	// �u���b�N�^�O�̏�񂪖����Ȃ�����I��
	//	if (pObject[nCntObj] == nullptr)
	//	{
	//		break;
	//	}

	//	// �u���b�N�N���X�փ_�E���L���X�g
	//	CBlock* pBlock = CUtility::GetInstance()->DownCast<CBlock, CObject>(pObject[nCntObj]);

	//	// �u���b�N�ƏՓ˂���ꍇ
	//	if (CUtility::GetInstance()->OnlyCube(pBlock->GetPos(), pBlock->GetSize(), m_posTarget, GetSize()))
	//	{
	//		// �����o������
	//		CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pBlock->GetPos(), pBlock->GetSize());

	//		// �Փ˔�����o��
	//		bDetected = 1;
	//	}
	//}

	//// ��^�O���擾
	//pObject = CObject::FindAllObject(CObject::TYPE::DESTRUCTIBLE);

	//for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	//{
	//	// ��^�O�̏�񂪖����Ȃ�����I��
	//	if (pObject[nCntObj] == nullptr)
	//	{
	//		break;
	//	}

	//	// ��u���b�N�փ_�E���L���X�g
	//	CBlockDestructible* pDestructible = CUtility::GetInstance()->DownCast<CBlockDestructible, CObject>(pObject[nCntObj]);

	//	// ��u���b�N�ƏՓ˂���ꍇ
	//	if (CUtility::GetInstance()->OnlyCube(pDestructible->GetPos(), pDestructible->GetSize(), m_posTarget, GetSize()))
	//	{
	//		// �����o������
	//		CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pDestructible->GetPos(), pDestructible->GetSize());

	//		// ��s��Ԃ̏ꍇ�̂�
	//		if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying))
	//		{
	//			// ��u���b�N��j��
	//			pDestructible->SetRelease();
	//		}

	//		// �Փ˔�����o��
	//		bDetected = 1;
	//	}
	//}

	//// �Ƃ��^�O���擾
	//pObject = CObject::FindAllObject(CObject::TYPE::SPIKES);

	//for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	//{
	//	// �Ƃ��^�O�̏�񂪖����Ȃ�����I��
	//	if (pObject[nCntObj] == nullptr)
	//	{
	//		break;
	//	}

	//	// �Ƃ��u���b�N�փ_�E���L���X�g
	//	CBlockSpikes* pBlockSpikes = CUtility::GetInstance()->DownCast<CBlockSpikes, CObject>(pObject[nCntObj]);

	//	// �Ƃ��u���b�N�ƏՓ˂���ꍇ
	//	if (CUtility::GetInstance()->OnlyCube(pBlockSpikes->GetPos(), pBlockSpikes->GetSize(), m_posTarget, GetSize()))
	//	{
	//		// �~�X��ԂɈڍs
	//		m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);

	//		// �Փ˔�����o��
	//		bDetected = 1;
	//	}
	//}

	//// �G�l�~�[�^�O���擾
	//pObject = CObject::FindAllObject(CObject::TYPE::ENEMY);

	//for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	//{
	//	// �G�l�~�[�^�O�̏�񂪖����Ȃ�����I��
	//	if (pObject[nCntObj] == nullptr)
	//	{
	//		break;
	//	}

	//	// �G�l�~�[�փ_�E���L���X�g
	//	CEnemy* pEnemy = CUtility::GetInstance()->DownCast<CEnemy, CObject>(pObject[nCntObj]);

	//	// �G�l�~�[�ƏՓ˂���ꍇ
	//	if (CUtility::GetInstance()->OnlyCube(pEnemy->GetPos(), pEnemy->GetSize(), m_posTarget, GetSize()))
	//	{
	//		if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying))
	//		{ // ��s��Ԃ̏ꍇ

	//			// �����o������
	//			CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pEnemy->GetPos(), pEnemy->GetSize());

	//			// �G�l�~�[��j��
	//			pEnemy->SetRelease();
	//		}
	//		else
	//		{
	//			// �~�X��ԂɈڍs
	//			m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);
	//		}

	//		// �Փ˔�����o��
	//		bDetected = 1;
	//	}
	//}

	return typeid(nullptr);
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