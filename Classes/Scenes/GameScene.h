//
//  GameScene.h
//  3TGame
//
//  Created by Eduardo Pérez on 11/10/18.
//

#ifndef GameScene_h
#define GameScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "ReactiveProtocols.h"
#include "GameObject.h"
#include "ParallaxLayer.h"
#include "Player.h"
#include "Constants.h"
#include "DynDLayer.h"
#include "GameHUD.h"

USING_NS_CC;

class GameScene: public Scene,public GameHUDClickProtocol,public DyDClickProtocol{
private:
    Player *player;
    GameObject *boardObject;
    GameHUD *hud;
    bool isGameOver;
    bool isPaused;
    bool isOnRespawnTask;
    int level;
    
    //Functions
    int getCollisionSide(Vec2 collisionPos,Node *nodeA,Node *nodeB);
    void update(float dt);
    void buildLevel(bool respawn);
    void moveSpritesBlock(float dt);
    void cleanLevelElements(bool respawn);
    void solveCollisionFor(Node *player,Node *object,int side);
    void displayView(DDLayerType type);
public:
    static Scene *createScene();
    virtual bool init();
    bool createGameScene();
    
    virtual void onAcceleration(Acceleration *acc, Event *event);
    virtual void onHUDItemClickedCallback(Ref *pSender);
    virtual void onDyItemClickedCallback(Ref *pSender);
    virtual bool onContactBegin(PhysicsContact& contact);
    
    CREATE_FUNC(GameScene);
};

#endif /* GameScene_h */
