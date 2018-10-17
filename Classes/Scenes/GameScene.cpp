//
//  GameScene.cpp
//  3TGame
//
//  Created by Eduardo Pérez on 11/10/18.
//
// Base Block 96x946

#include "GameScene.h"
#include "MovementProtocols.h"
#include "CollisionHandler.h"
#include "ObjectsSpawner.h"
#include "GameHUD.h"

Scene *GameScene::createScene(){
    auto scene =  GameScene::create();
    if (COW_DEBUG_MODE) {
        scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
        scene->getPhysicsWorld()->setGravity(Vec2(0,-98));
    }
    return scene;
}

bool GameScene::init() {
    if(!Scene::initWithPhysics()) {
        return false;
    }
    return this->createGameScene();
}

bool GameScene::createGameScene() {
    Size viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float scale = Director::getInstance()->getContentScaleFactor() / 2.0;
    float boardOffset = 10;//Offset for left, rigth and bottom
    
    GameSkin skin;
    skin.spritesFile = "sprites.plist";
    ObjectsSpawner *spawner = ObjectsSpawner::getInstance(skin,viewPort,origin,scale);
    
    /*
    
    GOAttributes boardAttributes;
    boardAttributes.name = "Board";
    boardAttributes.isCollidable = true;
    boardAttributes.canMove = true;
    boardAttributes.movementType = 2;*/
    
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
    /*
    GOPosition movementAccelInitialZero;
    movementAccelInitialZero.xVal = 1.22;
    movementAccelInitialZero.yVal = 0.22;
    movementAccelInitialZero.zVal = 1.51;
    
    //Board Instance and Configuration
    this->boardObject = new GameObject();
    this->boardObject->initWith("plank_base.png", boardAttributes, -1, 10);
    //this->boardObject->getSprite()->setScale(scale);
    Size boardSize = this->boardObject->getSprite()->getContentSize();
    boardSize.width = viewPort.width*0.95;
    this->boardObject->setExtras(scale, true, boardSize, Vec2(0.43,0.5));
    this->boardObject->getSprite()->getPhysicsBody()->setCollisionBitmask(PLAYER_EXTRA_COLLISION_MASK);
    this->boardObject->getSprite()->getPhysicsBody()->setCategoryBitmask(PLAYABLE_OBJECT);
    
    //Position board
    GOPosition boardPosition;
    boardPosition.xVal = origin.x + viewPort.width/2;
    boardPosition.yVal = origin.y + (boardSize.height*2);
    this->boardObject->setInitialPosition(boardPosition);
    this->boardObject->movement = movementAccelInitialZero;*/
    //Board
    this->boardObject = spawner->spawnBoardObject();
    
    //Player
    auto spriteCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> spriteAnim;
    spriteAnim.pushBack(spriteCache->getSpriteFrameByName("player1.png"));
    spriteAnim.pushBack(spriteCache->getSpriteFrameByName("player2.png"));
    spriteAnim.pushBack(spriteCache->getSpriteFrameByName("player3.png"));
    Animation *anim = Animation::createWithSpriteFrames(spriteAnim, 0.08f);
    
    //spriteCache->addSpriteFramesWithFile("sprites.plist");*/
    this->player = new Player();
    this->player->initWith(spriteCache->getSpriteFrameByName("player1.png"), playerAttributes,2);
    this->player->setSpecialAttributes(playerSpecialAttributes);
    this->player->setExtras(0.5, true, this->player->getSprite()->getContentSize(), Vec2(0.5,0.5));
    this->player->setDefaults();
    //Position Player
    Size boardSize = this->boardObject->getSprite()->getContentSize();
    GOPosition boardPosition = this->boardObject->getPosition();
    GOPosition playerPosition;
    playerPosition.xVal = origin.x + viewPort.width/2;
    playerPosition.yVal = boardPosition.yVal + boardSize.height + (boardOffset*2);
    this->player->setInitialPosition(playerPosition);
    this->player->getSprite()->runAction(RepeatForever::create(Animate::create(anim)));
    this->player->getSprite()->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_MASK);
    this->player->getSprite()->getPhysicsBody()->setCategoryBitmask(PLAYABLE_OBJECT);
    this->player->getSprite()->getPhysicsBody()->setGravityEnable(true);
    this->player->getSprite()->getPhysicsBody()->setDynamic(true);
    this->player->getSprite()->getPhysicsBody()->setMass(100);
    
    
    Size playerSize = this->player->getSprite()->getContentSize();
    CCLOG("w: %.3f,h: %.3f",playerSize.width,playerSize.height);
    
    //Add To View
    this->addChild(this->boardObject->getSprite(),PLAYABLE_OBJECTS_LAYER);
    this->addChild(this->player->getSprite(),PLAYABLE_OBJECTS_LAYER);
    
    //Parallax Layer
    this->parallax = ParallaxLayer::create();
    this->parallax->setupMovementFactor(0.05, 0.05, 2.0, 10.0, 50.0, viewPort.height, VERTICAL_MOVEMENT);
    
    //Parallax Nodes
    Sprite *bg = Sprite::create("bg.jpg");
    Sprite *bgp = Sprite::create("bg.jpg");
    bg->setScale(viewPort.width/bg->getContentSize().width * 1.0f,
                 viewPort.height/bg->getContentSize().height * 1.0f );
    bgp->setScale(viewPort.width/bgp->getContentSize().width * 1.0f,
                  viewPort.height/bgp->getContentSize().height * 1.0f );
    bg->setPosition(origin.x + viewPort.width/2,origin.y + viewPort.height/2);
    bgp->setPosition(origin.x + viewPort.width/2,bg->getPosition().y+viewPort.height);
    bg->setTag(STANDALONE_PARALLAX_SPRITE_1);
    bgp->setTag(STANDALONE_PARALLAX_SPRITE_2);
    
    this->addChild(bg, PARALLAX_LAYER);
    this->addChild(bgp, PARALLAX_LAYER);
    
    //GameHUD
    GameHUD *hud = GameHUD::create();
    hud->setupInteractions(this);
    
    this->addChild(hud, HUD_LAYER);
    
    //Update and Accelerometer
    EventListenerAcceleration *listener = EventListenerAcceleration::create(CC_CALLBACK_2(GameScene::onAcceleration, this));
    Device::setAccelerometerEnabled(true);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    this->scheduleUpdate();
    
    return true;
}

void GameScene::onAcceleration(Acceleration *acc, Event *event) {
    float KACCELMAXPOINTSPERSEC = 1;
    float threshold = 0.2;
    double rollingX,rollingY,rollingZ;
    
   // float temp = acc->y;
    //acc->x = -acc->x;
   // acc->x = temp;
    //acc->y = temp;
    
    rollingX = (acc->x * KFILTERINGFACTOR); //+ ( (1.0 - KFILTERINGFACTOR));
    rollingY = (acc->z * KFILTERINGFACTOR);
    rollingZ = (acc->y * KFILTERINGFACTOR);
    float accelX = acc->x - rollingX;
    float accelY = acc->z - rollingY;
    float accelZ = acc->y - rollingZ;
    float accelDiff = accelX - KRESTACCELX;
    float accelDiffW = accelY - KRESTACCELY;
    float accelDiffZ = accelZ - KRESTACCELZ;
    
    float accelFraction = accelDiff / KMAXDIFFX;
    float accelYFraction = accelDiffW / KMAXDIFFX;
    float accelZFraction = accelDiffZ / KMAXDIFFX;
    
    accelFraction = accelFraction < 0? accelFraction*KADJUSTSIDE: accelFraction;
    accelYFraction = accelYFraction < 0? accelYFraction*KADJUSTSIDE: accelYFraction;
    accelZFraction = accelZFraction < 0? accelZFraction*KADJUSTSIDE: accelZFraction;
    
    GOPosition accelMovement;
    accelMovement.xVal = accelFraction * KACCELMAXPOINTSPERSEC;
    accelMovement.yVal = accelYFraction * KACCELMAXPOINTSPERSEC;
    accelMovement.zVal = accelZFraction;
    
    GOPosition oldAccel = this->boardObject->movement;
    
    if (accelMovement.xVal < (oldAccel.xVal-threshold) || accelMovement.xVal > (oldAccel.xVal+threshold)){
        //Send Acceleromenter data to Board
        this->boardObject->movement = accelMovement;
        this->player->movement = accelMovement;
        CCLOG("x: %.5f, y: %.5f, z: %.5f",accelMovement.xVal,accelMovement.yVal,accelMovement.zVal);
    }
}

void GameScene::onHUDItemClickedCallback(cocos2d::Ref *pSender) {
    switch (((MenuItem*) pSender)->getTag()) {
        case PAUSE_TAG:
            CCLOG("PAUSE TAG");
            break;
    }
}

void GameScene::update(float dt) {
    auto viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //Move Board
    this->boardObject->move();
    
    //Move Player depending On Board
    auto playerChild = this->getChildByTag(PLAYER_TAG);
   /* GOPosition accel = this->player->movement;
    float pXVal = sqrtf(accel.xVal*accel.xVal);
    float pYVal = sqrtf(accel.yVal*accel.yVal);
    float newXPosition = playerChild->getPosition().x - pXVal;
    float newYPosition = playerChild->getPosition().y - pYVal;*/
    if (playerChild->getPosition().y < origin.y) {
        playerChild->setPosition(Vec2(origin.x+viewPort.width/2,origin.y+viewPort.height/2));
    }
    
    //MoveParallax Fake Sprites
    Point bgPSpeed = this->parallax->getPointSpeed();
    auto first = this->getChildByTag(STANDALONE_PARALLAX_SPRITE_1);
    auto second = this->getChildByTag(STANDALONE_PARALLAX_SPRITE_2);
    
    first->setPosition( first->getPosition().x,first->getPosition().y - sqrtf(0.5*0.5 + 0.5*0.5) );
    second->setPosition( second->getPosition().x,second->getPosition().y - sqrtf(0.5*0.5 + 0.5*0.5) );
    
    if( first->getPosition().y <= -(viewPort.height/2) ){
        first->setPosition(first->getPosition().x, second->getPosition().y + viewPort.height);
    }
    
    if( second->getPosition().y <= -(viewPort.height/2) ){
        second->setPosition(second->getPosition().x,first->getPosition().y + viewPort.height);
    }
}
