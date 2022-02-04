#pragma once

#include "BaseScene.h"
#include "SelectScene.h"
#include "LoadScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include "IntervalScene.h"

#include "TexCollision.h"

#include <mutex>
#include <thread>

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
	Text* text;
	DebugCamera* camera = nullptr;

	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	ParticleManager* particleMan = nullptr;

	Xinput xinput;

	float centerX = 1280 / 2;
	float centerY = 720 / 2;

	XMFLOAT2 mousePos;

	Sprite* tmpSprite = nullptr;

	TexCollision* texCollision = nullptr;

#pragma region 非同期ロード

	// 非同期ロード用
	std::thread* th;

	// ロード用
	Sprite* load = nullptr;
	Sprite* loadCircle = nullptr;

#pragma endregion
};
