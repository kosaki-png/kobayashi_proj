#include "Extend.h"

using namespace SpriteData;

Extend::Extend()
{
}

Extend::~Extend()
{
	safe_delete(line[0].sprite);
	safe_delete(line[1].sprite);
}

void Extend::Initialize()
{
	for (int i = 0; i < 2; i++)
	{
		// 初期位置設定
		line[i].sprite = Sprite::Create(INTERVAL, { 0,0 });
		line[i].size = { 3000, 10 };
		line[i].position = { -3000, WINDOW_HEIGHT / 2 - 5 };
		line[i].speed = { 70.0f, 0 };
	}

	line[1].sprite->SetAnchorPoint({ 0.0f, 1.0f });
}

void Extend::Update()
{
	isCover = false;

	if (isEffect)
	{
		// エフェクト終了
		if (startCnt > 180)
		{
			isEffect = false;
		}

		for (int i = 0; i < 2; i++)
		{
			if (startCnt >= 30 && startCnt < 90)
			{
				if (line[i].position.x <= WINDOW_WIDTH - 3000)
				{
					line[i].position.x += line[i].speed.x;
					line[i].position.y += line[i].speed.y;
				}
				if (line[i].position.x >= WINDOW_WIDTH - 3000)
				{
					if (width < WINDOW_HEIGHT / 2)
					{
						width += width / 8;
					}

					line[i].size = { 3000, width };
				}
			}
			if (startCnt >= 120)
			{
				if (width > 0)
				{
					width -= width / 8;
				}
				if (width <= 0)
				{
					width = 0;
				}
				line[i].size = { 3000, width };
			}

			if (startCnt == 90)
			{
				isCover = true;
			}
			line[i].sprite->SetPosition(line[i].position);
			line[i].sprite->SetSize(line[i].size);
		}
	}

	startCnt++;
}

void Extend::Draw()
{
	if (isEffect)
	{
		for (int i = 0; i < 2; i++)
		{
			line[i].sprite->Draw();
		}
	}
}

void Extend::Start()
{
	// エフェクト初期化
	Transition::Start();

	width = 10;

	for (int i = 0; i < 2; i++)
	{
		// 初期位置設定
		line[i].size = { 3000, 10 };
		line[i].position = { -3000, WINDOW_HEIGHT / 2 - 5 };
		line[i].speed = { 70.0f, 0 };
	}
}
