#include "stdafx.h"
#include "Effect.h"

#include "BackGround.h"


///////////////////////////////////////////////////////////////////
// �O���[�o���ϐ��B
///////////////////////////////////////////////////////////////////
HWND			g_hWnd = NULL;				//�E�B���h�E�n���h���B
CCamera* g_camera3D = NULL;					//3D�J�����B
GraphicsEngine* g_graphicsEngine = NULL;	//�O���t�B�b�N�X�G���W���B

BackGround g_backGround;					//�w�i�B
Player g_player;							//�v���C���[�B

///////////////////////////////////////////////////////////////////
// DirectX�̏I�������B
///////////////////////////////////////////////////////////////////
void ReleaseDirectX()
{
	delete g_camera3D;
	delete g_graphicsEngine;
	
}
///////////////////////////////////////////////////////////////////
//���b�Z�[�W�v���V�[�W���B
//hWnd�����b�Z�[�W�𑗂��Ă����E�B���h�E�̃n���h���B
//msg�����b�Z�[�W�̎�ށB
//wParam��lParam�͈����B���͋C�ɂ��Ȃ��Ă悢�B
///////////////////////////////////////////////////////////////////
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//�����Ă������b�Z�[�W�ŏ����𕪊򂳂���B
	switch (msg)
	{
	case WM_DESTROY:
		ReleaseDirectX();
		PostQuitMessage(0);
		break;	
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

///////////////////////////////////////////////////////////////////
// �E�B���h�E�̏������B
///////////////////////////////////////////////////////////////////
void InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�N���X�̃p�����[�^��ݒ�(�P�Ȃ�\���̂̕ϐ��̏������ł��B)
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),		//�\���̂̃T�C�Y�B
		CS_CLASSDC,				//�E�B���h�E�̃X�^�C���B
								//�����̎w��ŃX�N���[���o�[��������ł��邪�A�Q�[���ł͕s�v�Ȃ̂�CS_CLASSDC�ł悢�B
		MsgProc,				//���b�Z�[�W�v���V�[�W��(��q)
		0,						//0�ł����B
		0,						//0�ł����B
		GetModuleHandle(NULL),	//���̃N���X�̂��߂̃E�C���h�E�v���V�[�W��������C���X�^���X�n���h���B
								//�����C�ɂ��Ȃ��Ă悢�B
		NULL,					//�A�C�R���̃n���h���B�A�C�R����ς������ꍇ������ύX����B�Ƃ肠��������ł����B
		NULL,					//�}�E�X�J�[�\���̃n���h���BNULL�̏ꍇ�̓f�t�H���g�B
		NULL,					//�E�B���h�E�̔w�i�F�BNULL�̏ꍇ�̓f�t�H���g�B
		NULL,					//���j���[���BNULL�ł����B
		TEXT("Sample_01"),		//�E�B���h�E�N���X�ɕt���閼�O�B
		NULL					//NULL�ł����B
	};
	//�E�B���h�E�N���X�̓o�^�B
	RegisterClassEx(&wc);

	// �E�B���h�E�̍쐬�B
	g_hWnd = CreateWindow(
		TEXT("Sample_01"),		//�g�p����E�B���h�E�N���X�̖��O�B
								//��قǍ쐬�����E�B���h�E�N���X�Ɠ������O�ɂ���B
		TEXT("Sample_01"),		//�E�B���h�E�̖��O�B�E�B���h�E�N���X�̖��O�ƕʖ��ł��悢�B
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C���B�Q�[���ł͊�{�I��WS_OVERLAPPEDWINDOW�ł����A
		0,						//�E�B���h�E�̏���X���W�B
		0,						//�E�B���h�E�̏���Y���W�B
		(UINT)FRAME_BUFFER_W,	//�E�B���h�E�̕��B
		(UINT)FRAME_BUFFER_H,	//�E�B���h�E�̍����B
		NULL,					//�e�E�B���h�E�B�Q�[���ł͊�{�I��NULL�ł����B
		NULL,					//���j���[�B����NULL�ł����B
		hInstance,				//�A�v���P�[�V�����̃C���X�^���X�B
		NULL
	);

	ShowWindow(g_hWnd, nCmdShow);

}


///////////////////////////////////////////////////////////////////
// ���t���[���Ă΂��Q�[���̍X�V�����B
///////////////////////////////////////////////////////////////////
void GameUpdate()
{
	g_backGround.Update();
	g_player.Update();

	//12.2 Hands-On
	//12.4 Hands-On
	g_camera3D->Update();
}
///////////////////////////////////////////////////////////////////
// ���t���[���Ă΂��Q�[���̕`�揈���B
///////////////////////////////////////////////////////////////////
void GameRender()
{
	g_graphicsEngine->BegineRender();

	g_backGround.Draw();
	g_player.Draw();

	g_graphicsEngine->EndRender();

}
///////////////////////////////////////////////////////////////////
// �J�������������B
///////////////////////////////////////////////////////////////////
void InitCamera()
{
	//3D�J�������������B
	g_camera3D = new CCamera;
	
	g_camera3D->SetPosition({ 0.0f, 20.0f, 60.0f });	//���_��ݒ�B
	g_camera3D->SetTarget({ 0.0f, 20.0f, 0.0f });		//�����_�͌��_�B

}
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�̏������B
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	//DirectX�̏������B
	g_graphicsEngine = new GraphicsEngine();
	g_graphicsEngine->Init(g_hWnd);
	//�J�������������B
	InitCamera();
	
	//�w�i���������B
	g_backGround.Init();
	//�v���C���[���������B
	g_player.Init();
	//���b�Z�[�W�\���̂̕ϐ�msg���������B
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)	//���b�Z�[�W���[�v
	{
		//�E�B���h�E����̃��b�Z�[�W���󂯎��B
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//�E�B���h�E����̃��b�Z�[�W���Ȃ��̂ŁA�Q�[���̏��������s����B
			GameUpdate();
			GameRender();
		}
	}
}