#pragma once
#include "Effect.h"
class Sprite
{
public:
	Sprite();
	~Sprite();
	/*
	 *概要	初期化。
	 * Spriteクラスを使用できるようにします。
	 *引数	texFilePath		テクスチャのファイルパス。
	 */
	void Init(const wchar_t* texFilePath);
	/*!
	 * @brief	描画。
	 */
	void Draw();
	ID3D11Buffer*				m_vertexBuffer = NULL;	//頂点バッファ。
	ID3D11Buffer*				m_indexBuffer = NULL;	//インデックスバッファ。
	Effect						m_effect;				//エフェクト。気にしなくてよい。
	ID3D11ShaderResourceView*	m_texture = NULL;		//テクスチャ。
	ID3D11SamplerState*			m_samplerState = NULL;	//サンプラステート。

};

