#pragma once
#include "Effect.h"
class Sprite
{
public:
	Sprite();
	~Sprite();
	/*
	 *�T�v	�������B
	 * Sprite�N���X���g�p�ł���悤�ɂ��܂��B
	 *����	texFilePath		�e�N�X�`���̃t�@�C���p�X�B
	 */
	void Init(const wchar_t* texFilePath);
	/*!
	 * @brief	�`��B
	 */
	void Draw();
	ID3D11Buffer*				m_vertexBuffer = NULL;	//���_�o�b�t�@�B
	ID3D11Buffer*				m_indexBuffer = NULL;	//�C���f�b�N�X�o�b�t�@�B
	Effect						m_effect;				//�G�t�F�N�g�B�C�ɂ��Ȃ��Ă悢�B
	ID3D11ShaderResourceView*	m_texture = NULL;		//�e�N�X�`���B
	ID3D11SamplerState*			m_samplerState = NULL;	//�T���v���X�e�[�g�B

};

