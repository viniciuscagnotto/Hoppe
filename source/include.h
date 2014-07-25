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

//main
#include "main.h"

//utils
#include "utils.h"
#include "easyArray.h"

//managers
#include "savedataManager.h"
#include "resourceManager.h"
#include "spriteManager.h"
#include "parallaxManager.h"
#include "inputManager.h"
#include "audioManager.h"
#include "timerManager.h"
#include "sceneManager.h"
#include "triggersManager.h"

//entities
#include "gameObject.h"
#include "player.h"
#include "vortex.h"
#include "asteroid.h"
#include "comet.h"
#include "satellite.h"
#include "blackHole.h"
#include "star.h"

//scenes
#include "mainMenu.h"
#include "options.h"
#include "store.h"
#include "customize.h"
#include "items.h"
#include "getStars.h"
#include "game.h"