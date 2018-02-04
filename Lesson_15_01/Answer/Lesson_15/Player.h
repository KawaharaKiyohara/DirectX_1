#pragma once

#include "SkinModel.h"

class Player
{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	Player();
	/*!
	 *@brief	デストラクタ。
	 */
	~Player();
	/*!
	 *@brief	初期化。
	 */
	void Init();
	/*!
	 *@brief	更新。
	 */
	void Update();
	/*!
	 *@brief	描画。
	 */
	void Draw();

	CVector3 m_position = CVector3::Zero();				//座標。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	SkinModel m_model;									//モデルデータ。
};

