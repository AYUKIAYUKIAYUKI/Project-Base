//============================================================================
// 
// �J���� [camera.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "camera.h"
#include "utility.h"

// �C���v�b�g�擾�p
#include "manager.h"

// �f�o�C�X�擾�p
#include "renderer.h"

// �Ǐ]�n�_�Q�Ɨp
#include "game.h"
#include "player.h"
#include "dummy.h"
#include "stagemaker.h"

//============================================================================
// �f�t�H���g�R���X�g���N�^
//============================================================================
CCamera::CCamera() :
	m_pos{ 0.0f, 0.0f, 0.0f },			// �ʒu
	m_posTarget{ 0.0f, 0.0f, 0.0f },	// �ڕW�ʒu
	m_posV{ 0.0f, 0.0f, 0.0f },			// ���_�ʒu
	m_posTargetV{ 0.0f, 0.0f, 0.0f },	// �ڕW���_�ʒu
	m_posR{ 0.0f, 0.0f, 0.0f },			// �����_�ʒu
	m_posTargetR{ 0.0f, 0.0f, 0.0f },	// �ڕW�����_�ʒu
	m_rot{ 0.0f, 0.0f, 0.0f },			// ����
	m_rotTarget{ 0.0f, 0.0f, 0.0f },	// �ڕW����
	m_fDistance{ 300.0f },				// ���_ -> �����_�Ԃ̋���
	m_posBG{ 0.0f, 0.0f, 0.0f },		// �w�i���W
	m_posTargetBG{ 0.0f, 0.0f, 0.0f },	// �w�i�ڕW���W
	m_posVBG{ 0.0f, 0.0f, 0.0f },		// �w�i���_
	m_posRBG{ 0.0f, 0.0f, 0.0f },		// �w�i�����_
	m_rotBG{ 0.0f, 0.0f, 0.0f },		// �w�i����
	m_rotTargetBG{ 0.0f, 0.0f, 0.0f },	// �w�i�ڕW����
	m_fDistanceBG{ 25.0f },				// �w�i���_ -> �����_�Ԃ̋���
	m_vecU{ 0.0f, 1.0f, 0.0f },			// ������x�N�g��
	m_fAdjust{ 0.0f }					// ���Փx��
{
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
	// �A���J�[�|�C���g��ǂݍ���
	ImportAnchorPoint();

	return S_OK;
}

//============================================================================
// �X�V����
//============================================================================
void CCamera::Update()
{
	// �X�N���[���p�̍X�V
	UpdateScreen();

	// �w�i�p�̍X�V
	UpdateBG();

#ifdef _DEBUG
	// ���W���f�o�b�O�\��
	CRenderer::GetInstance()->SetDebugString("�y�w�i�J�����|�C���g�z");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << "p X:" << m_posBG.x << "\np Y:" << m_posBG.y << "\np Z:" << m_posBG.z << "\nr X:" << m_rotBG.x << "\nr Y:" << m_rotBG.y << "\nr Z:" << m_rotBG.z;
	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());
#endif	// _DEBUG
}

//============================================================================
// �w�i�p�J�������Z�b�g
//============================================================================
void CCamera::SetCameraBG()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// ��ʃo�b�t�@�N���A
	pDev->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	// ���E
	if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))
	{
		m_rotBG.y += 0.01f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_LEFT))
	{
		m_rotBG.y -= 0.01f;
	}

	// �㉺
	if (CManager::GetKeyboard()->GetPress(DIK_UP))
	{
		m_rotBG.x += 0.01f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_DOWN))
	{
		m_rotBG.x -= 0.01f;
	}

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	//// ��]�ʌ���
	//m_rotTargetBG *= 0.8f;

	//// ��]�ʔ��f
	//m_rotBG += m_rotTargetBG * 0.5f;

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	//// ��]�̐���
	//if (m_rotBG.y > D3DX_PI)
	//{
	//	m_rotBG.y = -D3DX_PI;
	//}
	//else if (m_rotBG.y < -D3DX_PI)
	//{
	//	m_rotBG.y = D3DX_PI;
	//}

	//if (m_rotBG.x + m_rotTargetBG.x > D3DX_PI * 0.48f)
	//{
	//	m_rotBG.x = D3DX_PI * 0.48f;
	//}
	//else if (m_rotBG.x + m_rotTargetBG.x < -D3DX_PI * 0.48f)
	//{
	//	m_rotBG.x = -D3DX_PI * 0.48f;
	//}

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	if (CManager::GetKeyboard()->GetPress(DIK_T))
	{
		m_posBG.y += 0.25f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_G))
	{
		m_posBG.y += -0.25f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_H))
	{
		m_posBG.x += 0.25f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_F))
	{
		m_posBG.x += -0.25f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_U))
	{
		m_posBG.z += 0.25f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_J))
	{
		m_posBG.z += -0.25f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD8))
	{
		m_fDistanceBG--;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD5))
	{
		m_fDistanceBG++;
	}
	else if(CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD2))
	{
		m_fDistanceBG = 25.0f;
	}

#ifdef _DEBUG
	CRenderer::GetInstance()->SetDebugString("��ԃY�[��� : " + std::to_string(m_fDistanceBG));
#endif	// _DEBUG

	// ���_�͑Ώە��̌����
	m_posVBG =
	{
		m_posBG.x - (sinf(m_rotBG.y) * cosf(m_rotBG.x) * (m_fDistanceBG)),
		m_posBG.y - (sinf(m_rotBG.x) * (m_fDistanceBG)),
		m_posBG.z - (cosf(m_rotBG.y) * cosf(m_rotBG.x) * (m_fDistanceBG))
	};

	// �����_��Ώە��̑O����
	m_posRBG =
	{
		m_posBG.x + (sinf(m_rotBG.y) * cosf(m_rotBG.x) * m_fDistanceBG),
		m_posBG.y + (sinf(m_rotBG.x) * m_fDistanceBG),
		m_posBG.z + (cosf(m_rotBG.y) * cosf(m_rotBG.x) * m_fDistanceBG)
	};

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	/* ��̃}�g���b�N�X��p�� */
	D3DXMATRIX mtxView;

	/* �r���[�s����v�Z */

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	// �r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&mtxView,
		&m_posVBG,
		&m_posRBG,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDev->SetTransform(D3DTS_VIEW,
		&mtxView);
}

//============================================================================
// �J�������Z�b�g
//============================================================================
void CCamera::SetCamera()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// ��ʃo�b�t�@�N���A
	pDev->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(255, 255, 255, 0), 1.0f, 0);

	// �v���W�F�N�V�����s����v�Z
	CalcMtxProjection();
	
	// �r���[�s����v�Z
	CalcMtxView();
}

//============================================================================
// �ʒu���擾
//============================================================================
D3DXVECTOR3 CCamera::GetPos()
{
	return m_pos;
}

//============================================================================
// �ʒu��ݒ�
//============================================================================
void CCamera::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================================================
// �ڕW�ʒu���擾
//============================================================================
D3DXVECTOR3 CCamera::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// �ڕW�ʒu��ݒ�
//============================================================================
void CCamera::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// �������擾
//============================================================================
D3DXVECTOR3 CCamera::GetRot()
{
	return m_rot;
}

//============================================================================
// �A���J�[�|�C���g��ǂݍ���
//============================================================================
void CCamera::ImportAnchorPoint()
{
	//for (int i = 0; i < 10; i++)
	//{
	//	/* ���Ƀ����_���Ȑ��l��ݒ� */
	//	D3DXVECTOR3 newPos = { CUtility::GetInstance()->GetRandomValue<float>() * 0.25f, CUtility::GetInstance()->GetRandomValue<float>() * 0.25f, -50.0f };
	//	D3DXVECTOR3 newRot = { 0.0f, 0.0f, 0.0f };

	//	// ���l����1�ɂ܂Ƃ߂�
	//	AnchorPoint newAP = { newPos, newRot, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 180, false };

	//	// �A���J�[�|�C���^����ǉ�
	//	m_vAnchorPoint.push_back(newAP);
	//}

	// �A���J�[�|�C���g����W�J
	std::ifstream Import{ "Data\\TXT\\AnchorPoint.txt" };

	if (!Import)
	{ // �W�J���s
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("�y�x���z�A���J�[�|�C���g���̓ǂݍ��݂Ɏ��s���܂���", 300);
#endif	// _DEBUG

		return;
#endif
	}

	// �e�L�X�g���i�[
	std::string str;

	// �t�@�C������s���A����S�Ď擾����
	while (std::getline(Import, str))
	{
		// ���l�i�[�p
		D3DXVECTOR3 newPos = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 newRot = { 0.0f, 0.0f, 0.0f };
		int nNewNumStep{ 0 };

		// ���l�ƂȂ镶���񕪗��p
		std::string value[7];

		for (int i = 0; i < 7; i++)
		{
			// ���l�����̂ݒ��o����
			value[i] = str.substr(str.find(":") + 1, str.find(",") - (str.find(":") + 1));

			// �s�K�v�ɂȂ����������폜����
			str.erase(0, str.find(",") + 1);
		}

		// ���o�������l�����W�ɕϊ�
		newPos.x = std::stof(value[0]);
		newPos.y = std::stof(value[1]);
		newPos.z = std::stof(value[2]);
		newRot.x = std::stof(value[3]);
		newRot.y = std::stof(value[4]);
		newRot.z = std::stof(value[5]);
		nNewNumStep = std::stoi(value[6]);

		// ���l����1�ɂ܂Ƃ߂�
		AnchorPoint newAP = { newPos, newRot, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, nNewNumStep, false };

		// �A���J�[�|�C���g�ɒǉ�
		m_vAnchorPoint.push_back(newAP);
	}
}

//============================================================================
// �X�N���[���p�̍X�V
//============================================================================
void CCamera::UpdateScreen()
{
	// �I�u�W�F�N�g�p�|�C���^
	CObject* pObj{ nullptr };

	// �v���C���[�^�C�v�̃I�u�W�F�N�g���擾
	pObj = CObject::FindObject(CObject::TYPE::PLAYER);

	if (pObj != nullptr)
	{ // �v���C���[�^�C�v�̎擾�ɐ���

		// �v���C���[�N���X�Ƀ_�E���L���X�g
		CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(pObj);

		// �ʒu�𓯊�
		m_pos = pPlayer->GetPos();
		m_fAdjust = 50.0f;
	}
	else
	{ // �v���C���[�^�C�v�̎擾�Ɏ��s

		// �_�~�[�^�C�v�̃I�u�W�F�N�g���擾
		pObj = CObject::FindObject(CObject::TYPE::DUMMY);

		if (pObj != nullptr)
		{ // �_�~�[�^�C�v�̎擾�ɐ���

			// �_�~�[�N���X�Ƀ_�E���L���X�g
			CDummy* pDummy = CUtility::GetInstance()->DownCast<CDummy, CObject>(pObj);

			// �ʒu�𓯊�
			m_pos = pDummy->GetPos();
			m_fAdjust = 0.0f;
		}
	}

	// �J��������
	Control();

	// ��]
	Rotation();

	// �ړ�
	//Translation();

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
	// �Ǐ]�x��
	float fTracking = 0.25f;

	// �ړ��ʔ��f
	// posTarget�ɒl��ݒ肵�Ă��Ȃ��ꍇ�͐��l�����������Ȃ�܂�
	m_pos += (m_posTarget - m_pos) * fTracking;
}

//============================================================================
// ���[�p�͈̔͂𐧌�
//============================================================================
void CCamera::RestrictYaw()
{
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
// �w�i�p�̍X�V
//============================================================================
void CCamera::UpdateBG()
{
	// ���݂̃��[�h���擾
	CScene::MODE mode{ CManager::GetScene()->GetMode() };

	// �A���J�[�|�C���g�̔ԍ�
	static int nNumElement{ 0 };

	// �����l -> �ڕW���l�ւ̕�ԑ��x���i�[
	float fCoeff{ 0.0f };

	if (mode == CScene::MODE::STAGE)
	{
		// �������s��Ȃ�
		return;
	}
	else if (mode == CScene::MODE::GAME)
	{
		// �w�i�p�J�����̖ڕW���W�E�ڕW�������A�ێ����Ă���ڕW���l�Ƃ͕ʓr�ŌŒ肷��
		D3DXVECTOR3 posTarget = { -3.0f, 0.0f, 0.0f };
		D3DXVECTOR3 rotTarget = { 0.0f, 0.0f, 0.0f };

		// ��ԑ��x��ݒ�
		fCoeff = 0.1f;

		// �ڕW���W�֔���
		m_posBG = CUtility::GetInstance()->AdjustToTarget(m_posBG, posTarget, fCoeff);

		// �ڕW�����֔���
		m_rotBG = CUtility::GetInstance()->AdjustToTarget(m_rotBG, rotTarget, fCoeff);

		// �A���J�[�|�C���g�̔ԍ������Z�b�g
		/* �R�����g�A�E�g�ŃQ�[���J�n���̃|�C���g���瑱���悤�Ɍ����� */
		nNumElement = 0;

		//// �A���J�[�|�C���g�ւ̑����ʂ��A���̍��W����Čv�Z����
		///* �����l�ƖڕW���l��������Ă���ꍇ�s�v */
		//for (auto&& it : m_vAnchorPoint)
		//{
		//	it.bSet = false;
		//}
	}
	else
	{
		// �A���J�[�|�C���g�������ʐݒ���I���Ă��Ȃ����
		if (!m_vAnchorPoint[nNumElement].bSet)
		{
			// ���鐔
			float nDivider{ static_cast<float>(m_vAnchorPoint[nNumElement].nNumStep) };

			// �����ʂ̐ݒ���s��
			m_vAnchorPoint[nNumElement].stepPos = (m_vAnchorPoint[nNumElement].pos - m_posTargetBG) / nDivider;
			m_vAnchorPoint[nNumElement].stepRot = (m_vAnchorPoint[nNumElement].rot - m_rotTargetBG) / nDivider;

			// �ݒ���I������
			m_vAnchorPoint[nNumElement].bSet = true;
		}

		if (fabsf(m_vAnchorPoint[nNumElement].pos.x - m_posTargetBG.x) >= 0.01f)
		{ // �ڕW�n�_�Ƃ̍���������x�����

			// ��Ԃ��Ă���
			m_posTargetBG += m_vAnchorPoint[nNumElement].stepPos;
			m_rotTargetBG += m_vAnchorPoint[nNumElement].stepRot;
		}
		else
		{ // �قƂ�ǖڕW�n�_�ɓ��B��

			// ���̃|�C���g�ł̑����ʐݒ�����Z�b�g����
			m_vAnchorPoint[nNumElement].bSet = false;
			
			// ���̃|�C���g�֐i��
			nNumElement++;

			// �Ō�̃|�C���g�ɓ��B������ŏ��֖߂�
			if (nNumElement >= m_vAnchorPoint.size())
			{
				nNumElement = 0;
			}

#ifdef _DEBUG
			CRenderer::GetInstance()->SetTimeString("���̃A���J�[�|�C���g : " + std::to_string(nNumElement), 300);
#endif	// _DEBUG
		}

		// ��ԑ��x��ݒ肷��
		fCoeff = 0.01f;

		// �ڕW���W�֔���
		m_posBG = CUtility::GetInstance()->AdjustToTarget(m_posBG, m_posTargetBG, fCoeff);

		// �ڕW�����֔���
		m_rotBG = CUtility::GetInstance()->AdjustToTarget(m_rotBG, m_rotTargetBG, fCoeff);
	}

#ifdef _DEBUG
	// ���̃A���J�[�|�C���g���f�o�b�O�\��
	CRenderer::GetInstance()->SetDebugString("�y�����|�C���g�z");
	std::ostringstream oss0;
	oss0 << std::fixed << std::setprecision(2) << "p X:" << m_vAnchorPoint[nNumElement].pos.x << "\np Y:" << m_vAnchorPoint[nNumElement].pos.y << "\np Z:" << m_vAnchorPoint[nNumElement].pos.z << "\nr X:" << m_vAnchorPoint[nNumElement].rot.x << "\nr Y:" << m_vAnchorPoint[nNumElement].rot.y << "\nr Z:" << m_vAnchorPoint[nNumElement].rot.z;
	CRenderer::GetInstance()->SetDebugString(oss0.str().c_str());

	// �ڕW���W���f�o�b�O�\��
	CRenderer::GetInstance()->SetDebugString("�y�w�i�J�����ڕW�|�C���g");
	std::ostringstream oss1;
	oss1 << std::fixed << std::setprecision(2) << "p X:" << m_posTargetBG.x << "\np Y:" << m_posTargetBG.y << "\np Z:" << m_posTargetBG.z << "\nr X:" << m_rotTargetBG.x << "\nr Y:" << m_rotTargetBG.y << "\nr Z:" << m_rotTargetBG.z;
	CRenderer::GetInstance()->SetDebugString(oss1.str().c_str());
#endif	// _DEBUG
}

//============================================================================
// �v���W�F�N�V�����s��v�Z
//============================================================================
void CCamera::CalcMtxProjection()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

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
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// ���_�ʒu�̒����p
	D3DXVECTOR3 posV = m_posV;
	D3DXVECTOR3 posR = m_posR;

	// �J��������ՋC����
	//posV.y += m_fAdjust;

	// �r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,
		&posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDev->SetTransform(D3DTS_VIEW,
		&m_mtxView);
}