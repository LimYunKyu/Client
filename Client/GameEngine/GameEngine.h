#pragma once
class GameEngine
{
public:
	~GameEngine();
public:
	void Initialize(const WindowInfo& wInfo);
	void Update();
	void Render();
	void CallScreenResize(const WindowInfo& wInfo);
	ID3D11Device* GetDevice() { return mDevice; }
	ID3D11DeviceContext* GetDeviceContext() { return mDeviceContext; }
	
public:
	WindowInfo GetWinfo() { return mWinfo; }

private:

	void InitializeDeviceAndSwapChain();
	void CreateSampleState();
	void ScreenResize();
	void RenderBegin();
	void RenderEnd();
	void ShowFPS();

	
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


	D3D_DRIVER_TYPE				md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	UINT						m4xMsaaQuality = 0;
	bool						mEnable4xMsaa = false;
	int                         check = 0;

};

