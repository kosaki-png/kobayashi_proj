#pragma once
#include "Sprite.h"

namespace SpriteData
{
	// 文字描画用 0〜
	const int FONT_DEF = 0;

	// タイトル用 1〜
	const int TITLE = 1;
	const int FADE = 2;

	// セレクト用 10〜
	const int SELECT_FLAME = 10;

	// ロード用 20〜
	const int LOADFLAME = 20;
	const int LOADBAR   = 21;
	const int LOADED	= 22;
	const int LOADING   = 23;

	// ゲーム用 30〜
	// 表示マップ系 30〜
	const int MAP_FLAME   = 30;
	const int MAP_POINT   = 31;
	const int MAP_CURSOR  = 32;
	const int MAP_MINI	  = 33;

	// ポーズ用 35〜
	const int GAME_FLAME = 35;
	const int PAUSE_FLAME = 36;
	const int PAUSE_DEBUG = 37;

	// ステージマップ系 40〜
	const int MAP01_FLAME = 40;
	const int MAP02_FLAME = 41;
	const int MAP03_FLAME = 42;
	const int MAP04_FLAME = 43;
	const int MAP01_REF   = 44;
	const int MAP02_REF   = 45;
	const int MAP03_REF   = 46;
	const int MAP04_REF   = 47;

	// エンド用 60〜
	const int RESULT_FRAME = 60;
	const int RESULT_CURSOR = 61;

	// インターバル用 70〜
	const int INTERVAL		= 70;
	const int WHITE			= 71;
	const int BLACK			= 72;
	const int FADE_CIRCLE   = 73;
	const int FADE_PARALLEL = 74;
	const int FADE_VERTICAL = 75;
	const int CLEAR_WHITE   = 76;
	const int CLEAR_BAR	    = 77;
	const int CLEAR_SQUARE  = 78;

	class SpriteLoader
	{
	public:
		// スプライト読み込み
		static void LoadTitleSprite();
		static void LoadSelectSprite();
		static void LoadLoadSprite();
		static void LoadGameSprite();
		static void LoadEndSprite();
		static void LoadIntervalSprite();

		// ロードフラグ取得
		static bool GetTitleFlag() { return titleFlag; }
		static bool GetSelectFlag() { return selectFlag; }
		static bool GetLoadFlag() { return loadFlag; }
		static bool GetGameFlag() { return gameFlag; }
		static bool GetEndFlag() { return endFlag; }
		static bool GetIntervalFlag() { return intervalFlag; }

	private:
		// ロードしたかのフラグ
		static bool titleFlag;
		static bool selectFlag;
		static bool loadFlag;
		static bool gameFlag;
		static bool endFlag;
		static bool intervalFlag;

	};
};

