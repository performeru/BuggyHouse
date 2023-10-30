#include "Bug.h"

Bug::Bug(D2DFramework* pFramework) :
	Actor(pFramework, L"Images/bug.png")
{
	RECT rct{};
	GetClientRect(pFramework->GetHWND(), &rct);

	mX = static_cast<float>(rand() % (rct.right - rct.left));
	mY = static_cast<float>(rand() % (rct.bottom - rct.top));

	mRotation = 0.0;
	mSteps = 0.0f;
}

void Bug::Draw()
{
	auto pRT = mpFramework->GetRenderTarget();

	if (!pRT)
	{
		return;
	}

	auto size = mpBitmap->GetPixelSize();

	auto matTranslate = D2D1::Matrix3x2F::Translation(mX, mY);
	auto matRotation = D2D1::Matrix3x2F::Rotation(15.0f,
		D2D_POINT_2F{size.width * 0.5f, size.height * 0.5f});
	pRT->SetTransform(matRotation * matTranslate);

	D2D1_RECT_F rect{ 0, 0, static_cast<float>(size.width), static_cast<float>(size.height)};
	pRT->DrawBitmap(mpBitmap, rect, mOpacity);
}
