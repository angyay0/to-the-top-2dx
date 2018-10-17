//
//  ObjectsSpawner.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "ObjectsSpawner.h"
#include "CollisionHandler.h"

ObjectsSpawner *ObjectsSpawner::instance = NULL;

ObjectsSpawner *ObjectsSpawner::getInstance() { //It may cause Crash if not initilized first
    return instance;
}

ObjectsSpawner *ObjectsSpawner::getInstance(struct GameSkin gameSkin, Size viewPort, Vec2 origin, float scale) {
    
    if(!instance){
        instance = new ObjectsSpawner;
    }
    instance->skin = gameSkin;
    instance->zero.xVal = 1.22;
    instance->zero.yVal = 0.22;
    instance->zero.zVal = 1.51;
    instance->viewPort = viewPort;
    instance->viewOrigin = origin;
    instance->scale = scale;
    
    //Initialize SpriteCache for all Sprites in Curren GameSkin
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(instance->skin.spritesFile);
    
    return instance;
}

GameObject *ObjectsSpawner::spawnBoardObject() {
    GOPosition boardPosition;
    GOAttributes boardAttributes;
    boardAttributes.name = "Board";
    boardAttributes.isCollidable = true;
    boardAttributes.canMove = true;
    boardAttributes.movementType = 2;
    
    GameObject *board = new GameObject();
    board->initWith(SpriteFrameCache::getInstance()->getSpriteFrameByName("plank_base.png"), boardAttributes, -1,2);
    board->getSprite()->setScale(scale);
    
    Size boardSize = board->getSprite()->getContentSize();
    boardPosition.xVal = this->viewOrigin.x + boardSize.width/2 + (this->viewPort.width-boardSize.width)/2;
    boardPosition.yVal = this->viewOrigin.y + (boardSize.height*2);
    
    board->setExtras(1, true, boardSize, Vec2(0.5,0.5));
    board->getSprite()->getPhysicsBody()->setCollisionBitmask(PLAYER_EXTRA_COLLISION_MASK);
    board->getSprite()->getPhysicsBody()->setCategoryBitmask(PLAYABLE_OBJECT);
    board->setInitialPosition(boardPosition);
    board->movement = zero;
    
    return board;
}
