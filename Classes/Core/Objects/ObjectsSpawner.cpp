//
//  ObjectsSpawner.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "ObjectsSpawner.h"

ObjectsSpawner *ObjectsSpaner::instance = NULL;

ObjectsSpawner *ObjectsSpawner::getInstance(struc GameSkin skin) {
    if (!instance) {
        instance = new ObjectsSpawner;
    }

    this->skin = skin;

    return instance;
}
