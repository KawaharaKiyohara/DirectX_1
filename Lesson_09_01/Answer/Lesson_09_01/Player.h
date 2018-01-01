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
};

