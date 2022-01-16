#include "pch.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameEngine.h"

XMMATRIX Camera::ViewMatrix;
XMMATRIX Camera::ProjectionMatrix;

Camera::Camera() : Component(COMPONENT_TYPE::CAMERA)
{
	mViewMatrix = XMMatrixIdentity();
	mProJectionMatirx = XMMatrixIdentity();
	ViewMatrix = XMMatrixIdentity();
	ProjectionMatrix = XMMatrixIdentity();
	_width = GEngine->GetWinfo().ClientWidth;
	_height = GEngine->GetWinfo().ClientHeight;
}

void Camera::Initialize()
{
	
}

void Camera::LateInitialize()
{
}

void Camera::Update()
{
}

void Camera::LateUpdate()
{
	XMMATRIX WorldMatrix = mGameObject.lock()->GetTransform()->GetWorldMat();
	mViewMatrix = XMMatrixInverse(nullptr, WorldMatrix);

	if (mProjectionType == PROJECTION_TYPE::PERSPECTIVE)
		mProJectionMatirx = ::XMMatrixPerspectiveFovLH(XMConvertToRadians(45.f), _width / _height, _near, _far);
	else
		mProJectionMatirx = ::XMMatrixOrthographicLH(_width * _scale, _height * _scale, _near, _far);

	ViewMatrix = mViewMatrix;
	ProjectionMatrix = mProJectionMatirx;

}

void Camera::FinalUpdate()
{
}
	

void Camera::Render()
{


}
