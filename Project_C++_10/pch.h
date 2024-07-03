//============================================================================
// 
// �v���R���p�C���ς݃w�b�_�[ [pch.h]
// Author : ���c����
// 
//============================================================================
#pragma once	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include <stdio.h>
#include <assert.h>
#include <windows.h>	// Windows�A�v���P�[�V��������p
#include <d3dx9.h>		// DirectX9����p

#define DIRECTINPUT_VERSION	0x0800	// DirectInput�̃o�[�W����
#include <dinput.h>					// DirectInput����p
#include <xinput.h>					// �R���g���[���[����p
#include <xaudio2.h>				// �T�E���h����p

// �W�����C�u����
#include <fstream>
#include <string>
#include <vector>

//****************************************************
// ���C�u�����̃����N
//****************************************************
#pragma	comment(lib,"d3d9.lib")		// �`�揈���p
#pragma	comment(lib,"d3dx9.lib")	// [d3d9.lib]�̊g�����C�u����
#pragma	comment(lib,"dxguid.lib")	// DirectX�̃R�[�|�l���g�g�p�̂���
#pragma	comment(lib,"dinput8.lib")	// DirectInput����p
#pragma comment(lib,"xinput.lib")	// �R���g���[������p

//****************************************************
// �}�N����`
//****************************************************

// ���_�t�H�[�}�b�g
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �E�B���h�E�T�C�Y
#define SCREEN_WIDTH	1280	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	720		// �E�C���h�E�̍���