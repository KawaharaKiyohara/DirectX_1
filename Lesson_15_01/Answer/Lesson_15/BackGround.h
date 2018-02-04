#pragma once
#include "SkinModel.h"

class BackGround
{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	BackGround();
	/*!
	 *@brief	デストラクタ。
	 */
	~BackGround();
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
	SkinModel m_model;	//モデルデータ。
};

