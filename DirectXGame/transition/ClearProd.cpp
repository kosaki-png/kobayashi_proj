#include "ClearProd.h"

using namespace SpriteData;

ClearProd::ClearProd()
{
}

ClearProd::~ClearProd()
{
	safe_delete(black.sprite);
	safe_delete(white.sprite);
	safe_delete(bar.sprite);
	safe_delete(square.sprite);
	safe_delete(fade.sprite);
}

void ClearProd::Initialize()
{
	black.sprite = Sprite::Create(BLACK, { 0,0 });
	white.sprite = Sprite::Create(CLEAR_WHITE, { 0,0 });
	bar.sprite = Sprite::Create(CLEAR_BAR, { 0,0 });
	square.sprite = Sprite::Create(CLEAR_SQUARE, { 0,0 });
	fade.sprite = Sprite::Create(FADE_CIRCLE, { 0,0 }, { 0,0,0,1 });

	black.Init();
	white.Init();
	bar.Init();
	square.Init();
	fade.Init();

	black.sprite->SetAnchorPoint({ 0.5f, 0.5f });
	white.sprite->SetAnchorPoint({ 0.5f, 0.5f });
	bar.sprite->SetAnchorPoint({ 0.5f, 0.5f });
	square.sprite->SetAnchorPoint({ 0.5f, 0.5f });
	fade.sprite->SetAnchorPoint({ 0.5f, 0.5f });

	square.alpha = 0.0f;
	square.size = { square.size.x * 0.2f, square.size.y * 0.2f };

	bar.size = { bar.size.x, 0 };

	black.size = { black.size.x, 0 };

	white.size = { white.size.x * 0.9f, white.size.y * 0.9f };
}

void ClearProd::Update()
{
	isCover = false;

	// スクエアのαを上げる
	if (startCnt < 100 && square.alpha <= 1.0f)
	{
		square.alpha += 1.0f / 60;
		square.size.x -= 1280.0f * 0.2f / 60;
		square.size.y -= 720.0f * 0.2f / 60;
	}
	if (square.alpha >= 1.0f && bar.size.y <= 720.0f)
	{
		bar.size.y += (721.0f - bar.size.y) / 10;
		bar.size.x += (2000.0f - bar.size.x) / 10;
	}
	if (square.alpha >= 1.0f && black.size.y <= 150.0f && white.alpha > 0)
	{
		black.size.y += (150.0f - black.size.y) / 20;
	}
	if (bar.size.y > 600.0f && bar.alpha > 0)
	{
		bar.alpha -= 1.0f / 30;
	}
	if (startCnt > 200.0f && white.alpha > 0)
	{
		white.alpha -= 1.0f / 30;
	}
	if (white.alpha < 0 && black.size.y < 720.0f)
	{
		black.size.y += (721.0f - black.size.y) / 10;
		if (black.size.y >= 720.0f)
		{
			isCover = true;
		}
	}
	if (black.size.y > 720.0f && square.size.x >= 0)
	{
		square.size.x -= square.size.x / 60;
		square.size.y -= square.size.y / 60;
		square.rotation += 4;
		square.alpha -= 1.0f / 20;
	}
	if (square.size.x <= 300 && square.alpha <= 0)
	{
		black.alpha -= 1.0f / 30;
	}
	if (black.alpha <= 0)
	{
		fade.alpha -= 1.0f / 30;

		if (fade.alpha <= 0)
		{
			isEffect = false;
		}
	}
	
	black.Update();
	white.Update();
	bar.Update();
	square.Update();
	fade.Update();

	startCnt++;
}

void ClearProd::Draw()
{
	if (isEffect)
	{
		black.sprite->Draw();
		square.sprite->Draw();
		if (bar.size.y > 600.0f)
		{
			white.sprite->Draw();
		}
		bar.sprite->Draw();

		if (black.size.y > 720.0f)
		{
			fade.sprite->Draw();
		}
	}
}

void ClearProd::Start()
{
	Transition::Start();

	square.alpha = 0.0f;
	square.size = { 1280.0f + 1280.0f * 0.2f, 720.0f + 720.0f * 0.2f };

	bar.size = { bar.size.x, 0 };
	bar.alpha = 1.0f;

	black.alpha = 1.0f;
	black.size = { black.size.x, 0 };

	white.alpha = 1.0f;

	fade.alpha = 1.0f;
}
