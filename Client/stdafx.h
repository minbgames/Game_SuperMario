// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <ctime>
#include <iostream>
#include <io.h>


using namespace std;

#include <vld.h>

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")


// FMOD
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")

//#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")

#include "Define.h"
#include "Typedef.h"
#include "Enum.h"
#include "Extern.h"
#include "Struct.h"
#include "Function.h"
#include "Macro.h"
#include "Ballence.h"

// Managers
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "ObjectMgr.h"
#include "MathMgr.h"
#include "CollisionMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ObstacleMgr.h"
#include "PathMgr.h"
#include "PanelMgr.h"
#include "SoundMgr.h"

#define KEY_PRESSING(key) CKeyMgr::GetInstance()->KeyPressing(key)
#define KEY_DOWN(key) CKeyMgr::GetInstance()->KeyDown(key)
#define KEY_UP(key) CKeyMgr::GetInstance()->KeyUp(key)
