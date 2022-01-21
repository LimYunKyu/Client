#include "pch.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameEngine.h"
#include "Scene.h"
#include "SceneManager.h"
#include "MeshRender.h"
#include "Shader.h"

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

	

}

void Camera::FinalUpdate()
{
	_frustum.FinalUpdate();
}
	

void Camera::Render()
{
	ViewMatrix = mViewMatrix;
	ProjectionMatrix = mProJectionMatirx;

	shared_ptr<Scene> scene = SceneManager::GetInstance()->GetCurrentScene();

	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjectVector();

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetMeshRender() == nullptr)
			continue;

		if (IsCulled(gameObject->GetLayerIndex()))
			continue;

		if (gameObject->GetCheckFrustum())
		{
			if (_frustum.ContainsSphere(
				gameObject->GetTransform()->GetPosition(),
				gameObject->GetTransform()->GetBoundingSphereRadius()) == false)
			{
				continue;
			}
		}

		gameObject->Render();
	}

}

void Camera::SortGameObject()
{
	shared_ptr<Scene> scene = SceneManager::GetInstance()->GetCurrentScene();
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjectVector();
	_vecForward.clear();
	_vecDeferred.clear();

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetMeshRender() == nullptr)
			continue;

		if (IsCulled(gameObject->GetLayerIndex()))
			continue;

		if (gameObject->GetCheckFrustum())
		{
			if (_frustum.ContainsSphere(
				gameObject->GetTransform()->GetPosition(),
				gameObject->GetTransform()->GetBoundingSphereRadius()) == false)
			{
				continue;
			}
		}

		SHADER_TYPE shaderType = gameObject->GetMeshRender()->GetMaterial()->GetShader()->GetShaderType();
		switch (shaderType)
		{
		case SHADER_TYPE::DEFERRED:
			_vecDeferred.push_back(gameObject);
			break;
		case SHADER_TYPE::FORWARD:
			_vecForward.push_back(gameObject);
			break;
		}
	}

}

void Camera::Render_Deferred()
{
	ViewMatrix = mViewMatrix;
	ProjectionMatrix = mProJectionMatirx;
	for (auto& gameObject : _vecDeferred)
	{
		gameObject->Render();
	}
}

void Camera::Render_Forward()
{
	ViewMatrix = mViewMatrix;
	ProjectionMatrix = mProJectionMatirx;

	for (auto& gameObject : _vecForward)
	{
		gameObject->Render();
	}
}
