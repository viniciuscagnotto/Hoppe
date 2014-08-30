#ifndef __CORE_H__
#define __CORE_H__

//Typedefs
typedef unsigned int uint;

//Iw API - Marmelade
#include "IwGx.h"
#include "Iw2D.h"
#include "Iw2DSceneGraph.h"
#include "IwTween.h"
#include "IwHashString.h"
#include "IwSound.h"

using namespace IwTween;
using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;


//s3e API - Marmelade
#include "s3e.h"
#include "s3eFlurry.h"

//C++
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <time.h>

//utils
#include "utils.h"
#include "easyArray.h"

//managers
#include "csvCommands.h"
#include "savedataManager.h"
#include "resourceManager.h"
#include "spriteManager.h"
#include "parallaxManager.h"
#include "inputManager.h"
#include "audioManager.h"
#include "timerManager.h"

#endif //__CORE_H__