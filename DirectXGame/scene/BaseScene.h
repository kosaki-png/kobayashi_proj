#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "SafeDelete.h"

// ���͊֌W
#include "Input.h"
#include "XinputControll.h"

// �I�u�W�F�N�g�֌W
#include "Sprite.h"
#include "Fbx.h"
#include "FbxLoader.h"
#include "Audio.h"

// �J�����֌W
#include "DebugCamera.h"
#include "FixedCamera.h"
#include "MainCamera.h"
#include "OrbitCamera.h"

// �Ǘ��֌W
#include "Objectmanager.h"
#include "ModelManager.h"

// �f�[�^�֌W
#include "StageDataStorage.h"
#include "SpriteData.h"

struct SceneButton
{
	DirectX::XMFLOAT2 position = { 0,0 };
	DirectX::XMFLOAT2 scale = { 0,0 };
};

class BaseScene
{
protected: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	BaseScene();
	virtual ~BaseScene();

	/// <summary>
	/// �V�[��������
	/// </summary>
	/// <param name="dxCommon">DirectX�n���</param>
	/// <param name="input">���͏��</param>
	/// <param name="audio">�����</param>
	virtual void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	/// <summary>
	/// �V�[���X�V
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 3D�I�u�W�F�N�g�`��
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// �O�i�`��
	/// </summary>
	virtual void FrontDraw() = 0;

	/// <summary>
	/// �V�[���I��������
	/// </summary>
	virtual void Finalize() = 0;

	BaseScene* GetNextScene() { return nextScene; }

	// �|�X�g�G�t�F�N�g�p
	bool GetGodrayFlag() { return isGodray; }
	XMFLOAT2 GetCameraRot() { return camera->GetCameraRot(); }
	bool GetIsGame() { return isGame; }

	// �V�[���J�ڗp
	int GetTrans() { return trans; }

protected:
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;

	Camera* camera = nullptr;

	// ���̃V�[���ւ̃g���K�[
	BaseScene* nextScene = nullptr;

	StageDataStorage* stageData = StageDataStorage::GetInstance();

	bool stop = true;

	bool isGodray = false;

	// ��ʒ��S
	const float WINDOW_WIDTH = 1280.0f;
	const float WINDOW_HEIGHT = 720.0f;
	const XMFLOAT2 SCREEN_CENTER = { 1280.0f / 2.0f, 720.0f / 2.0f };

	XMFLOAT2 mousePos;
	bool isGame = false;

	int trans = 0;
};
