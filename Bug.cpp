#include "Bug.h"

Bug::Bug(D2DFramework* pFramework) :
	Actor(pFramework, L"Images/bug.png")
{
	RECT rct{};
	GetClientRect(pFramework->GetHWND(), &rct);

	mX = static_cast<float>(rand() % (rct.right - rct.left));
	mY = static_cast<float>(rand() % (rct.bottom - rct.top));

	mRotation = 0.0f;
	mSteps = 0.0f;
	mIsDead = false;
}

void Bug::Draw()
{
	auto pRT = mpFramework->GetRenderTarget();

	if (!pRT)
	{
		return;
	}

	auto size = mpBitmap->GetPixelSize();

	if (mSteps++ > 30)
	{
		mSteps = 0;
		mRotation += (1 - rand() % 3) * 45.0f;
	}

	auto forward = UPVECTOR * D2D1::Matrix3x2F::Rotation(mRotation);

	mX += forward.x;
	mY += forward.y;

	
	auto matTranslate = D2D1::Matrix3x2F::Translation(mX, mY);
	auto matRotation = D2D1::Matrix3x2F::Rotation(mRotation, D2D_POINT_2F{ size.width * 0.5f, size.height * 0.5f });
	pRT->SetTransform(matRotation * matTranslate);


	D2D1_RECT_F rect{ 0,0,static_cast<float>(size.width), static_cast<float>(size.height) };
	pRT->DrawBitmap(mpBitmap, rect, mOpacity);
}

bool Bug::IsClicked(POINT& pt)
{
	auto size = mpBitmap->GetPixelSize();

	if (pt.x >= mX && pt.y >= mY && pt.x <= mX + size.width && pt.y <= mY + size.height)
	{
		mIsDead = true;
		return true;
	}

	return false;
}