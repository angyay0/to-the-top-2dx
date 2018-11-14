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

//Constructor Section
Scene *GameScene::createScene(){
    auto scene =  GameScene::create();
    scene->getPhysicsWorld()->setGravity(Vec2(0,-980));
    
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
    this->buildLevel(false);
    
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

void GameScene::buildLevel(bool respawn) {
    Size viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float boardOffset = 10;//Offset for left, rigth and bottom
    
    this->isOnRespawnTask = true;
    
    this->removeAllChildren();
    
    ObjectsSpawner *spawner = ObjectsSpawner::getInstance();
    spawner->resetLevel(); //Reinitialize GameCreator
    
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
    
    //if (!respawn) { //Just if is First Live Instantiate new, continue otherwise
        //Board
    this->boardObject = spawner->spawnBoardObject();
    this->player = spawner->spawnPlayer(this->boardObject->getSprite()->getContentSize(), this->boardObject->getPosition(),(boardOffset*2),!respawn?player:nullptr,this->isGameOver);
   // }
    
    //Add To View
    this->addChild(this->boardObject->getSprite(),PLAYABLE_OBJECTS_LAYER);
    this->addChild(this->player->getSprite(),PLAYABLE_OBJECTS_LAYER);
    
    // Level Map
    PlayerHability hab;
    int** byteLevelMap = Toolkit::getInstance()->getLevelMap(1,GAME_DIFFICULTY::_NORMAL,hab);
    int height = Toolkit::getInstance()->getActualMapHeight();
    
    GOPosition pos = this->player->getPosition();
    pos.xVal = origin.x - boardOffset;
    GOPosition newRefPos;
    newRefPos.xVal = pos.xVal;
    newRefPos.yVal = pos.yVal + 48.f;
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
        newRefPos.yVal = newRefPos.yVal + 130.f;
    }
    //Mark As Level Created
    spawner->setLevelCreated(true);
    
    //GameHUD
    this->hud = GameHUD::create();
    hud->setupInteractions(this);
    hud->setupPlayer(player);
    
    this->addChild(hud, HUD_LAYER);
    
   /* if (COW_DEBUG_MODE) {
        this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    }
    */
    if (this->isGameOver) {
        this->isGameOver = false;
    }
   
    this->isOnRespawnTask = false;
}

void GameScene::displayView(DDLayerType type) {
    DynDLayer *layer = DynDLayer::create();
    std::string data[] = {"Hola","Es","Un","Placeholder"};
    layer->setupInteraction(this);
    layer->setupFor(type, data);
    
    this->addChild(layer, HUD_LAYER);
    
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
                this->solveCollisionFor(nodeA, nodeB,this->getCollisionSide(contact.getContactData()->points[0],nodeA,nodeB));
            }
        } else if (nodeB->getTag() == PLAYER_TAG) {
            if (nodeA->getTag() != PLAYER_EXTRA_TAG) { //Evita un Contact Solver para la barra
                this->solveCollisionFor(nodeB, nodeA,this->getCollisionSide(contact.getContactData()->points[0],nodeB,nodeA));
            }
        }
    }
    return true;
}

void GameScene::onHUDItemClickedCallback(cocos2d::Ref *pSender) {
    switch (((MenuItem*) pSender)->getTag()) {
        case PAUSE_TAG:
            this->displayView(DDLayerType::_PauseLayer);//Pause
            this->isPaused = true;
            CCLOG("PAUSE TAG");
            break;
    }
}

void GameScene::onDyItemClickedCallback(Ref *pSender){
    switch (((MenuItem*) pSender)->getTag()) {
        case PLAY_TAG:
        {
            CCLOG("Resume");
            this->removeChild(this->getChildByTag(DYNLAYER_TAG));
            if (this->isPaused) {//More things todo
                this->isPaused = false;
            } else if (this->isGameOver) {//more things todo
                //this->isGameOver = false;
                //this->isPaused = false;
                this->isOnRespawnTask = true;
                this->buildLevel(true);
            }
        }
            break;
        case NEXT_TAG:
            CCLOG("Next Level");
            this->level++;
            player->setLives(player->getLives()+1);
            player->calculateScore(150);
            this->buildLevel(false);
        case HOME_TAG:
            CCLOG("Go Back Home");
            Director::getInstance()->popScene();
            break;
        case HELP_TAG:
            CCLOG("Some item Action");
            break;
        default:
            CCLOG("Not Mapped");
            break;
    }
}

//Update Task
void GameScene::update(float dt) {
    auto viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (!this->isOnRespawnTask && !this->isPaused && !this->isGameOver){
        //Move Board
        this->boardObject->move();
        //Move Player depending On Board
        auto playerChild = this->getChildByTag(PLAYER_TAG);
        
        if (playerChild->getPosition().y < origin.y) { //Falls and lose a live
            int lives = player->getLives();
            lives--;
          
            if (lives <= 0) {//Display GameOver
                this->displayView(DDLayerType::_GameOverLayer);//Game Over Scene/View
                this->isPaused = true;
                this->isGameOver = true;
                CCLOG("Game OVer");
            } else {//Continue
                player->setLives(lives);
                player->resetLiveLose();
                player->setPosition(origin.x+viewPort.width/2,origin.y+viewPort.height/2);
               // playerChild->setPosition(Vec2(origin.x+viewPort.width/2,origin.y+viewPort.height/2));
                this->buildLevel(false);
                return;
            }
        }
        
        if (player->getCurrentHealth() <= 0){ //Lose by Friction and regenerate
            int lives = player->getLives();
            lives--;
            
            if (lives <= 0) {//Display GameOver
                this->displayView(DDLayerType::_GameOverLayer);//Game Over Scene/View
                //this->isPaused = true;
                this->isGameOver = true;
                CCLOG("Game OVer");
            } else {//Continue
                player->setLives(lives);
                player->resetLiveLose();
                player->setPosition(origin.x+viewPort.width/2,origin.y+viewPort.height/2);
                // playerChild->setPosition(Vec2(origin.x+viewPort.width/2,origin.y+viewPort.height/2));
                this->buildLevel(false);
                return;
            }
        }
        
        //Move Background
        auto first = this->getChildByTag(STANDALONE_PARALLAX_SPRITE_1);
        auto second = this->getChildByTag(STANDALONE_PARALLAX_SPRITE_2);
        float parallaxSpeed = sqrtf(0.5*0.5 + 0.5*0.5);
        
        first->setPosition( first->getPosition().x,first->getPosition().y - parallaxSpeed );
        second->setPosition( second->getPosition().x,second->getPosition().y - parallaxSpeed );
        
        if( first->getPosition().y <= -(viewPort.height/2) ){
            first->setPosition(first->getPosition().x, second->getPosition().y + viewPort.height);
            
            this->player->calculateScore(100);//Score Per distance
        }
        
        if( second->getPosition().y <= -(viewPort.height/2) ){
            second->setPosition(second->getPosition().x,first->getPosition().y + viewPort.height);
            
            this->player->calculateScore(100);//Score Per distance
        }
        
        //Move Blocks Layer
        this->moveSpritesBlock(dt);
        
        //Update HUD
        this->hud->updateValues(dt);
    } else {
        GOPosition pos = player->getPosition();
        player->setPosition(pos.xVal, pos.yVal);
    }
}

void GameScene::moveSpritesBlock(float dt) {
    auto items = this->getChildren();//Fetching Pending Sprites
    float blockSpeed = sqrtf(0.25*0.25 + 0.25*0.25);
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
            tmpSp->setPosition(pos.x,pos.y - blockSpeed);
            
            if (pos.y < -50 ) { //Elimina el elemento si ya no se ve
                this->removeChild(tmpSp);
                
                this->player->calculateScore(20);//Score Per Block
            }
        }
    }
}

void GameScene::cleanLevelElements(bool respawn){
    auto items = this->getChildren();//Fetching all elements
    Node *tmpSp;
    int tag = 0;
    
    for(int i=0;i<items.size();i++) { //Iten Cleaner Loop
        tmpSp = items.at(i);
        tag = tmpSp->getTag();
        if (tag != PLAYER_TAG || tag != PLAYER_EXTRA_TAG) { //If isnt player sprites
           this->removeChild(tmpSp);
        }
    }
}

int GameScene::getCollisionSide(Vec2 collisionPos, Node *nodeA, Node *nodeB){
    //Side Detection Algorithm
    //This side detections will be doing a MinMax with nodes position
    //Then it depends on Anchor point to detect sides
    //TODO: Verify if still works when Dynamic Bodies Fly around
    Vec2 bodyAPos = nodeA->getPosition();
    Vec2 bodyBPos = nodeB->getPosition();
    Size bodyASize = nodeA->getContentSize();
    Size bodyBSize = nodeB->getContentSize();
    int position = BOTTOM_DETECTED;
    
    //Always As player as main Object
    if( collisionPos.x >= bodyAPos.x ){
        position = RIGHT_DETECTED;
    }else if (collisionPos.x <= bodyAPos.x){
        position = LEFT_DETECTED;
    }
    
    //Verify if top Collide  TODO: Improve Detection
    if (collisionPos.y >= (bodyAPos.y-1) && collisionPos.y <= (bodyAPos.y+1+bodyASize.height*.4)) {
        position = TOP_DETECTED;
    }
    
    return position;
}

void GameScene::solveCollisionFor(Node *player,Node *object,int side) {
    if (this->isPaused)return;
    if (side == TOP_DETECTED){
        switch (object->getTag()) {
            case BLOCK_ITEM_MASK: //Bloque
                CCLOG("Chocaste con algo ups"); //perdera salud y a ver si una vida y puntos
                this->player->calculateDamage(0.08);
                break;
            case STGCL_ITEM_MASK: //Stage Clear Box
                CCLOG("GANASTE"); //Siguiente Nivel
                //this->isPaused = true;
                this->player->calculateScore(150);
                this->displayView(DDLayerType::_WinLayer);
                break;
            case BONUS_ITEM_MASK: //Bonus item: TODO
                break;
            case COIN_ITEM_MASK: //Coin item: TODO
                break;
            case POWUP_ITEM_MASK: //PowerUp item: TODO
                break;
        }
    }
}
