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
/*
*@brief	�X�V�B
*/
void Sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, CVector2 pivot)
{
	//�s�{�b�g���l���ɓ��ꂽ���s�ړ��s����쐬�B
	//�s�{�b�g�͐^�񒆂�0.0, 0.0�A���オ-1.0f, -1.0�A�E����1.0�A1.0�ɂȂ�悤�ɂ���B
	CVector2 localPivot = pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;
	//�摜�̃n�[�t�T�C�Y�����߂�B
	CVector2 halfSize = m_size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;
	CMatrix mPivotTrans;

	mPivotTrans.MakeTranslation(
	{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(trans);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world.Mul(mPivotTrans, mScale);
	m_world.Mul(m_world, mRot);
	m_world.Mul(m_world, mTrans);
}
//�萔�o�b�t�@�̏������B
void Sprite::InitConstantBuffer()
{
	D3D11_BUFFER_DESC desc;
	
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = (((sizeof(ConstantBuffer) - 1) / 16) + 1) * 16;	//16�o�C�g�A���C�����g�ɐ؂肠����B
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_cb);
}
//Sprite::Init�֐��̎����B
void Sprite::Init(const wchar_t* texFilePath, float w, float h)
{
	m_size.x = w;
	m_size.y = h;
	//���_�o�b�t�@�̏������B
	InitVertexBuffer(m_vertexBuffer, w, h);
	//�C���f�b�N�X�o�b�t�@�̏������B
	InitIndexBuffer(m_indexBuffer);
	//�T���v���X�e�[�g�̏������B
	InitSamplerState(m_samplerState);
	//�G�t�F�N�g�t�@�C���̃��[�h�B�C�ɂ��Ȃ��Ă悢�B
	m_effect.Load("Assets/shader/sprite.fx");
	//�e�N�X�`���̃t�@�C���p�X��Resource��t������B
	wchar_t filePath[256];
	swprintf_s(filePath, L"Resource/%s", texFilePath);
	//�e�N�X�`�������[�h�B
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),	//D3D�f�o�C�X�B
		filePath,					//�ǂݍ��މ摜�f�[�^�̃t�@�C���p�X�B
		0,                          //���͋C�ɂ��Ȃ��Ă悢�B
		D3D11_USAGE_DEFAULT,		//���͋C�ɂ��Ȃ��Ă悢�B
		D3D11_BIND_SHADER_RESOURCE,	//���͋C�ɂ��Ȃ��Ă悢�B
		0,							//���͋C�ɂ��Ȃ��Ă悢�B
		0,							//���͋C�ɂ��Ȃ��Ă悢�B
		false,						//���͋C�ɂ��Ȃ��Ă悢�B
		nullptr,					//���͋C�ɂ��Ȃ��Ă悢�B
		&m_texture					//�ǂݍ��񂾃e�N�X�`����
									//�A�N�Z�X���邽�߂̃C���^�[�t�F�[�X�̊i�[��B
	);
	//�萔�o�b�t�@���������B
	InitConstantBuffer();
}
//Sprite::Draw�֐��̎����B
void Sprite::Draw()
{
	m_effect.BeginRender();
	unsigned int vertexSize = sizeof(SVertex);	//���_�̃T�C�Y�B
	unsigned int offset = 0;
	GraphicsEngine* ge = g_graphicsEngine;
	ge->GetD3DDeviceContext()->IASetVertexBuffers(	//���_�o�b�t�@��ݒ�B
		0,					//StartSlot�ԍ��B����0�ł����B
		1,					//�o�b�t�@�̐��B����1�ł����B
		&m_vertexBuffer,	//���_�o�b�t�@�B
		&vertexSize,		//���_�̃T�C�Y�B
		&offset				//�C�ɂ��Ȃ��Ă悢�B
	);
	ge->GetD3DDeviceContext()->IASetIndexBuffer(	//�C���f�b�N�X�o�b�t�@��ݒ�B
		m_indexBuffer,			//�C���f�b�N�X�o�b�t�@�B
		DXGI_FORMAT_R32_UINT,	//�C���f�b�N�X�̃t�H�[�}�b�g�B
								//�����32bit�Ȃ̂ŁADXGI_FORMAT_R32_UINT�ł����B
		0						//�I�t�Z�b�g0�ł����B
	);

	//�e�N�X�`����ݒ�B
	ge->GetD3DDeviceContext()->PSSetShaderResources(0, 1, &m_texture);
	//�T���v���X�e�[�g��ݒ�B
	ge->GetD3DDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);
	//���[���h�r���[�v���W�F�N�V�����s����쐬�B
	ConstantBuffer cb;
	cb.WVP = m_world;
	cb.WVP.Mul(cb.WVP, g_camera2D->GetViewMatrix());
	cb.WVP.Mul(cb.WVP, g_camera2D->GetProjectionMatrix());
	ge->GetD3DDeviceContext()->UpdateSubresource(m_cb, 0, NULL, &cb, 0, 0);
	ge->GetD3DDeviceContext()->VSSetConstantBuffers(0, 1, &m_cb);
	//�v���~�e�B�u�̃g�|���W�[��
	//�g���C�A���O���X�g���b�v��ݒ肷��B
	ge->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ge->GetD3DDeviceContext()->DrawIndexed(	//�`�施�߁B
		6,				//�C���f�b�N�X���B
		0,				//�J�n�C���f�b�N�X�ԍ��B0�ł����B
		0				//�J�n���_�ԍ��B0�ł����B
	);
}