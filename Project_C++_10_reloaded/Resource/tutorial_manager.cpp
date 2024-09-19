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
// �f�t�H���g�R���X�g���N�^
//============================================================================
CTutorial_Manager::CTutorial_Manager() :
	m_pText{ nullptr }
{

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

		// �o���ݒ�
		m_pText->SetAppear(true);

		// �ڕW���W��ݒ�
		m_pText->SetPosTarget(D3DXVECTOR3{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f });

		// �ڕW�T�C�Y��ݒ�
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f, 50.0f, 0.0f });
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
	else
	{
		// �e�L�X�g�𐶐�
		CreateText();
	}

	// �e�L�X�g�̖ڕW���W��ݒ�
	m_pText->SetPosTarget(D3DXVECTOR3{ SCREEN_WIDTH * 0.5f, (SCREEN_HEIGHT * 0.8f) + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });

	// �v���C���[�̍��W���R�s�[
	D3DXVECTOR3 Pos{ pPlayer->GetPos() };
}