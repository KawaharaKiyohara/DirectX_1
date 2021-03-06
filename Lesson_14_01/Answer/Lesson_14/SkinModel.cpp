#include "stdafx.h"
#include "SkinModel.h"



SkinModel::SkinModel()
{
	memset(&m_worldMatrix, 0.0f, sizeof(m_worldMatrix));
}

SkinModel::~SkinModel()
{
}

void SkinModel::UpateWorldMatrix(
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
	//平行移動行列、回転行列、拡大行列を作成する。
	CMatrix mTrans, mRotation, mScale;
	mTrans.MakeTranslation( position );
	mRotation.MakeRotationFromQuaternion( rotation );
	mRotation.Mul(mBias, mRotation);	//3dsMaxと軸を合わせる。
	mScale.MakeScaling( scale );

	//ワールド行列を作成する。
	//ワールド行列は拡大行列×回転行列×平行移動行列の順番で乗算する
	m_worldMatrix.Mul( mScale, mRotation );
	m_worldMatrix.Mul( m_worldMatrix, mTrans );
}
void SkinModel::Load(const wchar_t* filePath)
{
	//テクスチャのファイルパスにResourceを付加する。
	wchar_t newFilePath[256];
	swprintf_s(newFilePath, L"Resource/%s", filePath);
	//cmoファイルをロード。
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
	//共通レンダリングステート。
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