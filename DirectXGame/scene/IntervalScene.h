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
		Sprite* trance = nullptr;
		XMFLOAT2 position;
		XMFLOAT2 speed;
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
	Trance trance[6];

	bool isEffect = false;

	bool isCover = false;

	int startCnt = 0;
};