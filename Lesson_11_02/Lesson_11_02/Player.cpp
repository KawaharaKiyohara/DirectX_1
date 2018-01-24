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
	//プレイヤーの回転の補間。-45度と315度で同じ方向を表しているのに
	//補間のされ方が異なることを確認する。
	CVector3 startRot = {0.0f, 45.0f, 0.0f};	//Y軸周りに45°
	//CVector3 endRot = {0.0f, -45.0f, 0.0f};		//Y軸周りに-45°。
	CVector3 endRot = { 0.0f, 315.0f, 0.0f };	//Y軸周りに-45度と同じ姿勢を表すのだけど・・・。

	//startRotとendRotの間で線形補間。
	CVector3 rot;
	//補間時間の加算。
	m_interpolateTime += 0.01f;
	if (m_interpolateTime > 1.0f) {
		//1.0で補間終了。
		m_interpolateTime = 1.0f;
	}
	//補間を実行。
	rot.x = endRot.x * m_interpolateTime + startRot.x * (1.0f - m_interpolateTime);
	rot.y = endRot.y * m_interpolateTime + startRot.y * (1.0f - m_interpolateTime);
	rot.z = endRot.z * m_interpolateTime + startRot.z * (1.0f - m_interpolateTime);

	//ワールド行列を更新。
	m_model.UpdateWorldMatrixEuler(m_position, rot, CVector3::One());
}
void Player::Draw(CCamera* camera)
{
	m_model.Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}
