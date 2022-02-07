#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "SafeDelete.h"

// 入力関係
#include "Input.h"
#include "XinputControll.h"

// オブジェクト関係
#include "Sprite.h"
#include "Fbx.h"
#include "FbxLoader.h"
#include "Audio.h"

// カメラ関係
#include "DebugCamera.h"
#include "FixedCamera.h"
#include "MainCamera.h"
#include "OrbitCamera.h"

// 管理関係
#include "Objectmanager.h"
#include "ModelManager.h"

// データ関係
#include "StageDataStorage.h"

struct SceneButton
{
	DirectX::XMFLOAT2 position = { 0,0 };
	DirectX::XMFLOAT2 scale = { 0,0 };
};

class BaseScene
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

	static const int texNumber = 0;

public:
	BaseScene();
	~BaseScene();

	/// <summary>
	/// シーン初期化
	/// </summary>
	/// <param name="dxCommon">DirectX系情報</param>
	/// <param name="input">入力情報</param>
	/// <param name="audio">音情報</param>
	virtual void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	/// <summary>
	/// シーン更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 背景スプライト描画
	/// </summary>
	//virtual void BackSpriteDraw();

	/// <summary>
	/// 3Dオブジェクト描画
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// 前景スプライト描画
	/// </summary>
	//virtual void ForeSpriteDraw();

	/// <summary>
	/// シーン終了
	/// </summary>
	virtual void Finalize() = 0;

	BaseScene* GetNextScene() { return nextScene; }

	bool GetGodrayFlag() { return isGodray; }

protected:
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;

	// 次のシーンへのトリガー
	BaseScene* nextScene = nullptr;

	StageDataStorage* stageData = StageDataStorage::GetInstance();

	bool stop = true;

	bool isGodray = false;

	// 画面中心
	const float WINDOW_WIDTH = 1280.0f;
	const float WINDOW_HEIGHT = 720.0f;
	const XMFLOAT2 SCREEN_CENTER = { 1280.0f / 2.0f, 720.0f / 2.0f };

	XMFLOAT2 mousePos;

	Camera* camera = nullptr;
};
