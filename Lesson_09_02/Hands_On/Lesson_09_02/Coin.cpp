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
	//�R�C������v���C���[�Ɍ������ĐL�т�x�N�g�����v�Z�B
	CVector3 v = g_player->m_position - m_position;
	//Hands-On �R�C�����v���C���[�ɒǏ]����悤�ɂ���B

	//���[���h�s����X�V�B
	m_model.UpateWorldMatrix(m_position, CQuaternion::Identity(), {20.0f, 20.0f, 20.0f});
}
void Coin::Draw(CCamera* camera)
{
	m_model.Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}

