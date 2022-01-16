#include "pch.h"
#include "CameraScript.h"
#include "InputManager.h"
#include "Timer.h"
#include "GameObject.h"
#include "Transform.h"

CameraScript::CameraScript()
{
}

CameraScript::~CameraScript()
{
}

void CameraScript::Initialize()
{
}

void CameraScript::LateInitialize()
{
}

void CameraScript::Update()
{
	XMFLOAT3 pos = mGameObject.lock()->GetTransform()->GetPosition();
	float DeltaTime = Timer::GetInstance()->GetDeltaTime();

	if (InputManager::GetInstance()->GetButton(KEY_TYPE::W))
	{
		XMVECTOR CurrentPos = XMLoadFloat3(&pos) + (mGameObject.lock()->GetTransform()->GetLook() * _speed * DeltaTime);
		XMStoreFloat3(&pos, CurrentPos);
		mGameObject.lock()->GetTransform()->SetTranslate(pos);

	}


	if (InputManager::GetInstance()->GetButton(KEY_TYPE::S))
	{
		XMVECTOR CurrentPos = XMLoadFloat3(&pos) - (mGameObject.lock()->GetTransform()->GetLook() * _speed * DeltaTime);
		XMStoreFloat3(&pos, CurrentPos);
		mGameObject.lock()->GetTransform()->SetTranslate(pos);
	}


	if (InputManager::GetInstance()->GetButton(KEY_TYPE::A))
	{
		XMVECTOR CurrentPos = XMLoadFloat3(&pos) - (mGameObject.lock()->GetTransform()->GetRight() * _speed * DeltaTime);
		XMStoreFloat3(&pos, CurrentPos);
		mGameObject.lock()->GetTransform()->SetTranslate(pos);
	}


	if (InputManager::GetInstance()->GetButton(KEY_TYPE::D))
	{
		XMVECTOR CurrentPos = XMLoadFloat3(&pos) + (mGameObject.lock()->GetTransform()->GetRight() * _speed * DeltaTime);
		XMStoreFloat3(&pos, CurrentPos);
		mGameObject.lock()->GetTransform()->SetTranslate(pos);
	}


	if (InputManager::GetInstance()->GetButton(KEY_TYPE::Q))
	{
		XMFLOAT3 rotation = mGameObject.lock()->GetTransform()->GetRotation();
		rotation.x += (DeltaTime * 0.5f);
		mGameObject.lock()->GetTransform()->SetRotateX(rotation.x);
	}

	if (InputManager::GetInstance()->GetButton(KEY_TYPE::E))
	{
		XMFLOAT3 rotation = mGameObject.lock()->GetTransform()->GetRotation();
		rotation.x -= (DeltaTime * 0.5f);
		mGameObject.lock()->GetTransform()->SetRotateX(rotation.x);
	}

	if (InputManager::GetInstance()->GetButton(KEY_TYPE::Z))
	{
		XMFLOAT3 rotation = mGameObject.lock()->GetTransform()->GetRotation();
		rotation.y -= (DeltaTime * 0.5f);
		mGameObject.lock()->GetTransform()->SetRotateY(rotation.y);
	}

	if (InputManager::GetInstance()->GetButton(KEY_TYPE::C))
	{
		XMFLOAT3 rotation = mGameObject.lock()->GetTransform()->GetRotation();
		rotation.y += (DeltaTime * 0.5f);
		mGameObject.lock()->GetTransform()->SetRotateY(rotation.y);
	}
}

void CameraScript::LateUpdate()
{
	


	
}

void CameraScript::FinalUpdate()
{
}

void CameraScript::Render()
{
}
