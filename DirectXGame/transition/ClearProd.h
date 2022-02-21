#pragma once
#include "Transition.h"
#include "SpriteData.h" 

class ClearProd : public Transition
{
private:
	struct Trance
	{
		Sprite* sprite = nullptr;
		XMFLOAT2 position = { 1280.0f / 2,720.0f / 2  };
		float rotation = 0.0f;
		XMFLOAT2 size = { 1,1 };
		float alpha = 1.0f;

		void Init() {
			size = sprite->GetSize();
		}

		void Update() { 
			sprite->SetPosition(position);
			sprite->SetRotation(rotation);
			sprite->SetAlpha(alpha);
			sprite->SetSize(size);
		}
	};

public:
	ClearProd();
	~ClearProd() override;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Start() override;

private:
	Trance black, white, bar, square, fade;
	
};

