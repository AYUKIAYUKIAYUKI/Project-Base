//============================================================================
// 
// �X�e�[�W�f�o�b�O [stage_debug.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "stage_debug.h"
#include "stagemaker.h"

#include "manager.h"
#include "dummy.h"
#include "line.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CStage_Debug::CStage_Debug()
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CStage_Debug::~CStage_Debug()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CStage_Debug::Init()
{
	// �X�e�[�W�쐬�N���X�̃C���X�^���X����
	if (FAILED(CStageMaker::Create()))
	{
		return E_FAIL;
	}

	// �X�e�[�W�쐬�N���X�̏����ݒ�
	CStageMaker::GetInstance()->Init();

	// �O���b�h���C������
	CLine::CreateGrid();

	// �_�~�[�̐���
	CDummy::Create({ 0.0f, 0.0f, 0.0f });

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CStage_Debug::Uninit()
{
	// �X�e�[�W�쐬�N���X�̃C���X�^���X�j��
	CStageMaker::Release();

	// ���N���X�̏I������
	CScene::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CStage_Debug::Update()
{
	// �Q�[�����[�h�֖߂�
	if (CManager::GetKeyboard()->GetTrigger(DIK_F1))
	{
		CManager::GetFade()->SetFade(MODE::GAME);
	}

	// �X�e�[�W�쐬�̍X�V
	CStageMaker::GetInstance()->Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CStage_Debug::Draw()
{

}