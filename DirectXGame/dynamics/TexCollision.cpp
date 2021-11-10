#include "TexCollision.h"
#include <cassert>
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

TexCollision::TexCollision(int texWidth, int texHeight, int maxMapX, int maxMapY)
{
	TEX_WIDTH = texWidth;
	TEX_HEIGHT = texHeight;

	// 領域の確保
 	textures.resize(maxMapX);
	for (int i = 0; i < maxMapX; i++)
	{
		textures.at(i).resize(maxMapY);
	}
}

TexCollision::~TexCollision()
{
	delete pcolor;
}

void TexCollision::LoadTexture(int mapX, int mapY, const wchar_t* filename)
{
	HRESULT result;
	// WICテクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	result = LoadFromWICFile(
		filename, WIC_FLAGS_NONE,
		&metadata, scratchImg);
	if (FAILED(result)) {
		assert(0);
	}

	//const Image* img = scratchImg.GetImage(0, 0, 0); // 生データ抽出
	//scratchImg.GetPixels();
	//size_t a = scratchImg.GetPixelsSize();

	pcolor = reinterpret_cast<ColorInfo*>(scratchImg.GetPixels());
	size = { (float)scratchImg.GetImages()->width, (float)scratchImg.GetImages()->height };
	
	/*color++;
	color[4].r;
	colors[0][4].r;
	pcolors[0]->r;
	assert(metadata.format == DXGI_FORMAT_R8G8B8A8_UNORM);
	texCnt += 1;
	static unsigned char tmp;
	tmp = pcolors[0][0].r;
	static float tmpIntr, tmpIntg, tmpIntb, tmpInta;
	tmpIntr = (float)pcolors[0][3].r;
	tmpIntg = (float)pcolors[0][3].g;
	tmpIntb = (float)pcolors[0][3].b;
	tmpInta = (float)pcolors[0][3].a / 255.0f;*/


	textures[mapX][mapY].colors.resize(TEX_WIDTH);
	// 当たり判定用画像の縦横色を抽出
	for (int i = 0; i < TEX_WIDTH; i++)
	{
		textures[mapX][mapY].colors[i].resize(TEX_HEIGHT);
		for (int j = 0; j < TEX_HEIGHT; j++)
		{
			// それそれコピー
  			textures[mapX][mapY].colors[i][j] = pcolor[j * (int)size.x + i];
		}
	}

	int a = 0;
}

XMFLOAT4 TexCollision::GetPixelColor(XMFLOAT3 position)
{
	// 座標取得用に変換
	int x = position.x / TEX_WIDTH;
	int y = position.z / TEX_HEIGHT;
	int posX = position.x - x * TEX_WIDTH;
	int posY = position.z - y * TEX_HEIGHT;

	XMFLOAT4 outColor;
	outColor.x = (float)textures[x][y].colors[posX][posY].r;
	outColor.y = (float)textures[x][y].colors[posX][posY].g;
	outColor.z = (float)textures[x][y].colors[posX][posY].b;
	outColor.w = (float)textures[x][y].colors[posX][posY].a;
	return outColor;
}

bool TexCollision::GetRedFlag(XMFLOAT3 position)
{
	// 座標取得用に変換
	int x = position.x / TEX_WIDTH;
	int y = position.z / TEX_HEIGHT;
	int posX = position.x - x * TEX_WIDTH;
	int posY = position.z - y * TEX_HEIGHT;

	if ((int)textures[x][y].colors[posX][posY].r == 255)
	{
		return true;
	}
	else
	{
		return false;
	}
}