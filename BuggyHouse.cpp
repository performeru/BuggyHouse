#include "BuggyHouse.h"
#include "Bug.h"

HRESULT BuggyHouse::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;
    hr = D2DFramework::Initialize(hInstance, title, width, height);
    ThrowIfFailed(hr, "Failed in D2DFramework::Initailize");

    mspBackground = std::make_shared<Actor>(this, L"Images/back.png", 0.0f, 0.0f, 1.0f);

    float x{};
    float y{};
    RECT rct{};
    GetClientRect(mHwnd, &rct);

    for (int i = 0; i < 40; i++)
    {
        mBugList.push_back(std::make_shared<Bug>(this));
    }

    return S_OK;
}

void BuggyHouse::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

  
    mspBackground->Draw();

    for (auto& bug : mBugList)
    {
        
        bug->Draw();
    }

    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}

void BuggyHouse::Release()
{
    for (auto& bug : mBugList)
    {
        bug.reset();
    }

    mBugList.clear();
    mspBackground.reset();

    D2DFramework::Release();
}
