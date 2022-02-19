#include "Gradually.h"

using namespace SpriteData;

Gradually::Gradually(bool dir)
	: dir(dir)
{}

Gradually::~Gradually()
{
	safe_delete(gradually);
}

void Gradually::Initialize()
{
	// 向きによって初期化分岐
	if (dir)
	{
		gradually = Sprite::Create(FADE_VERTICAL, { 0,0 });
		position = { 0,-WINDOW_HEIGHT * 3.0f };
	}
	else
	{
		gradually = Sprite::Create(FADE_PARALLEL, { 0,0 });
		position = { -WINDOW_WIDTH * 3.0f,0 };
	}
}

void Gradually::Update()
{
	isCover = false;

	if (isEffect)
	{
		if (dir)
		{
			position.y += speed;

			if (position.y == -WINDOW_HEIGHT)
			{
				isCover = true;
			}
			if (position.y > WINDOW_HEIGHT)
			{
				isEffect = false;
			}
		}
		else
		{
			position.x += speed;

			if (position.x == -WINDOW_WIDTH)
			{
				isCover = true;
			}

			if (position.x > WINDOW_WIDTH)
			{
				isEffect = false;
			}
		}
	}

	// 座標セット
	gradually->SetPosition(position);
}

void Gradually::Draw()
{
	if (isEffect)
	{
		gradually->Draw();
	}
}

void Gradually::Start()
{
	// エフェクト初期化
	Transition::Start();

	if (dir)
	{
		position = { 0,-WINDOW_HEIGHT * 3.0f };
	}
	else
	{
		position = { -WINDOW_WIDTH * 3.0f,0 };
	}
}
