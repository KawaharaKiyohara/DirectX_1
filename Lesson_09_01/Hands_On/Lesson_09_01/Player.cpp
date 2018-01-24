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
	}
	else if (GetAsyncKeyState('A')) {
		//Aキーが押された。
		m_position.x -= 5.0f;
	}
	
	if(g_coin->m_isGet == false){	//g_coinが取得済みかどうかをチェック。
		//Hands-On 1 
		//コインとプレイヤーの距離を計算して、コインをゲットできるようにしなさい。
		//コインの座標はg_coin->m_positionで取得可能。
		CVector3 v = m_position - g_coin->m_position;
		float len = v.Length();
		if (len < 70.0f) {
			//コインとプレイヤーの距離が70cm以下なので、コイン取得フラグを設定する。
			g_coin->m_isGet = true;
		}
	}
	//ワールド行列を更新。
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 90.0f);
	m_model.UpateWorldMatrix(m_position, qRot, CVector3::One());
}
void Player::Draw(CCamera* camera)
{
	m_model.Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
}
