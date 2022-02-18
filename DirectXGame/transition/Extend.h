#pragma once
#include "Transition.h"

class Extend : public Transition
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
	Extend();
	~Extend() override;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Start() override;

private:
	// 演出用スプライト
	Trance line[2];

	float width = 10;

};

