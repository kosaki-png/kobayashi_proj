#include "Text.h"

Text* Text::instance = nullptr;

Text* Text::GetInstance()
{
	if (!instance)
	{
		instance = new Text();
	}
	return instance;
}

void Text::Initialize()
{
	for (int i = 0; i < maxCharCount; i++)
	{
		// スプライトを生成する
		sprite[i].reset(Sprite::Create(0, { 0,0 }));
	}
}

void Text::PrintNumber(int num, XMFLOAT2 position, float scale)
{
	int number = num;

	// 12を超えていたら上限値に
	if (number >= 12)
	{
		number = 11;
	}

	sprite[indexCnt]->SetPosition(position);
	sprite[indexCnt]->SetTextureRect({ (float)(fontWidth * number), 0 }, { (float)fontWidth , (float)fontHeight });
	sprite[indexCnt]->SetSize({ (float)(fontWidth * scale), (float)(fontHeight * scale) });

	indexCnt++;
}

void Text::PrintTime(int min, int sec, XMFLOAT2 position, float scale)
{
	int minutes = min;
	int second = sec;

	// 上限値に修正
	{
		if (minutes >= 100)
		{
			minutes = 99;
		}
		if (minutes < 0)
		{
			minutes = 0;
		}

		if (second >= 60)
		{
			second = 59;
		}
		if (second < 0)
		{
			second = 0;
		}
	}
	
	PrintNumber((int)(minutes / 10), { position.x + fontWidth * scale * 0, position.y }, scale);
	PrintNumber((int)(minutes % 10), { position.x + fontWidth * scale * 1, position.y }, scale);
	PrintNumber(				10 , { position.x + fontWidth * scale * 2, position.y }, scale);
	PrintNumber( (int)(second / 10), { position.x + fontWidth * scale * 3, position.y }, scale);
	PrintNumber( (int)(second % 10), { position.x + fontWidth * scale * 4, position.y }, scale);
}

void Text::PrintScore(int now, int all, XMFLOAT2 position, float scale)
{
	int nowScore = now;
	int allScore = all;

	// 上限値に修正
	{
		if (nowScore >= 100)
		{
			nowScore = 99;
		}
		if (nowScore < 0)
		{
			nowScore = 0;
		}

		if (allScore >= 100)
		{
			allScore = 99;
		}
		if (allScore < 0)
		{
			allScore = 0;
		}
	}

	PrintNumber((int)(nowScore / 10), { position.x + fontWidth * scale * 0, position.y }, scale);
	PrintNumber((int)(nowScore % 10), { position.x + fontWidth * scale * 1, position.y }, scale);
	PrintNumber(				 11 , { position.x + fontWidth * scale * 2, position.y }, scale);
	PrintNumber((int)(allScore / 10), { position.x + fontWidth * scale * 3, position.y }, scale);
	PrintNumber((int)(allScore % 10), { position.x + fontWidth * scale * 4, position.y }, scale);
}

void Text::DrawAll()
{
	// 全て描画
	for (int i = 0; i < indexCnt; i++)
	{
		sprite[i]->Draw();
	}

	indexCnt = 0;
}

void Text::Destroy()
{
	delete instance;
}

Text::Text()
{
}

Text::~Text()
{
}
