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
	CVector3 cameraForward = g_camera3D->m_target - g_camera3D->m_position;
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	m_position += cameraForward * 5.0f * g_pad.GetLStickYF();

	CVector3 cameraRight;
	cameraRight.Cross({ 0.0f, 1.0f, 0.0f }, cameraForward);
	cameraRight.Normalize();
	m_position += cameraRight * 5.0f * g_pad.GetLStickXF();

	m_model.UpateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Player::Draw()
{
	m_model.Draw(g_camera3D->GetViewMatrix(), g_camera3D->GetProjectionMatrix());
}