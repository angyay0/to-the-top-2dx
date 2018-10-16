//
//  Constants.h
//  ToTheTop
//
//  Created by Eduardo Pérez on 09/10/18.
//

#ifndef Constants_h
#define Constants_h

#include <stdio.h>
#include <string>

//GameHUD Constants
#define PAUSE_TAG 1
#define RESUME_TAG 0

//Interaction Constants
#define PLAY_TAG 1
#define TROPHY_TAG 2
#define HELP_TAG 3
#define CREDITS_TAG 4
#define SHARE_TAG 5
#define HOME_TAG 6
#define BACK_TAG 7

//Scenes and Layer and Child Levels
#define PARALLAX_LAYER 0
#define SCENE_OBJECTS_LAYER 1
#define SCENE_DYNAMIC_OBJECT_LAYER 2
#define PLAYABLE_OBJECTS_LAYER 3
#define FX_LAYER 4
#define HUD_LAYER 5


typedef enum {
    _RUNNING,
    _PAUSED,
    _FINISH
} GAME_STATE;

typedef enum {
    _SINGLEMODE,
    _VSMODE,
    _2VS2MODE,
    _BATTLE
} GAME_MODE;

struct GameSkin {
    std::string boardFile;
    std::string playerFile;
    std::string blockBaseFile;
    std::string blockLowFile;
    std::string blockMidFile;
    std::string blockAdvFile;
    std::string blockProFile;
    std::string powerupsFile;
    std::string invadersFile;
    std::string uiItemsFile;
};

struct GameSound {

};

#endif
