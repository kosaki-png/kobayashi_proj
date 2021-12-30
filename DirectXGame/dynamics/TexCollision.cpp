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

	// �̈�̊m��
 	pixelColors.resize(maxMapX * TEX_WIDTH);
	for (int i = 0; i < maxMapX * TEX_WIDTH; i++)
	{
		pixelColors.at(i).resize(maxMapY * TEX_HEIGHT);
	}
}

TexCollision::~TexCollision()
{
	delete pcolor;
}

void TexCollision::LoadTexture(int mapX, int mapY, const wchar_t* filename)
{
	HRESULT result;
	// WIC�e�N�X�`���̃��[�h
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	result = LoadFromWICFile(
		filename, WIC_FLAGS_NONE,
		&metadata, scratchImg);
	if (FAILED(result)) {
		assert(0);
	}

	//const Image* img = scratchImg.GetImage(0, 0, 0); // ���f�[�^���o
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

	// �����蔻��p�摜�̏c���F�𒊏o
	for (int i = 0; i < TEX_WIDTH; i++)	// X��
	{
		for (int j = 0; j < TEX_HEIGHT; j++)	// Y��
		{
			for (int k = 0; k < 4; k++)	// rgba
			{
				// ���ꂻ��R�s�[
				// �w��̃}�b�v�̏ꏊ�Ɏw��摜�̏�������
				pixelColors[i + mapX * TEX_WIDTH][j + mapY * TEX_HEIGHT].colors[k] = pcolor[j * (int)size.x + i].colors[k];
			}
		}
	}
}

XMFLOAT4 TexCollision::GetPixelColor(XMFLOAT3 position)
{
	XMFLOAT4 outColor;
	outColor.x = (float)pixelColors[(int)position.x][(int)position.z].colors[2];
	outColor.y = (float)pixelColors[(int)position.x][(int)position.z].colors[1];
	outColor.z = (float)pixelColors[(int)position.x][(int)position.z].colors[0];
	outColor.w = (float)pixelColors[(int)position.x][(int)position.z].colors[3];
	return outColor;
}

bool TexCollision::GetHitFlag(ArgColor color, XMFLOAT3 position)
{
	// �w��F�ɉ����Ĕ����Ԃ�
	if ((int)pixelColors[(int)position.x][(int)position.z].colors[color] == 255)
	{
		return true;
	}
	return false;
}

XMFLOAT3 TexCollision::Hit2Color(ArgColor color, XMFLOAT3 position, XMFLOAT3 move)
{
	XMFLOAT3 outVec = move;

	// �ړ��ʂ��������画��
	if (!move.x == 0 && !move.z == 0)
	{
		// �ǂ���Ɉړ��ʂ����邩����
		bool signX = false;
		bool signY = false;
		if (move.x > 0)
		{
			signX = true;
		}
		if (move.z > 0)
		{
			signY = true;
		}

		// �c������p�̐F�����擾
		ColorInfo tmpColorX, tmpColorY;
		if (signX)
		{
			if (signY)	// X��Y���{�̂Ƃ�
			{
				tmpColorX = pixelColors[(int)position.x + 1][(int)position.z];
				tmpColorY = pixelColors[(int)position.x][(int)position.z + 1];
			}
			else	// X���{�AY���[�̂Ƃ�
			{
				tmpColorX = pixelColors[(int)position.x + 1][(int)position.z];
				tmpColorY = pixelColors[(int)position.x][(int)position.z - 1];
			}
		}
		else
		{
			if (signY)	// X���[�AY���{�̂Ƃ�
			{
				tmpColorX = pixelColors[(int)position.x - 1][(int)position.z];
				tmpColorY = pixelColors[(int)position.x][(int)position.z + 1];
			}
			else	// X��Y���[�̂Ƃ�
			{
				tmpColorX = pixelColors[(int)position.x - 1][(int)position.z];
				tmpColorY = pixelColors[(int)position.x][(int)position.z - 1];
			}
		}

		// �ړ������̃s�N�Z���̐F���Ȃ��Ȃ�ړ��ʂ�����
		if (tmpColorX.colors[color] == 0)
		{
			outVec.x = 0;
		}
		if (tmpColorY.colors[color] == 0)
		{
			outVec.z = 0;
		}
	}

	return outVec;
}

bool TexCollision::Check(ArgColor Color, Dir dir, XMFLOAT3 position, int length, int value)
{
	bool result = false;

	// length�̕�����
	for (int i = 0; i < length; i++)
	{
		switch (dir)
		{
		case Up:
			// �͈͓��ɐF���������ꍇ
			if (pixelColors[(int)position.x][(int)position.z + (i + 1)].colors[Color] == value)
			{
				result = true;
				break;
			}
			break;

		case Down:
			// �͈͓��ɐF���������ꍇ
			if (pixelColors[(int)position.x][(int)position.z - (i + 1)].colors[Color] == value)
			{
				result = true;
				break;
			}
			break;

		case Right:
			// �͈͓��ɐF���������ꍇ
			if (pixelColors[(int)position.x + (i + 1)][(int)position.z].colors[Color] == value)
			{
				result = true;
				break;
			}
			break;

		case Left:
			// �͈͓��ɐF���������ꍇ
			if (pixelColors[(int)position.x - (i + 1)][(int)position.z].colors[Color] == value)
			{
				result = true;
				break;
			}
			break;
		}
	}
	
	return result;
}

bool TexCollision::CheckNot(ArgColor Color, Dir dir, XMFLOAT3 position, int length, int value)
{
	bool result = false;

	// length�̕�����
	for (int i = 0; i < length; i++)
	{
		switch (dir)
		{
		case Up:
			// �͈͓��ɐF���������ꍇ
			if (pixelColors[(int)position.x][(int)position.z + (i + 1)].colors[Color] != value)
			{
				result = true;
				break;
			}
			break;

		case Down:
			// �͈͓��ɐF���������ꍇ
			if (pixelColors[(int)position.x][(int)position.z - (i + 1)].colors[Color] != value)
			{
				result = true;
				break;
			}
			break;

		case Right:
			// �͈͓��ɐF���������ꍇ
			if (pixelColors[(int)position.x + (i + 1)][(int)position.z].colors[Color] != value)
			{
				result = true;
				break;
			}
			break;

		case Left:
			// �͈͓��ɐF���������ꍇ
			if (pixelColors[(int)position.x - (i + 1)][(int)position.z].colors[Color] != value)
			{
				result = true;
				break;
			}
			break;
		}
	}

	return result;
}
