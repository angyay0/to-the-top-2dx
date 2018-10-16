//
//  ObjectsSpawner.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#ifndef ObjectsSpawner_h
#define ObjectsSpawner_h

#include <stdio.h>
#include "Constants.h"
#include "GameObject.h"
#include "Player.h"

struct SpawnerControl {
	bool isBoardSpawned = false;
	bool isPlayerSpawned = false;
	bool isLevelMapped = false;
	bool isLevelCreated = false;
};

class ObjectsSpawner {
private:
	ObjectsSpawner(){};
	ObjectsSpawner(ObjectsSpawner const&){};
	ObjectsSpawner& operator = (ObjectsSpawner const&){};
	static ObjectsSpawner *instance;
	struct GameSkin skin;
	struct SpawnerControl control;
public:
	static ObjectsSpawner *getInstance(struct GameSkin gameSkin){};
	struct SpawnerControl isProcessCompleted();
	GameObject *spawnBoardObject();
};
#endif