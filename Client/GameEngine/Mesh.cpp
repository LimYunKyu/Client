#include "pch.h"
#include "Mesh.h"
#include "GameEngine.h"

Mesh::Mesh() : Object(OBJECT_TYPE::MESH)
{
}

Mesh::~Mesh()
{

	ReleaseCOM(mVertexBuffer);
	ReleaseCOM(mIndexBuffer);
	
}

void Mesh::Create(const vector<Vertex>& vertexBuffer, const vector<UINT>& indexBuffer)
{
	CreateVertexBuffer(vertexBuffer);
	CreateIndexBuffer(indexBuffer);
}

void Mesh::CreateVertexBuffer(const vector<Vertex>& buffer)
{
	D3D11_BUFFER_DESC vbd;
	//vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(Vertex) * (buffer).size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &(buffer[0]);
	GEngine->GetDevice()->CreateBuffer(&vbd, &vinitData, &mVertexBuffer);


	mVertexCount = buffer.size();
}

void Mesh::CreateIndexBuffer(const vector<UINT>& buffer)
{

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * buffer.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &(buffer[0]);

	GEngine->GetDevice()->CreateBuffer(&ibd, &iinitData, &mIndexBuffer);

	mIndexCount = buffer.size();
}



void Mesh::Render()
{
	
	GEngine->GetDeviceContext()->IASetInputLayout(mInputLayout);
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	GEngine->GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	GEngine->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);


	D3DX11_TECHNIQUE_DESC techDesc;
	mTech->GetDesc(&techDesc);

	for (UINT p = 0; p < techDesc.Passes; ++p)
	{

		mTech->GetPassByIndex(p)->Apply(0, GEngine->GetDeviceContext());

		GEngine->GetDeviceContext()->DrawIndexed(mIndexCount, 0, 0);

	}
}
