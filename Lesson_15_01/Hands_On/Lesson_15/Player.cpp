#include "stdafx.h"
#include "Player.h"
#include "Pad.h"


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
	//Hands-On 13.6
	m_model.UpateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Player::Draw()
{
	m_model.Draw(g_camera3D->GetViewMatrix(), g_camera3D->GetProjectionMatrix());
}