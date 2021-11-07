#pragma once

#include "SafeDelete.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Fbx.h"
#include "FbxLoader.h"
#include "ParticleManager.h"
#include "Text.h"
#include "DebugCamera.h"
#include "LightGroup.h"
#include "XinputControll.h"

#include "BaseScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "EndScene.h"

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
	Text* text;
	DebugCamera* camera = nullptr;

	Xinput xinput;

	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	ParticleManager* particleMan = nullptr;

	float centerX = 1280 / 2;
	float centerY = 720 / 2;

	XMFLOAT2 mousePos;

	Sprite* tmpSprite = nullptr;
};
