//============================================================================
// 
// �|���S���̕`�� 5_16 [main.cpp]
// Author : ���c����
// 
//============================================================================

#ifndef _MAIN_H_
#define _MAIN_H_	// ��d�C���N���[�h�h�~

// �C���N���[�h�t�@�C��
#include "renderer.h"

// ���_���̍\����
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���Z��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
};

CRenderer* GetRenderer(void);	// �擾

#endif // _MAIN_H_
