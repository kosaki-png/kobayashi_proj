#include "Fade.h"

Fade* Fade::instance = nullptr;

const float MAX_ALPHA = 1.5f;
const float MIN_ALPHA = 0.0f;
const float ORIGIN_ALPHA = 1.0f;

Fade::Fade()
{
}

Fade::~Fade()
{
	safe_delete(fadeSprite);
}

Fade* Fade::GetInstance()
{
	if (!instance)
	{
		instance = new Fade();
	}
	return instance;
}

void Fade::Initialize()
{
	// スプライト読み込み
	{
		Sprite::LoadTexture(100, L"Resources/texture/fade.png");
	}
	
	// スプライト生成
	{
		fadeSprite = Sprite::Create(100, { 0,0 });
	}

	effectTimeIn = 100;
	effectTimeOut = 100;
}

void Fade::Update()
{
	// フェードイン
	if (in && alpha == 0)
	{
		// α値を上げる
		alpha += ORIGIN_ALPHA / effectTimeIn;

		// 一定のα値になったら停止
		if (alpha >= MAX_ALPHA)
		{
			isEffect = false;
			alphaFlag = true;
			alpha = MAX_ALPHA;
			in = false;
		}
	}

	// フェードアウト
	if (out && alpha == 1)
	{
		// α値を下げる
		alpha -= ORIGIN_ALPHA / effectTimeOut;

		// 一定のα値になったら停止
		if (alpha <= MIN_ALPHA)
		{
			isEffect = false;
			alphaFlag = false;
			alpha = MIN_ALPHA;
			out = false;
		}
	}

	fadeSprite->SetAlpha(alpha);
	count++;
	
}

void Fade::Draw()
{
	if (in || out || alphaFlag)
	{
		fadeSprite->Draw();
	}
}