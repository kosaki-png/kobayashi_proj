#include "TexCollision.h"
#include <cassert>
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>

#pragma comment(lib, "d3dcompiler.lib")
#pragma warning(disable:26451)

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


	textures[mapX][mapY].pixelColors.resize(TEX_WIDTH);
	// 当たり判定用画像の縦横色を抽出
	for (int i = 0; i < TEX_WIDTH; i++)
	{
		textures[mapX][mapY].pixelColors[i].resize(TEX_HEIGHT);
		for (int j = 0; j < TEX_HEIGHT; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				// それそれコピー
				textures[mapX][mapY].pixelColors[i][j].colors[k] = pcolor[j * (int)size.x + i].colors[k];
			}
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
	outColor.x = (float)textures[x][y].pixelColors[posX][posY].colors[2];
	outColor.y = (float)textures[x][y].pixelColors[posX][posY].colors[1];
	outColor.z = (float)textures[x][y].pixelColors[posX][posY].colors[0];
	outColor.w = (float)textures[x][y].pixelColors[posX][posY].colors[3];
	return outColor;
}

bool TexCollision::GetRedFlag(XMFLOAT3 position)
{
	// 座標取得用に変換
	int x = position.x / TEX_WIDTH;
	int y = position.z / TEX_HEIGHT;
	int posX = position.x - x * TEX_WIDTH;
	int posY = position.z - y * TEX_HEIGHT;

	if ((int)textures[x][y].pixelColors[posX][posY].colors[2] == 255)
	{
		return true;
	}
	return false;
}

bool TexCollision::GetHitFlag(ArgColor color, XMFLOAT3 position)
{
	// 座標取得用に変換
	int x = position.x / TEX_WIDTH;
	int y = position.z / TEX_HEIGHT;
	int posX = position.x - x * TEX_WIDTH;
	int posY = position.z - y * TEX_HEIGHT;

	// 指定色に応じて判定を返す
	if ((int)textures[x][y].pixelColors[posX][posY].colors[color] == 255)
	{
		return true;
	}
	return false;
}

XMFLOAT3 TexCollision::Hit2Color(ArgColor color, XMFLOAT3 position)
{
	// 座標取得用に変換
	int x = position.x / TEX_WIDTH;
	int y = position.z / TEX_HEIGHT;
	int posX = position.x - x * TEX_WIDTH;
	int posY = position.z - y * TEX_HEIGHT;

	ColorInfo tmpColor[4];

	// 縦横判定用の色情報を取得
	tmpColor[0] = textures[x][y].pixelColors[posX + 1][posY];
	tmpColor[1] = textures[x][y].pixelColors[posX - 1][posY];
	tmpColor[2] = textures[x][y].pixelColors[posX][posY + 1];
	tmpColor[3] = textures[x][y].pixelColors[posX][posY - 1];

	int changeXY = 0;

	// 縦横のいずれかが指定色の成分のない場合
	// どの方向に戻すか決める
	// 0 : このフレームの移動無し
	// 1 : X軸のプラス方向へ戻す
	// 2 : X軸のマイナス方向へ戻す
	// 3 : Y軸のプラス方向へ戻す
	// 4 : Y軸のマイナス方向へ戻す
	for (int i = 0; i < 4; i++)
	{
		// 指定色に応じて判定を返す
		if (tmpColor[i].colors[color] == 0)
		{
			changeXY = i + 1;
			break;
		}
	}

	// それぞれ変更移動方向を返す
	XMFLOAT3 outVec = { 0,0,0 };
	switch (changeXY)
	{
	case 0:
		outVec = { 0,0,0 };
	case 1:
		outVec = { 1,0,0 };
	case 2:
		outVec = { -1,0,0 };
	case 3:
		outVec = { 0,0,1 };
	case 4:
		outVec = { 0,0,-1 };
	}
	return outVec;
}