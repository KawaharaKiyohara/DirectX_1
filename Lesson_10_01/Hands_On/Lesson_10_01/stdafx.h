#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>

#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"
#include "myLib.h"
#include "Vector.h"
#include "Matrix.h"
#include "Camera.h"
#include "GraphicsEngine.h"


const float FRAME_BUFFER_W = 1280.0f;				//フレームバッファの幅。
const float FRAME_BUFFER_H = 720.0f;				//フレームバッファの高さ。
extern CCamera* g_camera2D;							//2Dカメラ。
extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン
