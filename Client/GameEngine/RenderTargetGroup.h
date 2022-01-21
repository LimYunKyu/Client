#pragma once

#include "Texture.h"

enum class RENDER_TARGET_GROUP_TYPE : UINT8
{
	SWAP_CHAIN, // BACK_BUFFER, FRONT_BUFFER
	G_BUFFER, // POSITION, NORMAL, COLOR
	END,
};

enum
{
	RENDER_TARGET_G_BUFFER_GROUP_MEMBER_COUNT = 3,
	RENDER_TARGET_GROUP_COUNT = static_cast<UINT8>(RENDER_TARGET_GROUP_TYPE::END)
};

struct RenderTarget
{
	shared_ptr<Texture> target;
	float clearColor[4];
};

class RenderTargetGroup
{
public:
	void Create(RENDER_TARGET_GROUP_TYPE groupType, vector<RenderTarget>& rtVec, shared_ptr<Texture> dsTexture);

	
	void OMSetRenderTargets();
	void ClearRenderTargetView();

	shared_ptr<Texture> GetRTTexture(UINT32 index) { return _rtVec[index].target; }
	shared_ptr<Texture> GetDSTexture() { return _dsTexture; }
	

private:
	RENDER_TARGET_GROUP_TYPE		_groupType;
	vector<RenderTarget>			_rtVec;
	vector<ID3D11RenderTargetView*> _rtvVec;
	vector<ID3D11ShaderResourceView*> _srvVec;
	ID3D11RenderTargetView* _srcArray[3];
	UINT32							_rtCount;
	shared_ptr<Texture>				_dsTexture;

};

