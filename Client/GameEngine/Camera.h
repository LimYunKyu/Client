#pragma once
#include "Component.h"
#include "Frustum.h"

enum class PROJECTION_TYPE
{
    PERSPECTIVE,
    ORTHOGRAPHIC,

};


class Camera :public Component
{
public:
    Camera();

public:
    virtual void Initialize();
    virtual void LateInitialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    virtual void Render();

public:
    static XMMATRIX GetViewMatrix() { return ViewMatrix; }
    static XMMATRIX GetProjectionMatrix() { return ProjectionMatrix; }
public:
    PROJECTION_TYPE GetCameraType() { return mProjectionType; }



    void SetCameraType(PROJECTION_TYPE type) { mProjectionType = type; }
    void SetNear(float val) { _near = val; }
    void SetFar(float val) { _near = val; }
    void SetFov(float val) { _near = val; }
    void SetScale(float val) { _near = val; }
    void SetWidth(float val) { _near = val; }
    void SetHeight(float val) { _near = val; }


private:
    float _near = 1.f;
    float _far = 1000.f;
    float _fov = XM_PI / 4.f;
    float _scale = 1.f;
    float _width = 0.f;
    float _height = 0.f;
private:
    XMMATRIX mViewMatrix;
    XMMATRIX mProJectionMatirx;


private:
    static XMMATRIX ViewMatrix;
    static XMMATRIX ProjectionMatrix;

    PROJECTION_TYPE mProjectionType = PROJECTION_TYPE::PERSPECTIVE;
    Frustum _frustum;
};



