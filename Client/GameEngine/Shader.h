#pragma once
#include "Object.h"
#include "Material.h"

enum class SHADER_TYPE : UINT8
{
	DEFERRED,
	FORWARD,
};

enum class RASTERIZER_TYPE
{
	CULL_NONE,
	CULL_FRONT,
	CULL_BACK,
	WIREFRAME,
};

enum class DEPTH_STENCIL_TYPE
{
	LESS,
	LESS_EQUAL,
	GREATER,
	GREATER_EQUAL,
};

struct ShaderInfo
{
	SHADER_TYPE shaderType = SHADER_TYPE::FORWARD;
	RASTERIZER_TYPE rasterizerType = RASTERIZER_TYPE::CULL_BACK;
	DEPTH_STENCIL_TYPE depthStencilType = DEPTH_STENCIL_TYPE::LESS;
	D3D_PRIMITIVE_TOPOLOGY topologyType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

class Shader :
    public Object
{
public:
	Shader(const wstring& path, const LPCSTR tech_name, SHADER_TYPE stype = SHADER_TYPE::FORWARD, RASTERIZER_TYPE rtype = RASTERIZER_TYPE::CULL_BACK, DEPTH_STENCIL_TYPE dtype = DEPTH_STENCIL_TYPE::LESS);

	void Render();

public:
	void CreateShaderFile(const wstring& path, const LPCSTR tech_name);
	void CreateVertexLayout();
	void PushTransformData(TransformParams params);
	void PushTextureData(array<shared_ptr<class Texture>, TEXTURE_COUNT>& _array, TEXTURE_ON texon, int count);
	void PushLightData(LightParams& params);
	void SetMaterial(shared_ptr<class Material> material) { mMaterial = material; }
	void BindDepthStencilAndRasterizerState();

	SHADER_TYPE GetShaderType() { return mShaderInfo.shaderType; }

private:
	void CreateRasterizerState();
	
public:
	ID3DX11EffectTechnique* GetTech() { return mTech; }

public:
	ID3D11InputLayout* GetInputLayout() { return mInputLayout; }
	
private:
	ID3DX11Effect*				mFX;
	ID3DX11EffectTechnique*		mTech;
	ID3DX11EffectVariable*		mMatrixParams;
	ID3DX11EffectVariable*      mTextureOnParams;
	ID3DX11EffectVariable*      mLightParams;
	ID3D11InputLayout*			mInputLayout;
	ID3D11RasterizerState*		mRasterizerState;
	ID3D11DepthStencilState*	mDepthStencilState;


	ShaderInfo					mShaderInfo;


	int CurrentTextureCount = 0;
	array<ID3DX11EffectShaderResourceVariable*, SRVCOUNT> mSRVariableArray;
	array<shared_ptr<class Texture>, TEXTURE_COUNT>       mTextureArray;
	
	TransformParams				mTransformParams;


	weak_ptr<class Material> mMaterial;


};

