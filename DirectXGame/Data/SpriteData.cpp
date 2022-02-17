#include "SpriteData.h"

using namespace SpriteData;

bool SpriteLoader::titleFlag = false;
bool SpriteLoader::selectFlag = false;
bool SpriteLoader::loadFlag = false;
bool SpriteLoader::gameFlag = false;
bool SpriteLoader::endFlag = false;
bool SpriteLoader::intervalFlag = false;

void SpriteLoader::LoadTitleSprite()
{
	Sprite::LoadTexture(TITLE, L"Resources/texture/title.png");
	Sprite::LoadTexture(FADE, L"Resources/texture/fade.png");

	titleFlag = true;
}

void SpriteLoader::LoadSelectSprite()
{
	selectFlag = true;
}

void SpriteLoader::LoadLoadSprite()
{
	// 表示マップ系
	Sprite::LoadTexture(LOADFLAME, L"Resources/texture/load_bar.png");
	Sprite::LoadTexture(LOADBAR, L"Resources/texture/load_bar_white.png");
	Sprite::LoadTexture(LOADED, L"Resources/texture/loaded.png");
	Sprite::LoadTexture(LOADING, L"Resources/texture/loading.png");

	loadFlag = true;
}

void SpriteLoader::LoadGameSprite()
{
	Sprite::LoadTexture(MAP_FLAME, L"Resources/texture/map_all_frame.png");
	Sprite::LoadTexture(MAP_POINT, L"Resources/texture/map_all_point.png");
	Sprite::LoadTexture(MAP_CURSOR, L"Resources/texture/map_Cursor.png");
	Sprite::LoadTexture(MAP_MINI, L"Resources/texture/miniMap.png");

	// オプション
	Sprite::LoadTexture(OPTION, L"Resources/texture/option.png");

	// ステージマップ系
	Sprite::LoadTexture(MAP01_FLAME, L"Resources/texture/map_01_frame.png");
	Sprite::LoadTexture(MAP02_FLAME, L"Resources/texture/map_02_frame.png");
	Sprite::LoadTexture(MAP03_FLAME, L"Resources/texture/map_03_frame.png");
	Sprite::LoadTexture(MAP04_FLAME, L"Resources/texture/map_04_frame.png");
	Sprite::LoadTexture(MAP01_REF, L"Resources/texture/map_01_ref.png");
	Sprite::LoadTexture(MAP02_REF, L"Resources/texture/map_02_ref.png");
	Sprite::LoadTexture(MAP03_REF, L"Resources/texture/map_03_ref.png");
	Sprite::LoadTexture(MAP04_REF, L"Resources/texture/map_04_ref.png");

	// UI
	Sprite::LoadTexture(DANGER, L"Resources/texture/danger.png");

	gameFlag = true;
}

void SpriteLoader::LoadEndSprite()
{
	Sprite::LoadTexture(CLEAR, L"Resources/texture/clear.png");

	endFlag = true;
}

void SpriteLoader::LoadIntervalSprite()
{
	Sprite::LoadTexture(INTERVAL, L"Resources/texture/white_1000x1000.png");

	intervalFlag = true;
}