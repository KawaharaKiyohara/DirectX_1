#include "stdafx.h"
#include "Effect.h"

///////////////////////////////////////////////////////////////////
// �O���[�o���ϐ��B
///////////////////////////////////////////////////////////////////
HWND					g_hWnd = NULL;				//�E�B���h�E�n���h���B

//��������DirectX11�֌W�̕ϐ��B
D3D_FEATURE_LEVEL		g_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
ID3D11Device*			g_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
IDXGISwapChain*			g_pSwapChain = NULL;		//�X���b�v�`�F�C���B
ID3D11DeviceContext*	g_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
ID3D11RenderTargetView* g_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
ID3D11RasterizerState*	g_rasterizerState = NULL;
///////////////////////////////////////////////////////////////////
//��������l�p�`�|���S���`��֌W�̕ϐ��ȂǁB
///////////////////////////////////////////////////////////////////
ID3D11Buffer* g_vertexBuffer = NULL;		//���_�o�b�t�@�B
ID3D11Buffer* g_indexBuffer = NULL;			//�C���f�b�N�X�o�b�t�@�B
Effect g_effect;							//�G�t�F�N�g�B�C�ɂ��Ȃ��Ă悢�B
ID3D11ShaderResourceView* g_texture = NULL;	//�e�N�X�`���B
ID3D11SamplerState* g_samplerState = NULL;	//�T���v���X�e�[�g�B

//���_�\���́B
struct SVertex {
	float position[4];		//���_���W�B4�v�f�Ȃ͍̂��͋C�ɂ��Ȃ��B
	float uv[2];			//UV���W�B���ꂪ�e�N�X�`�����W
};

///////////////////////////////////////////////////////////////////
// DirectX�̏������B
///////////////////////////////////////////////////////////////////
void InitDirectX()
{
	//�X���b�v�`�F�C�����쐬���邽�߂̏���ݒ肷��B
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;									//�X���b�v�`�F�C���̃o�b�t�@���B�ʏ�͂P�B
	sd.BufferDesc.Width = 500;							//�t���[���o�b�t�@�̕��B
	sd.BufferDesc.Height = 500;							//�t���[���o�b�t�@�̍����B
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//�t���[���o�b�t�@�̃t�H�[�}�b�g�BR8G8B8A8��32bit�B
	sd.BufferDesc.RefreshRate.Numerator = 60;			//���j�^�̃��t���b�V�����[�g�B(�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���^�C�~���O�ƂȂ�B)
	sd.BufferDesc.RefreshRate.Denominator = 1;			//�Q�ɂ�����30fps�ɂȂ�B1�ł����B
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//�T�[�t�F�X�܂��̓��\�[�X���o�̓����_�[ �^�[�Q�b�g�Ƃ��Ďg�p���܂��B
	sd.OutputWindow = g_hWnd;							//�o�͐�̃E�B���h�E�n���h���B
	sd.SampleDesc.Count = 1;							//1�ł����B
	sd.SampleDesc.Quality = 0;							//MSAA�Ȃ��B0�ł����B
	sd.Windowed = TRUE;									//�E�B���h�E���[�h�BTRUE�ł悢�B

	//���p����DirectX�̋@�\�Z�b�g�BDirectX10�ȏ�ɑΉ����Ă���GPU�𗘗p�\�Ƃ���B
	//���̔z���D3D11CreateDeviceAndSwapChain�̈����Ƃ��Ďg���B
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	
	//D3D�f�o�C�X�ƃX���b�v�`�F�C�����쐬����B
	D3D11CreateDeviceAndSwapChain(
		NULL,											//NULL�ł����B
		D3D_DRIVER_TYPE_HARDWARE,						//D3D�f�o�C�X���A�N�Z�X����h���C�o�[�̎�ށB
														//��{�I��D3D_DRIVER_TYPE_HARDWARE���w�肷��΂悢�B
		NULL,											//NULL�ł����B
		0,												//�O�ł����B
		featureLevels,									//D3D�f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g���w�肷��B
														//����̃T���v����DirectX10�ȏ���T�|�[�g����̂ŁA
														//�������܂�D3D_FEATURE_LEVEL�̔z���n���B
		sizeof(featureLevels)/sizeof(featureLevels[0]),	//�@�\�Z�b�g�̐��B
		D3D11_SDK_VERSION,								//�g�p����DirectX�̃o�[�W�����B
														//D3D11_SDK_VERSION���w�肷��΂悢�B
		&sd,											//�X���b�v�`�F�C�����쐬���邽�߂̏��B
		&g_pSwapChain,									//�쐬�����X���b�v�`�F�C���̃A�h���X�̊i�[��B
		&g_pd3dDevice,									//�쐬����D3D�f�o�C�X�̃A�h���X�̊i�[��B
		&g_featureLevel,								//�g�p�����@�\�Z�b�g�̊i�[��B
		&g_pd3dDeviceContext							//�쐬����D3D�f�o�C�X�R���e�L�X�g�̃A�h���X�̊i�[��B
	);

	//�������ݐ�ɂȂ郌���_�����O�^�[�Q�b�g���쐬�B
	ID3D11Texture2D* pBackBuffer = NULL;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_backBuffer);
	pBackBuffer->Release();

	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.DepthClipEnable = true;
	desc.MultisampleEnable = true;

	//���X�^���C�U�ƃr���[�|�[�g���������B
	g_pd3dDevice->CreateRasterizerState(&desc, &g_rasterizerState);

	D3D11_VIEWPORT viewport;
	viewport.Width = 500;
	viewport.Height = 500;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	g_pd3dDeviceContext->RSSetViewports(1, &viewport);
	g_pd3dDeviceContext->RSSetState(g_rasterizerState);
}
///////////////////////////////////////////////////////////////////
// DirectX�̏I�������B
///////////////////////////////////////////////////////////////////
void ReleaseDirectX()
{
	if (g_texture != NULL) {
		g_texture->Release();
	}
	if (g_samplerState != NULL) {
		g_samplerState->Release();
	}
	if (g_indexBuffer != NULL) {
		g_indexBuffer->Release();
	}
	if (g_vertexBuffer != NULL) {
		g_vertexBuffer->Release();
	}
	if (g_rasterizerState != NULL) {
		g_rasterizerState->Release();
	}
	if (g_backBuffer != NULL) {
		g_backBuffer->Release();
	}
	if (g_pSwapChain != NULL) {
		g_pSwapChain->Release();
	}
	if (g_pd3dDeviceContext != NULL) {
		g_pd3dDeviceContext->Release();
	}
	if (g_pd3dDevice != NULL) {
		g_pd3dDevice->Release();
	}
	
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
		500,					//�E�B���h�E�̕��B
		500,					//�E�B���h�E�̍����B
		NULL,					//�e�E�B���h�E�B�Q�[���ł͊�{�I��NULL�ł����B
		NULL,					//���j���[�B����NULL�ł����B
		hInstance,				//�A�v���P�[�V�����̃C���X�^���X�B
		NULL
	);

	ShowWindow(g_hWnd, nCmdShow);

}
///////////////////////////////////////////////////////////////////
// ���_�o�b�t�@�̏������B
///////////////////////////////////////////////////////////////////
void InitVertexBuffer()
{
	//��Œ�`�������_���g�p���Ē��_�o�b�t�@���쐬����B
	//���_�o�b�t�@���쐬���邽�߂ɂ�D3D11_BUFFER_DESC��D3D11_SUBRESOURCE_DATA��ݒ肷��K�v������B
	SVertex vertex[4] = {
		//���_�P
		{
			//���W�@position[4]
			-0.5f,  -0.5f, 0.0f, 1.0f,
			//UV���W uv[2]
			0.0f, 1.0f
		},
		//���_�Q
		{
			//���W�@position[4]
			0.5f, -0.5f, 0.0f, 1.0f,
			//UV���W uv[2]
			1.0f, 1.0f
		},
		//���_�R
		{
			//���W�@position[4]
			-0.5f,  0.5f, 0.0f, 1.0f,
			//UV���W uv[2]
			0.0f, 0.0f
		},
		//���_�S
		{
			//���W�@position[4]
			0.5f,  0.5f, 0.0f, 1.0f,
			//UV���W uv[2]
			1.0f, 0.0f
		},
	};
	//��Œ�`�������_���g�p���Ē��_�o�b�t�@���쐬����B
	//���_�o�b�t�@���쐬���邽�߂ɂ�D3D11_BUFFER_DESC��D3D11_SUBRESOURCE_DATA��ݒ肷��K�v������B
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//�\���̂�0�ŏ���������B
	bd.Usage = D3D11_USAGE_DEFAULT;				//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@�B
												//��肠������D3D11_USAGE_DEFAULT�ł悢�B
	bd.ByteWidth = sizeof(vertex);				//���_�o�b�t�@�̃T�C�Y�B���_�̃T�C�Y�~���_���ƂȂ�B
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//���ꂩ��쐬����o�b�t�@�����_�o�b�t�@�ł��邱�Ƃ��w�肷��B

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;

	//���_�o�b�t�@�̍쐬�B
	g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_vertexBuffer);
}
///////////////////////////////////////////////////////////////////
// �C���f�b�N�X�o�b�t�@�̏������B
///////////////////////////////////////////////////////////////////
void InitIndexBuffer()
{
	//���ꂪ�C���f�b�N�X�B���_�ԍ��B
	int index[6] = {
		0,1,2,		//�O�p�`���
		2,1,3		//�O�p�`���
	};
	//��Œ�`�����C���f�b�N�X���g�p���ăC���f�b�N�X�o�b�t�@���쐬����B
	//�C���f�b�N�X�o�b�t�@�̍쐬�����_�o�b�t�@�Ɠ��l�ɁA
	//D3D11_BUFFER_DESC��D3D11_SUBRESOURCE_DATA��ݒ肷��K�v������B
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//�\���̂�0�ŏ���������B
	bd.Usage = D3D11_USAGE_DEFAULT;				//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@�B
												//��肠������D3D11_USAGE_DEFAULT�ł悢�B
	bd.ByteWidth = sizeof(index);				//�C���f�b�N�X�o�b�t�@�̃T�C�Y�B
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;		//���ꂩ��쐬����o�b�t�@���C���f�b�N�X�o�b�t�@�ł��邱�Ƃ��w�肷��B

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = index;

	//�C���f�b�N�X�o�b�t�@�̍쐬�B
	g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_indexBuffer);
}
///////////////////////////////////////////////////////////////////
// �l�p�`�|���S���̏������B
///////////////////////////////////////////////////////////////////
void InitQuadPolygon()
{
	//���_�o�b�t�@�̏������B
	InitVertexBuffer();
	//�C���f�b�N�X�o�b�t�@���쐬�B
	InitIndexBuffer();
	//�V�F�[�_�[�����[�h�B
	g_effect.Load("Assets/shader/primitive.fx");
}
///////////////////////////////////////////////////////////////////
// �T���v���X�e�[�g�̏������B
///////////////////////////////////////////////////////////////////
void InitSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_pd3dDevice->CreateSamplerState(&desc, &g_samplerState);
}
///////////////////////////////////////////////////////////////////
// ���t���[���Ă΂��Q�[���̍X�V�����B
///////////////////////////////////////////////////////////////////
void GameUpdate()
{
	float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; //red,green,blue,alpha
	//�`�����ݐ���o�b�N�o�b�t�@�ɂ���B
	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_backBuffer, NULL);
	//�o�b�N�o�b�t�@���D�F�œh��Ԃ��B
	g_pd3dDeviceContext->ClearRenderTargetView(g_backBuffer, ClearColor);
	
	/////////////////////////////////////////////////
	// ������3D���f���Ȃǂ�`�悷��R�[�h�������Ă����B
	/////////////////////////////////////////////////
	g_effect.BeginRender();						//�`��J�n�B
	unsigned int vertexSize = sizeof(SVertex);	//���_�̃T�C�Y�B
	unsigned int offset = 0;						
	g_pd3dDeviceContext->IASetVertexBuffers(	//���_�o�b�t�@��ݒ�B
		0,					//StartSlot�ԍ��B����0�ł����B
		1,					//�o�b�t�@�̐��B����1�ł����B
		&g_vertexBuffer,	//���_�o�b�t�@�B
		&vertexSize,		//���_�̃T�C�Y�B
		&offset				//�C�ɂ��Ȃ��Ă悢�B
	);
	g_pd3dDeviceContext->IASetIndexBuffer(	//�C���f�b�N�X�o�b�t�@��ݒ�B
		g_indexBuffer,			//�C���f�b�N�X�o�b�t�@�B
		DXGI_FORMAT_R32_UINT,	//�C���f�b�N�X�̃t�H�[�}�b�g�B
								//�����32bit�Ȃ̂ŁADXGI_FORMAT_R32_UINT�ł����B
		0						//�I�t�Z�b�g0�ł����B
	);

	//�e�N�X�`����ݒ�B
	g_pd3dDeviceContext->PSSetShaderResources(0, 1, &g_texture);
	//�T���v���X�e�[�g��ݒ�B
	g_pd3dDeviceContext->PSSetSamplers(0, 1, &g_samplerState);

	//�v���~�e�B�u�̃g�|���W�[��
	//�g���C�A���O���X�g���b�v��ݒ肷��B(�ڂ�����Lesson_3�ŉ�����s���B)
	g_pd3dDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_pd3dDeviceContext->DrawIndexed(	//�`�施�߁B
		6,				//�C���f�b�N�X���B
		0,				//�J�n�C���f�b�N�X�ԍ��B0�ł����B
		0				//�J�n���_�ԍ��B0�ł����B
	);
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pSwapChain->Present(0, 0);
}
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�̏������B
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	//DirectX�̏������B
	InitDirectX();
	//�l�p�`�|���S���̏������B
	InitQuadPolygon();
	//�T���v���X�e�[�g�̏������B
	InitSamplerState();
	//�e�N�X�`�������[�h�B
	DirectX::CreateDDSTextureFromFileEx(
		g_pd3dDevice,				//D3D�f�o�C�X�B
		L"Assets/mikyan.dds",		//�ǂݍ��މ摜�f�[�^�̃t�@�C���p�X�B
		0,                          //���͋C�ɂ��Ȃ��Ă悢�B
		D3D11_USAGE_DEFAULT,		//���͋C�ɂ��Ȃ��Ă悢�B
		D3D11_BIND_SHADER_RESOURCE,	//���͋C�ɂ��Ȃ��Ă悢�B
		0,							//���͋C�ɂ��Ȃ��Ă悢�B
		0,							//���͋C�ɂ��Ȃ��Ă悢�B
		false,						//���͋C�ɂ��Ȃ��Ă悢�B
		nullptr,					//���͋C�ɂ��Ȃ��Ă悢�B
		&g_texture					//�ǂݍ��񂾃e�N�X�`����
									//�A�N�Z�X���邽�߂̃C���^�[�t�F�[�X�̊i�[��B
	);
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