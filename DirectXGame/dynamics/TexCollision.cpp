#include "TexCollision.h"
#include <cassert>
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

TexCollision::TexCollision()
{
}

TexCollision::~TexCollision()
{
	for (int i = 0; i < texCnt; i++)
	{
		delete[] pcolors[i];
	}
	for (int i = 0; i < 9; i++)
	{
		for (auto x : colors[i])
		{
			x.clear();
		}
	}
}

void TexCollision::LoadTexture(int texNum, const wchar_t* filename)
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

	pcolors[texNum] = reinterpret_cast<ColorInfo*>(scratchImg.GetPixels());
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

	// 領域を確保
	colors[texNum].resize(scratchImg.GetImages()->height);
	// 当たり判定用画像の縦横色を抽出
	for (int i = 0; i < size.y; i++)
	{
		// 領域を確保
		colors[texNum].at(i).resize(scratchImg.GetImages()->width);
		for (int j = 0; j < size.x; j++)
		{
			// それそれコピー
			colors[texNum].at(i).at(j).r = pcolors[texNum][i * (int)size.x + j].r;
			colors[texNum].at(i).at(j).g = pcolors[texNum][i * (int)size.x + j].g;
			colors[texNum].at(i).at(j).b = pcolors[texNum][i * (int)size.x + j].b;
			colors[texNum].at(i).at(j).a = pcolors[texNum][i * (int)size.x + j].a;
		}
	}
}

XMFLOAT4 TexCollision::GetPixelColor(int texNum, XMFLOAT2 position)
{
	XMFLOAT4 outColor;
	outColor.x = (float)colors[texNum][(int)position.x][(int)position.y].r;
	outColor.y = (float)colors[texNum][(int)position.x][(int)position.y].g;
	outColor.z = (float)colors[texNum][(int)position.x][(int)position.y].b;
	outColor.w = (float)colors[texNum][(int)position.x][(int)position.y].a;
	return outColor;
}

bool TexCollision::GetRedFlag(int texNum, XMFLOAT2 position)
{
	if ((int)colors[texNum][(int)position.x][(int)position.y].r == 255)
	{
		return true;
	}
	else
	{
		return false;
	}
}