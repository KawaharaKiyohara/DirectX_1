#pragma once
/*!
 *@brief	cmoファイルを使用したモデル表示クラス。
 */
class SkinModel
{
public:
	/*!
	*@brief	FBXの上方向。
	*/
	enum EnFbxUpAxis {
		enFbxUpAxisY,		//Y-up
		enFbxUpAxisZ,		//Z-up
	};
	/*!
	 *@brief	コンストラクタ。
	 */
	SkinModel();
	/*!
	 *@brief	デストラクタ
	 */
	~SkinModel();
	/*!
	 *@brief	ロード。
	 *@param[in]	filePath		ロードするcmoファイルのファイルパス。
	 */
	void Load(const wchar_t* filePath);
	/*!
	 *@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	 *@param[in]	position	モデルの座標。
	 *@param[in]	rotation	モデルの回転。
	 *@param[in]	scale		モデルの拡大率。
	 *@param[in]	upAxis		FBXの上方向。
	 */
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale, EnFbxUpAxis upAxis = enFbxUpAxisZ);
	void UpdateWorldMatrixEuler(CVector3 position, CVector3 rotation, CVector3 scale, EnFbxUpAxis upAxis = enFbxUpAxisZ);
	/*!
	 *@brief	モデルを描画。
	 *@param[in]	viewMatrix		カメラ行列。
	 *  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
	 *@param[in]	projMatrix		プロジェクション行列。
	 *  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
	 */
	void Draw(CMatrix viewMatrix, CMatrix projMatrix);
private:
	std::unique_ptr<DirectX::Model>	m_modelDX;		//!<DirectXTKが提供するモデルクラス。
	CMatrix m_worldMatrix;							//!<ワールド行列。
};

