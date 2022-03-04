#pragma once

#include "Sprite.h"
#include "SpriteData.h"
#include <Windows.h>
#include <string>
#include <memory>
#include <array>
#include <DirectXMath.h>

class Text
{
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;

public:
	static const int maxCharCount = 32;	// 最大文字数
	static const int fontWidth = 100;			// フォント画像内1文字分の横幅
	static const int fontHeight = 150;		// フォント画像内1文字分の縦幅

public:
	static Text* GetInstance();

	void Initialize();

	/// <summary>
	/// 数字を一つ描画
	/// </summary>
	/// <param name="number">表示する数字（最大９９）</param>
	/// <param name="position">左上座標</param>
	/// <param name="scale">文字の大きさ</param>
	void PrintNumber(int number, XMFLOAT2 position, float scale = 1);

	/// <summary>
	/// 時間描画
	/// </summary>
	/// <param name="minutes">分（最大９９）</param>
	/// <param name="seconds">秒（最大９９）</param>
	/// <param name="position">左上座標</param>
	/// <param name="scale">大きさ</param>
	void PrintTime(int min, int sec, XMFLOAT2 position, float scale = 1);

	/// <summary>
	/// スコア描画
	/// </summary>
	/// <param name="now">今のスコア</param>
	/// <param name="all">集める総数</param>
	/// <param name="position">左上座標</param>
	/// <param name="scale">大きさ</param>
	void PrintScore(int now, int all, XMFLOAT2 position, float scale = 1);

	void DrawAll();

	void Destroy();

private:
	Text();
	~Text();

	static Text* instance;

	// 文字表示用のスプライト
	std::array<std::unique_ptr<Sprite>, maxCharCount> sprite;

	int indexCnt = 0;

};

