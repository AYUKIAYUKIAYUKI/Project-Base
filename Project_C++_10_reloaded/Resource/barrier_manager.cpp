//============================================================================
// 
// �o���A�}�l�[�W���[ [barrier_manager.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "barrier_manager.h"
#include "utility.h"

// �f�o�b�O�\���p
#include "renderer.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CBarrier_Manager::CBarrier_Manager()
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CBarrier_Manager::~CBarrier_Manager()
{

}

//============================================================================
// �X�e�[�W�Ƀo���A�𐶐�����
//============================================================================
void CBarrier_Manager::CreateStageBarrier()
{
	// �o���A�A���J�[�^�O�����ׂĎ擾
	CObject** pObject{ CObject::FindAllObject(CObject::TYPE::BARRIER_ANCHOR) };

	// �o���A�A���J�[�̃|�C���^
	CBarrier_Anchor* pAnchor[2] = { nullptr, nullptr };

	// �I�u�W�F�N�g�����J�E���g
	int nCntObj{ 0 };

	for (nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �o���A�A���J�[�փ_�E���L���X�g
		pAnchor[nCntObj] = CUtility::GetInstance()->DownCast<CBarrier_Anchor, CObject>(pObject[nCntObj]);
	}

	// �o���A�A���J�[�̕s��
	if (nCntObj < 2)
	{
#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("�y�o���A�A���J�[�̐����s�����Ă��܂��I�z", 120);
#endif // _DEBUG
		return;
	}

	// 2�̍��W�̉�������̌�_�ɂ���ɃA���J�[�������2�쐬����
	CBarrier_Anchor::Create(D3DXVECTOR3{ pAnchor[0]->GetPos().x, pAnchor[1]->GetPos().y, 0.0f });
	CBarrier_Anchor::Create(D3DXVECTOR3{ pAnchor[1]->GetPos().x, pAnchor[0]->GetPos().y, 0.0f });

	// 4�̍��W�𒸓_�Ƃ����`�̕ӂ�`���悤�Ƀo���A�𐶐�����
	float fBeginX{ 0.0f }, fBeginY{ 0.0f }, fEndX{ 0.0f }, fEndY{ 0.0f };

	// ���l�̏�����������傫�����߂����ă��C�����������߁A�n�_�ƏI�_�����߂�
	if (pAnchor[0]->GetPos().x < pAnchor[1]->GetPos().x)
	{
		fBeginX = pAnchor[0]->GetPos().x;
		fEndX = pAnchor[1]->GetPos().x;
	}
	else
	{
		fBeginX = pAnchor[1]->GetPos().x;
		fEndX = pAnchor[0]->GetPos().x;
	}

	// ����
	if (pAnchor[0]->GetPos().y < pAnchor[1]->GetPos().y)
	{
		fBeginY = pAnchor[0]->GetPos().y;
		fEndY = pAnchor[1]->GetPos().y;
	}
	else
	{
		fBeginY = pAnchor[1]->GetPos().y;
		fEndY = pAnchor[0]->GetPos().y;
	}

	// ���̃��C����2�{����
	while (fBeginX <= fEndX)
	{
		for (int nCntAnchor = 0; nCntAnchor < 2; nCntAnchor++)
		{
			CBarrier::Create(D3DXVECTOR3{ fBeginX, pAnchor[nCntAnchor]->GetPos().y, 0.0f }, D3DXVECTOR3{ 0.0f, 0.0f, D3DX_PI * 0.5f });
		}

		fBeginX += 20.0f;
	}

	// �c�̃��C����2�{����
	while (fBeginY <= fEndY)
	{
		for (int nCntAnchor = 0; nCntAnchor < 2; nCntAnchor++)
		{
			CBarrier::Create(D3DXVECTOR3{ pAnchor[nCntAnchor]->GetPos().x, fBeginY, 0.0f }, D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
		}

		fBeginY += 20.0f;
	}
}