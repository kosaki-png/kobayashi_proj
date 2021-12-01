#pragma once

#include "SafeDelete.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Fbx.h"
#include "FbxLoader.h"
#include "ParticleManager.h"
#include "Text.h"
#include "DebugCamera.h"
#include "MainCamera.h"
#include "LightGroup.h"
#include "XinputControll.h"
#include "Fade.h"

#include "BaseScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "EndScene.h"

#include <mutex>

#include "Player.h"
#include "ObjectManager.h"
#include "ModelManager.h"
#include "TexCollision.h"

class GameScene :
	public BaseScene
{
private:
	using ArgColor = TexCollision::ArgColor;

public:
	GameScene();
	~GameScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
	Text* text;
	DebugCamera* camera = nullptr;
	MainCamera* mainCamera = nullptr;

	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	ParticleManager* particleMan = nullptr;

	Xinput xinput;

	// 画面中心
	XMFLOAT2 SCREEN_CENTER = { 1280.0f / 2.0f, 720.0f / 2.0f };

	XMFLOAT2 mousePos;

	// 非同期ロード用
	std::thread* th;

	// ロード用
	Sprite* load = nullptr;
	Sprite* loadcircle = nullptr;
	bool preload = false;
	bool isInit = false;

	// オプション用
	bool option = false;
	Sprite* optionSprite = nullptr;
	Sprite* cursorSprite = nullptr;

	// オブジェクト宣言
	Player* player = nullptr;

	ObjectManager* objMng = nullptr;

	TexCollision* texCol = nullptr;

	// マップ（一時的）
	Fbx* map[9] = {};
	Fbx* floor[9] = {};

	// 移動量保存用変数
	XMFLOAT3 keepVec = { 0,0,0 };
};