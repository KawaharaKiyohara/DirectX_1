#include "stdafx.h"
#include "Coin.h"
#include "Player.h"

Coin::Coin()
{
	m_model.Load(L"modelData/star.cmo");
	m_position.x = 300.0f;
	m_position.y = -200.0f;
}


Coin::~Coin()
{	
}

void Coin::Update()
{
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 1.0f);
	m_rotation.Multiply(qRot);
	//ワールド行列を更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, {20.0f, 20.0f, 20.0f});
}
void Coin::Draw(CCamera* camera)
{
	m_model.Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}

