#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//モデルのロード。
	m_model.Load(L"modelData/unityChan.cmo");
	//プレイヤーの初期位置を設定する。
	m_position.x = 0.0f;
	m_position.y = -200.0f;
}


Player::~Player()
{
}
void Player::Update()
{
	//プレイヤーの回転の補間。オイラー角と違って-45°と315°で同じ補間が行われていることに注目する。
	CQuaternion qStart;
	qStart.SetRotationDeg(CVector3::AxisY(), 45.0f);
	CQuaternion qEnd;
	qEnd.SetRotationDeg(CVector3::AxisY(), -45.0f);
	//qEnd.SetRotationDeg(CVector3::AxisY(), 315.0f);
	

	//startRotとendRotで補間。
	CQuaternion rot;
	//補間時間の加算。
	m_interpolateTime += 0.01f;
	if (m_interpolateTime > 1.0f) {
		//1.0で補間終了。
		m_interpolateTime = 1.0f;
	}
	//補間を実行。
	rot.Slerp(m_interpolateTime, qStart, qEnd);

	//ワールド行列を更新。
	m_model.UpdateWorldMatrix(m_position, rot, CVector3::One());
}
void Player::Draw(CCamera* camera)
{
	m_model.Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}
