#pragma once

#include "BaseScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "LoadScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include "IntervalScene.h"

#include <thread>

class IntervalScene :
	public BaseScene
{
private:
	struct Trance
	{
		Sprite* sprite = nullptr;
		XMFLOAT2 position = { 0,0 };
		XMFLOAT2 speed = { 0,0 };
		XMFLOAT2 size = { 1,1 };
	};

public:
	IntervalScene();
	~IntervalScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void Start();

	bool GetIsEffect() { return isEffect; }

	bool GetIsCover() { return isCover; }

private:
	Text* text = nullptr;
	OrbitCamera* camera = nullptr;

	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	ParticleManager* particleMan = nullptr;

	Xinput xinput;

	float centerX = 1280 / 2;
	float centerY = 720 / 2;

	XMFLOAT2 mousePos;

	Sprite* tmpSprite = nullptr;

#pragma region 演出

	// 演出用スプライト
	Sprite* back = nullptr;
	Trance trance[4];

	float alpha = 0;

	Trance line[2];
	float width = 10;

	// 演出が機能しているか
	bool isEffect = false;

	// 完全に隠れたか
	bool isCover = false;

	// 演出が始まってからの時間
	int startCnt = 0;

#pragma endregion

private:
	const float WINDOW_WIDTH = 1280.0f;
	const float WINDOW_HEIGHT = 720.0f;
};