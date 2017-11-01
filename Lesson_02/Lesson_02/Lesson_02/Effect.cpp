#include "stdafx.h"
#include "Effect.h"

Effect::Effect()
{
}


Effect::~Effect()
{
	if (m_psBlobOut) {
		m_psBlobOut->Release();
	}
	if (m_vsBlobOut) {
		m_vsBlobOut->Release();
	}
	if (m_vs) {
		m_vs->Release();
	}
	if (m_ps) {
		m_ps->Release();
	}
}
void Effect::SetEffect()
{
	g_pd3dDeviceContext->VSSetShader(m_vs, NULL, NULL);
	g_pd3dDeviceContext->PSSetShader(m_ps, NULL, NULL);
}
void Effect::Load(const char* filePath)
{
	//プログラムを読み込み。
	FILE* fp = fopen(filePath, "rb");
	fseek(fp, 0, SEEK_END);
	fpos_t fPos;
	fgetpos(fp, &fPos);
	fseek(fp, 0, SEEK_SET);
	int fileSize = (int)fPos;
	std::unique_ptr<char[]> readBuff = std::make_unique<char[]>(fileSize);
	fread(readBuff.get(), fileSize, 1, fp);
	fclose(fp);

	//頂点シェーダーをコンパイル。
	D3DCompile(readBuff.get(), fileSize, filePath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VSMain", 
		"vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_vsBlobOut, NULL);
	//頂点シェーダーを作成。
	g_pd3dDevice->CreateVertexShader(m_vsBlobOut->GetBufferPointer(), m_vsBlobOut->GetBufferSize(), NULL, &m_vs);

	//ピクセルシェーダーをコンパイル。
	D3DCompile(readBuff.get(), fileSize, filePath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PSMain",
		"ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_psBlobOut, NULL);
	//ピクセルシェーダーを作成。
	g_pd3dDevice->CreatePixelShader(m_psBlobOut->GetBufferPointer(), m_psBlobOut->GetBufferSize(), NULL, &m_ps);

}
