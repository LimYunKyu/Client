#pragma once
#include "Object.h"


class Material : public Object, public enable_shared_from_this<Material>
{
public:
	Material();

public:
	
	virtual void Render();

public:
	void SetShader(shared_ptr<class Shader> shader);
	void SetTexture(shared_ptr<class Texture> texture);

	shared_ptr<class Shader> GetShader() { return mShader; }
private:
	shared_ptr<class Shader>   mShader;
	shared_ptr<class Texture>  mTexture;
	
};

