//============================================================================
// 
// �v���R���p�C���ς݃w�b�_�[ [pch.h]
// Author : ���c����
// 
//============================================================================
#pragma once	// ��d�C���N���[�h�h�~

// �C���N���[�h�t�@�C��
#include <windows.h>
#include "d3dx9.h"

// ���C�u�����̃����N
#pragma	comment(lib,"d3d9.lib")		// �`�揈���p
#pragma	comment(lib,"d3dx9.lib")	// [d3d9.lib]�̊g�����C�u����
#pragma	comment(lib,"dxguid.lib")	// DirectX�̃R�[�|�l���g�g�p�̂���

// �}�N����`
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g
#define SCREEN_WIDTH	1280	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	720		// �E�C���h�E�̍���