#pragma once
/*!
 *@brief	cmo�t�@�C�����g�p�������f���\���N���X�B
 */
class SkinModel
{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	SkinModel();
	/*!
	 *@brief	�f�X�g���N�^
	 */
	~SkinModel();
	/*!
	 *@brief	���[�h�B
	 *@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	 */
	void Load(const wchar_t* filePath);
	/*!
	 *@brief	���f�������[���h���W�n�ɕϊ����邽�߂̃��[���h�s����X�V����B
	 *@param[in]	position	���f���̍��W�B
	 *@param[in]	rotation	���f���̉�]�B
	 *@param[in]	scale		���f���̊g�嗦�B
	 */
	void UpateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	 *@brief	���f����`��B
	 *@param[in]	viewMatrix		�J�����s��B
	 *  ���[���h���W�n��3D���f�����J�������W�n�ɕϊ�����s��ł��B
	 *@param[in]	projMatrix		�v���W�F�N�V�����s��B
	 *  �J�������W�n��3D���f�����X�N���[�����W�n�ɕϊ�����s��ł��B
	 */
	void Draw(CMatrix viewMatrix, CMatrix projMatrix);
private:
	std::unique_ptr<DirectX::Model>	m_modelDX;		//!<DirectXTK���񋟂��郂�f���N���X�B
	CMatrix m_worldMatrix;							//!<���[���h�s��B
};

