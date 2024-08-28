//============================================================================
// 
// ���j�^�[ [monitor.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "monitor.h"
#include "utility.h"

// ���j�^�[��ʕ`��p
//#include "fakescreen.h"
#include "renderer.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CMonitor::CMonitor() :
	CObject_X{ static_cast<int>(LAYER::BG) },	// �`��D��x���w��
	m_velocity{ 0.0f, 0.0f, 0.0f },				// �����x
	m_bAppear{ false }							// �o���t���O
{

}

//============================================================================
// �f�X�g���N�^
//============================================================================
CMonitor::~CMonitor()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CMonitor::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_X::Init();

	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::MONITOR);

	// ���j�^�[�̉�ʕ����ɋ^���X�N���[����`�悷��
	//model->ppTex[1] = CFakeScreen::GetInstance()->GetTexture();
	model->ppTex[0] = CRenderer::GetInstance()->GetTexture();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CMonitor::Uninit()
{
	// ���N���X�̏I������
	CObject_X::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CMonitor::Update()
{
	//if (!m_bAppear)
	//{
	//	// �o��
	//	m_bAppear = Appear();
	//}

	// ���N���X�̍X�V
	CObject_X::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CMonitor::Draw()
{
	// ���N���X�̕`�揈��
	CObject_X::Draw();
}

//============================================================================
// ����
//============================================================================
CMonitor* CMonitor::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X�𐶐�
	CMonitor* pMonitor = DBG_NEW CMonitor;

	if (pMonitor == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pMonitor->SetType(TYPE::NONE);

	// ���N���X�̏����ݒ�
	pMonitor->Init();

	// ���W�̐ݒ�
	pMonitor->SetPos({ 0.0f, 0.0f, 0.0f });

	// ���f�����擾
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::MONITOR);

	// ���f����ݒ�
	pMonitor->BindModel(model);

	// �T�C�Y��ݒ�
	pMonitor->SetSize(model->size);

	// �`�悳���O�Ɉ�x�X�V���Ă���
	pMonitor->Update();

	return pMonitor;
}

//============================================================================
// �o��
//============================================================================
bool CMonitor::Appear()
{
	// �d�͉���
	m_velocity.y += -0.2f;
	//m_velocity.y *= 1.01f;
	
	// ���W��ύX
	D3DXVECTOR3 posTarget = GetPos();
	posTarget += m_velocity;
	SetPos(posTarget);

	if (posTarget.y < 0.0f)
	{
		// ���W�Ɖ����x�����Z�b�g
		m_velocity = Recoil();
		//posTarget.y = 0.0f;

		// ���W�𔽉f
		//SetPos(posTarget);
	
		// �o���I��
		//return true;
	}

	return false;
}

//============================================================================
// ����
//============================================================================
D3DXVECTOR3 CMonitor::Recoil()
{
	// ���������̊p�x���Z�o
	float fDropAngle = atan2f(m_velocity.x, m_velocity.y);
	CRenderer::GetInstance()->SetTimeString("�܂�" + std::to_string(fDropAngle), 800);

	// �����̉����x��ێ�
	D3DXVECTOR3 recoilVelocity{ 0.0f, 0.0f, 0.0f };

	// �����̉����x���Z�o
	//recoilVelocity.x = -sinf(fDropAngle) * 2.0f;
	recoilVelocity.y = -cosf(fDropAngle) * 4.0f;

	//CRenderer::GetInstance()->SetTimeString("������" + std::to_string(recoilVelocity.x), 800);
	CRenderer::GetInstance()->SetTimeString("��������" + std::to_string(recoilVelocity.y), 800);

	return recoilVelocity;
}