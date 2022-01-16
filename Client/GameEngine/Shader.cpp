#include "pch.h"
#include "Shader.h"
#include "GameEngine.h"

Shader::Shader(const wstring& path, const LPCSTR tech_name) : Object(OBJECT_TYPE::SHADER)
{
	CreateShaderFile(path, tech_name);
	CreateVertexLayout();
	TexOn = {};
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


}

void Shader::CreateVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{

		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},

	};

	// Create the input layout
	D3DX11_PASS_DESC passDesc;
	HRESULT hr =  mTech->GetPassByIndex(0)->GetDesc(&passDesc);

	GEngine->GetDevice()->CreateInputLayout(vertexDesc, 3, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &mInputLayout);

	//GEngine->GetDeviceContext()->IASetInputLayout(mInputLayout);
	
}

void Shader::PushTransformData(TransformParams params)
{
	mTransformParams = params;
	mMatrixParams->SetRawValue(&mTransformParams,0,sizeof(TransformParams));

}

void Shader::PushTextureData(ID3D11ShaderResourceView* _srvView, int num)
{
	mSRVArray[num] = _srvView;
	mSRVariableArray[num]->SetResource(mSRVArray[num]);
	
	switch (num)
	{

	case 0:
		TexOn.Tex0_On = 1;
		break;
	case 1:
		TexOn.Tex0_On = 1;
		break;
	case 2:
		TexOn.Tex0_On = 1;
		break;
	case 3:
		TexOn.Tex0_On = 1;
		break;
	case 4:
		TexOn.Tex0_On = 1;
		break;
	default:
		break;
	}

	mTextureOnParams->SetRawValue(&TexOn,0,sizeof(TEXTURE_ON));
}
