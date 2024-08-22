//============================================================================
// 
// �t���ρA�w�b�_�t�@�C�� [leaf.h]
// Author : ���c����
// 
//============================================================================

#ifndef _LEAF_H_
#define _LEAF_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_billboard.h"

// �e�N�X�`���擾�p
#include "texture_manager.h"

//****************************************************
// �t���σN���X
//****************************************************
class CLeaf : public CObject_billboard
{
public:

	CLeaf();				// �f�t�H���g�R���X�g���N�^
	~CLeaf() override;		// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static void UpdateToCreate();	// �����p�X�V
	static CLeaf* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);	// ����

private:

	//****************************************************
	// �U���̎��
	//****************************************************
	enum class OSCILLATION
	{
		NONE = 0,	// ����
		WEAK,		// ���
		MODERATE,	// ����
		STRONG,		// ����
		MAX
	};

	void Rotate();		// ��]
	void Translate();	// �ړ�
	
	static OSCILLATION GetRandomOscillation();		// �����_���ȐU���̎�ނ��擾
	static LPDIRECT3DTEXTURE9 GetRandomTexture();	// �����_���ȗt���σe�N�X�`���̎�ނ��擾

	OSCILLATION m_type;		// �U���̎��
	D3DXVECTOR3 m_velocity;	// �����x

	static int m_nCntSpawn;	// �����Ԋu
};

#endif // _LEAF_H_