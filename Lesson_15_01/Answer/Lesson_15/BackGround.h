#pragma once
#include "SkinModel.h"

class BackGround
{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	BackGround();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~BackGround();
	/*!
	 *@brief	�������B
	 */
	void Init();
	/*!
	 *@brief	�X�V�B
	 */
	void Update();
	/*!
	 *@brief	�`��B
	 */
	void Draw();
	SkinModel m_model;	//���f���f�[�^�B
};

