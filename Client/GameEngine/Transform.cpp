#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "Material.h"
#include "MeshRender.h"
#include "Shader.h"
#include "Camera.h"

Transform::Transform() : Component(COMPONENT_TYPE::TRANSFORM)
{
	XMMATRIX I = XMMatrixIdentity();

	mScaleMat		= I;
	mRotateMat		= I;
	mTranslateMat	= I;
	mLocalMat		= I;
	mWorldMat		= I;
	mRotateXMat		= I;
	mRotateYMat		= I;
	mRotateZMat		= I;
	mCurrentPos		= { 0.f,0.f,0.f };
	mCurrentRot		= { 0.f,0.f,0.f };
	mCurrentScale	= { 1.f,1.f,1.f };

	

}

void Transform::Initialize()
{
}

void Transform::LateInitialize()
{
}

void Transform::Update()
{
}

void Transform::LateUpdate()
{
	mRotateMat = mRotateXMat * mRotateYMat * mRotateZMat;
	mLocalMat = mScaleMat * mRotateMat * mTranslateMat;
	mWorldMat = mLocalMat;

}

void Transform::FinalUpdate()
{
	
}

void Transform::Render()
{
	if (!mGameObject.lock()->GetMeshRender())
		return;


	TransformParams params;
	params.matWorld = mWorldMat;
	params.matView = Camera::GetViewMatrix();
	params.matProjection = Camera::GetProjectionMatrix();
	params.matWV = params.matWorld * params.matView;
	params.matWVP = params.matWorld * params.matView * params.matProjection;


	XMVECTOR te = { mCurrentPos.x,mCurrentPos.y,mCurrentPos.z,1 };
	XMVECTOR test = XMVector4Transform(te, params.matWVP);
	

	
	mGameObject.lock()->GetMeshRender()->GetMaterial()->GetShader()->PushTransformData(params);

}

void Transform::SetScale(XMFLOAT3 scale)
{
	mCurrentScale = scale;
	mScaleMat = XMMatrixScaling(mCurrentScale.x, mCurrentScale.y, mCurrentScale.z);

}

void Transform::SetRotateX(FLOAT x)
{
	mCurrentRot.x = x;
	mRotateXMat = XMMatrixRotationX(x);
}

void Transform::SetRotateY(FLOAT y)
{
	mCurrentRot.y = y;
	mRotateYMat = XMMatrixRotationY(y);
}

void Transform::SetRotateZ(FLOAT z)
{
	mCurrentRot.z = z;
	mRotateZMat = XMMatrixRotationZ(z);
}

void Transform::SetTranslate(XMFLOAT3 trans)
{
	mCurrentPos = trans;
	mTranslateMat = XMMatrixTranslation(mCurrentPos.x, mCurrentPos.y, mCurrentPos.z);

}
