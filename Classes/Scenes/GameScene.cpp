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
#include "Toolkit.h"
#include "GameHUD.h"

Scene *GameScene::createScene(){
    auto scene =  GameScene::create();
    scene->getPhysicsWorld()->setGravity(Vec2(0,-980));
    
    if (COW_DEBUG_MODE) {
        scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    SpriteFrameCache *cache = SpriteFrameCache::getInstance();
    
    //Board
    this->boardObject = spawner->spawnBoardObject();
    this->player = spawner->spawnPlayer(this->boardObject->getSprite()->getContentSize(), this->boardObject->getPosition(),(boardOffset*2));
    
    //Add To View
    this->addChild(this->boardObject->getSprite(),PLAYABLE_OBJECTS_LAYER);
    this->addChild(this->player->getSprite(),PLAYABLE_OBJECTS_LAYER);
    
    // Level Map
    PlayerHability hab;
    int** byteLevelMap = Toolkit::getInstance()->getLevelMap(1,GAME_DIFFICULTY::_EASY,hab);
    //int spaces = Toolkit::getInstance()->countSpacesInMap(byteLevelMap);
    int height = sizeof(byteLevelMap);
    int count = 0;
    GOPosition pos = this->player->getPosition();
    pos.xVal = origin.x + boardOffset;
    GOPosition newRefPos;
    newRefPos.xVal = pos.xVal;
    newRefPos.yVal = pos.yVal;
    newRefPos.zVal = pos.zVal;
    
    Sprite **sprites = new Sprite*[2];
    sprites[0] = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("block1.png"));
    sprites[1] = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("bonusbox.png"));
    PhysicsBody *body1 = PhysicsBody::createEdgeBox(sprites[0]->getContentSize());
    PhysicsBody *body2 = PhysicsBody::createEdgeBox(sprites[1]->getContentSize());
    body1->setDynamic(false); body2->setDynamic(false);
    body1->setCollisionBitmask(OBJECT_COLLISION_MASK);
    body2->setCollisionBitmask(OBJECT_COLLISION_MASK);
    body1->setCategoryBitmask(STATIC_OBJECT);
    body2->setCategoryBitmask(STATIC_OBJECT);
    sprites[0]->addComponent(body1); sprites[1]->addComponent(body2);
    
    
    for(int i=0;i<height;i++) {
        for(int j=0;j<LEVEL_BASE_WIDTH;j++) {
            int byteMap = byteLevelMap[i][j];
            if (byteMap != SPACE_ITEM_MASK ) {
                
                count++;
            }
        }
        newRefPos.xVal = boardOffset;
        newRefPos.yVal = newRefPos.yVal + (boardOffset * 3.f);
    }
    
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
