#include "pch.h"
#include "Shader.h"
#include "GameEngine.h"
#include "Texture.h"


Shader::Shader(const wstring& path, const LPCSTR tech_name, RASTERIZER_TYPE rtype, DEPTH_STENCIL_TYPE dtype) : Object(OBJECT_TYPE::SHADER)
{

	
	
	mShaderInfo.rasterizerType = rtype;
	mShaderInfo.depthStencilType = dtype;
	CreateShaderFile(path, tech_name);
	CreateVertexLayout();
	
}

void Shader::Render()
{
	BindDepthStencilAndRasterizerState();
}


void Shader::CreateShaderFile(const wstring& path, const LPCSTR tech_name)
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr = D3DCompileFromFile(path.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "fx_5_0", shaderFlags,
		0, &compiledShader, &compilationMsgs);

	D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, GEngine->GetDevice(), &mFX);

	mTech = mFX->GetTechniqueByName(tech_name);
	mMatrixParams = mFX->GetVariableByName("g_TransformParmas");
	mTextureOnParams = mFX->GetVariableByName("g_Tex_On");
	mSRVariableArray[0] = mFX->GetVariableByName("g_tex_0")->AsShaderResource();
	mSRVariableArray[1] = mFX->GetVariableByName("g_tex_1")->AsShaderResource();
	mSRVariableArray[2] = mFX->GetVariableByName("g_tex_2")->AsShaderResource();
	mSRVariableArray[3] = mFX->GetVariableByName("g_tex_3")->AsShaderResource();
	mSRVariableArray[4] = mFX->GetVariableByName("g_tex_4")->AsShaderResource();
	mLightParams = mFX->GetVariableByName("g_lightParams");

}

void Shader::CreateVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{

		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},

	};

	// Create the input layout
	D3DX11_PASS_DESC passDesc;
	HRESULT hr =  mTech->GetPassByIndex(0)->GetDesc(&passDesc);

	GEngine->GetDevice()->CreateInputLayout(vertexDesc, 4, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &mInputLayout);

	
	CreateRasterizerState();


	
}

void Shader::PushTransformData(TransformParams params)
{
	mTransformParams = params;
	mMatrixParams->SetRawValue(&mTransformParams,0,sizeof(TransformParams));

}



void Shader::PushTextureData(array<shared_ptr<class Texture>, TEXTURE_COUNT>& _array, TEXTURE_ON texon, int count)
{
	for (int i = 0; i < count; i++)
	{
		mSRVariableArray[i]->SetResource(_array[i]->GetSRV());
	}

	mTextureOnParams->SetRawValue(&texon, 0, sizeof(TEXTURE_ON));
}

void Shader::PushLightData(LightParams& params)
{
	LightParams lightparams = params;
	mLightParams->SetRawValue(&lightparams, 0, sizeof(LightParams));

}

void Shader::BindDepthStencilAndRasterizerState()
{
	GEngine->GetDeviceContext()->RSSetState(mRasterizerState);
	GEngine->GetDeviceContext()->OMSetDepthStencilState(mDepthStencilState, 1);
}

void Shader::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC RasterState;
	ZeroMemory(&RasterState, sizeof(D3D11_RASTERIZER_DESC));

	switch (mShaderInfo.rasterizerType)
	{
	case RASTERIZER_TYPE::CULL_BACK:
		RasterState.FillMode = D3D11_FILL_SOLID;
		RasterState.CullMode = D3D11_CULL_BACK;
		break;
	case RASTERIZER_TYPE::CULL_FRONT:
		RasterState.FillMode = D3D11_FILL_SOLID;
		RasterState.CullMode = D3D11_CULL_FRONT;
		break;
	case RASTERIZER_TYPE::CULL_NONE:
		RasterState.FillMode = D3D11_FILL_SOLID;
		RasterState.CullMode = D3D11_CULL_NONE;
		break;
	case RASTERIZER_TYPE::WIREFRAME:
		RasterState.FillMode = D3D11_FILL_WIREFRAME;
		RasterState.CullMode = D3D11_CULL_NONE;
		break;
	default:
		break;
	}


	RasterState.FrontCounterClockwise = false;
	RasterState.DepthBias = false;
	RasterState.DepthBiasClamp = 0;
	RasterState.SlopeScaledDepthBias = 0;
	RasterState.DepthClipEnable = true;
	RasterState.ScissorEnable = false;
	RasterState.MultisampleEnable = false;
	RasterState.AntialiasedLineEnable = false;

	GEngine->GetDevice()->CreateRasterizerState(&RasterState, &mRasterizerState);

	D3D11_DEPTH_STENCIL_DESC DSState;


	switch (mShaderInfo.depthStencilType)
	{
	case DEPTH_STENCIL_TYPE::LESS:
		DSState.DepthEnable = true;
		DSState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DSState.DepthFunc = D3D11_COMPARISON_LESS;
		break;
	case DEPTH_STENCIL_TYPE::LESS_EQUAL:
		DSState.DepthEnable = true;
		DSState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DSState.DepthFunc = D3D11_COMPARISON_EQUAL;
		break;
	case DEPTH_STENCIL_TYPE::GREATER:
		DSState.DepthEnable = true;
		DSState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DSState.DepthFunc = D3D11_COMPARISON_GREATER;
		break;
	case DEPTH_STENCIL_TYPE::GREATER_EQUAL:
		DSState.DepthEnable = true;
		DSState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DSState.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
		break;
	default:
		break;
	}



	DSState.StencilEnable = true;
	DSState.StencilReadMask = 0xFF;
	DSState.StencilWriteMask = 0xFF;

	DSState.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DSState.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	DSState.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DSState.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	DSState.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DSState.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	DSState.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DSState.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;




	GEngine->GetDevice()->CreateDepthStencilState(&DSState, &mDepthStencilState);
}