//============================================================================
// 
// �Ƃ��ړ��u���b�N [block_spikes_move.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "block_spikes_move.h"
#include "utility.h"

// �f�o�b�O�\��
#include "renderer.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CBlockSpikesMove::CBlockSpikesMove() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },
	m_posHold{ 0.0f, 0.0f, 0.0f },
	m_fAngle{ 0.0f },
	m_fAdder{ 0.0f },
	m_fCoeff{ 0.0f }
{

}

//============================================================================
// �v���C�I���e�B�w��R���X�g���N�^
//============================================================================
CBlockSpikesMove::CBlockSpikesMove(LAYER priority) :
	CObject_X{ static_cast<int>(priority) },
	m_posHold{ 0.0f, 0.0f, 0.0f },
	m_fAngle{ 0.0f },
	m_fAngleInit{ 0.0f },
	m_fAdder{ 0.0f },
	m_fCoeff{ 0.0f }
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CBlockSpikesMove::~CBlockSpikesMove()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CBlockSpikesMove::Init()
{
	// �����p�x�𔽉f
	m_fAngle = m_fAngleInit;

	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CBlockSpikesMove::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CBlockSpikesMove::Update()
{
	// �ړ�
	Translate();

	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CBlockSpikesMove::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// �z�[���h���W��ݒ�
//============================================================================
void CBlockSpikesMove::SetPosHold(D3DXVECTOR3 pos)
{
	m_posHold = pos;
}

//============================================================================
// �z�[���h���W���擾
//============================================================================
D3DXVECTOR3 CBlockSpikesMove::GetPosHold()
{
	return m_posHold;
}

//============================================================================
// �����p�x�̎擾
//============================================================================
float CBlockSpikesMove::GetAngleInit()
{
	return m_fAngleInit;
}

//============================================================================
// �����p�x�̐ݒ�
//============================================================================
void CBlockSpikesMove::SetAngleInit(float fAngleInit)
{
	m_fAngleInit = fAngleInit;
}

//============================================================================
// �p�x�̎擾
//============================================================================
float CBlockSpikesMove::GetAngle()
{
	return m_fAngle;
}

//============================================================================
// �p�x�̐ݒ�
//============================================================================
void CBlockSpikesMove::SetAngle(float fAngle)
{
	m_fAngle = fAngle;
}


//============================================================================
// �����ʂ̎擾
//============================================================================
float CBlockSpikesMove::GetAdder()
{
	return m_fAdder;
}

//============================================================================
// �����ʂ̐ݒ�
//============================================================================
void CBlockSpikesMove::SetAdder(float fAdder)
{
	m_fAdder = fAdder;
}

//============================================================================
// ���f�W���̎擾
//============================================================================
float CBlockSpikesMove::GetCoeff()
{
	return m_fCoeff;
}

//============================================================================
// ���f�W���̐ݒ�
//============================================================================
void CBlockSpikesMove::SetCoeff(float fCoeff)
{
	m_fCoeff = fCoeff;
}

//============================================================================
// ����
//============================================================================
CBlockSpikesMove* CBlockSpikesMove::Create(D3DXVECTOR3 pos, float fAngle, float fAdder, float fCoeff)
{
	// �C���X�^���X�𐶐�
	CBlockSpikesMove* pBlockSpikesMove = DBG_NEW CBlockSpikesMove{ LAYER::MIDDLE };

	if (pBlockSpikesMove == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pBlockSpikesMove->SetType(TYPE::SPIKES_MOVE);

	// �z�[���h���W�̐ݒ� (��s)
	pBlockSpikesMove->SetPosHold(pos);

	// �����p�x�̐ݒ� (�ݒ�)
	pBlockSpikesMove->SetAngleInit(fAngle);

	// �����ʂ̐ݒ�
	pBlockSpikesMove->SetAdder(fAdder);

	// ���f�W���̐ݒ�
	pBlockSpikesMove->SetCoeff(fCoeff);

	// ���N���X�̏����ݒ�
	pBlockSpikesMove->Init();

	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::SPIKES_MOVE);

	// ���f����ݒ�
	pBlockSpikesMove->BindModel(model);

	// �T�C�Y��ݒ�
	pBlockSpikesMove->SetSize(model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pBlockSpikesMove->Update();

	return pBlockSpikesMove;
}

//============================================================================
// �ړ�
//============================================================================
void CBlockSpikesMove::Translate()
{
	// �V�������W���쐬
	D3DXVECTOR3 newPos{ GetPosHold() };

	// �p�x�𑝉�
	m_fAngle += m_fAdder;

	if (m_fAngle > D3DX_PI)
	{
		m_fAngle += -D3DX_PI * 2.0f;
	}
	else if (m_fAngle < -D3DX_PI)
	{
		m_fAngle += D3DX_PI * 2.0f;
	}

	// ���炳�ꂽ���W����_�Ɍʂ�`���悤�Ɉړ�
	newPos += {
		sinf(m_fAngle) * m_fCoeff,
		cosf(m_fAngle) * m_fCoeff,
		0.0f
	};

	CRenderer::GetInstance()->SetDebugString("�ړ��Ƃ� : " + std::to_string(newPos.x) + " : " + std::to_string(newPos.y) + " : " + std::to_string(m_fAngle));

	// ���W�𔽉f
	SetPos(newPos);
}

//============================================================================
// �p�x����ă��Z�b�g
//============================================================================
void CBlockSpikesMove::ResetAngleAll()
{
	// �u���b�N�^�C�v�̃I�u�W�F�N�g�����ׂĎ擾
	CObject** pObject = CObject::FindAllObject(CObject::TYPE::SPIKES_MOVE);

	// �Ƃ��ړ��u���b�N�^�C�v�̃I�u�W�F�N�g�����ׂĎ擾
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES_MOVE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// �I�u�W�F�N�g�̏�񂪖����Ȃ�����I��
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// �Ƃ��ړ��u���b�N�N���X�փ_�E���L���X�g
		CBlockSpikesMove* pSpike_Move = CUtility::GetInstance()->DownCast<CBlockSpikesMove, CObject>(pObject[nCntObj]);

		// �p�x�����Z�b�g
		pSpike_Move->SetAngle(pSpike_Move->GetAngleInit());
	}
}