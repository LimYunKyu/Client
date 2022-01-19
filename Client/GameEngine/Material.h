#pragma once
#include "Object.h"

enum {

	TEXTURE_COUNT = 5,

};


class Material : public Object, public enable_shared_from_this<Material>
{
public:
	Material();

public:
	
	virtual void Render();

public:
	void SetShader(shared_ptr<class Shader> shader);
	void SetTexture(shared_ptr<class Texture> texture, int idx);

	shared_ptr<class Shader> GetShader() { return mShader; }
private:
	shared_ptr<class Shader>   mShader;
	array<shared_ptr<class Texture>, TEXTURE_COUNT> mTextureArray;
	TEXTURE_ON mTexOn;

	int CurrentTextureCount = 0;
};

