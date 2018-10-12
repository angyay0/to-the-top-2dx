//
//  GameScene.cpp
//  3TGame
//
//  Created by Eduardo Pérez on 11/10/18.
//

#include "GameScene.h"
#include "MovementProtocols.h"

Scene *GameScene::createScene(){
    return GameScene::create();
}

bool GameScene::init() {
    if(!Scene::init()) {
        return false;
    }
    return this->createGameScene();
}

bool GameScene::createGameScene() {
    Size viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float scale = Director::getInstance()->getContentScaleFactor() / 2.0;
    
    float boardOffset = 10;//Offset for left, rigth and bottom
    
    GOAttributes boardAttributes;
    boardAttributes.name = "Board";
    boardAttributes.isCollidable = true;
    boardAttributes.canMove = true;
    boardAttributes.movementType = 2;
    
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
    
    //Board Instance and Configuration
    this->boardObject = new GameObject();
    this->boardObject->initWith("plank_base.png", boardAttributes);
    this->boardObject->getSprite()->setScale(scale);
    Size boardSize = this->boardObject->getSprite()->getContentSize();
    boardSize.width = viewPort.width*0.9;
    this->boardObject->getSprite()->setContentSize(boardSize);
    //Position board
    GOPosition boardPosition;
    boardPosition.xVal = origin.x + boardOffset;
    boardPosition.yVal = origin.y + this->boardObject->getSprite()->getContentSize().height + (boardOffset*2);
    this->boardObject->setInitialPosition(boardPosition);
    
    //Add To View
    this->addChild(this->boardObject->getSprite(),PLAYABLE_OBJECTS_LAYER);
    
    //Update and Accelerometer
    EventListenerAcceleration *listener = EventListenerAcceleration::create(CC_CALLBACK_2(GameScene::onAcceleration, this));
    Device::setAccelerometerEnabled(true);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    this->scheduleUpdate();
    
    return true;
}

void GameScene::onAcceleration(Acceleration *acc, Event *event) {
    Size winSize = Director::getInstance()->getVisibleSize();
    
    float KACCELMAXPOINTSPERSECY = winSize.height/2;
    float KACCELMAXPOINTSPERSECX = winSize.width/2;
    double rollingX,rollingY,rollingZ;
    
    float temp = acc->z;
    acc->z = acc->x;
    acc->x = acc->y;
    acc->y = temp;
    
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
    accelMovement.xVal = accelFraction;
    accelMovement.yVal = accelYFraction;
    accelMovement.zVal = accelZFraction;
    
    //Send Acceleromenter data to Board
    this->boardObject->movement = accelMovement;
    
}

void GameScene::update(float dt) {
    this->boardObject->move();
}
