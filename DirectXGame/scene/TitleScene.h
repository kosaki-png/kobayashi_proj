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

	Sprite* tmpSprite = nullptr;

#pragma region �񓯊����[�h

	// �񓯊����[�h�p
	std::thread* th;

	// ���[�h�p
	Sprite* load = nullptr;
	Sprite* loadCircle = nullptr;

#pragma endregion
};
