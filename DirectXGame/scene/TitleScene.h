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

	void FrontDraw() override;

	void Finalize() override;

private:
	Sprite* tmpSprite = nullptr;
	Sprite* fadeSprite = nullptr;

	// タイトル演出用
	XMFLOAT2 fadeSize = { 0,0 };
	float fadeAlpha = 1.0f;

#pragma region 非同期ロード

	// 非同期ロード用
	std::thread* th = nullptr;

#pragma endregion

};
