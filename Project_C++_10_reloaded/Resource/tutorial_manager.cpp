//============================================================================
// 
// �`���[�g���A���}�l�[�W���[ [tutorial_manager.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "tutorial_manager.h"
#include "utility.h"

// �f�o�b�O�\���p
#include "renderer.h"

// �v���C���[�擾�p
#include "player.h"
#include "player_state.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
CTutorial_Manager* CTutorial_Manager::m_pInstance = nullptr;	// ���N���X�̃|�C���^

//============================================================================
// �X�V
//============================================================================
void CTutorial_Manager::UpdateTutorial()
{
	if (!m_pInstance)
	{
		// ����
		CTutorial_Manager::CreateInstance();
	}

	// �v���C���[�̍��W���m�F
	m_pInstance->CheckPlayerPos();
}

//============================================================================
// �폜
//============================================================================
void CTutorial_Manager::DeleteInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

//============================================================================
// �e�N�X�`���^�C�v���擾
//============================================================================
CTexture_Manager::TYPE CTutorial_Manager::GetTexType()
{
	if (m_pInstance)
	{
		return m_pInstance->m_TexType;
	}

	return CTexture_Manager::TYPE::TEXT00;
}

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CTutorial_Manager::CTutorial_Manager() :
	m_pText{ nullptr },
	m_apHand{ nullptr, nullptr },
	m_apInput_UI{ nullptr, nullptr },
	m_TexType{ CTexture_Manager::TYPE::TEXT00 }
{
	// �e�L�X�g�𐶐�
	CreateText();

	// �C���v�b�gUI�𐶐� (�����s)
	m_apInput_UI[0] = CInput_UI::Create(CTexture_Manager::TYPE::CNT);
	m_apInput_UI[1] = CInput_UI::Create(CTexture_Manager::TYPE::BOARD);

	// ��Ƃ��𐶐�
	m_apHand[0] = CHand::Create(CTexture_Manager::TYPE::LHAND);
	m_apHand[1] = CHand::Create(CTexture_Manager::TYPE::RHAND);
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CTutorial_Manager::~CTutorial_Manager()
{
	// �ȗ�
	if (m_pText)
	{
		m_pText->SetDisappear(true);
		m_pText->SetPosTarget(D3DXVECTOR3{ 0.0f, SCREEN_HEIGHT + 100.0f, 0.0f });
		m_pText->SetSizeTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
		m_pText = nullptr;
	}

	if (m_apHand[0])
	{
		m_apHand[0]->SetDisappear();
		m_apHand[0]->SetPosTarget({ -3.0f, -7.5f, -10.0f, });	// �l��CHand::Init���
		m_apHand[0]->SetSizeTarget(D3DXVECTOR3{ 10.0f, 10.0f, 0.0f });
		m_apHand[0] = nullptr;
	}

	if (m_apHand[1])
	{
		m_apHand[1]->SetDisappear();
		m_apHand[1]->SetPosTarget({ -3.0f, -7.5f, -10.0f, });	// �l��CHand::Init���
		m_apHand[1]->SetSizeTarget(D3DXVECTOR3{ 10.0f, 10.0f, 0.0f });
		m_apHand[1] = nullptr;
	}

	if (m_apInput_UI[0])
	{
		m_apInput_UI[0]->SetDisappear();
		m_apInput_UI[0]->SetPosTarget({ -3.0f, -7.5f, -10.0f, });	// �l��CInput_UI::Init���
		m_apInput_UI[0]->SetSizeTarget(D3DXVECTOR3{ 10.0f, 10.0f, 0.0f });
		m_apInput_UI[0] = nullptr;
	}

	if (m_apInput_UI[1])
	{
		m_apInput_UI[1]->SetDisappear();
		m_apInput_UI[1]->SetPosTarget({ -15.5f, 6.0f, -10.0f });	// �l��CInput_UI::Init���
		m_apInput_UI[1]->SetSizeTarget(D3DXVECTOR3{ 5.5f, 5.5f, 0.0f });
		m_apInput_UI[1] = nullptr;
	}
}

//============================================================================
// ����
//============================================================================
void CTutorial_Manager::CreateInstance()
{
	if (m_pInstance != nullptr)
	{ // ��d�����֎~
		assert(false);
	}

	// �`���[�g���A���}�l�[�W���[�𐶐�
	m_pInstance = DBG_NEW CTutorial_Manager{};
}

//============================================================================
// �e�L�X�g�̐���
//============================================================================
void CTutorial_Manager::CreateText()
{
	if (!m_pText)
	{
		// �e�L�X�g�̐���
		m_pText = CText::Create(CTexture_Manager::TYPE::TEXT00);

		// �^�C�v�̕ێ�
		m_TexType = CTexture_Manager::TYPE::TEXT00;

		// �o���ݒ�
		m_pText->SetAppear(true);

		// �ڕW���W��ݒ�
		// �X�V���Œʏ���W�ݒ�

		// �ڕW�T�C�Y��ݒ�
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 1.4f, 50.0f * 1.4f, 0.0f });
	}
}

//============================================================================
// �e�L�X�g�̍폜
//============================================================================
void CTutorial_Manager::DeleteText()
{
	// �ȗ�
	if (m_pText)
	{
		m_pText->SetDisappear(true);
		m_pText->SetPosTarget(D3DXVECTOR3{ 0.0f, SCREEN_HEIGHT + 100.0f, 0.0f });
		m_pText->SetSizeTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
		m_pText = nullptr;
	}
}

//============================================================================
// �v���C���[�̍��W���m�F
//============================================================================
void CTutorial_Manager::CheckPlayerPos()
{
	// �v���C���[�^�O���擾
	CObject* pObj{ CObject::FindObject(CObject::TYPE::PLAYER) };

	// �擾���s
	if (!pObj)
	{
		return;
	}

	// �v���C���[�N���X�Ƀ_�E���L���X�g
	CPlayer* pPlayer{ CUtility::GetInstance()->DownCast<CPlayer, CObject>(pObj) };

	// ��Ԃɉ����ăe�L�X�g����
	if (typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateGoal))
	{
		// �e�L�X�g���폜
		DeleteText();

		// �ȍ~�e�L�X�g��������Ȃ�
		return;
	}

	// �e�L�X�g�̖ڕW���W��ݒ�
	m_pText->SetPosTarget(D3DXVECTOR3{ SCREEN_WIDTH * 0.5f, (SCREEN_HEIGHT * 0.75f) + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });

	// �v���C���[�̍��W���R�s�[
	D3DXVECTOR3 Pos{ pPlayer->GetPos() };

	//===== �ȉ����@�n�� =====//

	// �u�ړ����Ă݂悤�v����
	if (m_TexType == CTexture_Manager::TYPE::TEXT00 && Pos.y < -60.0f)
	{
		// �e�L�X�g�ύX
		m_TexType = CTexture_Manager::TYPE::TEXT01;	// �Ƃ�ł݂悤
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT01 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateFlying) && Pos.y > -20.0f)
	{
		// �e�L�X�g�ύX
		m_TexType = CTexture_Manager::TYPE::TEXT02;	// �u���b�N�ɂԂ��낤
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT02 && Pos.x > 300.0f)
	{
		// �e�L�X�g�ύX
		m_TexType = CTexture_Manager::TYPE::TEXT03;	// �E�֐i��ł݂悤
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT03 && Pos.x > 560.0f)
	{
		// �e�L�X�g�ύX
		m_TexType = CTexture_Manager::TYPE::TEXT04;	// ��ς����ł���
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 1.65f, 50.0f * 1.65f, 0.0f });
	}

	// ����u���u��
	if (m_TexType == CTexture_Manager::TYPE::TEXT04)
	{
		m_pText->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.005f });
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT04 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateStopping) && Pos.x > 600.0f)
	{
		// �e�L�X�g�ύX
		m_TexType = CTexture_Manager::TYPE::TEXT05;	// �ːi���Ă݂悤
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 1.4f, 50.0f * 1.4f, 0.0f });
		m_pText->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT05 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateMistook) && Pos.x > 1000.0f)
	{
		// �e�L�X�g�ύX
		m_TexType = CTexture_Manager::TYPE::TEXT06;	// �c�O�I���܁[�݂�
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 0.9f, 50.0f * 0.9f, 0.0f });
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT06 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateMistook) && Pos.x < 260.0f)
	{
		// �e�L�X�g�ύX
		m_TexType = CTexture_Manager::TYPE::TEXT07;	// �����ƁI���v��������
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 1.4f, 50.0f * 1.4f, 0.0f });
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT07 && Pos.x > 260.0f)
	{
		// �e�L�X�g�ύX
		m_TexType = CTexture_Manager::TYPE::TEXT08;	// ������x�ːi���Ă݂悤
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
}