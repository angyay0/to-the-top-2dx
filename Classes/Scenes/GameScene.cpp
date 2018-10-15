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
    
    GOPosition movementAccelInitialCero;
    movementAccelInitialCero.xVal = 1.22;
    movementAccelInitialCero.yVal = 0.22;
    movementAccelInitialCero.zVal = 1.51;
    
    //Board Instance and Configuration
    this->boardObject = new GameObject();
    this->boardObject->initWith("plank_base.png", boardAttributes);
    this->boardObject->getSprite()->setScale(scale);
    Size boardSize = this->boardObject->getSprite()->getContentSize();
    boardSize.width = viewPort.width*0.95;
    this->boardObject->getSprite()->setContentSize(boardSize);
    //Position board
    GOPosition boardPosition;
    boardPosition.xVal = viewPort.width/2 + (viewPort.width - boardSize.width) + boardOffset;
    boardPosition.yVal = origin.y + (boardSize.height*2);
    this->boardObject->setInitialPosition(boardPosition);
    this->boardObject->movement = movementAccelInitialCero;
    
    //Add To View
    this->addChild(this->boardObject->getSprite(),PLAYABLE_OBJECTS_LAYER);
    
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
        CCLOG("x: %.5f, y: %.5f, z: %.5f",accelMovement.xVal,accelMovement.yVal,accelMovement.zVal);
    }
}

void GameScene::update(float dt) {
    this->boardObject->move();
    
    //MoveParallax Fake Sprites
    Point bgPSpeed = this->parallax->getPointSpeed();
    auto viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto first = this->getChildByTag(STANDALONE_PARALLAX_SPRITE_1);
    auto second = this->getChildByTag(STANDALONE_PARALLAX_SPRITE_2);
    
    first->setPosition( first->getPosition().x,first->getPosition().y - bgPSpeed.getLength() );
    second->setPosition( second->getPosition().x,second->getPosition().y - bgPSpeed.getLength() );
    
    if( first->getPosition().y <= -(viewPort.height/2) ){
        first->setPosition(first->getPosition().x, second->getPosition().y + viewPort.height);
    }
    
    if( second->getPosition().y <= -(viewPort.height/2) ){
        second->setPosition(second->getPosition().x,first->getPosition().y + viewPort.height);
    }
}
