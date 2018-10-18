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
public:
	static ObjectsSpawner *getInstance(struct GameSkin gameSkin,Size viewPort,Vec2 origin,float scale);
    static ObjectsSpawner *getInstance();
	struct SpawnerControl isProcessCompleted();
	GameObject *spawnBoardObject();
    Player *spawnPlayer(Size boardSize,GOPosition boardPosition,float offset);
    Vector<GameObject*> spawnLevel();
    Vector<GameObject*> spawnPowerups();
    Vector<GameObject*> spawnEnemies();
    void resetLevel();
    void resetPlayer();
};
#endif
