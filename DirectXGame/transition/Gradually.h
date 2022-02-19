#pragma once
#include "Transition.h"

class Gradually : public Transition
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="dir">グラデーションの向き デフォルトでfalse(横)</param>
	Gradually(bool dir = false);
	~Gradually() override;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Start() override;

private:
	Sprite* gradually = nullptr;

	// グラデーションの向き		false : 横 / true : 縦
	bool dir = false;

	XMFLOAT2 position = { 0,0 };
	float speed = 40.0f;
};

