#pragma once

#include "PostEffect.h"

#include "BaseScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include "IntervalScene.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();
	void Destroy();

	void Start(DirectXCommon* dxCommon, Input* input, Audio* audio);
	void Update();
	void Draw();
	void Finalize();

	void PostEffectDraw();

private:
	BaseScene* scene = nullptr;

	IntervalScene* interval = nullptr;

	DirectXCommon* dxCommon;
	Input* input;
	Audio* audio;

	PostEffect* postEffect = nullptr;

protected:
	static SceneManager* SceneManager::instance;
	SceneManager();
	~SceneManager();
};

