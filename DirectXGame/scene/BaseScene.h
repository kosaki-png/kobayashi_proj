#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include <DirectXMath.h>

#include "Fade.h"

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

	virtual void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Finalize() = 0;

	BaseScene* GetNextScene() { return nextScene; }

protected:
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;

	BaseScene* nextScene = nullptr;

	Fade* fade = Fade::GetInstance();

	bool nextSceneFlag = true;
};
