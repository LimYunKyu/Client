#pragma once
#include "RenderTargetGroup.h"


class GameEngine
{
public:
	~GameEngine();
public:
	void Initialize(const WindowInfo& wInfo);
	void Update();
	void Render();
	void CallScreenResize(const WindowInfo& wInfo);
	

public:
	ID3D11Device* GetDevice() { return mDevice; }
	ID3D11DeviceContext* GetDeviceContext() { return mDeviceContext; }
	shared_ptr<RenderTargetGroup> GetRTGroup(RENDER_TARGET_GROUP_TYPE type) { return _rtGroups[static_cast<UINT8>(type)]; }
public:
	WindowInfo GetWinfo() { return mWinfo; }

private:

	void InitializeDeviceAndSwapChain();
	void CreateSampleState();
	void ScreenResize();
	void RenderBegin();
	void RenderEnd();
	void ShowFPS();
	void CreateRenderTargetGroups();
	void ScreenSetting();
	
private:
	WindowInfo					mWinfo;
	ID3D11Device*				mDevice;
	ID3D11DeviceContext*		mDeviceContext;
	IDXGISwapChain*				mSwapChain;
	ID3D11Texture2D*			mDepthStencilBuffer;
	ID3D11Texture2D*			mBackBuffer;
	ID3D11RenderTargetView*		mRenderTargetView;
	ID3D11DepthStencilView*		mDepthStencilView;
	D3D11_VIEWPORT				mViewPort;
	ID3D11SamplerState*			g_pSamplerLinear = NULL;
	ID3D11Buffer*				g_buffer = NULL;



	IDXGIDevice*				mdxgiDevice;
	IDXGIAdapter*				mdxgiAdapter;
	IDXGIFactory*				mdxgiFactory;

	//shared_ptr<class Texture>         dsTexture;

	D3D_DRIVER_TYPE				md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	UINT						m4xMsaaQuality = 0;
	bool						mEnable4xMsaa = false;
	int                         check = 0;

	array<shared_ptr<class RenderTargetGroup>, RENDER_TARGET_GROUP_COUNT> _rtGroups;

};

