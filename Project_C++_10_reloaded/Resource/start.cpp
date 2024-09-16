//============================================================================
// 
// �X�^�[�g [start.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "start.h"
#include "utility.h"

// �v���C���[�擾�p
#include "player.h"
#include "player_state.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CStart::CStart() :
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
CStart::~CStart()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CStart::Init()
{
	// �ڕW���W��ݒ�
	m_PosTarget = m_ActualPos;
	m_PosTarget.z = 30.0f;

	// �ڕW�k�ڂ�ݒ�
	m_fScaleTarget = 0.75f;

	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CStart::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CStart::Update()
{
	// �v���C���[�^�O�̃I�u�W�F�N�g���擾
	CObject* pObj{ CObject::FindObject(CObject::TYPE::PLAYER) };

	// �I�u�W�F�N�g���擾�o������
	if (pObj)
	{
		// �v���C���[�փ_�E���L���X�g
		CPlayer* pPlayer{ CUtility::GetInstance()->DownCast<CPlayer, CObject>(pObj) };

		// �v���C���[�����S��ԂȂ�
		if (typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateMistook))
		{
			// �������ړ�����
			m_PosTarget.x = m_ActualPos.x + CUtility::GetInstance()->GetRandomValue<float>() * 0.5f;
			m_PosTarget.y = m_ActualPos.y + CUtility::GetInstance()->GetRandomValue<float>() * 0.5f;

			// ���W����O��
			D3DXVECTOR3 NewPos{ GetPos() };
			NewPos.z = -30.0f;
			SetPos(NewPos);

			// ���f�����g��
			SetScale(1.5f);
		}
		else
		{
			// ���ʂ�����
			m_RotTarget = {
				0.0f,
				0.0f,
				CUtility::GetInstance()->GetRandomValue<float>() * 0.005f };

			// �㉺����
			m_PosTarget.x = m_ActualPos.x;
			m_PosTarget.y = m_ActualPos.y + CUtility::GetInstance()->GetRandomValue<float>() * 0.1f;
		}
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
void CStart::Draw()
{
	// ���N���X�̕`��
	CObject_X::Draw();
}

//============================================================================
// �����W�̎擾
//============================================================================
D3DXVECTOR3 CStart::GetActualPos()
{
	return m_ActualPos;
}

//============================================================================
// �����W�̐ݒ�
//============================================================================
void CStart::SetActualPos(D3DXVECTOR3 Pos)
{
	m_ActualPos = Pos;
}

//============================================================================
// ����
//============================================================================
CStart* CStart::Create(D3DXVECTOR3 Pos)
{
	// �C���X�^���X�𐶐�
	CStart* pStart{ DBG_NEW CStart };

	if (pStart == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pStart->SetType(TYPE::START);

	// �����W�̐ݒ� (��s)
	pStart->SetActualPos(Pos);

	// ���N���X�̏����ݒ�
	pStart->Init();

	// ���W�̐ݒ�
	pStart->SetPos(Pos);

	// ���f�����擾
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::START) };

	// ���f����ݒ�
	pStart->BindModel(Model);

	// �T�C�Y��ݒ�
	pStart->SetSize(Model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pStart->Update();

	return pStart;
}