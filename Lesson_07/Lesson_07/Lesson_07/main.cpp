#include "stdafx.h"
#include "Effect.h"

#include "Sprite.h"	//Spriteクラスを使用するので、ヘッダーをインクルード。
#include "SkinModel.h" //SkinModelクラスを使用するので、ヘッダーをインクルード。

///////////////////////////////////////////////////////////////////
// グローバル変数。
///////////////////////////////////////////////////////////////////
HWND			g_hWnd = NULL;				//ウィンドウハンドル。
CCamera* g_camera2D = NULL;					//2Dカメラ。
CCamera* g_camera3D = NULL;					//3Dカメラ。
GraphicsEngine* g_graphicsEngine = NULL;	//グラフィックスエンジン。


Sprite g_sprite;		//スプライト。
CVector3 g_spritePos = CVector3::Zero();	//スプライトの座標。

SkinModel g_skinModel;	//スキンモデル。

///////////////////////////////////////////////////////////////////
// DirectXの終了処理。
///////////////////////////////////////////////////////////////////
void ReleaseDirectX()
{
	delete g_camera2D;
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
	
	g_graphicsEngine->BegineRender();
	//3Dモデルを描画する。
	g_skinModel.UpateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	g_skinModel.Draw(g_camera3D->GetViewMatrix(), g_camera3D->GetProjectionMatrix());
	//SpriteのUpdate関数を呼び出す。
	//Sin,Cosカーブを使ってSpriteを適当に動かす。
	static float t = 0.0f;
	t += 0.0005f;
	g_spritePos.x = sinf(t) * 400.0f;
	g_spritePos.y = cosf(t) * 200.0f;
	g_sprite.Update(g_spritePos, CQuaternion::Identity(), CVector3::One());
	//SpriteのDraw関数を呼び出す。
	g_sprite.Draw();

	g_graphicsEngine->EndRender();
	
}

///////////////////////////////////////////////////////////////////
// カメラを初期化。
///////////////////////////////////////////////////////////////////
void InitCamera()
{
	//2Dカメラを初期化。
	g_camera2D = new CCamera;
	g_camera2D->SetTarget(CVector3::Zero());
	g_camera2D->SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D->SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);	//カメラの計算方式を平行投影にする。
	g_camera2D->SetNear(0.1f);
	g_camera2D->SetFar(1000.0f);
	g_camera2D->Update();
	//3Dカメラを初期化。
	g_camera3D = new CCamera;
	g_camera3D->SetTarget({0.0f, 50.0f, 0.0f});			//注視点は原点。
	g_camera3D->SetPosition({ 0.0f, 50.0f, -500.0f });	//視点を設定。
	g_camera3D->Update();

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
	
	//Spriteを初期化
	g_sprite.Init(L"sprite/mikyan.dds", 240.0f, 240.0f);
	//SkinModelを初期化。
	g_skinModel.Load(L"modelData/teapot.cmo");
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
		}
	}
}