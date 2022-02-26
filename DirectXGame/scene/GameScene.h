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
#include "Crystal.h"

#include "TexCollision.h"

#include "Gush.h"

class GameScene :
	public BaseScene
{
private:
	using ArgColor = TexCollision::ArgColor;

public:
	GameScene(int stage);
	~GameScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

	void FrontDraw() override;

	void Finalize() override;

private:
	// 1マップの大きさ
	const float MAP_WIDTH = 3390.0f;
	const float MAP_HEIGHT = 2775.0f;

private:
	// プレイヤー
	Player* player = nullptr;

	// 敵
	//static const int ENEMY_COUNT = 100;
	//Enemy* enemy[ENEMY_COUNT] = {};

	// クリスタル
	static const int CRYSTAL_COUNT = 50;
	std::array<Crystal*, CRYSTAL_COUNT> crystal = {};
	std::array<XMFLOAT3, CRYSTAL_COUNT> crystalPos = {};
	
	ModelManager* modelMng = nullptr;
	ObjectManager* objMng = nullptr;
	TexCollision* texCol = nullptr;

	// オプション用
	bool option = false;
	Sprite* optionSprite = nullptr;
	Sprite* cursorSprite = nullptr;

	static const int GUSH_COUNT = 50;
	std::array<Gush*, GUSH_COUNT> gush = {};

#pragma region マップ

	// 指定ステージ
	int stage = 0;

	// ミニマップ
	Sprite* minimap = nullptr;
	Sprite* miniFrame = nullptr;
	Sprite* mapCursor = nullptr;

	// 全体マップ
	Sprite* mapAllFrame = nullptr;
	Sprite* mapAllPoint = nullptr;
	Sprite* mapAll = nullptr;
	bool isMap = false;

	// マップオブジェクト
	std::array<Fbx*, 9> map;
	Fbx* floor = nullptr;
	Fbx* skydome = nullptr;
	const float WORLD_HEIGHT = 1130 * 3;
	const float WORLD_WIDTH = 925 * 3;

#pragma endregion

	// 感度変更用
	float sence = 1.0f;

	XMFLOAT3 tmp = { 0,0,0 };

	int clearCnt = 0;
};