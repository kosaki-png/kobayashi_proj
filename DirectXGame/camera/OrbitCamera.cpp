#include "OrbitCamera.h"
#include <cassert>

using namespace DirectX;

OrbitCamera::OrbitCamera(int window_width, int window_height)
	: Camera(window_width, window_height)
{
	WINDOW_WIDTH = window_width;
	WINDOW_HEIGHT = window_height;
}

void OrbitCamera::Update()
{
	phi += 0.2f;

	// éOäpä÷êîÇÃåvéZ
	angleX = -phi * XM_PI / 180;
	angleY = -theta * XM_PI / 180;

	float sinX = sinf(angleX);
	float cosX = cosf(angleX);
	float sinY = sinf(angleY);
	float cosY = cosf(angleY);

	const float CAMERA_DISTANCE = 200;
	XMFLOAT3 target = GetTarget();
	XMFLOAT3 eye = GetEye();

	SetEye({ cosX * cosY * CAMERA_DISTANCE + target.x,
			 sinY * CAMERA_DISTANCE + target.y + 100,
			 sinX * cosY * CAMERA_DISTANCE + target.z });

	Camera::Update();
}