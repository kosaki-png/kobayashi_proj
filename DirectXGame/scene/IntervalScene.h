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
#include "SelectScene.h"
#include "EndScene.h"
#include "IntervalScene.h"

#include <thread>

class IntervalScene :
	public BaseScene
{
public:
	IntervalScene();
	~IntervalScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
	Text* text = nullptr;
	DebugCamera* camera = nullptr;

	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	ParticleManager* particleMan = nullptr;

	Xinput xinput;

	float centerX = 1280 / 2;
	float centerY = 720 / 2;

	XMFLOAT2 mousePos;

	Sprite* tmpSprite = nullptr;

#pragma region 非同期ロード

	// 非同期ロード用
	std::thread* th;

	// ロード用
	Sprite* load = nullptr;
	Sprite* loadCircle = nullptr;

#pragma endregion

	bool isEffect = false;



};