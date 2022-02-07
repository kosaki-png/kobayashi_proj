#pragma once

#include "BaseScene.h"
#include "TitleScene.h"
#include "LoadScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include "IntervalScene.h"

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
	Camera* camera = nullptr;

	float centerX = 1280 / 2;
	float centerY = 720 / 2;

	XMFLOAT2 mousePos;

	Sprite* tmpSprite = nullptr;

	// セレクト用マップ
	Fbx* map[4] = {};
	XMFLOAT3 mapPos[4] = {};
	float mapRad = 0;

	// セレクト背景
	Fbx* back = nullptr;
};
