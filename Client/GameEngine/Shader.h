#pragma once
#include "Object.h"



class Shader :
    public Object
{
public:
	Shader(const wstring& path, const LPCSTR tech_name);

public:
	void CreateShaderFile(const wstring& path, const LPCSTR tech_name);
	void CreateVertexLayout();
	void PushTransformData(TransformParams params);
	void PushTextureData(ID3D11ShaderResourceView* _srvView, int num);

	void SetMaterial(shared_ptr<class Material> material) { mMaterial = material; }
public:
	ID3DX11EffectTechnique* GetTech() { return mTech; }

public:
	ID3D11InputLayout* GetInputLayout() { return mInputLayout; }
	
private:
	ID3DX11Effect*				mFX;
	ID3DX11EffectTechnique*		mTech;
	ID3DX11EffectVariable*		mMatrixParams;
	ID3DX11EffectVariable*      mTextureOnParams;
	ID3D11InputLayout*			mInputLayout;


	array<ID3DX11EffectShaderResourceVariable*, SRVCOUNT> mSRVariableArray;
	array<ID3D11ShaderResourceView*, SRVCOUNT> mSRVArray;
	TransformParams				mTransformParams;

	TEXTURE_ON TexOn;

	weak_ptr<class Material> mMaterial;
};

