#pragma once
#include "Object.h"




class Texture :public Object
{
public:
	Texture();

public:
	void CreateTexture(wstring path,int srvnum);
	void SetMaterial(shared_ptr<class Material> material) { mMaterial = material; }

private:
	ID3D11ShaderResourceView* mSRV1;
	ID3D11Resource* mResource1;

	array<ID3D11ShaderResourceView*, SRVCOUNT> mSRVArray;
	weak_ptr<class Material> mMaterial;
};

