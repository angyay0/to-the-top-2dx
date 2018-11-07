//
//  GameScene.cpp
//  3TGame
//
//  Created by Eduardo Pérez on 11/10/18.
//
// Base Block 96x96 => 44x44

#include "GameScene.h"
#include "MovementProtocols.h"
#include "CollisionHandler.h"
#include "ObjectsSpawner.h"
#include "Toolkit.h"
#include "GameHUD.h"

//Constructor Section
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
    
    GameSkin skin;
    skin.spritesFile = "sprites.plist";
    ObjectsSpawner::getInstance(skin,viewPort,origin,scale);
    
    //Create Level Objects
    this->buildLevel();
    
    //Accelerometer Event Handler
    EventListenerAcceleration *accelListener = EventListenerAcceleration::create(CC_CALLBACK_2(GameScene::onAcceleration, this));
    Device::setAccelerometerEnabled(true);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(accelListener, this);
    
    //Collision Event Handler
    EventListenerPhysicsContact *collisionListener = EventListenerPhysicsContact::create();
    collisionListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionListener, this);
    
    //Render Update
    this->scheduleUpdate();
    
    return true;
}

void GameScene::buildLevel() {
    Size viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float boardOffset = 10;//Offset for left, rigth and bottom
    
    this->removeAllChildren();
    ObjectsSpawner *spawner = ObjectsSpawner::getInstance();
    //Parallax Layer
    this->parallaxMap = ParallaxLayer::create();
    this->parallaxMap->setupMovementFactor(0.05, 0.05, 2.0, 10.0, 50.0, viewPort.height, VERTICAL_MOVEMENT);
    this->parallaxMap->setupBehavior(false,true);
    
    //Parallax Nodes Background
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
    
    //Board
    this->boardObject = spawner->spawnBoardObject();
    this->player = spawner->spawnPlayer(this->boardObject->getSprite()->getContentSize(), this->boardObject->getPosition(),(boardOffset*2));
    
    //Add To View
    this->addChild(this->boardObject->getSprite(),PLAYABLE_OBJECTS_LAYER);
    this->addChild(this->player->getSprite(),PLAYABLE_OBJECTS_LAYER);
    
    // Level Map
    PlayerHability hab;
    int** byteLevelMap = Toolkit::getInstance()->getLevelMap(1,GAME_DIFFICULTY::_JAGUAR,hab);
    int height = Toolkit::getInstance()->getActualMapHeight();
    
    GOPosition pos = this->player->getPosition();
    pos.xVal = origin.x - boardOffset;
    GOPosition newRefPos;
    newRefPos.xVal = pos.xVal;
    newRefPos.yVal = pos.yVal + 45.f;
    newRefPos.zVal = pos.zVal;
    
    GameObject *item;
    int byteMap;
    
    for(int i=0;i<height;i++) {
        for(int j=0;j<LEVEL_BASE_WIDTH;j++) {
            byteMap = byteLevelMap[i][j];
            if (byteMap != SPACE_ITEM_MASK) {
                item = spawner->spawnMapObject(byteMap, newRefPos, boardOffset);
                this->addChild(item->getSprite(), PLAYABLE_OBJECTS_LAYER);
            }
            newRefPos.xVal += 48.f;
        }
        newRefPos.xVal = origin.x ;
        newRefPos.yVal = newRefPos.yVal + 100.f;
    }
    
    //GameHUD
    GameHUD *hud = GameHUD::create();
    hud->setupInteractions(this);
    hud->setupPlayer(player);
    
    this->addChild(hud, HUD_LAYER);
}

void GameScene::displayView(int type) {
    //TODO
}

//Listener & Handlers
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
        //CCLOG("x: %.5f, y: %.5f, z: %.5f",accelMovement.xVal,accelMovement.yVal,accelMovement.zVal);
    }
}

bool GameScene::onContactBegin(PhysicsContact &contact) {
    Node *nodeA = contact.getShapeA()->getBody()->getNode();
    Node *nodeB = contact.getShapeB()->getBody()->getNode();
    
    if (nodeA && nodeB) { //Habilita que hay interaccion de dos elementos aka Existe colision
        if (nodeA->getTag() == PLAYER_TAG ) {
            if (nodeB->getTag() != PLAYER_EXTRA_TAG) { //Evita un Contact Solver para la barra
                this->solveCollisionFor(nodeA, nodeB);
            }
        } else if (nodeB->getTag() == PLAYER_TAG) {
            if (nodeA->getTag() != PLAYER_EXTRA_TAG) { //Evita un Contact Solver para la barra
                this->solveCollisionFor(nodeB, nodeA);
            }
        }
    }
    return true;
}

void GameScene::onHUDItemClickedCallback(cocos2d::Ref *pSender) {
    switch (((MenuItem*) pSender)->getTag()) {
        case PAUSE_TAG:
            this->displayView(2);//Pause View
            CCLOG("PAUSE TAG");
            break;
    }
}

//Update Task
void GameScene::update(float dt) {
    auto viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //Move Board
    this->boardObject->move();
    
    //Move Player depending On Board
    auto playerChild = this->getChildByTag(PLAYER_TAG);
    
    if (playerChild->getPosition().y < origin.y) {
        playerChild->setPosition(Vec2(origin.x+viewPort.width/2,origin.y+viewPort.height/2));
        int lives = player->getLives();
        lives--;
        player->setLives(lives);
        if (lives <= 0) {//Display GameOver
            this->displayView(0);//Game Over Scene/View
        }//Continue
    }
    
    //Move Background
    Point bgPSpeed = this->parallaxMap->getPointSpeed();
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
    
    //Move Blocks Layer
    this->moveSpritesBlock(dt);
}

void GameScene::moveSpritesBlock(float dt) {
    auto items = this->getChildren();//Fetching Pending Sprites
    Sprite *tmpSp;
    int tag = 0;
    
    for(int i=0;i<items.size();i++) {
        tmpSp = (Sprite*)items.at(i);
        tag = tmpSp->getTag();
        if (tag == BLOCK_ITEM_MASK || tag == STGCL_ITEM_MASK ||
            tag == TRAP_ITEM_MASK || tag == BONUS_ITEM_MASK ||
            tag == SPIKE_ITEM_MASK || tag == COIN_ITEM_MASK ||
            tag == POWUP_ITEM_MASK) { //If is a block or interactive item
            Vec2 pos = tmpSp->getPosition();
            tmpSp->setPosition(pos.x,pos.y - sqrtf(0.6*0.6 + 0.6*0.6));
            
            if (pos.y < -50 ) { //Elimina el elemento si ya no se ve
                this->removeChild(tmpSp);
            }
        }
    }
}


void GameScene::solveCollisionFor(Node *player,Node *object) {
    switch (object->getTag()) {
        case BLOCK_ITEM_MASK: //Bloque
            CCLOG("Chocaste con algo ups"); //perdera salud y a ver si una vida y puntos
            break;
        case STGCL_ITEM_MASK: //Stage Clear Box
            CCLOG("GANASTE"); //Siguiente Nivel
            break;
        case BONUS_ITEM_MASK: //Bonus item: TODO
            break;
        case COIN_ITEM_MASK: //Coin item: TODO
            break;
        case POWUP_ITEM_MASK: //PowerUp item: TODO
            break;
    }
}
