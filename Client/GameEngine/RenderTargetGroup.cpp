#include "pch.h"
#include "RenderTargetGroup.h"
#include "GameEngine.h"


void RenderTargetGroup::Create(RENDER_TARGET_GROUP_TYPE groupType, vector<RenderTarget>& rtVec, shared_ptr<Texture> dsTexture)
{
	_groupType = groupType;
	_rtVec = rtVec;
	_rtCount = static_cast<UINT32>(rtVec.size());
	_dsTexture = dsTexture;

	for (int i = 0; i < _rtCount; i++)
	{
		_rtvVec.push_back(_rtVec[i].target->GetRTV());
		_srcArray[i] = _rtVec[i].target->GetRTV();
	}
}



void RenderTargetGroup::OMSetRenderTargets()
{
	if (_groupType == RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)
	{
		ID3D11RenderTargetView* rtv = _rtVec[0].target->GetRTV();
		GEngine->GetDeviceContext()->OMSetRenderTargets(1, &rtv, _dsTexture->GetDSV());
	}
	else
	{
		
		GEngine->GetDeviceContext()->OMSetRenderTargets(_rtCount, _srcArray, _dsTexture->GetDSV());
	}
	//GEngine->GetDeviceContext()->ClearDepthStencilView(_dsTexture->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}


void RenderTargetGroup::ClearRenderTargetView()
{

	if (_groupType == RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)
	{
		ID3D11RenderTargetView* rtv = _rtVec[0].target->GetRTV();
		GEngine->GetDeviceContext()->ClearRenderTargetView(rtv, reinterpret_cast<const float*>(&Colors::AliceBlue));
	}
	else
	{
		for (int i = 0; i < _rtCount; i++)
		{
			ID3D11RenderTargetView* rtv = _rtVec[i].target->GetRTV();
			GEngine->GetDeviceContext()->ClearRenderTargetView(rtv, reinterpret_cast<const float*>(&Colors::Red));
		}
		
	}
	
}
