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

private:

	void InitializeDeviceAndSwapChain();
	void ScreenResize();
	void RenderBegin();
	void RenderEnd();
	
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

	IDXGIDevice*				mdxgiDevice;
	IDXGIAdapter*				mdxgiAdapter;
	IDXGIFactory*				mdxgiFactory;


	D3D_DRIVER_TYPE				md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	UINT						m4xMsaaQuality = 0;
	bool						mEnable4xMsaa = false;

};
