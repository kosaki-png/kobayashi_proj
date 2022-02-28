#include "Button.h"

Button::Button(XMFLOAT2 position, XMFLOAT2 scale)
	:	position(position), scale(scale)
{
}

Button::~Button()
{
}

bool Button::GetHitFlag(XMFLOAT2 position)
{
	bool result = false;

	// AABB“–‚½‚è”»’è
	if (position.x > this->position.x && position.x < this->position.x + scale.x &&
		position.y > this->position.y && position.y < this->position.y + scale.y)
	{
		result = true;
	}

	return result;
}
