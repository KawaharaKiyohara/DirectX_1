#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}
void BackGround::Init()
{
	m_model.Load(L"modelData/background.cmo");
}
void BackGround::Update()
{
	m_model.UpateWorldMatrix(
		CVector3::Zero(),
		CQuaternion::Identity(),
		CVector3::One(),
		SkinModel::enFbxUpAxisY);
}
void BackGround::Draw()
{
	m_model.Draw(g_camera3D->GetViewMatrix(), g_camera3D->GetProjectionMatrix());
}