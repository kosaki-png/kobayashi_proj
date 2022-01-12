#pragma once
#include "Camera.h"
#include "Input.h"

/// <summary>
/// デバッグ用カメラ
/// </summary>
class FixedCamera :
	public Camera
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	/// <param name="input">入力</param>
	FixedCamera(int window_width, int window_height);
	~FixedCamera();

	// 更新
	void Update() override;

private:
	// カメラ注視点までの距離
	float distance = 20;
};

