//============================================================================
// 
// �S�[�� [goal.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "goal.h"
#include "utility.h"

// �X�N���[���e�N�X�`���擾�p
#include "renderer.h"

// �J�����擾�p
#include "manager.h"

// �v���C���[�擾�p
#include "player.h"
#include "player_state.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CGoal::CGoal() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },
	m_ActualPos{ 0.0f, 0.0f, 0.0f },
	m_PosTarget{ 0.0f, 0.0f, 0.0f },
	m_RotTarget{ 0.0f, 0.0f, 0.0f },
	m_fScaleTarget{ 0.0f }
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CGoal::~CGoal()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CGoal::Init()
{
	// �ڕW���W��ݒ�
	m_PosTarget = m_ActualPos;
	m_PosTarget.z = 0.0f;

	// �ڕW�k�ڂ�ݒ�
	m_fScaleTarget = 1.0f;

	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CGoal::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CGoal::Update()
{
	// �v���C���[�^�O�̃I�u�W�F�N�g���擾
	CObject* pObj{ CObject::FindObject(CObject::TYPE::PLAYER) };

	// �I�u�W�F�N�g���擾�o������
	if (pObj)
	{
		// �v���C���[�փ_�E���L���X�g
		CPlayer* pPlayer{ CUtility::GetInstance()->DownCast<CPlayer, CObject>(pObj) };

		// �v���C���[���S�[����ԂȂ�
		if (typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateGoal))
		{
			// �v���C���[�̍��W���e���r�ɋz���񂹂�
			pPlayer->SetPos(CUtility::GetInstance()->AdjustToTarget(pPlayer->GetPos(), GetPos(), 0.1f));

			// ���ʂ�����
			m_RotTarget = {
				0.0f,
				0.0f,
				CUtility::GetInstance()->GetRandomValue<float>() * 0.005f };

			// �㉺����
			m_PosTarget.y = m_ActualPos.y + CUtility::GetInstance()->GetRandomValue<float>() * 0.1f;
		}
		else
		{
			// �J�����̊ԋ��������Z�b�g
			CManager::GetCamera()->SetDistance(300.0f);
		}

		// ���ʂ�����
		m_RotTarget = {
			0.0f,
			0.0f,
			CUtility::GetInstance()->GetRandomValue<float>() * 0.005f };

		// �㉺����
		m_PosTarget.y = m_ActualPos.y + CUtility::GetInstance()->GetRandomValue<float>() * 0.1f;
	}

	// �ڕW������
	SetRot(CUtility::GetInstance()->AdjustToTarget(GetRot(), m_RotTarget, 0.05f));

	// �ڕW���W��
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), m_PosTarget, 0.05f));

	// �ڕW�k�ڂ�
	SetScale(CUtility::GetInstance()->AdjustToTarget(GetScale(), m_fScaleTarget, 0.035f));

	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CGoal::Draw()
{
	// ���N���X�̕`��
	CObject_X::Draw();
}

//============================================================================
// �����W�̎擾
//============================================================================
D3DXVECTOR3 CGoal::GetActualPos()
{
	return m_ActualPos;
}

//============================================================================
// �����W�̐ݒ�
//============================================================================
void CGoal::SetActualPos(D3DXVECTOR3 Pos)
{
	m_ActualPos = Pos;
}

//============================================================================
// ����
//============================================================================
CGoal* CGoal::Create(D3DXVECTOR3 Pos)
{
	// �C���X�^���X�𐶐�
	CGoal* pGoal{ DBG_NEW CGoal };

	if (pGoal == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pGoal->SetType(TYPE::GOAL);

	// �����W�̐ݒ� (��s)
	pGoal->SetActualPos(Pos);

	// ���N���X�̏����ݒ�
	pGoal->Init();

	// �ʒu�̐ݒ�
	pGoal->SetPos(Pos);

	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::GOAL) };

	// ���f����ݒ�
	pGoal->BindModel(Model);

	// �T�C�Y��ݒ�
	pGoal->SetSize(Model->size);

	// �S�[���V���{���̃��j�^�[��ʂɃe�N�X�`����ݒ�
	Model->ppTex[0] = CRenderer::GetInstance()->GetTexture();

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pGoal->Update();

	return pGoal;
}