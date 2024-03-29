#include "SpriteData.h"

using namespace SpriteData;

// それぞれのロードフラグ
bool SpriteLoader::titleFlag = false;
bool SpriteLoader::selectFlag = false;
bool SpriteLoader::loadFlag = false;
bool SpriteLoader::gameFlag = false;
bool SpriteLoader::endFlag = false;
bool SpriteLoader::intervalFlag = false;

void SpriteLoader::LoadTitleSprite()
{
	Sprite::LoadTexture(TITLE, L"Resources/texture/title.png");
	Sprite::LoadTexture(FADE,  L"Resources/texture/fade.png");

	// ロード完了
	titleFlag = true;
}

void SpriteLoader::LoadSelectSprite()
{
	Sprite::LoadTexture(SELECT_FLAME, L"Resources/texture/select_flame.png");

	// ロード完了
	selectFlag = true;
}

void SpriteLoader::LoadLoadSprite()
{
	// 表示マップ系
	Sprite::LoadTexture(LOADFLAME, L"Resources/texture/load_bar.png");
	Sprite::LoadTexture(LOADBAR,   L"Resources/texture/load_bar_white.png");
	Sprite::LoadTexture(LOADED,    L"Resources/texture/loaded.png");
	Sprite::LoadTexture(LOADING,   L"Resources/texture/loading.png");

	// ロード完了
	loadFlag = true;
}

void SpriteLoader::LoadGameSprite()
{
	Sprite::LoadTexture(MAP_FLAME,  L"Resources/texture/map_all_frame.png");
	Sprite::LoadTexture(MAP_POINT,  L"Resources/texture/map_all_point.png");
	Sprite::LoadTexture(MAP_CURSOR, L"Resources/texture/map_Cursor.png");
	Sprite::LoadTexture(MAP_MINI,   L"Resources/texture/miniMap.png");

	// ポーズ
	Sprite::LoadTexture(GAME_FLAME,  L"Resources/texture/game_pause.png");
	Sprite::LoadTexture(PAUSE_FLAME, L"Resources/texture/pause.png");
	Sprite::LoadTexture(PAUSE_DEBUG, L"Resources/texture/game_debug.png");

	// ステージマップ系
	Sprite::LoadTexture(MAP01_FLAME, L"Resources/texture/map_01_frame.png");
	Sprite::LoadTexture(MAP02_FLAME, L"Resources/texture/map_02_frame.png");
	Sprite::LoadTexture(MAP03_FLAME, L"Resources/texture/map_03_frame.png");
	Sprite::LoadTexture(MAP04_FLAME, L"Resources/texture/map_04_frame.png");
	Sprite::LoadTexture(MAP01_REF, L"Resources/texture/map_01_ref.png");
	Sprite::LoadTexture(MAP02_REF, L"Resources/texture/map_02_ref.png");
	Sprite::LoadTexture(MAP03_REF, L"Resources/texture/map_03_ref.png");
	Sprite::LoadTexture(MAP04_REF, L"Resources/texture/map_04_ref.png");

	// ロード完了
	gameFlag = true;
}

void SpriteLoader::LoadEndSprite()
{
	Sprite::LoadTexture(RESULT_FRAME,  L"Resources/texture/result_frame.png");
	Sprite::LoadTexture(RESULT_CURSOR, L"Resources/texture/result_cursor.png");

	// ロード完了
	endFlag = true;
}

void SpriteLoader::LoadIntervalSprite()
{
	Sprite::LoadTexture(INTERVAL,      L"Resources/texture/white_1000x1000.png");
	Sprite::LoadTexture(WHITE,		   L"Resources/texture/white.png");
	Sprite::LoadTexture(BLACK,		   L"Resources/texture/black.png");
	Sprite::LoadTexture(FADE_CIRCLE,   L"Resources/texture/fade_circle.png");
	Sprite::LoadTexture(FADE_PARALLEL, L"Resources/texture/fade_parallel.png");
	Sprite::LoadTexture(FADE_VERTICAL, L"Resources/texture/fade_vertical.png");
	Sprite::LoadTexture(CLEAR_WHITE,   L"Resources/texture/clear_white.png");
	Sprite::LoadTexture(CLEAR_BAR,	   L"Resources/texture/clear_bar.png");
	Sprite::LoadTexture(CLEAR_SQUARE,  L"Resources/texture/clear_square.png");

	// ロード完了
	intervalFlag = true;
}