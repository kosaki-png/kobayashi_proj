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
	// �X�v���C�g�ǂݍ���
	{
		Sprite::LoadTexture(100, L"Resources/texture/fade.png");
	}
	
	// �X�v���C�g����
	{
		fadeSprite = Sprite::Create(100, { 0,0 });
	}

	effectTimeIn = 100;
	effectTimeOut = 100;
}

void Fade::Update()
{
	// �@�\�̂����ꂩ���J�n��
	if (in || out)
	{	 
		// �t�F�[�h�C��
		if (in)
		{
			// ���l���グ��
			alpha += ORIGIN_ALPHA / effectTimeIn;

			// ���̃��l�ɂȂ������~
			if (alpha >= MAX_ALPHA)
			{
				alphaFlag = true;
				if (goOut)
				{
					OutStart();
				}
				in = false;
			}
		}

		// �t�F�[�h�A�E�g
		if (out)
		{
			// ���l��������
			alpha -= ORIGIN_ALPHA / effectTimeIn;

			// ���̃��l�ɂȂ������~
			if (alpha <= MIN_ALPHA)
			{
				alphaFlag = false;
				out = false;
			}
		}

		fadeSprite->SetAlpha(alpha);
		count++;
	}
}

void Fade::Draw()
{
	if (in || out || alphaFlag)
	{
		fadeSprite->Draw();
	}
}