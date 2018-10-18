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
        board->getSprite()->getPhysicsBody()->setCollisionBitmask(PLAYER_EXTRA_COLLISION_MASK);
        board->getSprite()->getPhysicsBody()->setCategoryBitmask(PLAYABLE_OBJECT);
        board->getSprite()->getPhysicsBody()->setMass(500);
        board->setInitialPosition(boardPosition);
        board->movement = zero;
        
        
        this->control.isBoardSpawned = true;
        return board;
    }
    
    return nullptr;
}

Player *ObjectsSpawner::spawnPlayer(Size boardSize,GOPosition boardPosition,float offset) {
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
        playerPosition.xVal = this->viewOrigin.x + this->viewPort.width/2;
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
        player->getSprite()->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_MASK);
        player->getSprite()->getPhysicsBody()->setCategoryBitmask(PLAYABLE_OBJECT);
        player->getSprite()->getPhysicsBody()->setGravityEnable(true);
        player->getSprite()->getPhysicsBody()->setDynamic(true);
        player->getSprite()->getPhysicsBody()->setMass(50);//TBD
        
        
        this->control.isPlayerSpawned = true;
        return player;
    }
    
    return nullptr;
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
