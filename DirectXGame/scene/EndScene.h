#pragma once

#include "BaseScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "LoadScene.h"
#include "GameScene.h"
#include "IntervalScene.h"

class EndScene :
	public BaseScene
{
public:
	EndScene(int stage);
	~EndScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

	void FrontDraw() override;

	void Finalize() override;

private:
	int stage = 0;

	Sprite* frame = nullptr;
	Sprite* cursor = nullptr;

	bool cursorFlip = false;

	Fbx* mapObj = nullptr;

};