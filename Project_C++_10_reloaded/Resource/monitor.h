//============================================================================
// 
// ���j�^�[�A�w�b�_�t�@�C�� [monitor.h]
// Author : ���c����
// 
//============================================================================

#ifndef _MONITOR_H_
#define _MONITOR_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// ���j�^�[�N���X
//****************************************************
class CMonitor : public CObject_X
{
public:

	CMonitor();				// �f�t�H���g�R���X�g���N�^
	~CMonitor() override;	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CMonitor* Create(D3DXVECTOR3 pos);	// ����
};

#endif // _MONITOR_H_