#pragma once
enum PLANE_TYPE : UINT8
{
	PLANE_FRONT,
	PLANE_BACK,
	PLANE_UP,
	PLANE_DOWN,
	PLANE_LEFT,
	PLANE_RIGHT,

	PLANE_END
};

class Frustum
{
public:
	void FinalUpdate();
	bool ContainsSphere(const XMFLOAT3& pos, float radius);

private:
	array<XMVECTOR, PLANE_END> _planes;
};

