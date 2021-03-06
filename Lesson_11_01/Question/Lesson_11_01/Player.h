#pragma once

#include "SkinModel.h" //SkinModelクラスを使用するので、ヘッダーをインクルード。


class Player
{
public:
	//コンストラクタ。
	Player();
	//デストラクタ。
	~Player();
	//更新。
	void Update();
	//描画。
	void Draw(CCamera* camera);
	/////////////////////////////////////////////////
	// ここからメンバ変数。
	/////////////////////////////////////////////////
	SkinModel m_model;		//モデル。
	CVector3 m_position = CVector3::Zero();	//座標。
	//Hunds-On-1 オイラー角を表すベクトル型の変数を用意する。
	CVector3 m_rotation = CVector3::Zero();
};

extern Player* g_player;
