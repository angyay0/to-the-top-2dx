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

//Tags for Id in Scene
#define PLAYER_TAG 100
#define PLAYER_EXTRA_TAG 101
#define HUD_TAG 102
#define DYNLAYER_TAG 103

//Scenes and Layer and Child Levels
#define PARALLAX_LAYER 0
#define SCENE_OBJECTS_LAYER 1
#define SCENE_DYNAMIC_OBJECT_LAYER 2
#define PLAYABLE_OBJECTS_LAYER 3
#define FX_LAYER 4
#define HUD_LAYER 5

//Data For Create Levels
#define STGCL_ITEM_MASK 0x01
#define BLOCK_ITEM_MASK 0x03
#define SPACE_ITEM_MASK 0x02
#define BONUS_ITEM_MASK 0x07
#define SPIKE_ITEM_MASK 0x05
#define MIDBLOCK_ITEM_MASK 0x04
#define DECORATION_ITEM_MASK 0x0A
#define COIN_ITEM_MASK 0x8
#define POWUP_ITEM_MASK 0x9
#define TRAP_ITEM_MASK 0x06

#define LEVEL_BASE_WIDTH 9
#define LEVEL_BASE_HEIGHT 9

//Configurations Extra
#define COW_DEBUG_MODE 1


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

typedef enum {
    _EASY = 0x01,
    _NORMAL = 0x03,
    _HARD = 0x09,
    _PRO = 0x0E,
    _QUETZAL = 0x13,
    _JAGUAR = 0x1D
} GAME_DIFFICULTY;

struct PlayerHability {
    bool preferLoseLives;
    bool preferObtainPowerups;
    int preferedBalance;
    float healthInLevel;
};

struct GameSkin {
    std::string spritesFile;
    std::string parallaxFile;
};

struct GameSound {
    std::string menuMusic;
    std::string gameMusic;
};

#endif
