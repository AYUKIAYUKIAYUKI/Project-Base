//============================================================================
// 
// �Ƌ�A�w�b�_�t�@�C�� [furniture.h]
// Author : ���c����
// 
//============================================================================

#ifndef _FURNITURE_H_
#define _FURNITURE_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// �Ƌ�N���X
//****************************************************
class CFurniture : public CObject_X
{
public:

	CFurniture();			// �f�t�H���g�R���X�g���N�^
	~CFurniture() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CFurniture* Create(D3DXVECTOR3 pos, float fScale, CModel_X_Manager::TYPE type);	// ����
};

#endif // _FURNITURE_H_