#pragma once

//エフェクト
class Effect
{
public:
	Effect();
	~Effect();
	//ロード。
	void Load(const char* shaderFilePath);
	void SetEffect();
private:
	ID3D11VertexShader* m_vs = NULL;	//頂点シェーダー。
	ID3D11PixelShader* m_ps = NULL;	//ピクセルシェーダー。
	ID3DBlob* m_vsBlobOut = NULL;
	ID3DBlob* m_psBlobOut = NULL;
};

