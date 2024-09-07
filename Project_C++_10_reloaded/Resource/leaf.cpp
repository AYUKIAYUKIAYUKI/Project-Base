//============================================================================
// 
// �t���� [leaf.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "leaf.h"
#include "utility.h"

// �I�u�W�F�N�g�p
#include "player.h"

//****************************************************
// �ÓI�����o�̏�����
//****************************************************
int CLeaf::m_nCntSpawn = 0;	// �����Ԋu

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CLeaf::CLeaf() :
	CObject_billboard{ static_cast<int>(LAYER::MIDDLE) },	// �`��D��x���w��
	m_type{ CLeaf::OSCILLATION::NONE },						// �U���̎��
	m_velocity{ 0.0f, 0.0f, 0.0f }							// �����x
{
	// �����_���ȃ^�C�v��ݒ�
	m_type = GetRandomOscillation();

	// �������擾
	D3DXVECTOR3 rotTarget = GetRot();

	// �ڕW�����������_���ɐݒ�
	rotTarget.z = CUtility::GetInstance()->GetRandomValue<float>();

	// �ڕW�����𔽉f
	SetRot(rotTarget);
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CLeaf::~CLeaf()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CLeaf::Init()
{
	// ���N���X�̏����ݒ�
	HRESULT hr = CObject_billboard::Init();

	return hr;
}

//============================================================================
// �I������
//============================================================================
void CLeaf::Uninit()
{
	// ���N���X�̏I������
	CObject_billboard::Uninit();
}

//============================================================================
// �X�V����
//============================================================================
void CLeaf::Update()
{
	// ��]
	Rotate();

	// �ړ�
	Translate();

	// �k��
	D3DXVECTOR3 size = GetSize();
	size *= 0.99f;
	SetSize(size);

	if (size.x <= 0.1f || size.y <= 0.11f)
	{
		// �j���\��
		SetRelease();
	}

	// ���N���X�̍X�V
	CObject_billboard::Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CLeaf::Draw()
{
	// ���N���X�̕`�揈��
	CObject_billboard::Draw();
}

//============================================================================
// �����p�X�V
//============================================================================
void CLeaf::UpdateToCreate()
{
	m_nCntSpawn++;

	if (m_nCntSpawn > 10)
	{
		m_nCntSpawn = 0;

		// �v���C���[���擾
		CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(CObject::FindObject(CObject::TYPE::PLAYER));

		// �o�����W��ݒ肷��
		D3DXVECTOR3 posTarget{ 0.0f, 0.0f, 0.0f };

		if (rand() % 2 == 0)
		{
			posTarget.x = pPlayer->GetPos().x + 100.0f + (rand() % 50);
		}
		else
		{
			posTarget.x = pPlayer->GetPos().x + - 100.0f - (rand() % 50);
		}

		posTarget.y = pPlayer->GetPos().y + 250.0f;


		// ����
		auto p = Create(posTarget, pPlayer->GetSize(), GetRandomTexture());
		p->m_velocity.y = -1.0f;

		p->m_velocity = { CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, -3.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f };
	}
}

//============================================================================
// ����
//============================================================================
CLeaf* CLeaf::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	// �C���X�^���X�𐶐�
	CLeaf* pLeaf = DBG_NEW CLeaf{};

	if (pLeaf == nullptr)
	{ // �������s
		assert(false);
	}

	// �^�C�v��ݒ�
	pLeaf->SetType(TYPE::NONE);

	// ���N���X�̏����ݒ�
	pLeaf->Init();

	// �ʒu�̐ݒ�
	pLeaf->SetPos(pos);

	// �T�C�Y�̐ݒ�
	pLeaf->SetSize(size);

	// �e�N�X�`����ݒ�
	pLeaf->BindTex(tex);

	return pLeaf;
}

//============================================================================
// ��]
//============================================================================
void CLeaf::Rotate()
{
	// �������擾
	D3DXVECTOR3 rotTarget = GetRot();

	// �ڕW�����ɉ����x�����Z
	rotTarget.z += CUtility::GetInstance()->GetRandomValue<float>() * 0.0001f;

	// �ڕW�����𔽉f
	SetRot(rotTarget);
}

//============================================================================
// �ړ�
//============================================================================
void CLeaf::Translate()
{
	// ���W���擾
	D3DXVECTOR3 posTarget = GetPos();

	// �ڕW���W�ɉ����x�����Z
	posTarget += m_velocity;

	// �ڕW���W�𔽉f
	SetPos(posTarget);
}

//============================================================================
// �����_���ȗt���σe�N�X�`���̎�ނ��擾
//============================================================================
LPDIRECT3DTEXTURE9 CLeaf::GetRandomTexture()
{
	LPDIRECT3DTEXTURE9 tex{ nullptr };

	switch (rand() % 5)
	{
	case 0:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_00);
		break;

	case 1:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_01);
		break;

	case 2:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_02);
		break;

	case 3:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_03);
		break;

	case 4:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_04);
		break;

	default:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_00);
		break;
	}

	return tex;
}

//============================================================================
// �����_���ȐU���̎�ނ��擾
//============================================================================
CLeaf::OSCILLATION CLeaf::GetRandomOscillation()
{
	return static_cast<OSCILLATION>(rand() % static_cast<int>(OSCILLATION::MAX));
}