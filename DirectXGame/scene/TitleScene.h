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
#include "GameScene.h"
#include "SelectScene.h"
#include "EndScene.h"

#include "TexCollision.h";

#include <mutex>

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

};
