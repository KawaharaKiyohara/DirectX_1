#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	m_model.Load(L"modelData/Thethief_H.cmo");
}

void Player::Update()
{
	if (GetAsyncKeyState('A')) {
		m_position.x += 1.0f;
	}
	if (GetAsyncKeyState('D')) {
		m_position.x -= 1.0f;
	}
	if (GetAsyncKeyState('W')) {
		m_position.z -= 1.0f;
	}
	if (GetAsyncKeyState('S')) {
		m_position.z += 1.0f;
	}
	m_model.UpateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Player::Draw()
{
	m_model.Draw(g_camera3D->GetViewMatrix(), g_camera3D->GetProjectionMatrix());
}