#pragma once

#include "BaseScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "LoadScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include "IntervalScene.h"

#include "Transition.h"
#include "Extend.h"
#include "Gradually.h"
#include "ClearProd.h"

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
	void FrontDraw() override;
	void Finalize() override;

	void Start();

	bool GetIsEffect() { return transition->GetIsEffect(); }

	bool GetIsCover() { return transition->GetIsCover(); }

	void SetTrans(int mode);

private:
	Transition* transition = nullptr;

	Extend* extend = nullptr;
	Gradually* gradually = nullptr;
	ClearProd* clearProd = nullptr;
};