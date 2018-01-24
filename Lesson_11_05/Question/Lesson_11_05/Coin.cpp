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
	//ワールド行列を更新。
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	m_rotation.Multiply(m_rotation, qRot);
	//m_rotation.y += 0.2f;
	m_model.UpdateWorldMatrix(
		m_position, 
		m_rotation, 
		{20.0f, 20.0f, 20.0f}
	);
}
void Coin::Draw(CCamera* camera)
{
	m_model.Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}

