#pragma once

#include "BaseScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "LoadScene.h"
#include "EndScene.h"
#include "IntervalScene.h"

#include <mutex>

#include "Player.h"
#include "Enemy.h"

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
	const float MAP_WIDTH = 3390.0f;
	const float MAP_HEIGHT = 2775.0f;

private:
	Text* text;
	DebugCamera* camera = nullptr;
	MainCamera* mainCamera = nullptr;

	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	ParticleManager* particleMan = nullptr;

	Xinput xinput;

	// 画面中心
	const XMFLOAT2 SCREEN_CENTER = { 1280.0f / 2.0f, 720.0f / 2.0f };

	XMFLOAT2 mousePos;

	// 各クラス宣言宣言
	Player* player = nullptr;
	
	ModelManager* modelMng = nullptr;
	ObjectManager* objMng = nullptr;
	TexCollision* texCol = nullptr;

	// オプション用
	bool option = false;
	Sprite* optionSprite = nullptr;
	Sprite* cursorSprite = nullptr;

	// ミニマップ用
	Sprite* minimap = nullptr;
	Sprite* mini = nullptr;

	// マップ（一時的）
	Fbx* map[9] = {};
	Fbx* floor[9] = {};
	Fbx* skydome = nullptr;

	// 移動量保存用変数
	XMFLOAT3 keepVec = { 0,0,0 };

	// 感度変更用
	float sence = 1.0f;
};