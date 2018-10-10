//
//  Constants.h
//  ToTheTop
//
//  Created by Eduardo Pérez on 09/10/18.
//

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

//MovementConstants
#define PLAYER_MAX_SPEED 10

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

