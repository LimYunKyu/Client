#pragma once
#include "Component.h"
class Transform : public Component
{
public:
	Transform();


public:
	virtual void Initialize();
	virtual void LateInitialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();
	virtual void Render();

public:
	
	void SetScale(XMFLOAT3 scale);
	void SetRotateX(FLOAT x);
	void SetRotateY(FLOAT y);
	void SetRotateZ(FLOAT z);
	void SetTranslate(XMFLOAT3 trans);


public:
	XMFLOAT3& GetPosition() { return mCurrentPos; }
	XMFLOAT3& GetRotation() { return mCurrentRot; }
	XMVECTOR GetRight() { return mWorldMat.r[0]; }
	XMVECTOR GetUp() { return mWorldMat.r[1]; }
	XMVECTOR GetLook() { return mWorldMat.r[2]; }
public:
	XMMATRIX GetWorldMat() {return mWorldMat; }


private:

	XMFLOAT3 mCurrentPos;
	XMFLOAT3 mCurrentRot;
	XMFLOAT3 mCurrentScale;

	XMMATRIX mScaleMat;
	XMMATRIX mRotateMat;

	XMMATRIX mRotateXMat;
	XMMATRIX mRotateYMat;
	XMMATRIX mRotateZMat;


	XMMATRIX mTranslateMat;



	XMMATRIX mLocalMat;
	XMMATRIX mWorldMat;

};

