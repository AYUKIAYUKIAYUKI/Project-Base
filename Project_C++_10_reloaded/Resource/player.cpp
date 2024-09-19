//============================================================================
// 
// �v���C���[ [player.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "player.h"
#include "player_state.h"
#include "utility.h"
#include "sound.h"

// �t�F�[�Y���p
#include "game_manager.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �I�u�W�F�N�g���p 
#include "achievement.h"
#include "barrier.h"
#include "barrier_anchor.h"
#include "block.h"
#include "block_destructible.h"
#include "block_destructible_big.h"
#include "block_spikes.h"
#include "block_spikes_move.h"
#include "enemy.h"
#include "fakescreen.h"
#include "goal.h"
#include "smoke.h"
#include "start.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },	// �`��D��x���w��
	m_pStateManager{ nullptr },						// ��ԃ}�l�[�W���[�̏�����
	m_velocity{ 0.0f, 0.0f, 0.0f },					// �����x�̏�����
	m_velocityTarget{ 0.0f, 0.0f, 0.0f },			// �ڕW�����x�̏�����
	m_posTarget{ 0.0f, 0.0f, 0.0f },				// �ڕW�ʒu�̏�����
	m_rotTarget{ 0.0f, 0.0f, 0.0f },				// �ڕW�����̏�����
	m_fAngleFlying{ 0.0f }							// ��s�����̏�����
{
	
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CPlayer::~CPlayer()
{
	m_pStateManager = nullptr;					// ��ԃ}�l�[�W���[�̏�����
	m_velocity = { 0.0f, 0.0f, 0.0f };			// �����x�̏�����
	m_velocityTarget = { 0.0f, 0.0f, 0.0f };	// �ڕW�����x�̏�����
	m_posTarget = { 0.0f, 0.0f, 0.0f };			// �ڕW�ʒu�̏�����
	m_rotTarget = { 0.0f, 0.0f, 0.0f };			// �ڕW�����̏�����
	m_fAngleFlying = 0.0f;						// ��s�����̏�����
}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CPlayer::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	if (m_pStateManager == nullptr)
	{
		// ��ԃ}�l�[�W���[�̐���
		m_pStateManager = DBG_NEW CPlayerStateManager;

		// �����ݒ�
		m_pStateManager->Init(this);
	}

	// �X�^�[�g�n�_������
	CObject* pObject = CObject::FindObject(CObject::TYPE::START);
	CStart* pStart = CUtility::GetInstance()->DownCast<CStart, CObject>(pObject);

	// �������W���X�^�[�g�n�_��
	SetPos(pStart->GetPos());

	// �����k�ڂ�ݒ�
	SetScale(0.0f);

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CPlayer::Uninit()
{
	// ��ԃ}�l�[�W���[�̔j��
	if (m_pStateManager != nullptr)
	{
		// �I������
		m_pStateManager->Uninit();
	
		// �����������
		delete m_pStateManager;

		// �|�C���^��������
		m_pStateManager = nullptr;
	}

	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CPlayer::Update()
{
	// ���ݍ��W���R�s�[���A�ȍ~���̃R�s�[��ڕW���W�Ƃ��ĕύX�������Ă���
	m_posTarget = CObject_X::GetPos();

	// ��ԃI�u�W�F�N�g����������Ă����
	if (m_pStateManager->GetState() != nullptr)
	{
		// ��Ԃ̍X�V
		m_pStateManager->GetState()->Update();

		// ��Ԃ̕ύX���m�F���� (������������܂ޏ����̂��߁A�X�V�̌�ɕʓr�s��)
		m_pStateManager->CheckStateChange();
	}

	// �ڕW���W�𔽉f
	SetPos(m_posTarget);

#ifdef _DEBUG
	// ���W���f�o�b�O�\��
	CRenderer::GetInstance()->SetDebugString("�y�v���C���[���W�z");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());

	CRenderer::GetInstance()->SetDebugString("�����xX : " + std::to_string(m_velocity.x));
	CRenderer::GetInstance()->SetDebugString("�����xY : " + std::to_string(m_velocity.y));
	CRenderer::GetInstance()->SetDebugString("���� : x " + std::to_string(GetRot().x) + " : y " + std::to_string(GetRot().y) + " : z " + std::to_string(GetRot().z));
	CRenderer::GetInstance()->SetDebugString("�ڕW���� : x " + std::to_string(m_rotTarget.x) + " : y " + std::to_string(m_rotTarget.y) + " : z " + std::to_string(m_rotTarget.z));
	CRenderer::GetInstance()->SetDebugString("���݂̔�s���� : " + std::to_string(m_fAngleFlying));
#endif	// _DEBUG

	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CPlayer::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// �����蔻��
//============================================================================
bool CPlayer::Collision()
{
	// �Փˌ��o�p
	bool bDetected{ false };

	// �I�u�W�F�N�g�擾�p�|�C���^
	CObject** pObject{ nullptr };

	// �o���A�^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::BARRIER);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �o���A�N���X�փ_�E���L���X�g
		CBarrier* pBarrier = CUtility::GetInstance()->DownCast<CBarrier, CObject>(pObject[nCntObj]);

		// �o���A�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pBarrier->GetPos(), pBarrier->GetSize(), m_posTarget, GetSize()))
		{
			// �~�X��ԂɈڍs
			m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);

			// �Փ˔�����o��
			bDetected = 1;

			// ���S��
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}

	// �o���A�A���J�[�^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::BARRIER_ANCHOR);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �o���A�A���J�[�N���X�փ_�E���L���X�g
		CBarrier_Anchor* pAnchor = CUtility::GetInstance()->DownCast<CBarrier_Anchor, CObject>(pObject[nCntObj]);

		// �o���A�A���J�[�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pAnchor->GetPos(), pAnchor->GetSize(), m_posTarget, GetSize()))
		{
			// �~�X��ԂɈڍs
			m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);

			// �Փ˔�����o��
			bDetected = 1;

			// ���S��
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}

	// �u���b�N�^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::BLOCK);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �u���b�N�^�O�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �u���b�N�N���X�փ_�E���L���X�g
		CBlock* pBlock = CUtility::GetInstance()->DownCast<CBlock, CObject>(pObject[nCntObj]);

		// �u���b�N�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pBlock->GetPos(), pBlock->GetSize(), m_posTarget, GetSize()))
		{
			// �����o������
			CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pBlock->GetPos(), pBlock->GetSize());

			// �Փ˔�����o��
			bDetected = 1;
		}
	}

	// ��^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::DESTRUCTIBLE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// ��^�O�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ��u���b�N�փ_�E���L���X�g
		CBlockDestructible* pDestructible = CUtility::GetInstance()->DownCast<CBlockDestructible, CObject>(pObject[nCntObj]);

		// ��u���b�N�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pDestructible->GetPos(), pDestructible->GetSize(), m_posTarget, GetSize()))
		{
			// �ːi��Ԃ̏ꍇ�̂�
			if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateRushing))
			{
				// ��u���b�N��j��
				pDestructible->SetRelease();

				// �����_���ȉ����x�𐶐�
				D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

				// ���𐶐�
				CSmoke::Create(
					pDestructible->GetPos() + RandomVelocity * 5.0f,	// ���W
					m_velocity * -0.5f);								// �����x

				// �j��
				CSound::GetInstance()->Play(CSound::LABEL::BREAK);
			}
			else
			{
				// �ՓˑO�̉����x��ێ�
				D3DXVECTOR3 OldVelocity{ m_velocity };

				// �����o������
				CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pDestructible->GetPos(), pDestructible->GetSize());

				// ��s��Ԃ̏ꍇ�̂�
				if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying) ||
					typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateStopping))
				{
					// ��u���b�N��j��
					pDestructible->SetRelease();

					// �G�t�F�N�g���쐬
					for (int i = 0; i < 3; i++)
					{
						// �����_���ȉ����x�𐶐�
						D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

						// ���𐶐�
						CSmoke* pSmoke{ CSmoke::Create(
							pDestructible->GetPos() + RandomVelocity * 2.0f,	// ���W
							OldVelocity * -0.5f) };								// �����x

						// �����߂�
						pSmoke->SetScale(0.75f);
					}

					// �j��
					CSound::GetInstance()->Play(CSound::LABEL::BREAK);
				}

				// �Փ˔�����o��
				bDetected = 1;
			}
		}
	}

	// ��ł��^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::DEST_BIG);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// ��ł��^�O�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ��ł��u���b�N�փ_�E���L���X�g
		CBlockDestructibleBig* pDest_Big = CUtility::GetInstance()->DownCast<CBlockDestructibleBig, CObject>(pObject[nCntObj]);

		// ��ł��u���b�N�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pDest_Big->GetPos(), pDest_Big->GetSize(), m_posTarget, GetSize()))
		{
			// �ːi��Ԃ̏ꍇ�̂�
			if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateRushing))
			{
				// �_���[�W����
				if (pDest_Big->Damage(-1))
				{
					// �j��d�؂�Ȃ��ꍇ�A�����o������
					CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pDest_Big->GetPos(), pDest_Big->GetSize());
				
					// �Փ˔�����o��
					bDetected = 1;
				}
				else
				{
					// �G�t�F�N�g���쐬
					for (int i = 0; i < 10; i++)
					{
						// �����_���ȉ����x�𐶐�
						D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), 0.0f };

						// ���𐶐�
						CSmoke* pSmoke{ CSmoke::Create(
							pDest_Big->GetPos() + RandomVelocity * 0.1f,	// ���W
							m_velocity * -1.0f) };							// �����x
					
						// �傫��
						pSmoke->SetScale(1.2f);
					}
				}

				// �j��
				CSound::GetInstance()->Play(CSound::LABEL::BREAK);
			}
			else
			{
				// �ՓˑO�̉����x��ێ�
				D3DXVECTOR3 OldVelocity{ m_velocity };

				// �����o������
				CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pDest_Big->GetPos(), pDest_Big->GetSize());

				// ��s��Ԃ̏ꍇ�̂�
				if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying))
				{
					// �_���[�W����
					if (!pDest_Big->Damage(-1))
					{ // �j��o������

						// �G�t�F�N�g���쐬
						for (int i = 0; i < 5; i++)
						{
							// �����_���ȉ����x�𐶐�
							D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), 0.0f };
						
							// ���𐶐�
							CSmoke* pSmoke{ CSmoke::Create(
								pDest_Big->GetPos() + RandomVelocity * 0.1f,	// ���W
								OldVelocity * -1.0f) };							// �����x

							// �傫��
							pSmoke->SetScale(1.2f);
						}
					}

					// �j��
					CSound::GetInstance()->Play(CSound::LABEL::BREAK);
				}

				// �Փ˔�����o��
				bDetected = 1;
			}
		}
	}

	// �Ƃ��^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �Ƃ��^�O�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �Ƃ��u���b�N�փ_�E���L���X�g
		CBlockSpikes* pBlockSpikes = CUtility::GetInstance()->DownCast<CBlockSpikes, CObject>(pObject[nCntObj]);

		// �Ƃ��u���b�N�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pBlockSpikes->GetPos(), pBlockSpikes->GetSize(), m_posTarget, GetSize()))
		{
			// �~�X��ԂɈڍs
			m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);

			// �Փ˔�����o��
			bDetected = 1;

			// ���S��
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}

	// �Ƃ��ړ��^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES_MOVE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �Ƃ��ړ��^�O�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �Ƃ��ړ��u���b�N�փ_�E���L���X�g
		CBlockSpikesMove* pBlockSpikesMove = CUtility::GetInstance()->DownCast<CBlockSpikesMove, CObject>(pObject[nCntObj]);

		// �Ƃ��ړ��u���b�N�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pBlockSpikesMove->GetPos(), pBlockSpikesMove->GetSize(), m_posTarget, GetSize()))
		{
			// �~�X��ԂɈڍs
			m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);

			// �Փ˔�����o��
			bDetected = 1;

			// ���S��
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}
	
	// �G�l�~�[�^�O���擾
	pObject = CObject::FindAllObject(CObject::TYPE::ENEMY);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �G�l�~�[�^�O�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �G�l�~�[�փ_�E���L���X�g
		CEnemy* pEnemy = CUtility::GetInstance()->DownCast<CEnemy, CObject>(pObject[nCntObj]);

		// �G�l�~�[�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->OnlyCube(pEnemy->GetPos(), pEnemy->GetSize(), m_posTarget, GetSize()))
		{
			// �ːi��Ԃ̏ꍇ�̂�
			if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateRushing))
			{
				// �����_���ȉ����x�𐶐�
				D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

				// ���𐶐�
				CSmoke::Create(
					pEnemy->GetPos() + RandomVelocity * 5.0f,	// ���W
					m_velocity * -0.5f);						// �����x

				// �G�l�~�[��j��
				pEnemy->SetRelease();
			}
			else
			{
				if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying))
				{ // ��s��Ԃ̏ꍇ

					// ���̎��_�ł̉����x��ێ�
					D3DXVECTOR3 OldVelocity{ m_velocity };

					// �����o������
					CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pEnemy->GetPos(), pEnemy->GetSize());

					// �G�t�F�N�g���쐬
					for (int i = 0; i < 3; i++)
					{
						// �����_���ȉ����x�𐶐�
						D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

						// ���𐶐�
						CSmoke* pSmoke{ CSmoke::Create(
							pEnemy->GetPos() + RandomVelocity * 2.0f,	// ���W
							OldVelocity * -0.5f) };						// �����x

						// �����߂�
						pSmoke->SetScale(0.75f);
					}

					// �G�l�~�[��j��
					pEnemy->SetRelease();
				}
				else
				{
					// �~�X��ԂɈڍs
					m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);
				}

				// �Փ˔�����o��
				bDetected = 1;
			}

			// ���S��
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}

	// �~�X��ԂɈڍs�\��ł���΃S�[���E�A�`�[�u�Ƃ̐ڐG�͔F�߂Ȃ�
	if (m_pStateManager->GetPendingState() == CPlayerState::STATE::MISS)
	{
		return bDetected;
	}

	// �A�`�[�u�I�u�W�F�N�g���擾
	if (CObject::FindObject(CObject::TYPE::ACHIEVE))
	{
		CAchieve* pAchieve = CUtility::GetInstance()->DownCast<CAchieve, CObject>(CObject::FindObject(CObject::TYPE::ACHIEVE));

		// �A�`�[�u�ƏՓ˂���ꍇ
		if (CUtility::GetInstance()->SphereAndCube(pAchieve->GetPos(), pAchieve->GetSize().x, m_posTarget, GetSize()))
		{
			// �j���\��
			pAchieve->SetRelease();

			// �擾��
			CSound::GetInstance()->Play(CSound::LABEL::GET);
		}
	}

	// �S�[���I�u�W�F�N�g���擾
	CGoal* pGoal = CUtility::GetInstance()->DownCast<CGoal, CObject>(CObject::FindObject(CObject::TYPE::GOAL));

	// �S�[���ƏՓ˂���ꍇ
	if (CUtility::GetInstance()->SphereAndCube(pGoal->GetActualPos(), pGoal->GetSize().x, m_posTarget, GetSize()))
	{
		// �S�[����ԂɈڍs
		m_pStateManager->SetPendingState(CPlayerState::STATE::GOAL);

		// �E�F�[�u�������I��
		CFakeScreen::GetInstance()->StopWave();

		// ���x���I���t�F�[�Y�ֈڍs
		CFakeScreen::GetInstance()->SetWave(CGameManager::PHASE::FINISH);

		// �S�[����
		CSound::GetInstance()->Play(CSound::LABEL::GOAL);
	}

	return bDetected;
}

//============================================================================
// �����x���擾
//============================================================================
D3DXVECTOR3 CPlayer::GetVelocity()
{
	return m_velocity;
}

//============================================================================
// �����x��ݒ�
//============================================================================
void CPlayer::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

//============================================================================
// �ڕW�����x���擾
//============================================================================
D3DXVECTOR3 CPlayer::GetVelocityTarget()
{
	return m_velocityTarget;
}

//============================================================================
// �ڕW�����x��ݒ�
//============================================================================
void CPlayer::SetVelocityTarget(D3DXVECTOR3 velocityTarget)
{
	m_velocityTarget = velocityTarget;
}

//============================================================================
// ��s�������擾
//============================================================================
float CPlayer::GetAngleFlying()
{
	return m_fAngleFlying;
}

//============================================================================
// ��s������ݒ�
//============================================================================
void CPlayer::SetAngleFlying(float fAngleFlying)
{
	m_fAngleFlying = fAngleFlying;
}

//============================================================================
// �ڕW�ʒu���擾
//============================================================================
D3DXVECTOR3 CPlayer::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// �ڕW�ʒu��ݒ�
//============================================================================
void CPlayer::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// �ڕW�������擾
//============================================================================
D3DXVECTOR3 CPlayer::GetRotTarget()
{
	return m_rotTarget;
}

//============================================================================
// �ڕW������ݒ�
//============================================================================
void CPlayer::SetRotTarget(D3DXVECTOR3 rotTarget)
{
	m_rotTarget = rotTarget;
}

//============================================================================
// ��ԊǗ��擾
//============================================================================
CPlayerStateManager* CPlayer::GetStateManager()
{
	return m_pStateManager;
}

//============================================================================
// ����
//============================================================================
CPlayer* CPlayer::Create()
{
	// �C���X�^���X�𐶐�
	CPlayer* pPlayer = DBG_NEW CPlayer;

	if (pPlayer == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pPlayer->SetType(TYPE::PLAYER);

	// ���N���X�̏����ݒ�
	pPlayer->Init();

	// ��s���čX�V���Ă���
	pPlayer->Update();

	return pPlayer;
}