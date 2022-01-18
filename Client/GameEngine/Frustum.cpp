#include "pch.h"
#include "Frustum.h"
#include "Camera.h"

void Frustum::FinalUpdate()
{
	XMMATRIX matViewInv = XMMatrixInverse(nullptr,Camera::GetViewMatrix());
	XMMATRIX matProjectionInv = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix()); 
	XMMATRIX matInv = matProjectionInv * matViewInv;

	vector<XMVECTOR> worldPos =
	{
		::XMVector3TransformCoord({-1.f, 1.f, 0.f}, matInv),
		::XMVector3TransformCoord({1.f, 1.f, 0.f}, matInv),
		::XMVector3TransformCoord({1.f, -1.f, 0.f}, matInv),
		::XMVector3TransformCoord({-1.f, -1.f, 0.f}, matInv),
		::XMVector3TransformCoord({-1.f, 1.f, 1.f}, matInv),
		::XMVector3TransformCoord({1.f, 1.f, 1.f}, matInv),
		::XMVector3TransformCoord({1.f, -1.f, 1.f}, matInv),
		::XMVector3TransformCoord({-1.f, -1.f, 1.f}, matInv)
	};
	
	

	_planes[PLANE_FRONT] = ::XMPlaneFromPoints(worldPos[0], worldPos[1], worldPos[2]); // CW
	_planes[PLANE_BACK] = ::XMPlaneFromPoints(worldPos[4], worldPos[7], worldPos[5]); // CCW
	_planes[PLANE_UP] = ::XMPlaneFromPoints(worldPos[4], worldPos[5], worldPos[1]); // CW
	_planes[PLANE_DOWN] = ::XMPlaneFromPoints(worldPos[7], worldPos[3], worldPos[6]); // CCW
	_planes[PLANE_LEFT] = ::XMPlaneFromPoints(worldPos[4], worldPos[0], worldPos[7]); // CW
	_planes[PLANE_RIGHT] = ::XMPlaneFromPoints(worldPos[5], worldPos[6], worldPos[1]); // CCW


}

bool Frustum::ContainsSphere(const XMFLOAT3& pos, float radius)
{
	for (const XMVECTOR& plane : _planes)
	{
		// n = (a, b, c)
		XMVECTOR normal = plane;
		XMFLOAT4 tempFloat;
		XMStoreFloat4(&tempFloat, plane);

		XMFLOAT4 dist;
		XMVECTOR Pos = { pos.x,pos.y,pos.z,1.f };
		XMVECTOR Dot = XMVector4Dot(plane, Pos);
		XMStoreFloat4(&dist, Dot);

		// ax + by + cz + d > radius
		if (dist.x + tempFloat.w > radius)
			return false;
	}

	return true;
}
