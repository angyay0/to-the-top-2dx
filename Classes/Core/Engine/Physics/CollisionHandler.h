//
//  CollisionHandler.h
//  3TGame
//
//  Created by Eduardo Pérez on 11/10/18.
//

#ifndef CollisionHandler_h
#define CollisionHandler_h

#include "cocos2d.h"
#include "GameObject.h"
#include "Player.h"

//Collision Mask
#define OBJECT_COLLISION_MASK 0x00
#define PLAYER_COLLISION_MASK 0x01

USING_NS_CC;

struct CollisionResults {
    
};

class CollisionHandler {
private:
    CollisionHandler(){};
    CollisionHandler(CollisionHandler const&){};
    CollisionHandler& operator = (CollisionHandler const&){};
    static CollisionHandler *instance;
public:
    static CollisionHandler *getInstance();
    void checkCollisionForPlayer(Player *player,const Vector<GameObject*> objectsInScene);
    void checkCollisionForObject(GameObject *mainObject,const Vector<GameObject*> objectsInScene);
    void checkCollisionAndRemoveNodes(Sprite *mainObject,Layer *container,const Vector<GameObject*> objectsInScene);
};

#endif /* CollisionHandler_h */
