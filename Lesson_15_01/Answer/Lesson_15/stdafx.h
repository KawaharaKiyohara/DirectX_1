#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>
#include <Xinput.h>

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
#include "Player.h"
#include "Pad.h"

const float FRAME_BUFFER_W = 1280.0f;				//�t���[���o�b�t�@�̕��B
const float FRAME_BUFFER_H = 720.0f;				//�t���[���o�b�t�@�̍����B
extern CCamera* g_camera3D;							//3D�J�����B
extern CCamera* g_camera2D;							//2D�J�����B
extern Player g_player;								//�v���C���[
extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��
extern Pad g_pad;									//�p�b�h�B
