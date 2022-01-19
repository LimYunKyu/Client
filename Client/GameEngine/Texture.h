#pragma once
#include "Object.h"




class Texture :public Object
{
public:
	Texture();
	void Render();
public:
	void CreateTexture(wstring path);
	void SetMaterial(shared_ptr<class Material> material) { mMaterial = material; }
	virtual void Load(const wstring& path) override;
	ID3D11ShaderResourceView* GetSRV() { return mSRV; }

private:
	int CurrentTextureCount = 0;
	TEXTURE_ON TexOn;
	//array<ID3D11ShaderResourceView*, SRVCOUNT> mSRVArray;
	weak_ptr<class Material> mMaterial;
	ID3D11ShaderResourceView* mSRV;
};

