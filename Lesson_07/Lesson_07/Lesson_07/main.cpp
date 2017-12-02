#include "stdafx.h"
#include "Effect.h"

#include "Sprite.h"	//Sprite�N���X���g�p����̂ŁA�w�b�_�[���C���N���[�h�B
#include "SkinModel.h" //SkinModel�N���X���g�p����̂ŁA�w�b�_�[���C���N���[�h�B

///////////////////////////////////////////////////////////////////
// �O���[�o���ϐ��B
///////////////////////////////////////////////////////////////////
HWND			g_hWnd = NULL;				//�E�B���h�E�n���h���B
CCamera* g_camera2D = NULL;					//2D�J�����B
CCamera* g_camera3D = NULL;					//3D�J�����B
GraphicsEngine* g_graphicsEngine = NULL;	//�O���t�B�b�N�X�G���W���B


Sprite g_sprite;		//�X�v���C�g�B
CVector3 g_spritePos = CVector3::Zero();	//�X�v���C�g�̍��W�B

//�e�B�[�|�b�g�֌W�̕ϐ��B
CVector3 g_teapotPosition = CVector3::Zero();			//�e�B�[�|�b�g�̍��W�B
CQuaternion g_teapotRotation = CQuaternion::Identity();	//�e�B�[�|�b�g�̉�]�B
CVector3 g_teapotScale = CVector3::One();				//�e�B�[�|�b�g�̊g�嗦�B
SkinModel g_teapotModel;								//�e�B�[�|�b�g���f���B

///////////////////////////////////////////////////////////////////
// DirectX�̏I�������B
///////////////////////////////////////////////////////////////////
void ReleaseDirectX()
{
	delete g_camera2D;
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
	
	g_graphicsEngine->BegineRender();
	//3D���f����`�悷��B
	g_teapotModel.UpateWorldMatrix(
		g_teapotPosition, 
		g_teapotRotation,
		g_teapotScale
	);
	g_teapotModel.Draw(g_camera3D->GetViewMatrix(), g_camera3D->GetProjectionMatrix());
	//Sprite��Update�֐����Ăяo���B
	//Sin,Cos�J�[�u���g����Sprite��K���ɓ������B
	static float t = 0.0f;
	t += 0.0005f;
	g_spritePos.x = sinf(t) * 400.0f;
	g_spritePos.y = cosf(t) * 200.0f;
	g_sprite.Update(g_spritePos, CQuaternion::Identity(), CVector3::One());
	//Sprite��Draw�֐����Ăяo���B
	g_sprite.Draw();

	g_graphicsEngine->EndRender();
	
}

///////////////////////////////////////////////////////////////////
// �J�������������B
///////////////////////////////////////////////////////////////////
void InitCamera()
{
	//2D�J�������������B
	g_camera2D = new CCamera;
	g_camera2D->SetTarget(CVector3::Zero());
	g_camera2D->SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D->SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);	//�J�����̌v�Z�����𕽍s���e�ɂ���B
	g_camera2D->SetNear(0.1f);
	g_camera2D->SetFar(1000.0f);
	g_camera2D->Update();
	//3D�J�������������B
	g_camera3D = new CCamera;
	g_camera3D->SetTarget({0.0f, 50.0f, 0.0f});			//�����_�͌��_�B
	g_camera3D->SetPosition({ 0.0f, 50.0f, -500.0f });	//���_��ݒ�B
	g_camera3D->Update();

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
	
	//Sprite��������
	g_sprite.Init(L"sprite/mikyan.dds", 240.0f, 240.0f);
	//�e�B�[�|�b�g���f�����������B
	g_teapotModel.Load(L"modelData/teapot.cmo");
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
		}
	}
}