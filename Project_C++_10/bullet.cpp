////============================================================================
//// 
//// �e [bullet.cpp]
//// Author : ���c����
//// 
////============================================================================
//
////****************************************************
//// �C���N���[�h�t�@�C��
////****************************************************
//#include "bullet.h"
//#include "main.h"
//#include "manager.h"
//#include "explosion.h"
//
////============================================================================
//// �R���X�g���N�^
////============================================================================
//CBullet::CBullet() : CObject2D::CObject2D()
//{
//	m_pos = { 0.0f, 0.0f, 0.0f };	// ���S�ʒu
//	m_rot = { 0.0f, 0.0f, 0.0f };	// ��]��
//	m_fAngle = 0.0f;				// �p�x
//	m_size = { 0.0f, 0.0f, 0.0f };	// �T�C�Y
//	m_fLength = 0.0f;				// �Ίp��
//	m_nRemain = 0;					// �g�p����
//	m_fFlyAngle = 0;				// ��Ԋp�x
//}
//
////============================================================================
//// �f�X�g���N�^
////============================================================================
//CBullet::~CBullet()
//{
//
//}
//
////============================================================================
//// �����ݒ�
////============================================================================
//HRESULT CBullet::Init()
//{
//	// ���N���X�̏����ݒ�
//	HRESULT hr = CObject2D::Init();
//
//	return hr;
//}
//
////============================================================================
//// �I������
////============================================================================
//void CBullet::Uninit()
//{
//	// ���N���X�̏I������
//	CObject2D::Uninit();
//}
//
////============================================================================
//// �X�V����
////============================================================================
//void CBullet::Update()
//{
//	// �K�v�Ȑ��l���Z�o
//	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
//	m_fAngle = atan2f(m_size.x, m_size.y);
//
//	// ���_���ւ̃|�C���^
//	VERTEX_2D* pVtx;
//
//	// ���_�o�b�t�@���擾
//	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
//
//	// ���_�o�b�t�@�����b�N
//	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	// �ʒu�̐ݒ�
//	pVtx[0].pos = {
//		m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength,
//		m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength,
//		0.0f
//	};
//
//	pVtx[1].pos = {
//		m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
//		m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
//		0.0f
//	};
//
//	pVtx[2].pos = {
//		m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength,
//		m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength,
//		0.0f
//	};
//
//	pVtx[3].pos = {
//		m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength,
//		m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength,
//		0.0f
//	};
//
//	// ���_�o�b�t�@���A�����b�N����
//	pVtxBuff->Unlock();
//
//	// �ړ�
//	Translation();
//
//	// ���Ԍo��
//	Progress();
//}
//
////============================================================================
//// �`�揈��
////============================================================================
//void CBullet::Draw()
//{
//	// ���N���X�̕`�揈��
//	CObject2D::Draw();
//}
//
////============================================================================
//// ����
////============================================================================
//CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nRemain, float fFlyAngle)
//{
//	CBullet* pBullet = new CBullet;
//
//	// �����o���Ă����珉���ݒ�
//	if (pBullet != nullptr)
//	{
//		pBullet->Init();
//		pBullet->m_pos = pos;
//		pBullet->m_size = size;
//		pBullet->m_nRemain = nRemain;
//		pBullet->m_fFlyAngle = fFlyAngle;
//	}
//
//	// �f�o�C�X���擾
//	CRenderer* pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDev = pRenderer->GetDeviece();
//
//	// �e�N�X�`���̃|�C���^
//	LPDIRECT3DTEXTURE9 pTex = nullptr;
//
//	// �e�N�X�`���̐���
//	D3DXCreateTextureFromFile(pDev,
//		"data\\TEXTURE\\bullet000.png",
//		&pTex);
//
//	// �e�N�X�`����ݒ�
//	pBullet->BindTex(pTex);
//
//	return pBullet;
//}
//
////============================================================================
//// �ړ�
////============================================================================
//void CBullet::Translation()
//{
//	// �ݒ肳�ꂽ�p�x�ɔ��ł���
//	m_pos.x += sinf(m_fFlyAngle) * 10.0f;
//	m_pos.y += cosf(m_fFlyAngle) * 10.0f;
//}
//
////============================================================================
//// ���Ԍo��
////============================================================================
//void CBullet::Progress()
//{
//	// �g�p���ԃJ�E���g�_�E��
//	m_nRemain--;
//
//	// �g�p���Ԃ��Ȃ��Ȃ�Ə���
//	if (m_nRemain <= 0)
//	{
//		// ���g��j��
//		CObject::Release();
//
//		// �����𐶐�
//		CExplosion::Create(
//			m_pos,						// ���S�ʒu
//			{ 50.0f, 50.0f, 0.0f });	// �T�C�Y
//	}
//}