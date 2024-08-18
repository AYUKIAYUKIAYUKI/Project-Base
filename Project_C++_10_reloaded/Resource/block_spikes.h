//============================================================================
// 
// �Ƃ��u���b�N�A�w�b�_�t�@�C�� [block_spikes.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BLOCK_SPIKES_H_
#define _BLOCK_SPIKES_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// ��u���b�N�N���X
//****************************************************
class CBlockSpikes : public CObject_X
{
public:

	CBlockSpikes();					// �f�t�H���g�R���X�g���N�^
	CBlockSpikes(LAYER priority);	// �v���C�I���e�B�w��R���X�g���N�^
	~CBlockSpikes() override;		// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CBlockSpikes* Create(D3DXVECTOR3 pos);		// ����
};

#endif // _BLOCK_SPIKES_H_