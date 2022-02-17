#pragma once

#include "BaseScene.h"
#include "TitleScene.h"
#include "LoadScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include "IntervalScene.h"

#include "Gush.h"

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
	// セレクト用マップ
	Fbx* map[4] = {};
	XMFLOAT3 mapPos[4] = {};
	float mapRad = 0;

	// セレクト背景
	Fbx* back = nullptr;

	float rad = 0;

	// ステージ選択用
	float vel = 0;
	bool isMove = false;
	float reRot = 0;
	int nowMap = 0;

	float selRad = 0.0f;

	std::array<Gush*, 30> gush;
};
