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


	textures[mapX][mapY].pixelColors.resize(TEX_WIDTH);
	// �����蔻��p�摜�̏c���F�𒊏o
	for (int i = 0; i < TEX_WIDTH; i++)
	{
		textures[mapX][mapY].pixelColors[i].resize(TEX_HEIGHT);
		for (int j = 0; j < TEX_HEIGHT; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				// ���ꂻ��R�s�[
				textures[mapX][mapY].pixelColors[i][j].colors[k] = pcolor[j * (int)size.x + i].colors[k];
			}
		}
	}

	int a = 0;
}

XMFLOAT4 TexCollision::GetPixelColor(XMFLOAT3 position)
{
	// ���W�擾�p�ɕϊ�
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
	// ���W�擾�p�ɕϊ�
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
	// ���W�擾�p�ɕϊ�
	int x = position.x / TEX_WIDTH;
	int y = position.z / TEX_HEIGHT;
	int posX = position.x - x * TEX_WIDTH;
	int posY = position.z - y * TEX_HEIGHT;

	// �w��F�ɉ����Ĕ����Ԃ�
	if ((int)textures[x][y].pixelColors[posX][posY].colors[color] == 255)
	{
		return true;
	}
	return false;
}

//XMFLOAT3 TexCollision::Hit2Color(ArgColor color, XMFLOAT3 position)
//{
//	// ���W�擾�p�ɕϊ�
//	int x = position.x / TEX_WIDTH;
//	int y = position.z / TEX_HEIGHT;
//	int posX = position.x - x * TEX_WIDTH;
//	int posY = position.z - y * TEX_HEIGHT;
//
//	ColorInfo tmpColor[4];
//
//	// �c������p�̐F�����擾
//	tmpColor[0] = textures[x][y].pixelColors[posX + 1][posY];
//	tmpColor[1] = textures[x][y].pixelColors[posX - 1][posY];
//	tmpColor[2] = textures[x][y].pixelColors[posX][posY + 1];
//	tmpColor[3] = textures[x][y].pixelColors[posX][posY - 1];
//
//	int changeXY = 0;
//
//	// �c���̂����ꂩ���w��F�̐����̂Ȃ��ꍇ
//	// �ǂ̕����ɖ߂������߂�
//	// 0 : ���̃t���[���̈ړ�����
//	// 1 : X���̃v���X�����֖߂�
//	// 2 : X���̃}�C�i�X�����֖߂�
//	// 3 : Y���̃v���X�����֖߂�
//	// 4 : Y���̃}�C�i�X�����֖߂�
//	// ���ꂼ��ύX�ړ�������Ԃ�
//	XMFLOAT3 outVec = { 0,0,0 };
//	for (int i = 0; i < 4; i++)
//	{
//		// �w��F�ɉ����Ĕ����Ԃ�
//		if (tmpColor[i].colors[color] == 255)
//		{
//			changeXY = i + 1;
//		}
//
//		switch (changeXY)
//		{
//		case 0:
//			break;
//		case 1:
//			outVec.x += -1;
//			break;
//		case 2:
//			outVec.x += 1;
//			break;
//		case 3:
//			outVec.z += -1;
//			break;
//		case 4:
//			outVec.z += 1;
//			break;
//		}
//	}
//	
//	return outVec;
//}

XMFLOAT3 TexCollision::Hit2Color(ArgColor color, XMFLOAT3 position, XMFLOAT3 move)
{
	XMFLOAT3 outVec = move;

	// ���W�擾�p�ɕϊ�
	int x = position.x / TEX_WIDTH;
	int y = position.z / TEX_HEIGHT;
	int posX = position.x - x * TEX_WIDTH;
	int posY = position.z - y * TEX_HEIGHT;

	// �ړ��ʂ̊m�F
	bool isMove = false;
	if (!move.x == 0 && !move.z == 0)
	{
		isMove = true;
	}

	// �ړ��ʂ���������
	if (isMove)
	{
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
		ColorInfo tmpColor[2];
		if (signX)
		{
			if (signY)	// X��Y���{�̂Ƃ�
			{
				tmpColor[0] = textures[x][y].pixelColors[posX + 1][posY];
				tmpColor[1] = textures[x][y].pixelColors[posX][posY + 1];
			}
			else	// X���{�AY���[�̂Ƃ�
			{
				tmpColor[0] = textures[x][y].pixelColors[posX + 1][posY];
				tmpColor[1] = textures[x][y].pixelColors[posX][posY - 1];
			}
		}
		else
		{
			if (signY)	// X���[�AY���{�̂Ƃ�
			{
				tmpColor[0] = textures[x][y].pixelColors[posX - 1][posY];
				tmpColor[1] = textures[x][y].pixelColors[posX][posY + 1];
			}
			else	// X��Y���[�̂Ƃ�
			{
				tmpColor[0] = textures[x][y].pixelColors[posX - 1][posY];
				tmpColor[1] = textures[x][y].pixelColors[posX][posY - 1];
			}
		}

		// �ړ������̃s�N�Z���̐F���Ȃ��Ȃ�ړ��ʂ�����
		if (tmpColor[0].colors[color] == 0)
		{
			outVec.x = 0;
		}
		if (tmpColor[1].colors[color] == 0)
		{
			outVec.z = 0;
		}

		return outVec;
	}
	else
	{
		return move;
	}
}