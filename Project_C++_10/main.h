//============================================================================
// 
// �|���S���̕`�� 5_16 [main.cpp]
// Author : ���c����
// 
//============================================================================

#ifndef _MAIN_H_
#define _MAIN_H_	// ��d�C���N���[�h�h�~

// �C���N���[�h�t�@�C��
#include <windows.h>
#include "d3dx9.h"

// ���C�u�����̃����N
#pragma	comment(lib,"d3d9.lib")		// �`�揈���p
#pragma	comment(lib,"d3dx9.lib")	// [d3d9.lib]�̊g�����C�u����
#pragma	comment(lib,"dxguid.lib")	// DirectX�̃R�[�|�l���g�g�p�̂���

// �}�N����`
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)	//���_�t�H�[�}�b�g
#define SCREEN_WIDTH	1280	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	720		// �E�C���h�E�̍���


// �|���S���N���X
class CPolygon
{
public:

	CPolygon();						// �R���X�g���N�^
	~CPolygon();					// �f�X�g���N�^
	void Init();					// ��������
	void Uninit();					// �I������
	void Update();					// �X�V����
	void Draw();					// �`�揈��
	static CPolygon* GetInstance();	// ���擾

private:

	// ���_���̍\����
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;	// ���_���W
		float rhw;			// ���Z��
		D3DCOLOR col;		// ���_�J���[
	};

	static CPolygon* m_pPolygon;		// �|���S�����i�[
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	VERTEX_2D m_Vtx;					// ���_���
};

#endif // _MAIN_H_
