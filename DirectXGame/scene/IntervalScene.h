#pragma once

#include "BaseScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "LoadScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include "IntervalScene.h"

#include <thread>

class IntervalScene :
	public BaseScene
{
private:
	struct Trance
	{
		Sprite* sprite = nullptr;
		XMFLOAT2 position = { 0,0 };
		XMFLOAT2 speed = { 0,0 };
		XMFLOAT2 size = { 1,1 };
	};

public:
	IntervalScene();
	~IntervalScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void Start();

	bool GetIsEffect() { return isEffect; }

	bool GetIsCover() { return isCover; }

private:

	OrbitCamera* camera = nullptr;

#pragma region ���o

	// ���o�p�X�v���C�g
	Trance line[2];

	float width = 10;

	// ���o���@�\���Ă��邩
	bool isEffect = false;

	// ���S�ɉB�ꂽ��
	bool isCover = false;

	// ���o���n�܂��Ă���̎���
	int startCnt = 0;

#pragma endregion
};