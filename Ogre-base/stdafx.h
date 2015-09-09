// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <math.h>

// TODO: reference additional headers your program requires here
#include <OGRE/OgrePlatform.h>

#ifdef _DEBUG
	#pragma comment(lib,"OgreMain_d.lib")
#else
	#pragma comment(lib,"OgreMain.lib")
#endif
