#include "stdafx.h"
#include "SkinModel.h"



SkinModel::SkinModel()
{
}

SkinModel::~SkinModel()
{
}
void SkinModel::UpdateWorldMatrixEuler(CVector3 position, CVector3 rotation, CVector3 scale, EnFbxUpAxis upAxis)
{
	CMatrix mBias = CMatrix::Identity();
	if (upAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	//���s�ړ��s����쐬�B
	CMatrix mTrans, mRotation, mScale;
	mTrans.MakeTranslation(position);
	//��]�s����쐬�B
	CMatrix mWork;
	mRotation.MakeRotationX(CMath::DegToRad(rotation.x));
	mWork.MakeRotationZ(CMath::DegToRad(rotation.z));
	mRotation.Mul(mRotation, mWork);
	mWork.MakeRotationY(CMath::DegToRad(rotation.y));
	mRotation.Mul(mRotation, mWork);
	mRotation.Mul(mBias, mRotation);	//3dsMax�Ǝ������킹��B

	mScale.MakeScaling(scale);

	//���[���h�s��͊g��s��~��]�s��~���s�ړ��s��̏��Ԃŏ�Z����
	m_worldMatrix.Mul(mScale, mRotation);
	m_worldMatrix.Mul(m_worldMatrix, mTrans);

}
void SkinModel::UpdateWorldMatrix(
	CVector3 position, 
	CQuaternion rotation, 
	CVector3 scale, 
	SkinModel::EnFbxUpAxis upAxis
)
{
	CMatrix mBias = CMatrix::Identity();
	if (upAxis == enFbxUpAxisZ){
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	//���s�ړ��s��A��]�s��A�g��s����쐬����B
	CMatrix mTrans, mRotation, mScale;
	mTrans.MakeTranslation( position );
	mRotation.MakeRotationFromQuaternion( rotation );
	mRotation.Mul(mBias, mRotation);	//3dsMax�Ǝ������킹��B
	mScale.MakeScaling( scale );

	//���[���h�s����쐬����B
	//���[���h�s��͊g��s��~��]�s��~���s�ړ��s��̏��Ԃŏ�Z����
	m_worldMatrix.Mul( mScale, mRotation );
	m_worldMatrix.Mul( m_worldMatrix, mTrans );
}
void SkinModel::Load(const wchar_t* filePath)
{
	//�e�N�X�`���̃t�@�C���p�X��Resource��t������B
	wchar_t newFilePath[256];
	swprintf_s(newFilePath, L"Resource/%s", filePath);
	//cmo�t�@�C�������[�h�B
	DirectX::EffectFactory effectFactory(g_graphicsEngine->GetD3DDevice());
	effectFactory.SetDirectory(L"Resource/modelData");
	
	m_modelDX = DirectX::Model::CreateFromCMO(
		g_graphicsEngine->GetD3DDevice(),
		newFilePath,
		effectFactory,
		false,
		false
	);
}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix)
{
	//���ʃ����_�����O�X�e�[�g�B
	if (m_modelDX) {
		static DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

		//Draw!!!
		m_modelDX->Draw(
			g_graphicsEngine->GetD3DDeviceContext(),
			state,
			m_worldMatrix,
			viewMatrix,
			projMatrix,
			false
		);
	}
}