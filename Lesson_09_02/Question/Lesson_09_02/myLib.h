#pragma once

extern void InitVertexBuffer(ID3D11Buffer*& vertexBuffer, float w, float h);
extern void InitIndexBuffer(ID3D11Buffer*& indexBuffer);
extern void InitSamplerState(ID3D11SamplerState*& samplerState);

struct SVertex {
	float position[4];		//頂点座標。4要素なのは今は気にしない。
	float uv[2];			//UV座標。これがテクスチャ座標
};