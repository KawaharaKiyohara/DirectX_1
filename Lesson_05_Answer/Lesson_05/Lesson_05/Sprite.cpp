#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
	if (m_vertexBuffer != NULL) {
		m_vertexBuffer->Release();
	}
	if (m_indexBuffer != NULL) {
		m_indexBuffer->Release();
	}
	if (m_samplerState != NULL) {
		m_samplerState->Release();
	}
	if (m_texture != NULL) {
		m_texture->Release();
	}
}
//Sprite::Init関数の実装。
void Sprite::Init(const wchar_t* texFilePath)
{

	//頂点バッファの初期化。
	InitVertexBuffer(m_vertexBuffer);
	//インデックスバッファの初期化。
	InitIndexBuffer(m_indexBuffer);
	//サンプラステートの初期化。
	InitSamplerState(m_samplerState);
	//エフェクトファイルのロード。気にしなくてよい。
	m_effect.Load("Assets/shader/primitive.fx");
	//テクスチャをロード。
	DirectX::CreateDDSTextureFromFileEx(
		g_pd3dDevice,				//D3Dデバイス。
		texFilePath,				//読み込む画像データのファイルパス。
		0,                          //今は気にしなくてよい。
		D3D11_USAGE_DEFAULT,		//今は気にしなくてよい。
		D3D11_BIND_SHADER_RESOURCE,	//今は気にしなくてよい。
		0,							//今は気にしなくてよい。
		0,							//今は気にしなくてよい。
		false,						//今は気にしなくてよい。
		nullptr,					//今は気にしなくてよい。
		&m_texture					//読み込んだテクスチャに
									//アクセスするためのインターフェースの格納先。
	);
}
//Sprite::Draw関数の実装。
void Sprite::Draw()
{
	m_effect.BeginRender();
	unsigned int vertexSize = sizeof(SVertex);	//頂点のサイズ。
	unsigned int offset = 0;
	g_pd3dDeviceContext->IASetVertexBuffers(	//頂点バッファを設定。
		0,					//StartSlot番号。今は0でいい。
		1,					//バッファの数。今は1でいい。
		&m_vertexBuffer,	//頂点バッファ。
		&vertexSize,		//頂点のサイズ。
		&offset				//気にしなくてよい。
	);
	g_pd3dDeviceContext->IASetIndexBuffer(	//インデックスバッファを設定。
		m_indexBuffer,			//インデックスバッファ。
		DXGI_FORMAT_R32_UINT,	//インデックスのフォーマット。
								//今回は32bitなので、DXGI_FORMAT_R32_UINTでいい。
		0						//オフセット0でいい。
	);

	//テクスチャを設定。
	g_pd3dDeviceContext->PSSetShaderResources(0, 1, &m_texture);
	//サンプラステートを設定。
	g_pd3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);

	//プリミティブのトポロジーは
	//トライアングルストリップを設定する。
	g_pd3dDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_pd3dDeviceContext->DrawIndexed(	//描画命令。
		6,				//インデックス数。
		0,				//開始インデックス番号。0でいい。
		0				//開始頂点番号。0でいい。
	);
}