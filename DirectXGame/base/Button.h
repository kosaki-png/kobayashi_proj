#pragma once
#include <DirectXMath.h>
#include "SafeDelete.h"

class Button
{
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">左上座標</param>
	/// <param name="scale">大きさ</param>
	Button(XMFLOAT2 position, XMFLOAT2 scale);

	~Button();

	/// <summary>
	/// 指定座標がボタン上にあるか
	/// </summary>
	/// <param name="mousePos">指定座標</param>
	/// <returns>当たっているか</returns>
	bool GetHitFlag(XMFLOAT2 position);

private:
	XMFLOAT2 position = { 0,0 };
	XMFLOAT2 scale = { 0,0 };
};

