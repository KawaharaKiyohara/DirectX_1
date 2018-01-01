#include "stdafx.h"
#include "Player.h"
#include "Coin.h"

Player::Player()
{
	//���f���̃��[�h�B
	m_model.Load(L"modelData/unityChan.cmo");
	//�v���C���[�̏����ʒu��ݒ肷��B
	m_position.x = -300.0f;
	m_position.y = -200.0f;
}


Player::~Player()
{
}
void Player::Update()
{
	//�v���C���[�̈ړ������B
	if (GetAsyncKeyState('D')) {
		//W�L�[�������ꂽ�B
		m_position.x += 5.0f;
	}
	else if (GetAsyncKeyState('A')) {
		//A�L�[�������ꂽ�B
		m_position.x -= 5.0f;
	}
	
	//���[���h�s����X�V�B
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 90.0f);
	m_model.UpateWorldMatrix(m_position, qRot, CVector3::One());
}
void Player::Draw(CCamera* camera)
{
	m_model.Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}
