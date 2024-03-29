#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "SafeDelete.h"

// 入力関係
#include "Input.h"
#include "XinputControll.h"
#include "Button.h"

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
#include "SpriteData.h"
#include "Text.h"

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

public:
	BaseScene();
	virtual ~BaseScene();

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
	/// 3Dオブジェクト描画
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// 前景描画
	/// </summary>
	virtual void FrontDraw() = 0;

	/// <summary>
	/// シーン終了時処理
	/// </summary>
	virtual void Finalize() = 0;

	BaseScene* GetNextScene() { return nextScene; }

	// ポストエフェクト用
	bool GetGodrayFlag() { return isGodray; }
	XMFLOAT2 GetCameraRot() { return camera->GetCameraRot(); }
	bool GetIsGame() { return isGame; }

	// シーン遷移用
	int GetTrans() { return trans; }

protected:
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;

	Camera* camera = nullptr;

	// 次のシーンへのトリガー
	BaseScene* nextScene = nullptr;

	Text* text = nullptr;

	StageDataStorage* stageData = StageDataStorage::GetInstance();

	bool stop = true;

	// ゴッドレイを入れるか
	bool isGodray = false;

	// 画面中心
	const float WINDOW_WIDTH = 1280.0f;
	const float WINDOW_HEIGHT = 720.0f;
	const XMFLOAT2 SCREEN_CENTER = { 1280.0f / 2.0f, 720.0f / 2.0f };

	XMFLOAT2 mousePos;
	bool isGame = false;

	int trans = 0;
};
