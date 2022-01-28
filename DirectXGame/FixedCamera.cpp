#include "FixedCamera.h"
#include <cassert>

using namespace DirectX;

FixedCamera::FixedCamera(int window_width, int window_height)
	: Camera(window_width, window_height)
{
}

FixedCamera::~FixedCamera()
{
}

void FixedCamera::Update()
{
	SetTarget({ 0,0,0 });
	SetEye({ 0, 0, 10 });

	Camera::Update();
}