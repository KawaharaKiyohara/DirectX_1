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
	//�v���C���[�̉�]�̕�ԁB-45�x��315�x�œ���������\���Ă���̂�
	//��Ԃ̂�������قȂ邱�Ƃ��m�F����B
	CVector3 startRot = {0.0f, 45.0f, 0.0f};	//Y�������45��
	//CVector3 endRot = {0.0f, -45.0f, 0.0f};		//Y�������-45���B
	CVector3 endRot = { 0.0f, 315.0f, 0.0f };	//Y�������-45�x�Ɠ����p����\���̂����ǁE�E�E�B

	//startRot��endRot�̊ԂŐ��`��ԁB
	CVector3 rot;
	//��Ԏ��Ԃ̉��Z�B
	m_interpolateTime += 0.01f;
	if (m_interpolateTime > 1.0f) {
		//1.0�ŕ�ԏI���B
		m_interpolateTime = 1.0f;
	}
	//��Ԃ����s�B
	rot.x = endRot.x * m_interpolateTime + startRot.x * (1.0f - m_interpolateTime);
	rot.y = endRot.y * m_interpolateTime + startRot.y * (1.0f - m_interpolateTime);
	rot.z = endRot.z * m_interpolateTime + startRot.z * (1.0f - m_interpolateTime);

	//���[���h�s����X�V�B
	m_model.UpdateWorldMatrixEuler(m_position, rot, CVector3::One());
}
void Player::Draw(CCamera* camera)
{
	m_model.Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}
