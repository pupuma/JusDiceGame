#pragma once

#pragma warning(disable:4996)

// 시스템 헤더
#include <Windows.h>
#include <assert.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <queue>
#include <stack>
//using std::string;
//using std::vector;
//using std::list;
//using std::map;




// 사용자 정의 헤더

#include "MacroDefine.h" 
#include "CustomDefine.h"
#include "Util.h"
#include "commonMacroFunction.h"
#include "CollisionFunction.h"
#include "RandomFunction.h"
#include "GameNode.h"
#include "Camera.h"
#include "Image.h"
#include "StateType.h"


// 사용자 정의 매니저

#include "KeyManager.h"
#include "TimeManager.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "GameSystem.h"
#include "StateManager.h"
#include "TimeCheck.h"
#include "FontManager.h"
#include "DiceManager.h"


