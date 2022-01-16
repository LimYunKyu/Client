#include "pch.h"
#include "MeshRender.h"
#include "Material.h"
#include "GameEngine.h"
#include "Shader.h"
#include "Mesh.h"

MeshRender::MeshRender() : Component(COMPONENT_TYPE::MESHRENDER)
{
	
}

void MeshRender::Initialize()
{
	
}

void MeshRender::LateInitialize()
{
}

void MeshRender::Update()
{
	mMaterial->Update();
	mMesh->Update();
}

void MeshRender::LateUpdate()
{
	mMaterial->LateUpdate();
	mMesh->LateUpdate();
}

void MeshRender::FinalUpdate()
{
	mMaterial->FinalUpdate();
	mMesh->FinalUpdate();
}

void MeshRender::Render()
{



	
	mMaterial->Render();
	mMesh->SetTech(mMaterial->GetShader()->GetTech());
	mMesh->SetInputLayout(mMaterial->GetShader()->GetInputLayout());
	mMesh->Render();

	


}
