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
		m_rotation.SetRotationDeg(CVector3::AxisY(), 90.0f);
	}
	else if (GetAsyncKeyState('A')) {
		//A�L�[�������ꂽ�B
		m_position.x -= 5.0f;
		m_rotation.SetRotationDeg(CVector3::AxisY(), -90.0f);
	}
	for (int i = 0; i < NUM_COIN; i++) {
		if (g_coin[i]->m_isGet == false) {	//�R�C���擾�ς݂łȂ���΁B
			CVector3 v = g_coin[i]->m_position - m_position;
			float len = v.Length();
			if (len < 70.0f) {
				//�R�C���ƃv���C���[�̋�����70cm�ȉ��Ȃ̂ŁA�R�C���擾�t���O�𗧂Ă�B
				g_coin[i]->m_isGet = true;	
			}
		}
	}
	//���[���h�s����X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}
void Player::Draw(CCamera* camera)
{
	m_model.Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}
