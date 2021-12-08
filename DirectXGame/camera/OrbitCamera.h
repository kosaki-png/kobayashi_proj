#pragma once
#include "Camera.h"
#include "Input.h"

/// <summary>
/// デバッグ用カメラ
/// </summary>
class OrbitCamera :
	public Camera
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	/// <param name="input">入力</param>
	OrbitCamera(int window_width, int window_height);

	// 更新
	void Update() override;

private:
	// カメラ注視点までの距離
	float distance = 20;

	float angleX = 0;	// rad
	float angleY = 0;	// rad

	float theta = 0;
	float phi = 90;

	int WINDOW_WIDTH = 0;
	int WINDOW_HEIGHT = 0;
};

