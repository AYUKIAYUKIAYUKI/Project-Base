//============================================================================
// 
// �����_���[�Ǘ� [renderer.cpp]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "fakescreen.h"

//============================================================================
// �R���X�g���N�^
//============================================================================
CRenderer::CRenderer() : m_pD3D(nullptr), m_pD3DDevice(nullptr)
{
	m_pFont = nullptr;		// �t�H���g
	m_pTexture = nullptr;	// �e�N�X�`���Ǘ�
	m_pModel_X = nullptr;	// X���f���Ǘ�
}

//============================================================================
// �f�X�g���N�^
//============================================================================
CRenderer::~CRenderer()
{

}

//============================================================================
// �����ݒ�
//============================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindiw)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{ // �����Ɏ��s�����ꍇ
		return E_FAIL;
	}

	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{ // ���݂̃f�B�X�v���C���[�h���擾
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));	// �p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[���T�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[���T�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindiw;									// �E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// Direct3D�f�o�C�X�̐����s���@
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		// Direct3D�f�o�C�X�̐����s���A
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			// Direct3D�f�o�C�X�̐����s���B
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ?
	//ID3DXAllocateHierarchy;

	// �t�H���g�𐶐�
	D3DXCreateFont(m_pD3DDevice, 22, 0, FW_HEAVY, 1,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont);

	// �e�N�X�`���Ǘ��C���X�^���X�𐶐�
	m_pTexture = DBG_NEW CTexture;

	if (m_pTexture == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// �e�N�X�`���ǂݍ���
	m_pTexture->Load();

	// X���f���Ǘ��C���X�^���X�𐶐�
	m_pModel_X = DBG_NEW CModel_X;

	if (m_pModel_X == nullptr)
	{ // �������s
		return E_FAIL;
	}

	// X���f���ǂݍ���
	m_pModel_X->Load();

	// �^���X�N���[���̏����ݒ�
	CFakeScreen::GetInstance()->Init();

	return S_OK;
}

//============================================================================
// �I������
//============================================================================
void CRenderer::Uninit()
{
	// �S�I�u�W�F�N�g�������
	CObject::ReleaseAll();
	
	// �^���X�N���[���̔j��
	CFakeScreen::GetInstance()->Release();

	//  �e�N�X�`���j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// X���f���j��
	if (m_pModel_X != nullptr)
	{
		m_pModel_X->Unload();
		delete m_pModel_X;
		m_pModel_X = nullptr;
	}

	// �t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}

	// Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//============================================================================
// �X�V����
//============================================================================
void CRenderer::Update()
{
	// ������N���A
	m_debugStr = {};

	// �S�I�u�W�F�N�g�X�V����
	CObject::UpdateAll();

	// �^���X�N���[���̍X�V
	CFakeScreen::GetInstance()->Update();
}

//============================================================================
// �`�揈��
//============================================================================
void CRenderer::Draw()
{
	// �����_�����O�^�[�Q�b�g�ێ��p
	LPDIRECT3DSURFACE9 oldRenderTarget = nullptr;

	// �o�b�N�o�b�t�@�̏����R�s�[
	m_pD3DDevice->GetRenderTarget(0, &oldRenderTarget);

	// �����_�����O�^�[�Q�b�g�ɋ^���X�N���[���p�̃e�N�X�`�����w��
	m_pD3DDevice->SetRenderTarget(0, CFakeScreen::GetInstance()->GetSurface());

	//// ��ʃN���A
	//m_pD3DDevice->Clear(0, nullptr,
	//	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
	//	D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// �J�������Z�b�g
		CManager::GetCamera()->SetCamera();

		// �S�I�u�W�F�N�g�`�揈��
		CObject::DrawAll();

		// �V�[���̐�p�`��
		CManager::GetScene()->Draw();

		// �t�F�[�h�̕`�揈��
		CManager::GetFade()->Draw();

		// �`��I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	//m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);

	// �����_�����O�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�
	m_pD3DDevice->SetRenderTarget(0, oldRenderTarget);

	// �ێ����Ă��������_�����O�^�[�Q�b�g�j��
	if (oldRenderTarget != nullptr)
	{
		oldRenderTarget->Release();
		oldRenderTarget = nullptr;
	}

	// ��ʃN���A
	m_pD3DDevice->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// ���C���[�`��
		//m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		// �^���X�N���[����`��
		CFakeScreen::GetInstance()->Draw();

		// �f�o�b�O�\��
		PrintDebug();

		// �`��I��
		m_pD3DDevice->EndScene();
	}
	
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//============================================================================
// �f�o�b�O�\��
//============================================================================
void CRenderer::PrintDebug()
{
	// �\���ʒu
	RECT rect = { 0, 50, SCREEN_WIDTH, SCREEN_HEIGHT };

	for (int i = 0; i < m_timeStr.size(); i++)
	{
		if (m_timeStr[i].second > 0)
		{
			// �\�����Ԃ��J�E���g�_�E��
			m_timeStr[i].second--;

			// ���͂��Ȃ���
			m_debugStr += m_timeStr[i].first + "\n";
		}
		else
		{
			// ���͂�����
			m_timeStr.erase(m_timeStr.begin() + i);
		}
	}

	//�e�L�X�g�̕`��
	m_pFont->DrawText(NULL, m_debugStr.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//============================================================================
// �f�o�b�O�p������ɒǉ�
//============================================================================
void CRenderer::SetDebugString(std::string str)
{
	m_debugStr += str + "\n";
}

//============================================================================
// �������f�o�b�O������ɒǉ�
//============================================================================
void CRenderer::SetTimeString(std::string str, int nCnt)
{
	m_timeStr.push_back({ str, nCnt });
}

//============================================================================
// �f�o�C�X�̎擾
//============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDeviece()
{
	return m_pD3DDevice;
}

//============================================================================
// �e�N�X�`���Ǘ��̎擾
//============================================================================
CTexture* CRenderer::GetTextureInstane()
{
	return m_pTexture;
}

//============================================================================
// ���f���Ǘ��̎擾
//============================================================================
CModel_X* CRenderer::GetModelInstane()
{
	return m_pModel_X;
}