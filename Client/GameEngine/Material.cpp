#include "pch.h"
#include "Material.h"
#include "Shader.h"

#include "Texture.h"
Material::Material() : Object(OBJECT_TYPE::MATERIAL)
{

}


void Material::Render()
{
	
	mShader->Render();
	mTexture->Render();
	

}

void Material::SetShader(shared_ptr<class Shader> shader)
{
	mShader = shader;
	mShader->SetMaterial(shared_from_this());

}

void Material::SetTexture(shared_ptr<class Texture> texture,int idx)
{
	/*mTextureArray[idx] = texture;
	mTextureArray[idx]->SetMaterial(shared_from_this());*/

	mTexture = texture;
	mTexture->SetMaterial(shared_from_this());
	
}
