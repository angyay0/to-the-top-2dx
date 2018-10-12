//
//  CollisionHandler.cpp
//  3TGame
//
//  Created by Eduardo Pérez on 11/10/18.
//

#include "CollisionHandler.h"

CollisionHandler *CollisionHandler::instance = NULL;

CollisionHandler *CollisionHandler::getInstance() {
    if (!instance) {
        instance = new CollisionHandler;
    }
    return instance;
}

void CollisionHandler::checkCollisionForPlayer(Player *player, const Vector<GameObject *> objectsInScene) {
    for(GameObject *object : objectsInScene) {
        
    }
}
