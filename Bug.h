#pragma once
#include "Actor.h"
class Bug : public Actor
{
	const D2D_POINT_2F UPVECTOR{ 0.0f, -1.0f };

	float mRotation;
	float mSteps;

public:
	Bug(D2DFramework* pFramework);

	virtual void Draw() override;
};

