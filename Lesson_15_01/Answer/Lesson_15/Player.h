#pragma once

#include "SkinModel.h"

class Player
{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	Player();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~Player();
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

	CVector3 m_position = CVector3::Zero();				//���W�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	SkinModel m_model;									//���f���f�[�^�B
};

