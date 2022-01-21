#include "pch.h"
#include "Texture.h"
#include "GameEngine.h"
#include "Material.h"
#include "Shader.h"

Texture::Texture() : Object(OBJECT_TYPE::TEXTURE)
{
	
}

void Texture::Render()
{
}
	

void Texture::Load(const wstring& path)
{
	wchar_t ext[_MAX_EXT] = {};
	_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);

	ScratchImage image;
	HRESULT hr;
	if (_wcsicmp(ext, L".dds") == 0)
	{
		hr = LoadFromDDSFile(path.c_str(), DDS_FLAGS_NONE, nullptr, image);
	}
	else if (_wcsicmp(ext, L".tga") == 0)
	{
		hr = LoadFromTGAFile(path.c_str(), nullptr, image);
	}
	else if (_wcsicmp(ext, L".hdr") == 0)
	{
		hr = LoadFromHDRFile(path.c_str(), nullptr, image);
	}
	else
	{
		hr = LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);
	}



	if (SUCCEEDED(hr))
	{
		CurrentTextureCount++;

		hr = CreateShaderResourceView(GEngine->GetDevice(),
			image.GetImages(), image.GetImageCount(),
			image.GetMetadata(), &(mSRV));
	}

	
}

void Texture::CreateTexture(DXGI_FORMAT format, UINT32 width, UINT32 height, XMFLOAT4 clearColor, D3D11_BIND_FLAG flag)
{


	D3D11_TEXTURE2D_DESC Tex2DBuffer;
	ZeroMemory(&Tex2DBuffer, sizeof(D3D11_TEXTURE2D_DESC));

	Tex2DBuffer.Width = width;
	Tex2DBuffer.Height = height;
	Tex2DBuffer.MipLevels = 1;
	Tex2DBuffer.ArraySize = 1;
	Tex2DBuffer.Format = format;
	Tex2DBuffer.SampleDesc.Count = 1;
	Tex2DBuffer.SampleDesc.Quality = 0;
	Tex2DBuffer.Usage =  D3D11_USAGE_DEFAULT;	
	Tex2DBuffer.CPUAccessFlags = 0;
	Tex2DBuffer.MiscFlags = 0;

	

	
	
	if (flag == D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
	{
		Tex2DBuffer.BindFlags = flag;
		HRESULT HR = GEngine->GetDevice()->CreateTexture2D(&Tex2DBuffer, nullptr, &mTex2D);
		GEngine->GetDevice()->CreateDepthStencilView(mTex2D, nullptr, &mDSV);


	}
	else 
	{
		if (flag == D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			Tex2DBuffer.BindFlags = flag | D3D11_BIND_SHADER_RESOURCE;
			HRESULT HR = GEngine->GetDevice()->CreateTexture2D(&Tex2DBuffer, nullptr, &mTex2D);
			GEngine->GetDevice()->CreateRenderTargetView(mTex2D, nullptr, &mRTV);

		}
		
		
		
		GEngine->GetDevice()->CreateShaderResourceView(mTex2D, nullptr, &mSRV);
	}
	



}

void Texture::CreateTextureFromResource(ID3D11Texture2D* tex)
{
	GEngine->GetDevice()->CreateRenderTargetView(tex, 0, &mRTV);

}


