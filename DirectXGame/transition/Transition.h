#pragma once
#include <DirectXMath.h>
#include "Sprite.h"
#include "SpriteData.h"
#include "SafeDelete.h"

class Transition
{
protected: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Transition();
	virtual ~Transition() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Start();

	bool GetIsCover() { return isCover; }
	bool GetIsEffect() { return isEffect; }

protected:
	// ���o���@�\���Ă��邩
	bool isEffect = false;

	bool isCover = false;
	int startCnt = 0;

	const float WINDOW_WIDTH = 1280.0f;
	const float WINDOW_HEIGHT = 720.0f;

};

