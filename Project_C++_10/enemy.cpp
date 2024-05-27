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

//============================================================================
// �R���X�g���N�^
//============================================================================
CEnemy::CEnemy() : CObject2D::CObject2D()
{
	m_rot_tgt = { 0.0f, 0.0f, 0.0f };	// �ڕW����
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CEnemy::~CEnemy()
{
	// �p�[�e�B�N���𐶐�
	for (int i = 0; i < 10; i++)
	{
		CParticle::Create(CObject2D::GetPos(),	// ���S�ʒu
			CObject2D::GetSize() * 0.5f,		// �T�C�Y
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
	// ��]
	Rotation();

	// �ړ�
	Translation();

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
	CEnemy* pEnemy = new CEnemy;

	// �����o���Ă����珉���ݒ�
	if (pEnemy != nullptr)
	{
		pEnemy->SetType(TYPE::ENEMY);	// �^�C�v��ݒ�

		pEnemy->Init();			// ���N���X�̏����ݒ�
		pEnemy->SetPos(pos);	// ���S�ʒu�̐ݒ�
		pEnemy->SetSize(size);	// �T�C�Y�̐ݒ�
	}

	// �e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 pTex = CManager::GetTexture()->GetTex(CTexture::TEX_TYPE::ENEMY_000);

	// �e�N�X�`����ݒ�
	pEnemy->BindTex(pTex);

	return pEnemy;
}

//============================================================================
// ��]
//============================================================================
void CEnemy::Rotation()
{
	// �������擾
	D3DXVECTOR3 rot = CObject2D::GetRot();

	// �u���[�L��
	float fStopEnergy = 0.1f;

	// ��]���f�Ɖ�]�ʂ̌���
	if (m_rot_tgt.z - rot.z > D3DX_PI)
	{
		rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy + (D3DX_PI * 1.8f));
	}
	else if (m_rot_tgt.z - rot.z < -D3DX_PI)
	{
		rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		rot.z += ((m_rot_tgt.z - rot.z) * fStopEnergy);
	}

	// �������ݒ�
	CObject2D::SetRot(rot);
}

//============================================================================
// �ړ�
//============================================================================
void CEnemy::Translation()
{
	// ���S�ʒu�����擾
	D3DXVECTOR3 pos = CObject2D::GetPos();

	pos.x += 0.5f;
	pos.y += -0.5f;

	// �[�֓��B�Ń��[�v
	if ((pos.x - CObject2D::GetSize().x) > SCREEN_WIDTH)
	{
		pos.x = 0.0f - CObject2D::GetSize().x;
	}
	else if ((pos.x + CObject2D::GetSize().x) < 0.0f)
	{
		pos.x = SCREEN_WIDTH;
	}

	if ((pos.y + CObject2D::GetSize().y) < 0.0f)
	{
		pos.y = SCREEN_HEIGHT + CObject2D::GetSize().y;
	}
	else if ((pos.y - CObject2D::GetSize().y) > SCREEN_HEIGHT)
	{
		pos.y = 0.0f;
	}

	// ���S�ʒu��ݒ�
	CObject2D::SetPos(pos);
}