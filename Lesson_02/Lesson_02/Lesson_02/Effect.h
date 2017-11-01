#pragma once

//�G�t�F�N�g
class Effect
{
public:
	Effect();
	~Effect();
	//���[�h�B
	void Load(const char* shaderFilePath);
	void SetEffect();
private:
	ID3D11VertexShader* m_vs = NULL;	//���_�V�F�[�_�[�B
	ID3D11PixelShader* m_ps = NULL;	//�s�N�Z���V�F�[�_�[�B
	ID3DBlob* m_vsBlobOut = NULL;
	ID3DBlob* m_psBlobOut = NULL;
};

