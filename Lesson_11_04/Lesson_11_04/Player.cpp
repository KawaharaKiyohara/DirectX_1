#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//���f���̃��[�h�B
	m_model.Load(L"modelData/unityChan.cmo");
	//�v���C���[�̏����ʒu��ݒ肷��B
	m_position.x = 0.0f;
	m_position.y = -200.0f;
}


Player::~Player()
{
}
void Player::Update()
{
	//�v���C���[�̉�]�̕�ԁB�I�C���[�p�ƈ����-45����315���œ�����Ԃ��s���Ă��邱�Ƃɒ��ڂ���B
	CQuaternion qStart;
	qStart.SetRotationDeg(CVector3::AxisY(), 45.0f);
	CQuaternion qEnd;
	qEnd.SetRotationDeg(CVector3::AxisY(), -45.0f);
	//qEnd.SetRotationDeg(CVector3::AxisY(), 315.0f);
	

	//startRot��endRot�ŕ�ԁB
	CQuaternion rot;
	//��Ԏ��Ԃ̉��Z�B
	m_interpolateTime += 0.01f;
	if (m_interpolateTime > 1.0f) {
		//1.0�ŕ�ԏI���B
		m_interpolateTime = 1.0f;
	}
	//��Ԃ����s�B
	rot.Slerp(m_interpolateTime, qStart, qEnd);

	//���[���h�s����X�V�B
	m_model.UpdateWorldMatrix(m_position, rot, CVector3::One());
}
void Player::Draw(CCamera* camera)
{
	m_model.Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}
