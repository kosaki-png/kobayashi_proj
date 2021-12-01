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
	// �u���b�N�A�E�g�p�X�v���C�g
	Sprite* fadeSprite = nullptr;
	// ���l
	float alpha = 0.0f;
	// ���l���オ�������̕\���p
	bool alphaFlag = true;

protected:
	static Fade* Fade::instance;
	Fade();
	~Fade();
};