#pragma once
// Windows ��� ����


#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <iostream>
#include <fstream>


#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXMath.h>

#include <wrl.h>
#include "d3dx11effect.h"
#include "DirectXTex.h"
#include "Struct.h"
#include "Define.h"
#include "DirectXTex.inl"





using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;
using namespace std;






#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "d3dcompiler")
#ifdef _DEBUG
#pragma comment(lib,"Effects11d.lib")
#pragma comment(lib,"DirectXTexd.lib")
#else
#pragma comment(lib,"Effects11.lib")
#pragma comment(lib, "DirectXTex\\DirectXTex.lib")
#endif

extern unique_ptr<class GameEngine> GEngine;