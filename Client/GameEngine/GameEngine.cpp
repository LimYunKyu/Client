#include "pch.h"
#include "GameEngine.h"
#include "SceneManager.h"
#include "Timer.h"
#include "InputManager.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "RenderTargetGroup.h"
void GameEngine::Initialize(const WindowInfo& wInfo)
{
	mWinfo = wInfo;
	InitializeDeviceAndSwapChain();
	ScreenSetting();
	//ScreenResize();
	CreateSampleState();
	
	CreateRenderTargetGroups();
	Timer::GetInstance()->Init();
	shared_ptr<TestScene> _scene = make_shared<TestScene>();
	ResourceManager::GetInstance()->Initialize();
	SceneManager::GetInstance()->SetScene(_scene);
	InputManager::GetInstance()->Init(mWinfo.hwnd);


}

void GameEngine::Update()
{

	Timer::GetInstance()->Update();
	ShowFPS();
	SceneManager::GetInstance()->Update();
	InputManager::GetInstance()->Update();
}

void GameEngine::Render()
{
	RenderBegin();

	SceneManager::GetInstance()->Render();

	RenderEnd();
}


void GameEngine::InitializeDeviceAndSwapChain()
{


	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

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
		featureLevels,
		ARRAYSIZE(featureLevels),              // default feature level array
		D3D11_SDK_VERSION,
		&mDevice,
		&featureLevel,
		&mDeviceContext);


	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);

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

void GameEngine::CreateSampleState()
{

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HRESULT hr = mDevice->CreateSamplerState(&sampDesc, &g_pSamplerLinear);

}

void GameEngine::ScreenResize()
{
	mSwapChain->ResizeBuffers(1, mWinfo.ClientWidth, mWinfo.ClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	mSwapChain->GetBuffer(0, IID_PPV_ARGS(&mBackBuffer));
   

	


	//D3D11_TEXTURE2D_DESC depthStencilDesc;

	//depthStencilDesc.Width = mWinfo.ClientWidth;
	//depthStencilDesc.Height = mWinfo.ClientHeight;
	//depthStencilDesc.MipLevels = 1;
	//depthStencilDesc.ArraySize = 1;
	//depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	//if (mEnable4xMsaa)
	//{
	//	depthStencilDesc.SampleDesc.Count = 4;
	//	depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
	//}
	//// No MSAA
	//else
	//{
	//	depthStencilDesc.SampleDesc.Count = 1;
	//	depthStencilDesc.SampleDesc.Quality = 0;
	//}

	//depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	//depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//depthStencilDesc.CPUAccessFlags = 0;
	//depthStencilDesc.MiscFlags = 0;

	//mDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer);
	//mDevice->CreateDepthStencilView(mDepthStencilBuffer, 0,&mDepthStencilView);

	//mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

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
	/*check = 1;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &check;*/

	//mDevice->CreateBuffer(&bd, NULL, &g_buffer);






	XMVECTORF32 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
	shared_ptr<Texture> dsTexture = ResourceManager::GetInstance()->Get<Texture>(L"DepthStencil");
	shared_ptr<Texture> rtTexture = ResourceManager::GetInstance()->Get<Texture>(L"SwapChainTarget");

	mDeviceContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
	//mDeviceContext->ClearRenderTargetView(rtTexture->GetRTV(), reinterpret_cast<const float*>(&Colors::BlanchedAlmond));
	mDeviceContext->ClearDepthStencilView(dsTexture->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
}

void GameEngine::RenderEnd()
{
	mSwapChain->Present(0, 0);
}

void GameEngine::ShowFPS()
{
	UINT32 fps = Timer::GetInstance()->GetFps();

	WCHAR text[100] = L"";
	::wsprintf(text, L"FPS : %d", fps);

	::SetWindowText(mWinfo.hwnd, text);
}

void GameEngine::CreateRenderTargetGroups()
{
	//DepthStencil
	shared_ptr<Texture> dsTexture = ResourceManager::GetInstance()->CreateTexture(L"DepthStencil", DXGI_FORMAT_D24_UNORM_S8_UINT,
		mWinfo.ClientWidth, mWinfo.ClientHeight, XMFLOAT4(0.69f, 0.77f, 0.87f, 1.0f), D3D11_BIND_DEPTH_STENCIL);
	
	
	//SwapChain

	{
		vector<RenderTarget> rtVec(SWAP_CHAIN_BUFFER_COUNT);
		mSwapChain->GetBuffer(0, IID_PPV_ARGS(&mBackBuffer));
		rtVec[0].target = ResourceManager::GetInstance()->CreateTextureFromResource(L"SwapChainTarget", mBackBuffer);
		_rtGroups[static_cast<UINT8>(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)] = make_shared<RenderTargetGroup>();
		_rtGroups[static_cast<UINT8>(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)]->Create(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN, rtVec, dsTexture);

	}
	
	//Deferred

	{
		vector<RenderTarget> rtVec(RENDER_TARGET_G_BUFFER_GROUP_MEMBER_COUNT);
		rtVec[0].target = ResourceManager::GetInstance()->CreateTexture(L"PositionTarget", DXGI_FORMAT_R32G32B32A32_FLOAT,
			mWinfo.ClientWidth, mWinfo.ClientHeight, XMFLOAT4(0.69f, 0.77f, 0.87f, 1.0f), D3D11_BIND_RENDER_TARGET);

		rtVec[1].target = ResourceManager::GetInstance()->CreateTexture(L"NomalTarget", DXGI_FORMAT_R32G32B32A32_FLOAT,
			mWinfo.ClientWidth, mWinfo.ClientHeight, XMFLOAT4(0.69f, 0.77f, 0.87f, 1.0f), D3D11_BIND_RENDER_TARGET);

		rtVec[2].target = ResourceManager::GetInstance()->CreateTexture(L"DiffuseTarget", DXGI_FORMAT_R8G8B8A8_UNORM,
			mWinfo.ClientWidth, mWinfo.ClientHeight, XMFLOAT4(0.69f, 0.77f, 0.87f, 1.0f), D3D11_BIND_RENDER_TARGET);
	
		_rtGroups[static_cast<UINT8>(RENDER_TARGET_GROUP_TYPE::G_BUFFER)] = make_shared<RenderTargetGroup>();
		_rtGroups[static_cast<UINT8>(RENDER_TARGET_GROUP_TYPE::G_BUFFER)]->Create(RENDER_TARGET_GROUP_TYPE::G_BUFFER, rtVec, dsTexture);
	}
	
	


}

void GameEngine::ScreenSetting()
{
	mSwapChain->ResizeBuffers(1, mWinfo.ClientWidth, mWinfo.ClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	mSwapChain->GetBuffer(0, IID_PPV_ARGS(&mBackBuffer));


	mViewPort.TopLeftX = 0;
	mViewPort.TopLeftY = 0;
	mViewPort.Width = static_cast<float>(mWinfo.ClientWidth);
	mViewPort.Height = static_cast<float>(mWinfo.ClientHeight);
	mViewPort.MinDepth = 0.0f;
	mViewPort.MaxDepth = 1.0f;

	mDeviceContext->RSSetViewports(1, &mViewPort);
}



void GameEngine::CallScreenResize(const WindowInfo& wInfo)
{

	mWinfo = wInfo;
	ScreenResize();

}

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