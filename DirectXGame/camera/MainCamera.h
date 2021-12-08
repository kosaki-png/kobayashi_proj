#pragma once
#include "Camera.h"
#include "Input.h"

/// <summary>
/// デバッグ用カメラ
/// </summary>
class MainCamera :
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
	MainCamera(int window_width, int window_height, Input* input);

	// カメラの平行移動
	void SetCameraPos(XMFLOAT3 position);

	// 更新
	void Update() override;

	void SetDistance(float distance) {
		this->distance = distance; viewDirty = true;
	}

	//// カメラの移動
	//void CameraMove(XMFLOAT3 moveVel) { this->moveVel = moveVel; dirty = true; }

	// thita,phiの取得
	XMFLOAT2 GetAngle() { return { angleX, angleY }; }

	// 感度変更
	void SetSence(float sence);
	float GetSence() { return sence; }

	// マウスで動かすフラグ変更
	void SetMouseFlag(bool mouse) { this->mouse = mouse; }

private:
	// 入力クラスのポインタ
	Input* input;
	// カメラ注視点までの距離
	float distance = 20;
	// スケーリング
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	// 回転行列
	XMMATRIX matRot = DirectX::XMMatrixIdentity();

	bool dirty = false;

	float angleX = 0;	// rad
	float angleY = 0;	// rad

	XMFLOAT3 moveVel = { 0,0,0 };

	float theta = 0;
	float phi = 90;

	XMFLOAT3 moveVec = { 0,0,0 };

	float sence = 1.0f;

	int WINDOW_WIDTH = 0;
	int WINDOW_HEIGHT = 0;

	bool mouse = true;
};

