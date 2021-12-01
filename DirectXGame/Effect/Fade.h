#pragma once

#include "BaseEffect.h"

class Fade : public BaseEffect
{
public:
	static Fade* GetInstance();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	// ブラックアウト用スプライト
	Sprite* fadeSprite = nullptr;
	// α値
	float alpha = 0.0f;
	// α値が上がった時の表示用
	bool alphaFlag = true;

protected:
	static Fade* Fade::instance;
	Fade();
	~Fade();
};