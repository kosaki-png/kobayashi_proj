#pragma once

#include "BaseScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "EndScene.h"
#include "IntervalScene.h"

#include <thread>

class LoadScene : 
	public BaseScene
{
public:
	LoadScene(int stage);
	~LoadScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

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

#pragma region �񓯊����[�h

	int stage = 0;

	// �񓯊����[�h�p
	std::thread* th;

	// ���[�h�p
	Sprite* loading = nullptr;
	Sprite* loaded = nullptr;
	Sprite* loadBar = nullptr;
	Sprite* loadBarWhite = nullptr;

#pragma endregion

	bool isEffect = false;

	Fbx* kogakuin = nullptr;
};