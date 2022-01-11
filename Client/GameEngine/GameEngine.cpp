#include "pch.h"
#include "GameEngine.h"
#include "SceneManager.h"

GameEngine::~GameEngine()
{
	ReleaseCOM(mRenderTargetView);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mSwapChain);
	ReleaseCOM(mDepthStencilBuffer);

	if (mDeviceContext)
		mDeviceContext->ClearState();
	ReleaseCOM(mDeviceContext);
	ReleaseCOM(mDevice);

}

void GameEngine::Initialize(const WindowInfo& wInfo)
{
	mWinfo = wInfo;
	InitializeDeviceAndSwapChain();
	ScreenResize();
}

void GameEngine::Update()
{
	SceneManager::GetInstance()->Update();

}

void GameEngine::Render()
{
	RenderBegin();

	SceneManager::GetInstance()->Render();

	RenderEnd();
}

void GameEngine::InitializeDeviceAndSwapChain()
{
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
		0,                 // default adapter
		md3dDriverType,
		0,                 // no software device
		createDeviceFlags,
		0, 0,              // default feature level array
		D3D11_SDK_VERSION,
		&mDevice,
		&featureLevel,
		&mDeviceContext);


	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);

	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);

	}

	mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	assert(m4xMsaaQuality > 0);

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = mWinfo.ClientWidth;
	sd.BufferDesc.Height = mWinfo.ClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (mEnable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	// No MSAA
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = mWinfo.hwnd;
	sd.Windowed = mWinfo.IsWindow;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	mDevice->QueryInterface(IID_PPV_ARGS(&mdxgiDevice));
	mdxgiDevice->GetParent(IID_PPV_ARGS(&mdxgiAdapter));
	mdxgiAdapter->GetParent(IID_PPV_ARGS(&mdxgiFactory));
	mdxgiFactory->CreateSwapChain(mDevice, &sd, &mSwapChain);
}

void GameEngine::ScreenResize()
{
	mSwapChain->ResizeBuffers(1, mWinfo.ClientWidth, mWinfo.ClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	mSwapChain->GetBuffer(0, IID_PPV_ARGS(&mBackBuffer));
	mDevice->CreateRenderTargetView(mBackBuffer, 0, &mRenderTargetView);

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = mWinfo.ClientWidth;
	depthStencilDesc.Height = mWinfo.ClientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (mEnable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	// No MSAA
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	mDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer);
	mDevice->CreateDepthStencilView(mDepthStencilBuffer, 0,&mDepthStencilView);

	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	mViewPort.TopLeftX = 0;
	mViewPort.TopLeftY = 0;
	mViewPort.Width = static_cast<float>(mWinfo.ClientWidth);
	mViewPort.Height = static_cast<float>(mWinfo.ClientHeight);
	mViewPort.MinDepth = 0.0f;
	mViewPort.MaxDepth = 1.0f;

	mDeviceContext->RSSetViewports(1, &mViewPort);

}

void GameEngine::RenderBegin()
{
	XMVECTORF32 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::LightSteelBlue));
	mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void GameEngine::RenderEnd()
{
	mSwapChain->Present(0, 0);
}



void GameEngine::CallScreenResize(const WindowInfo& wInfo)
{

	mWinfo = wInfo;
	ScreenResize();

}
