//============================================================================
// 
// �G�l�~�[ [enemy.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "enemy.h"
#include "manager.h"
#include "bullet.h"
#include "particle.h"

//****************************************************
// �ÓI�����o�ϐ��̏�����
//****************************************************
const float CEnemy::MAX_VELOCITY = 2.0f;	// �����x���
const float CEnemy::BRAKING_FORCE = 0.9f;	// ������

//============================================================================
// �R���X�g���N�^
//============================================================================
CEnemy::CEnemy() : CObject2D(static_cast<int>(LAYER::BACK_MIDDLE))
{
	m_velocity = { 0.0f, 0.0f, 0.0f };	// �����x
	m_posTarget = { 0.0f, 0.0f, 0.0f };	// �ڕW�ʒu
	m_rotTarget = { 0.0f, 0.0f, 0.0f };	// �ڕW����
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CEnemy::~CEnemy()
{
	// �p�[�e�B�N���𐶐�
	for (int i = 0; i < 10; i++)
	{
		CParticle::Create(
			GetPos(),	//�ʒu
			GetSize(),	// �T�C�Y
			atan2f((float)(rand() % 314), (float)(rand() % 314)) * (rand() % 314));	// ��Ԋp�x
	}
}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CEnemy::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject2D::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CEnemy::Uninit()
{
	// ���N���X�̏I������
	CObject2D::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CEnemy::Update()
{
	// ���݈ʒu���擾�A�ȍ~���̃R�s�[��ڕW�ʒu�Ƃ��ĕύX�������Ă���
	m_posTarget = GetPos();

	// �ړ�
	Translation();

	// ��������
	Braking();

	// �ʒu�𒲐��A���̏����̏I���ɖڕW�ʒu�𔽉f������
	AdjustPos();

	// ���N���X�̍X�V
	CObject2D::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CEnemy::Draw()
{
	// ���N���X�̕`�揈��
	CObject2D::Draw();
}

//============================================================================
// ����
//============================================================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X�𐶐�
	CEnemy* pEnemy = DBG_NEW CEnemy;

	if (pEnemy == nullptr)
	{ // �������s
		assert(false);
	}

	pEnemy->SetType(TYPE::ENEMY);	// �^�C�v��ݒ�

	pEnemy->Init();			// ���N���X�̏����ݒ�
	pEnemy->SetPos(pos);	// ���S�ʒu�̐ݒ�
	pEnemy->SetSize(size);	// �T�C�Y�̐ݒ�

	// �e�N�X�`����ݒ�
	pEnemy->BindTex(CManager::GetRenderer()->GetTextureInstane()->GetTexture(CTexture::TEX_TYPE::ENEMY_000));

	return pEnemy;
}

//============================================================================
// �ړ�
//============================================================================
void CEnemy::Translation()
{
	// �ړ�
	m_velocity.x += 5.0f;
	m_velocity.y += -0.0f;
}

//============================================================================
// ��������
//============================================================================
void CEnemy::Braking()
{
	// �����x����ɓ��B�ő��x�Œ�
	if (m_velocity.x > MAX_VELOCITY)
	{
		m_velocity.x = MAX_VELOCITY;
	}
	else if (m_velocity.x < -MAX_VELOCITY)
	{
		m_velocity.x = -MAX_VELOCITY;
	}

	if (m_velocity.y > MAX_VELOCITY)
	{
		m_velocity.y = MAX_VELOCITY;
	}
	else if (m_velocity.y < -MAX_VELOCITY)
	{
		m_velocity.y = -MAX_VELOCITY;
	}

	// �����������x������
	m_velocity = m_velocity * BRAKING_FORCE;
}

//============================================================================
// �ʒu����
//============================================================================
void CEnemy::AdjustPos()
{
	// �����x���ʒu��ϓ�
	m_posTarget += m_velocity;

	// �T�C�Y���擾
	D3DXVECTOR3 fSize = GetSize();

	// ��ʂ̍��E�[�ɓ��B�ł��ꂼ�ꃋ�[�v
	if (m_posTarget.x - fSize.x > SCREEN_WIDTH)
	{
		// �ʒu�����[�֐ݒ�
		m_posTarget.x = 0.0f - fSize.x;
	}
	else if (m_posTarget.x + fSize.x < 0.0f)
	{
		// �ʒu���E�[�֐ݒ�
		m_posTarget.x = SCREEN_WIDTH + fSize.x;
	}

	// ��ʂ̏㉺�[�ɓ��B�ł��ꂼ�ꃋ�[�v
	if (m_posTarget.y - fSize.y > SCREEN_HEIGHT)
	{
		// �ʒu����[�ɐݒ�
		m_posTarget.y = 0.0f - fSize.y;
	}
	else if (m_posTarget.y + fSize.y < 0.0f)
	{
		// �ʒu�����[�ɐݒ�
		m_posTarget.y = SCREEN_HEIGHT + fSize.y;
	}

	// �ʒu��ݒ�
	SetPos(m_posTarget);
}
