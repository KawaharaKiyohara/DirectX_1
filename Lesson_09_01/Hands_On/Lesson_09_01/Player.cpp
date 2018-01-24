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
	
	if(g_coin->m_isGet == false){	//g_coin���擾�ς݂��ǂ������`�F�b�N�B
		//Hands-On 1 
		//�R�C���ƃv���C���[�̋������v�Z���āA�R�C�����Q�b�g�ł���悤�ɂ��Ȃ����B
		//�R�C���̍��W��g_coin->m_position�Ŏ擾�\�B
		CVector3 v = m_position - g_coin->m_position;
		float len = v.Length();
		if (len < 70.0f) {
			//�R�C���ƃv���C���[�̋�����70cm�ȉ��Ȃ̂ŁA�R�C���擾�t���O��ݒ肷��B
			g_coin->m_isGet = true;
		}
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
