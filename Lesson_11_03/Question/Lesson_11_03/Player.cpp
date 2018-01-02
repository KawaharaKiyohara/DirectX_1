#include "stdafx.h"
#include "Player.h"
#include "Coin.h"

Player::Player()
{
	//モデルのロード。
	m_model.Load(L"modelData/unityChan.cmo");
	//プレイヤーの初期位置を設定する。
	m_position.x = -300.0f;
	m_position.y = -200.0f;
}


Player::~Player()
{
}
void Player::Update()
{
	//プレイヤーの移動処理。
	if (GetAsyncKeyState('D')) {
		//Wキーが押された。
		m_position.x += 5.0f;
		//Hunds-On-2 90°回す。
	}
	else if (GetAsyncKeyState('A')) {
		//Aキーが押された。
		m_position.x -= 5.0f;
		//Hunds-On-3 -90°回す。
	}
	for (int i = 0; i < NUM_COIN; i++) {
		if (g_coin[i]->m_isGet == false) {	//コイン取得済みでなければ。
			CVector3 v = g_coin[i]->m_position - m_position;
			float len = v.Length();
			if (len < 70.0f) {
				//コインとプレイヤーの距離が70cm以下なので、コイン取得フラグを立てる。
				g_coin[i]->m_isGet = true;	
			}
		}
	}
	//ワールド行列を更新。
	//Hunds-On-4　ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}
void Player::Draw(CCamera* camera)
{
	m_model.Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}
