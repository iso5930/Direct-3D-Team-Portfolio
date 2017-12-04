#pragma once

#include <iostream>
using namespace std;

#include <boost/unordered_map.hpp>
using namespace boost;

#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>

#include <Windows.h>
#include <tchar.h>
#include <process.h>
#include <ctime>
#include <fstream>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include <crtdbg.h>
#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif