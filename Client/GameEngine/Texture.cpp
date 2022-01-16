#include "pch.h"
#include "Texture.h"
#include "GameEngine.h"
#include "Material.h"
#include "Shader.h"

Texture::Texture() : Object(OBJECT_TYPE::TEXTURE)
{
}

void Texture::CreateTexture(wstring path,int srvnum)
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
		
		hr = CreateShaderResourceView(GEngine->GetDevice(),
			image.GetImages(), image.GetImageCount(),
			image.GetMetadata(), &(mSRVArray[srvnum]));

		if (SUCCEEDED(hr))
		{
			mMaterial.lock()->GetShader()->PushTextureData(mSRVArray[srvnum], srvnum);

		}
	}
}
