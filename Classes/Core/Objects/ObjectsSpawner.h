//
//  ObjectsSpawner.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#ifndef ObjectsSpawner_h
#define ObjectsSpawner_h

#include <stdio.h>
#include "cocos2d.h"
#include "Constants.h"
#include "GameObject.h"
#include "Player.h"

USING_NS_CC;

struct SpawnerControl {
	bool isBoardSpawned = false;
	bool isPlayerSpawned = false;
	bool isLevelMapped = false;
	bool isLevelCreated = false;
    bool drawAnchor = COW_DEBUG_MODE?true:false;//default activated
};

class ObjectsSpawner {
private:
	ObjectsSpawner(){};
	ObjectsSpawner(ObjectsSpawner const&){};
	ObjectsSpawner& operator = (ObjectsSpawner const&){};
	static ObjectsSpawner *instance;
	struct GameSkin skin;
	struct SpawnerControl control;
    struct GOPosition zero;
    Size viewPort;
    Vec2 viewOrigin;
    float scale;
    GameObject *spawnMapItem(int type,GOPosition refPosition,float offset);
public:
	static ObjectsSpawner *getInstance(struct GameSkin gameSkin,Size viewPort,Vec2 origin,float scale);
    static ObjectsSpawner *getInstance();
	struct SpawnerControl isProcessCompleted();
	GameObject *spawnBoardObject();//One
    Player *spawnPlayer(Size boardSize,GOPosition boardPosition,float offset);//One
    GameObject **spawnLevel(int level,GAME_DIFFICULTY dif,PlayerHability hab,GOPosition refPos,float verticalOffset,float horizontalOffset);//Many
    //Vector<GameObject*> spawnPowerups();
    //Vector<GameObject*> spawnEnemies();
    void resetLevel();
    void resetPlayer();
};
#endif
