//============================================================================
// 
// �J���� [camera.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************s
// �C���N���[�h�t�@�C��
//****************************************************
#include "camera.h"
#include "main.h"
#include "manager.h"

// �Ǐ]�n�_�Q�Ɨp
#include "game.h"
#include "player.h"
#include "stagemaker.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CCamera::CCamera()
{
	m_pos = { 0.0f, 0.0f, 0.0f };			// �ʒu
	m_posTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW�ʒu
	m_posV = { 0.0f, 0.0f, 0.0f };			// ���_�ʒu
	m_posTargetV = { 0.0f, 0.0f, 0.0f };	// �ڕW���_�ʒu
	m_posR = { 0.0f, 0.0f, 0.0f };			// �����_�ʒu
	m_posTargetR = { 0.0f, 0.0f, 0.0f };	// �ڕW�����_�ʒu
	m_rot = { 0.0f, 0.0f, 0.0f };			// ����
	m_rotTarget = { 0.0f, 0.0f, 0.0f };		// �ڕW����
	m_fDistance = 300.0f;					// ���_ -> �����_�Ԃ̋���
	m_vecU = { 0.0f, 1.0f, 0.0f };			// ������x�N�g��
	D3DXMatrixIdentity(&m_mtxProjection);	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxView);			// �r���[�}�g���b�N�X
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CCamera::~CCamera()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CCamera::Init()
{
	return S_OK;
}

//============================================================================
// �X�V����
//============================================================================
void CCamera::Update()
{
	// �V�[�����擾
	CScene* pScene = CManager::GetScene();

	// �V�[���N���X���Q�[���N���X�փ_�E���L���X�g
	CGame* pGame = dynamic_cast<CGame*>(pScene);

	// �_�E���L���X�g�ɐ��������ꍇ�̂�
	if (pGame != nullptr)
	{
		// �X�e�[�W�쐬���[�h�Ȃ�
		if (pGame->GetStageMaking())
		{
			// �J�����̈ʒu��ύX
			m_pos = CStageMaker::GetInstance()->GetPos();
		}
		else
		{
			for (int nCntPriority = 0; nCntPriority < static_cast<int>(CObject::LAYER::MAX); nCntPriority++)
			{
				for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
				{
					// �I�u�W�F�N�g�����擾
					CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

					if (pObject == nullptr)
					{ // ��񂪂Ȃ���΃R���e�B�j���[
						continue;
					}

					if (pObject->GetType() == CObject::TYPE::PLAYER)
					{ // �v���C���[�^�C�v�Ȃ�

						// �v���C���[�N���X�̃|�C���^
						CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);

						if (pPlayer == nullptr)
						{ // �_�E���L���X�g���s
							assert(false);
						}

						m_pos = pPlayer->GetPos();
					}
				}
			}
		}
	}
	else
	{
		for (int nCntPriority = 0; nCntPriority < static_cast<int>(CObject::LAYER::MAX); nCntPriority++)
		{
			for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
			{
				// �I�u�W�F�N�g�����擾
				CObject* pObject = CObject::GetObject(nCntPriority, nCntObj);

				if (pObject == nullptr)
				{ // ��񂪂Ȃ���΃R���e�B�j���[
					continue;
				}

				if (pObject->GetType() == CObject::TYPE::PLAYER)
				{ // �v���C���[�^�C�v�Ȃ�

					// �v���C���[�N���X�̃|�C���^
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);

					if (pPlayer == nullptr)
					{ // �_�E���L���X�g���s
						assert(false);
					}

					m_pos = pPlayer->GetPos();
				}
			}
		}
	}

	// �J��������
	//Control();

	// ��]
	Rotation();

	// �ړ�
	Translation();

	// ���[�p�͈̔͂𐧌�
	RestrictYaw();

	// �s�b�`�p�͈̔͂𐧌�
	RestrictPitch();

	// ���_�ʒu���Z�o
	CalcPosV();

	// �����_�ʒu���Z�o
	CalcPosR();
}

//============================================================================
// �J�������Z�b�g
//============================================================================
void CCamera::SetCamera()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// ��ʃo�b�t�@�N���A
	pDev->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �v���W�F�N�V�����s����v�Z
	CalcMtxProjection();
	
	// �r���[�s����v�Z
	CalcMtxView();
}

//============================================================================
// �������擾
//============================================================================
D3DXVECTOR3 CCamera::GetRot()
{
	return m_rot;
}

//============================================================================
// �J��������
//============================================================================
void CCamera::Control()
{
	// �Y�[���C�� / �A�E�g
	if (CManager::GetKeyboard()->GetPress(DIK_AT) && m_fDistance > 10.0f)
	{
		m_fDistance -= 10.0f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_COLON))
	{
		m_fDistance += 10.0f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_BACKSLASH))
	{
		// �����ԃ��Z�b�g
		m_fDistance = 200.0f;
	}

	// ���E
	if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))
	{
		m_rotTarget.y += 0.02f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_LEFT))
	{
		m_rotTarget.y -= 0.02f;
	}

	// �㉺
	if (CManager::GetKeyboard()->GetPress(DIK_UP))
	{
		m_rotTarget.x += 0.02f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_DOWN))
	{
		m_rotTarget.x -= 0.02f;
	}
}

//============================================================================
// ��]
//============================================================================
void CCamera::Rotation()
{
	// ��]�ʌ���
	m_rotTarget *= 0.8f;

	// ��]�ʔ��f
	m_rot += m_rotTarget * 0.5f;
}

//============================================================================
// �ړ�
//============================================================================
void CCamera::Translation()
{
	// �ړ��ʌ���
	m_posTarget *= 0.8f;

	// �ړ��ʔ��f
	m_pos += m_posTarget * 0.5f;
}

//============================================================================
// ���[�p�͈̔͂𐧌�
//============================================================================
void CCamera::RestrictYaw()
{
	// ��]�̐���
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}
}

//============================================================================
// �s�b�`�p�͈̔͂𐧌�
//============================================================================
void CCamera::RestrictPitch()
{
	if (m_rot.x + m_rotTarget.x > D3DX_PI * 0.48f)
	{
		m_rot.x = D3DX_PI * 0.48f;
	}
	else if (m_rot.x + m_rotTarget.x < -D3DX_PI * 0.48f)
	{
		m_rot.x = -D3DX_PI * 0.48f;
	}
}

//============================================================================
// ���_�ʒu���Z�o
//============================================================================
void CCamera::CalcPosV()
{
	// ���_�͑Ώە��̌����
	m_posV =
	{
		m_pos.x - (sinf(m_rot.y) * cosf(m_rot.x) * (m_fDistance)),
		m_pos.y - (sinf(m_rot.x) * (m_fDistance)),
		m_pos.z - (cosf(m_rot.y) * cosf(m_rot.x) * (m_fDistance))
	};
}

//============================================================================
// �����_�ʒu���Z�o
//============================================================================
void CCamera::CalcPosR()
{
	// �����_��Ώە��̑O����
	m_posR =
	{
		m_pos.x + (sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance),
		m_pos.y + (sinf(m_rot.x) * m_fDistance),
		m_pos.z + (cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance)
	};
}

//============================================================================
// �v���W�F�N�V�����s��v�Z
//============================================================================
void CCamera::CalcMtxProjection()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// �v���W�F�N�V�����s��̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����s��𐶐�
#if 1
	// �������e
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		5000.0f);
#else
	// ���s���e
	D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_WIDTH * 0.25f,
		(float)SCREEN_HEIGHT * 0.25f,
		10.0f,
		5000.0f);
#endif

	// �v���W�F�N�V�����s��̐ݒ�
	pDev->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}

//============================================================================
// �r���[�s��v�Z
//============================================================================
void CCamera::CalcMtxView()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CManager::GetRenderer()->GetDeviece();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// ���_�ʒu�̒����p
	D3DXVECTOR3 posV = m_posV;
	D3DXVECTOR3 posR = m_posR;

	// �J��������ՋC����
	posV.y += 50.0f;

	// �r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,
		&posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDev->SetTransform(D3DTS_VIEW,
		&m_mtxView);
}