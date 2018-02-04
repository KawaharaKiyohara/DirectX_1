#include "stdafx.h"
#include "Effect.h"
#include "Pad.h"
#include "BackGround.h"


///////////////////////////////////////////////////////////////////
// グローバル変数。
///////////////////////////////////////////////////////////////////
HWND			g_hWnd = NULL;				//ウィンドウハンドル。
CCamera* g_camera3D = NULL;					//3Dカメラ。
GraphicsEngine* g_graphicsEngine = NULL;	//グラフィックスエンジン。

BackGround g_backGround;					//背景。
Player g_player;							//プレイヤー。

Pad g_pad;									//パッド。

///////////////////////////////////////////////////////////////////
// DirectXの終了処理。
///////////////////////////////////////////////////////////////////
void ReleaseDirectX()
{
	delete g_camera3D;
	delete g_graphicsEngine;
	
}
///////////////////////////////////////////////////////////////////
//メッセージプロシージャ。
//hWndがメッセージを送ってきたウィンドウのハンドル。
//msgがメッセージの種類。
//wParamとlParamは引数。今は気にしなくてよい。
///////////////////////////////////////////////////////////////////
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//送られてきたメッセージで処理を分岐させる。
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
// ウィンドウの初期化。
///////////////////////////////////////////////////////////////////
void InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラスのパラメータを設定(単なる構造体の変数の初期化です。)
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),		//構造体のサイズ。
		CS_CLASSDC,				//ウィンドウのスタイル。
								//ここの指定でスクロールバーをつけたりできるが、ゲームでは不要なのでCS_CLASSDCでよい。
		MsgProc,				//メッセージプロシージャ(後述)
		0,						//0でいい。
		0,						//0でいい。
		GetModuleHandle(NULL),	//このクラスのためのウインドウプロシージャがあるインスタンスハンドル。
								//何も気にしなくてよい。
		NULL,					//アイコンのハンドル。アイコンを変えたい場合ここを変更する。とりあえずこれでいい。
		NULL,					//マウスカーソルのハンドル。NULLの場合はデフォルト。
		NULL,					//ウィンドウの背景色。NULLの場合はデフォルト。
		NULL,					//メニュー名。NULLでいい。
		TEXT("Sample_01"),		//ウィンドウクラスに付ける名前。
		NULL					//NULLでいい。
	};
	//ウィンドウクラスの登録。
	RegisterClassEx(&wc);

	// ウィンドウの作成。
	g_hWnd = CreateWindow(
		TEXT("Sample_01"),		//使用するウィンドウクラスの名前。
								//先ほど作成したウィンドウクラスと同じ名前にする。
		TEXT("Sample_01"),		//ウィンドウの名前。ウィンドウクラスの名前と別名でもよい。
		WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル。ゲームでは基本的にWS_OVERLAPPEDWINDOWでいい、
		0,						//ウィンドウの初期X座標。
		0,						//ウィンドウの初期Y座標。
		(UINT)FRAME_BUFFER_W,	//ウィンドウの幅。
		(UINT)FRAME_BUFFER_H,	//ウィンドウの高さ。
		NULL,					//親ウィンドウ。ゲームでは基本的にNULLでいい。
		NULL,					//メニュー。今はNULLでいい。
		hInstance,				//アプリケーションのインスタンス。
		NULL
	);

	ShowWindow(g_hWnd, nCmdShow);

}


///////////////////////////////////////////////////////////////////
// 毎フレーム呼ばれるゲームの更新処理。
///////////////////////////////////////////////////////////////////
void GameUpdate()
{
	g_backGround.Update();
	g_player.Update();
	//パッドの更新。
	g_pad.Update();

	//13.4 Hands-On
	char text[256];
	sprintf(text, "LStick X = %f, LStick Y = %f\n", g_pad.GetLStickXF(), g_pad.GetLStickYF());
	OutputDebugString(text);
	//実習課題　回答
	//注視点から視点へのベクトルを計算する。
	CVector3 toCameraPos = g_camera3D->m_position - g_camera3D->m_target;
	//新しい注視点を計算する。
	g_camera3D->m_target = g_player.m_position;
	g_camera3D->m_target.y += 22.0f;
	
	//Y軸周りの回転。
	CMatrix mRot = CMatrix::Identity();		//単位行列で初期化する。
	mRot.MakeRotationY(CMath::DegToRad(1.0f) * g_pad.GetRStickXF());
	mRot.Mul(toCameraPos);

	//続いてX軸周りに回す。
	//まず、回す軸を計算する。
	CVector3 rotAxis;
	CVector3 upAxis(0.0f, 1.0f, 0.0f);
	rotAxis.Cross( upAxis, toCameraPos );
	rotAxis.Normalize();
	mRot = CMatrix::Identity();
	mRot.MakeRotationAxis(rotAxis, CMath::DegToRad(1.0f) * g_pad.GetRStickYF());
	mRot.Mul(toCameraPos);

	//新しい視点を計算する。
	g_camera3D->m_position = g_camera3D->m_target + toCameraPos;

	g_camera3D->Update();
}
///////////////////////////////////////////////////////////////////
// 毎フレーム呼ばれるゲームの描画処理。
///////////////////////////////////////////////////////////////////
void GameRender()
{
	g_graphicsEngine->BegineRender();

	g_backGround.Draw();
	g_player.Draw();

	g_graphicsEngine->EndRender();

}
///////////////////////////////////////////////////////////////////
// カメラを初期化。
///////////////////////////////////////////////////////////////////
void InitCamera()
{
	//3Dカメラを初期化。
	g_camera3D = new CCamera;
	
	g_camera3D->SetPosition({ 0.0f, 20.0f, 60.0f });	//視点を設定。
	g_camera3D->SetTarget({ 0.0f, 20.0f, 0.0f });		//注視点は原点。

}
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの初期化。
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	//DirectXの初期化。
	g_graphicsEngine = new GraphicsEngine();
	g_graphicsEngine->Init(g_hWnd);
	//カメラを初期化。
	InitCamera();
	//パッドの初期化。
	g_pad.Init(0);
	//背景を初期化。
	g_backGround.Init();
	//プレイヤーを初期化。
	g_player.Init();
	//メッセージ構造体の変数msgを初期化。
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)	//メッセージループ
	{
		//ウィンドウからのメッセージを受け取る。
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//ウィンドウからのメッセージがないので、ゲームの処理を実行する。
			GameUpdate();
			GameRender();
		}
	}
}