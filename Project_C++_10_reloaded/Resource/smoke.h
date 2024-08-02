//============================================================================
// 
// ���G�t�F�N�g�A�w�b�_�t�@�C�� [smoke.h]
// Author : ���c����
// 
//============================================================================

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "Object_X.h"

//****************************************************
// ���G�t�F�N�g�N���X
//****************************************************
class CSmoke : public CObject_X
{
public:

	CSmoke();	// �R���X�g���N�^
	~CSmoke();	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	D3DXVECTOR3& GetVelocity();				// �����x���擾
	void SetVelocity(D3DXVECTOR3 velocity);	// �����x��ݒ�

	static CSmoke* Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity);	// ����

private:

	D3DXVECTOR3 m_velocity;	// �����x
};