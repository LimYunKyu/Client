#include "pch.h"
#include "Material.h"
#include "Shader.h"

#include "Texture.h"
Material::Material() : Object(OBJECT_TYPE::MATERIAL)
{
	mTexOn = {};
}


void Material::Render()
{
	
	mShader->PushTextureData(mTextureArray ,mTexOn,CurrentTextureCount);
	mShader->Render();
	
	

}

void Material::SetShader(shared_ptr<class Shader> shader)
{
	mShader = shader;
	mShader->SetMaterial(shared_from_this());

}

void Material::SetTexture(shared_ptr<class Texture> texture,int idx)
{
	mTextureArray[idx] = texture;
	mTextureArray[idx]->SetMaterial(shared_from_this());
	
	switch (idx)
	{

	case 0:
		mTexOn.Tex0_On = 1;
		CurrentTextureCount = idx+1;
		break;
	case 1:
		mTexOn.Tex1_On = 1;
		CurrentTextureCount = idx + 1;
		break;
	case 2:
		mTexOn.Tex2_On = 1;
		CurrentTextureCount = idx + 1;
		break;
	case 3:
		mTexOn.Tex3_On = 1;
		CurrentTextureCount = idx + 1;
		break;
	case 4:
		mTexOn.Tex4_On = 1;
		CurrentTextureCount = idx + 1;
		break;
	default:
		break;
	}

	/*mTexture = texture;
	mTexture->SetMaterial(shared_from_this());*/
	
}
