#pragma once

#include "SkinModel.h" //SkinModel�N���X���g�p����̂ŁA�w�b�_�[���C���N���[�h�B

class Coin
{
public:
	//�R���X�g���N�^�B
	Coin();
	//�f�X�g���N�^�B
	~Coin();
	//�X�V�B
	void Update();
	//�`��B
	void Draw(CCamera* camera);
	/////////////////////////////////////////////////
	// �������烁���o�ϐ��B
	/////////////////////////////////////////////////
	SkinModel m_model;		//���f���B
	CVector3 m_position = CVector3::Zero();	//���W�B
	bool m_isGet = false;	//�R�C���擾�ς݂̃t���O�B
};

extern Coin* g_coin;
