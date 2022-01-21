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

    void SortGameObject();
    void Render_Deferred();
    void Render_Forward();

    void SetCameraType(PROJECTION_TYPE type) { mProjectionType = type; }
    void SetNear(float val) { _near = val; }
    void SetFar(float val) { _near = val; }
    void SetFov(float val) { _near = val; }
    void SetScale(float val) { _near = val; }
    void SetWidth(float val) { _near = val; }
    void SetHeight(float val) { _near = val; }

    void SetCullingMaskLayerOnOff(UINT8 layer, bool on)
    {
        if (on)
            _cullingMask |= (1 << layer);
        else
            _cullingMask &= ~(1 << layer);
    }


    void SetCullingMaskAll() { SetCullingMask(UINT32_MAX); }
    void SetCullingMask(UINT mask) { _cullingMask = mask; }
    bool IsCulled(UINT8 layer) { return (_cullingMask & (1 << layer)) != 0; }


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
    UINT32 _cullingMask = 0;

private:
    vector<shared_ptr<GameObject>>	_vecDeferred;
    vector<shared_ptr<GameObject>>	_vecForward;
   
};



