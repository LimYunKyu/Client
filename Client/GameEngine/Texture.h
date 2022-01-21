#pragma once
#include "Object.h"




class Texture :public Object
{
public:
	Texture();
	void Render();
public:
	virtual void Load(const wstring& path) override;
	void SetMaterial(shared_ptr<class Material> material) { mMaterial = material; }
	void CreateTexture(DXGI_FORMAT format, UINT32 width, UINT32 height, XMFLOAT4 clearColor, D3D11_BIND_FLAG flag);
	void CreateTextureFromResource(ID3D11Texture2D* tex);


	ID3D11ShaderResourceView* GetSRV() { return mSRV; }
	ID3D11DepthStencilView* GetDSV() { return mDSV; }
	ID3D11RenderTargetView* GetRTV() { return mRTV; }
private:
	int CurrentTextureCount = 0;
	//array<ID3D11ShaderResourceView*, SRVCOUNT> mSRVArray;
	weak_ptr<class Material> mMaterial;
	ID3D11ShaderResourceView* mSRV;
	ID3D11DepthStencilView* mDSV;
	ID3D11RenderTargetView* mRTV;
	ID3D11Texture2D* mTex2D;
};

