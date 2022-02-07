#pragma once

#include "BaseScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "EndScene.h"
#include "IntervalScene.h"

#include <thread>

class LoadScene : 
	public BaseScene
{
public:
	LoadScene(int stage);
	~LoadScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:

#pragma region 非同期ロード

	int stage = 0;

	// 非同期ロード用
	std::thread* th;

	// ロード用
	Sprite* loading = nullptr;
	Sprite* loaded = nullptr;
	Sprite* loadBar = nullptr;
	Sprite* loadBarWhite = nullptr;

#pragma endregion

	bool isEffect = false;

	Fbx* mapObj = nullptr;
};