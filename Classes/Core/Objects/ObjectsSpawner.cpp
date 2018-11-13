//
//  ObjectsSpawner.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "ObjectsSpawner.h"
#include "CollisionHandler.h"
#include "Toolkit.h"
#include <stdio.h>

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
    if (!this->control.isBoardSpawned) {
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
        board->setExtras(1, this->control.drawAnchor, boardSize, Vec2(0.5,0.5));
        
        //Physics Configuration
        board->getSprite()->getPhysicsBody()->setContactTestBitmask(PLAYER_EXTRA_COLLISION_MASK);
        board->getSprite()->getPhysicsBody()->setCollisionBitmask(PLAYER_EXTRA_COLLISION_MASK);
        board->getSprite()->getPhysicsBody()->setCategoryBitmask(PLAYABLE_OBJECT);
        board->getSprite()->getPhysicsBody()->setMass(100);
        board->getSprite()->setTag(PLAYER_EXTRA_TAG);
        board->setInitialPosition(boardPosition);
        board->movement = zero;
        
        
        this->control.isBoardSpawned = true;
        return board;
    }
    
    return nullptr;
}

Player *ObjectsSpawner::spawnPlayer(Size boardSize,GOPosition boardPosition,float offset,Player *oldData,bool centered) {
    if(!this->control.isPlayerSpawned) {
        GOAttributes playerAttributes;
        playerAttributes.name = "Ball";
        playerAttributes.points = 0;
        playerAttributes.isAlive = true;
        playerAttributes.isPlayable = true;
        playerAttributes.isCollidable = true;
        playerAttributes.canInteract = true;
        playerAttributes.canMove = true;
        playerAttributes.hasSpecialAttributes = true;
        
        GOSAttributes playerSpecialAttributes;
        playerSpecialAttributes.materialType = 1;
        playerSpecialAttributes.resistance = 1.20;
        playerSpecialAttributes.health = 1.05;
        
        GOPosition playerPosition;
        playerPosition.xVal = (!centered)?this->viewOrigin.x:(this->viewOrigin.x+this->viewPort.width/2);
        playerPosition.yVal = boardPosition.yVal + boardSize.height + offset;
        
        auto spriteCache = SpriteFrameCache::getInstance();
        Vector<SpriteFrame*> spriteAnim;
        spriteAnim.pushBack(spriteCache->getSpriteFrameByName("player1.png"));
        spriteAnim.pushBack(spriteCache->getSpriteFrameByName("player2.png"));
        spriteAnim.pushBack(spriteCache->getSpriteFrameByName("player3.png"));
        Animation *anim = Animation::createWithSpriteFrames(spriteAnim, 0.07f);
        
        Player *player = new Player();
        player->initWith(SpriteFrameCache::getInstance()->getSpriteFrameByName("player1.png"), playerAttributes,2);
        player->setExtras(0.5, this->control.drawAnchor, player->getSprite()->getContentSize(), Vec2(0.5,0.5));
        player->getSprite()->runAction(RepeatForever::create(Animate::create(anim)));
        player->setSpecialAttributes(playerSpecialAttributes);
        player->setInitialPosition(playerPosition);
        player->setDefaults();
        
        //Physics Configuration
        player->getSprite()->getPhysicsBody()->setContactTestBitmask(PLAYER_COLLISION_MASK);
        player->getSprite()->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_MASK);
        player->getSprite()->getPhysicsBody()->setCategoryBitmask(PLAYABLE_OBJECT);
        player->getSprite()->getPhysicsBody()->setGravityEnable(true);
        player->getSprite()->getPhysicsBody()->setDynamic(true);
        player->getSprite()->getPhysicsBody()->setMass(500);//TBD
        player->getSprite()->setTag(PLAYER_TAG);
        
        if (oldData != nullptr) { //It Means Copy all Data; Pending if more required
            player->setLives(oldData->getLives());
            player->setScore(oldData->getScore());
            player->setDistance(oldData->getDistance());
        }
        
        this->control.isPlayerSpawned = true;
        return player;
    }
    
    return nullptr;
}

GameObject* ObjectsSpawner::spawnMapObject(int type, GOPosition refPosition,float offset) {
    SpriteFrameCache *sprites = SpriteFrameCache::getInstance();
    GameObject *object = new GameObject();
    PhysicsBody *spBody;
    
    if (!this->control.isLevelCreated){
        switch (type) {
            case BLOCK_ITEM_MASK:
                object->initWith(sprites->getSpriteFrameByName("block1.png"),object->getBlockBaseAttributes());
                break;
            case STGCL_ITEM_MASK:
                object->initWith(sprites->getSpriteFrameByName("bonusbox.png"),object->getBlockBaseAttributes());
                break;
            case TRAP_ITEM_MASK:
                object->initWith(sprites->getSpriteFrameByName("spikes.png"),object->getBlockBaseAttributes());
                break;
            default:
                break;
        }
        
        spBody = object->getSprite()->getPhysicsBody();
        spBody->setContactTestBitmask(BLOCK_ITEM_MASK);
        spBody->setCollisionBitmask(BLOCK_ITEM_MASK);
        spBody->setCategoryBitmask(PLAYABLE_OBJECT);
        
        GOPosition pos;
        pos.xVal = refPosition.xVal + object->getSprite()->getContentSize().width + offset;
        pos.yVal = refPosition.yVal; pos.zVal = refPosition.zVal;
        
        object->setInitialPosition(pos);
       // object->getSprite()->setPhysicsBody(spBody);
        object->getSprite()->setTag(type);
        object->setExtras(1, this->control.drawAnchor, object->getSprite()->getContentSize(), Vec2(0.5,0.5));
    }
    return object;
}

void ObjectsSpawner::setLevelCreated(bool value){
    this->control.isLevelMapped = value;
    this->control.isLevelCreated = value;
}

void ObjectsSpawner::resetLevel() {
    this->control.isBoardSpawned = false;
    this->control.isPlayerSpawned = false;
    this->control.isLevelMapped = false;
    this->control.isLevelCreated = false;
    this->control.drawAnchor = true;
}

void ObjectsSpawner::resetPlayer() {
    this->control.isPlayerSpawned = false;
}
