////============================================================================
//// 
//// �����A�w�b�_�t�@�C�� [explosion.h]
//// Author : ���c����
//// 
////============================================================================
//
//#ifndef _EXPLOSION_H_
//#define _EXPLOSION_H_	// ��d�C���N���[�h�h�~
//
////****************************************************
//// �C���N���[�h�t�@�C��
////****************************************************
//#include "object_billboard.h"
//
////****************************************************
//// �����N���X
////****************************************************
//class CExplosion : public CObject_billboard
//{
//public:
//
//	CExplosion();			// �f�t�H���g�R���X�g���N�^
//	~CExplosion() override;	// �f�X�g���N�^
//
//	HRESULT Init() override;	// �����ݒ�
//	void Uninit() override;		// �I������
//	void Update() override;		// �X�V����
//	void Draw() override;		// �`�揈��
//
//	static CExplosion* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����
//
//private:
//
//	bool Animation();	// �A�j���[�V����
//
//	int m_nCntTexChange;	// �e�N�X�`���ύX�Ǘ�
//};
//
//#endif // _EXPLOSION_H_