//
//  ObjectsSpawner.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "ObjectsSpawner.h"

ObjectsSpawner *ObjectsSpawner::instance = NULL;

ObjectsSpawner *ObjectsSpawner::getInstance(struct GameSkin skin) {
    if (!instance) {
        instance = new ObjectsSpawner;
    }
    instance->skin = skin;
    
    return instance;
}
